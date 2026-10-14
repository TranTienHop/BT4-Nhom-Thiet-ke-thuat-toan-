#include <iostream>
using namespace std;

const int INF = 1000000;

int main() {
    int n = 5;  
    int m = 7;  

    int u[7] = {1, 1, 2, 3, 3, 4, 2};
    int v[7] = {2, 3, 4, 2, 4, 5, 5};
    int w[7] = {4, 2, 3, -1, 5, 2, 7};
    // A->B=4, A->C=2, B->D=3, C->B=-1, C->D=5, D->E=2, B->E=7

    int src = 1;  

    int d[6];       
    int truoc[6]; 

    for (int i = 1; i <= n; i++) {
        d[i] = INF;
        truoc[i] = 0;
    }
    d[src] = 0;

    for (int k = 1; k <= n - 1; k++) {
        for (int i = 0; i < m; i++) {
            if (d[u[i]] != INF && d[u[i]] + w[i] < d[v[i]]) {
                d[v[i]] = d[u[i]] + w[i];
                truoc[v[i]] = u[i];
            }
        }
    }

    int coChuTrinhAm = 0;
    for (int i = 0; i < m; i++) {
        if (d[u[i]] != INF && d[u[i]] + w[i] < d[v[i]]) {
            coChuTrinhAm = 1;
            break;
        }
    }

    char ten[6] = {' ', 'A', 'B', 'C', 'D', 'E'};

    if (coChuTrinhAm) {
        cout << "Do thi co chu trinh am!\n";
    } else {
        cout << "=== KHOANG CACH NGAN NHAT TU " << ten[src] << " ===\n";
        for (int i = 1; i <= n; i++) {
            cout << ten[src] << " -> " << ten[i] << ": ";
            if (d[i] == INF) {
                cout << "Khong co duong di\n";
            } else {
                cout << d[i] << " gio | Duong di: ";

                int path[10], cnt = 0, cur = i;
                while (cur != 0) {
                    path[cnt++] = cur;
                    cur = truoc[cur];
                }
                for (int j = cnt - 1; j >= 0; j--) {
                    cout << ten[path[j]];
                    if (j > 0) cout << " -> ";
                }
                cout << "\n";
            }
        }
    }

    return 0;
}
