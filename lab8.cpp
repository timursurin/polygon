#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <cmath>
#include <limits>
#include <ctime>
#include <algorithm>
#include <chrono>
using namespace std;

// Структура узла. Память: sizeof(Node) ≈ 32 байта (зависит от реализации string и vector)
struct Node {
    string lon, lat;  //~16 байт каждый (в среднем)
    vector<pair<Node*, double>> neighbors;  // Список соседей. ~24 байта (пустой вектор)
};

template <typename T, typename... Args>
double measureTime(T func, Args&&... args) {
    auto start = chrono::high_resolution_clock::now();
    func(forward<Args>(args)...);  // Execute the function
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    return duration.count();
}

// Структура графа
struct Graph {
    vector<Node*> nodes; // Память: O(N), где N - количество узлов
    unordered_map<string, Node*> nodeMap;  // Хранит узлы по ключу "долгота,широта" Хеш-таблица для быстрого доступа к узлам. ~ N * (размер ключа + sizeof(Node*))

    explicit Graph(const string& filename) {
        loadGraphFromFile(filename);
    }

    // Загрузка графа из файла. Сложность: O(E), где E - количество ребер. Память: O(N+E)
    void loadGraphFromFile(const string& filename) {
        ifstream file(filename); // O(1)
        if (!file.is_open()) {
            cerr << "Ошибка открытия файла: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;

            // Парсинг родительского узла
            getline(ss, token, ':');
            string parentKey = token;  // Ключ - исходная строка координат
            Node* parentNode;

            if (nodeMap.find(parentKey) == nodeMap.end()) {
                stringstream parentCoordSS(token);
                getline(parentCoordSS, token, ',');
                string parentLon = token;
                getline(parentCoordSS, token, ',');
                string parentLat = token;

                parentNode = new Node{parentLon, parentLat};
                nodes.push_back(parentNode);
                nodeMap[parentKey] = parentNode;
            } else {
                parentNode = nodeMap[parentKey];
            }

            // Парсинг дочерних узлов и ребер
            while (getline(ss, token, ';')) {
                stringstream childSS(token);

                getline(childSS, token, ',');
                string childLon = token;
                getline(childSS, token, ',');
                string childLat = token;
                string childKey = childLon + "," + childLat; // Ключ - строка координат

                // Убираем пробелы из строки
                childLon.erase(remove(childLon.begin(), childLon.end(), ' '), childLon.end());
                childLat.erase(remove(childLat.begin(), childLat.end(), ' '), childLat.end());

                // Выводим значения для отладки
                cout << "Parsing lon, lat: " << childLon << ", " << childLat << endl;

                getline(childSS, token, ','); // Теперь токен это weight
                // Выводим значение для отладки
                cout << "Parsing weight: " << token << endl;

                if (token.empty()) {
                    cerr << "Empty string encountered before stod!" << endl;
                    exit(EXIT_FAILURE); // Завершаем программу при ошибке
                }
                double weight = 0.0;
                try {
                    weight = stod(token);
                    // Если удачно, продолжаем
                } catch (const std::invalid_argument& e) {
                    cerr << "Invalid argument for stod: '" << token << "' - could not convert to double" << endl;
                    exit(EXIT_FAILURE); // Завершаем программу при ошибке
                } catch (const std::out_of_range& e) {
                    cerr << "Out of range error for stod: '" << token << "'" << endl;
                    exit(EXIT_FAILURE); // Завершаем программу при ошибке
                }

                Node* childNode;
                if (nodeMap.find(childKey) == nodeMap.end()) {
                    childNode = new Node{childLon, childLat};
                    nodes.push_back(childNode);
                    nodeMap[childKey] = childNode;
                } else {
                    childNode = nodeMap[childKey];
                }




                parentNode->neighbors.push_back({childNode, weight});
            }
        }
        file.close();
    }

    // Поиск ближайшего узла к заданным координатам. Сложность: O(N). Память: O(1)
    Node* findClosestNode(double lat, double lon) const {
        Node* closestNode = nullptr;
        double minDistance = numeric_limits<double>::infinity();

        for (auto* node : nodes) {

            double nodeLat = stod(node->lat);
            double nodeLon = stod(node->lon);
            double distance = sqrt(pow(lat - nodeLat, 2) + pow(lon - nodeLon, 2));

            if (distance < minDistance) {
                minDistance = distance;
                closestNode = node;
            }
        }
        return closestNode;
    }

private:
    // Создание или получение узла. Сложность: O(1) в среднем. Память: O(1)
    Node* createOrGetNode(const string& key) {
        if (nodeMap.find(key) == nodeMap.end()) {
            stringstream ss(key);
            string lon, lat;

            getline(ss, lon, ',');
            getline(ss, lat, ',');

            Node* newNode = new Node{lon, lat};
            nodes.push_back(newNode);
            nodeMap[key] = newNode;
        }
        return nodeMap[key];
    }
};

