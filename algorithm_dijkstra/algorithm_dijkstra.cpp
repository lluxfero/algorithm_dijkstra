 #include <iostream>
#include <Windows.h>
#include <clocale>
#include <vector>
#include <queue>
using namespace std;

int err_n() {
    int m, ival = 1;
    cin >> m;
    while (ival == 1) {
        if (cin.fail() || m < 1) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Ошибка! Попробуйте еще раз: ";
            cin >> m;
        }
        else
            ival = 0;
    }
    return m;
}

int err_d() {
    int m, ival = 1;
    cin >> m;
    while (ival == 1) {
        if (cin.fail() || m < 0) {

            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Ошибка! Попробуйте еще раз: ";
            cin >> m;
        }
        else
            ival = 0;
    }
    return m;
}

int err_v(int n) {
    int m, ival = 1;
    cin >> m;
    while (ival == 1) {
        if (cin.fail() || m < 1 || m > n) {

            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Ошибка! Попробуйте еще раз: ";
            cin >> m;
        }
        else
            ival = 0;
    }
    return m;
}

void dijkstra(int** adj_matrix, int* dist_matrix, int n, int s) {
    priority_queue <pair <int, int> > priority_q; 
    priority_q.push(make_pair(0, s)); 

    int len_pr_q, v, vto, length;
    while (!priority_q.empty()) {
        len_pr_q = -priority_q.top().first; 
        v = priority_q.top().second;
        priority_q.pop(); 

        if (len_pr_q <= dist_matrix[v]) 
            for (int i = 0; i < n; i++) { 
                vto = i;
                length = adj_matrix[v][i];
                if ((dist_matrix[vto] > dist_matrix[v] + length) && (length > 0)) {
                    dist_matrix[vto] = dist_matrix[v] + length;
                    priority_q.push(make_pair(-dist_matrix[vto], vto));
                }
            }
    }
}

void result(int* dist_matrix, int n, int s) {
    bool check_m = true;
    for (int i = 0; i < n; i++) {
        if (dist_matrix[i] == 30000) check_m = false;
        break;
    }
    if (check_m == false) cout << "Ошибка! Данный орграф невозможно исследовать с помощью алгоритма Дейкстры";
    else {
        cout << "Кратчайшие пути от начальной вершины до всех остальных вершин орграфа: " << endl;
        for (int i = 0; i < n; i++)
            if (i != s) cout << i + 1 << "\t" << dist_matrix[i] << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Введите количество вершин орграфа: ";
    int n = err_n();

    int** adj_matrix = new int* [n];
    for (int i = 0; i < n; i++)
        adj_matrix[i] = new int[n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj_matrix[i][j] = 0;

    cout << "Введите матрицу смежности орграфа с весами ребер: " << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj_matrix[i][j] = err_d();
    cout << endl;

    cout << "Введите начальную вершину: ";
    int s = err_v(n); 
    s--;

    int* dist_matrix = new int [n];
    for (int i = 0; i < n; i++)
        dist_matrix[i] = 30000;
    dist_matrix[s] = 0;

    dijkstra(adj_matrix, dist_matrix, n, s);
    result(dist_matrix, n, s);
}