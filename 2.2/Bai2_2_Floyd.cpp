
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

const int INF = 1000000000;
const int MAX_KHO = 10;

int n;
vector<vector<int>> d;
vector<vector<int>> ke;

// Ma tran trong so cua nhom (km), -1 la khong co duong di truc tiep
int maTranNhom[4][4] = {
    { 0,  4, 11, -1},
    { 6,  0,  2, 15},
    { 3, -1,  0,  5},
    {-1,  1, -1,  0}
};

string tenKho(int i) {
    return "K" + to_string(i + 1);
}

void inMaTran(const string& tieuDe, const vector<vector<bool>>& thayDoi) {
    cout << "\n" << tieuDe << "\n";
    cout << setw(6) << " ";
    for (int j = 0; j < n; j++)
        cout << setw(6) << tenKho(j);
    cout << "\n";

    for (int i = 0; i < n; i++) {
        cout << setw(6) << tenKho(i);
        for (int j = 0; j < n; j++) {
            string o = (d[i][j] >= INF) ? "INF" : to_string(d[i][j]);
            if (thayDoi[i][j])
                o += "*";
            cout << setw(6) << o;
        }
        cout << "\n";
    }
}

void floyd() {
    vector<vector<bool>> thayDoi(n, vector<bool>(n, false));
    inMaTran("D(0) - Ma tran trong so ban dau:", thayDoi);

    for (int k = 0; k < n; k++) {
        thayDoi.assign(n, vector<bool>(n, false));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (d[i][k] >= INF || d[k][j] >= INF)
                    continue;

                if (d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    ke[i][j] = ke[i][k];
                    thayDoi[i][j] = true;
                }
            }
        }

        inMaTran("D(" + to_string(k + 1) + ") - Cho phep di qua " + tenKho(k)
                 + " (* la o vua duoc cap nhat):", thayDoi);
    }
}

string loTrinh(int u, int v) {
    if (d[u][v] >= INF)
        return "khong co duong di";

    string s = tenKho(u);
    while (u != v) {
        u = ke[u][v];
        s += " -> " + tenKho(u);
    }
    return s;
}

bool nhapMaTran() {
    cout << "Nhap so kho hang n (1 - " << MAX_KHO << "): ";
    if (!(cin >> n) || n < 1 || n > MAX_KHO) {
        cout << "So kho hang khong hop le!\n";
        return false;
    }

    d.assign(n, vector<int>(n));
    cout << "Nhap ma tran trong so " << n << " x " << n
         << " (-1 neu khong co duong di truc tiep):\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!(cin >> d[i][j]) || d[i][j] < -1) {
                cout << "Trong so khong hop le!\n";
                return false;
            }
        }
    }
    return true;
}

int main() {
    int chon;
    cout << "1. Dung ma tran cua nhom (4 kho K1 - K4)\n";
    cout << "2. Nhap ma tran moi\n";
    cout << "Chon: ";
    if (!(cin >> chon) || (chon != 1 && chon != 2)) {
        cout << "Lua chon khong hop le!\n";
        return 0;
    }

    if (chon == 1) {
        n = 4;
        d.assign(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                d[i][j] = maTranNhom[i][j];
    } else if (!nhapMaTran()) {
        return 0;
    }

    ke.assign(n, vector<int>(n, -1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                d[i][j] = 0;
            else if (d[i][j] == -1)
                d[i][j] = INF;

            if (d[i][j] < INF)
                ke[i][j] = j;
        }
    }

    floyd();

    cout << "\nLo trinh ngan nhat giua moi cap kho hang:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                continue;
            cout << tenKho(i) << " -> " << tenKho(j) << ": ";
            if (d[i][j] >= INF)
                cout << "khong co duong di\n";
            else
                cout << d[i][j] << " km  (" << loTrinh(i, j) << ")\n";
        }
    }

    if (n >= 4) {
        cout << "\nKET LUAN: Quang duong ngan nhat tu K2 den K4 = ";
        if (d[1][3] >= INF)
            cout << "khong co duong di\n";
        else
            cout << d[1][3] << " km, lo trinh " << loTrinh(1, 3) << "\n";
    }

    return 0;
}