// Алгоритм Дейкстры. Сложность: O(E log V), V - количество вершин. Память: O(V)
unordered_map<Node*, double> dijkstra(const vector<Node*>& nodes, Node* startNode) {
    unordered_map<Node*, double> distances;
    priority_queue<pair<double, Node*>, vector<pair<double, Node*>>, greater<>> pq;

    for (auto* node : nodes) {
        distances[node] = numeric_limits<double>::infinity();
    }
    distances[startNode] = 0.0;
    pq.push({0.0, startNode});

    while (!pq.empty()) {
        double currentDist = pq.top().first;
        Node* currentNode = pq.top().second;
        pq.pop();

        if (currentDist > distances[currentNode]) continue;

        for (const auto& [neighbor, weight] : currentNode->neighbors) {
            double newDist = currentDist + weight;
            if (newDist < distances[neighbor]) {
                distances[neighbor] = newDist;
                pq.push({newDist, neighbor});
            }
        }
    }
    return distances;
}

// Эвристика для A*. Сложность: O(1). Память: O(1)
double heuristic(Node* a, Node* b) {
    double lat1 = stod(a->lat), lon1 = stod(a->lon);
    double lat2 = stod(b->lat), lon2 = stod(b->lon);
    return sqrt(pow(lat1 - lat2, 2) + pow(lon1 - lon2, 2));
}

// Алгоритм A*.  Сложность: O(E log V) в худшем случае. Память: O(V)
unordered_map<Node*, double> aStar(const vector<Node*>& nodes, Node* startNode, Node* endNode) {
    unordered_map<Node*, double> distances, fScore;
    priority_queue<pair<double, Node*>, vector<pair<double, Node*>>, greater<>> pq;

    for (auto* node : nodes) {
        distances[node] = numeric_limits<double>::infinity();
        fScore[node] = numeric_limits<double>::infinity();
    }
    distances[startNode] = 0.0;
    fScore[startNode] = heuristic(startNode, endNode);
    pq.push({fScore[startNode], startNode});

    while (!pq.empty()) {
        Node* current = pq.top().second;
        pq.pop();

        if (current == endNode) break;

        for (const auto& [neighbor, weight] : current->neighbors) {
            double tentativeGScore = distances[current] + weight;
            if (tentativeGScore < distances[neighbor]) {
                distances[neighbor] = tentativeGScore;
                fScore[neighbor] = tentativeGScore + heuristic(neighbor, endNode);
                pq.push({fScore[neighbor], neighbor});
            }
        }
    }
    return distances;
}

// BFS. Сложность: O(V+E). Память: O(V)
double bfs(const vector<Node*>& nodes, Node* startNode, Node* endNode) {
    queue<pair<Node*, double>> q;
    unordered_set<Node*> visited;

    q.push({startNode, 0.0});
    visited.insert(startNode);

    while (!q.empty()) {
        Node* current = q.front().first;
        double currentDist = q.front().second;
        q.pop();

        if (current == endNode) return currentDist;
        for (const auto& [neighbor, weight] : current->neighbors) {
            if (visited.insert(neighbor).second) {
                q.push({neighbor, currentDist + weight});
            }
        }
    }
    return -1.0;
}

// DFS. Сложность: O(V+E). Память: O(V) в худшем случае (линейный граф).
double dfs(Node* startNode, Node* endNode, unordered_set<Node*>& visited) {
    if (startNode == endNode) return 0.0;

    visited.insert(startNode);

    for (const auto& [neighbor, weight] : startNode->neighbors) {
        if (visited.find(neighbor) == visited.end()) {
            double result = dfs(neighbor, endNode, visited);
            if (result != -1.0) return result + weight;
        }
    }
    return -1.0;
}

// Точка входа
int main() {
    Graph graph("spb_graph.txt");

    double myLat = 59.9532059, myLon = 30.2155522;
    double finLat = 59.937360, finLon = 30.385667;
    Node* startNode = graph.findClosestNode(myLat, myLon);
    Node* endNode = graph.findClosestNode(finLat, finLon);

    if (!startNode || !endNode) {
        cerr << "Ошибка: начальная или конечная вершина не найдена." << endl;
        return 1;
    }

    unordered_set<Node*> visited;

    // cout << "DFS Distance: " << dfs(startNode, endNode, visited) << endl;
    // double dfsTime = measureTime(dfs, startNode, endNode, ref(visited)); // Pass visited by reference
    // cout << "DFS Time: " << dfsTime << " seconds" << endl;

    double bfsTime = measureTime(bfs, graph.nodes, startNode, endNode);
    cout << "BFS Distance: " << bfs(graph.nodes, startNode, endNode) << endl;
    cout << "BFS Time: " << bfsTime << " seconds" << endl;

    double dijkstraTime = measureTime(dijkstra, graph.nodes, startNode);
    auto distancesDijkstra = dijkstra(graph.nodes, startNode);
    cout << endl << "Dijkstra Distance: " << distancesDijkstra[endNode] << endl;
    cout << "Dijkstra Time: " << dijkstraTime << " seconds" << endl;

    double aStarTime = measureTime(aStar, graph.nodes, startNode, endNode);
    auto distancesAStar = aStar(graph.nodes, startNode, endNode);
    cout << endl << "A* Distance: " << distancesAStar[endNode] << endl;
    cout << "A* Time: " << aStarTime << " seconds" << endl;


    return 0;
}