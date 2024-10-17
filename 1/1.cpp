#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Graph {
private:
    unordered_map<int, unordered_set<int> *> data;

    bool hasHamiltonianCycleHelper(int currentNode, vector<int> &path, unordered_set<int> &visited) {
        if (visited.size() == data.size()) {
            int firstNode = path.front();
            if (data[currentNode]->find(firstNode) != data[currentNode]->end()) {
                return true;
            }
            return false;
        }
        for (int neighbor : *(data[currentNode])) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                path.push_back(neighbor);

                if (hasHamiltonianCycleHelper(neighbor, path, visited)) {
                    return true;
                }

                path.pop_back();
                visited.erase(neighbor);
            }
        }

        return false;
    }

public:

    ~Graph() {
        for (const auto &pair: data) {
            delete pair.second;
        }
    }

    void addEdge(int start, int end) {
        if (data.find(start) == data.end()) {
            data[start] = new unordered_set<int>;
        }
        if (data.find(end) == data.end()) {
            data[end] = new unordered_set<int>;
        }
        data[start]->insert(end);
    }

    void printGraph() {
        for (const auto &pair: data) {
            cout << pair.first << ": -> [ ";
            for (const auto &element: *pair.second) {
                cout << element << " ";
            }
            cout << "]\n";
        }
        cout << endl;
    }

    bool hasHamiltonianCycle() {
        if (data.empty()) return false;

        vector<int> path;
        unordered_set<int> visited;

        int startNode = data.begin()->first;
        path.push_back(startNode);
        visited.insert(startNode);

        return hasHamiltonianCycleHelper(startNode, path, visited);
    }

};

int main() {
    auto *g = new Graph;
    int n, start, end;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> start >> end;
        g->addEdge(start, end);
    }
    cout << "Given graph:\n";
    g->printGraph();
    cout << "Has Hamiltonian Cycle: ";
    cout << (g->hasHamiltonianCycle() ? "True" : "False") << endl;
    delete g;
    return 0;
}
