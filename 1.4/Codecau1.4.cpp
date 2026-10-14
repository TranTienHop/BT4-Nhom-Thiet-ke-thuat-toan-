#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

const int INF = 1e9;


const vector<string> NODES = {"A", "B", "C", "D", "N"};
const int V = 5;


int getNodeIndex(const string& name) {
    for (int i = 0; i < V; ++i) {
        if (NODES[i] == name) return i;
    }
    return -1;
}


string formatCell(int d, int p, bool isFixed) {
    string content = "";
    if (d >= INF) {
        content = "inf";
    } else {
        string prevName = (p == -1) ? "-" : NODES[p];
        content = to_string(d) + "," + prevName;
    }
    if (isFixed) return "[" + content + "]";
    return "(" + content + ")";
}

int main() {
   
    vector<vector<int>> adj(V, vector<int>(V, INF));
    for (int i = 0; i < V; ++i) adj[i][i] = 0;

    
    auto addEdge = [&](string u, string v, int w) {
        adj[getNodeIndex(u)][getNodeIndex(v)] = w;
    };

    addEdge("A", "B", 3);
    addEdge("A", "C", 7);
    addEdge("B", "D", 2);
    addEdge("B", "N", 8);
    addEdge("C", "D", 1);
    addEdge("D", "N", 4);
    addEdge("N", "A", 1);

    
    vector<int> d(V, INF);
    vector<int> p(V, -1);
    vector<bool> visited(V, false);

    
    int startNode = getNodeIndex("A");
    d[startNode] = 0;

    cout << "=== BANG THEO DOI CAC BUOC THUAT TOAN DIJKSTRA ===" << endl;
    cout << left << setw(8) << "Buoc" << setw(10) << "Chot (u)";
    for (const string& node : NODES) {
        cout << setw(12) << ("Dinh " + node);
    }
    cout << "\n" << string(68, '-') << endl;

    
    cout << left << setw(8) << "0 (KT)" << setw(10) << "-";
    for (int i = 0; i < V; ++i) {
        cout << setw(12) << formatCell(d[i], p[i], false);
    }
    cout << endl;

    
    for (int step = 1; step <= V; ++step) {
        int u = -1;
        int min_d = INF;

       
        for (int i = 0; i < V; ++i) {
            if (!visited[i] && d[i] < min_d) {
                min_d = d[i];
                u = i;
            }
        }

        if (u == -1) break;
        visited[u] = true;  

        
        for (int v = 0; v < V; ++v) {
            if (!visited[v] && adj[u][v] < INF) {
                if (d[u] + adj[u][v] < d[v]) {
                    d[v] = d[u] + adj[u][v];
                    p[v] = u;
                }
            }
        }

        cout << left << setw(8) << step << setw(10) << NODES[u];
        for (int i = 0; i < V; ++i) {
            cout << setw(12) << formatCell(d[i], p[i], visited[i]);
        }
        cout << endl;
    }

    cout << string(68, '-') << endl;
    cout << "\n=== KET QUA DUONG DI NGAN NHAT TU A ===" << endl;
    for (int i = 0; i < V; ++i) {
        if (i == startNode) continue;
        cout << "Tu A den " << NODES[i] << " (Do dai: " << d[i] << "): ";
        vector<string> path;
        int curr = i;
        while (curr != -1) {
            path.push_back(NODES[curr]);
            curr = p[curr];
        }
        reverse(path.begin(), path.end());
        for (size_t j = 0; j < path.size(); ++j) {
            cout << path[j] << (j + 1 < path.size() ? " -> " : "");
        }
        cout << endl;
    }

    return 0;
}
