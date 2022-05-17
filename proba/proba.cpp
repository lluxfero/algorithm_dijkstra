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

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n;
    /*cout << "Введите количество вершин дерева: ";
    n = err_n();

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
    cout << endl;*/

    n = 5;
    int adj_matrix[5][5] = { {0, 10, 30, 50, 10},
                             {0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 10},
                             {0, 40, 20, 0, 0},
                             {10, 0, 10, 30, 0} };

    /*int adj_matrix[5][5] = {{0, 10, 30, 0, 10},
                             {0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 10},
                             {0, 40, 20, 0, 0},
                             {10, 0, 10, 0, 0} };*/
    int s;
    cout << "Введите начальную вершину: ";
    s = err_v(n);
    s--;

    int* dist_matrix = new int[n];
    for (int i = 0; i < n; i++)
        dist_matrix[i] = 30000;
    dist_matrix[s] = 0; //в начальную вершину мы можем попасть за нулевое расстояние

    priority_queue <pair <int, int> > priority_q; //приоритетная очередь из пары чисел (длина, вершина), автоматически упорядоченные по расстояниям
    priority_q.push(make_pair(0, s)); //добавляем первую пару

    int len_pr_q, v, vto, length;
    while (!priority_q.empty()) {
        len_pr_q = -priority_q.top().first; //сортируем отрицательные числа, т.к. элементы в п.о. располагаются по убыванию
        v = priority_q.top().second;
        cout << "рас: " << len_pr_q << ", верш: " << priority_q.top().second + 1 << ", хран.рас: " << dist_matrix[v] << endl;
        priority_q.pop(); //достаем из очереди первый элемент

        if (len_pr_q <= dist_matrix[v]) //если длина не больше хранящегося расстояния для вершины
            for (int i = 0; i < n; i++) { //перебираем все вершины, в которые мы можем попасть из данной
                vto = i;
                length = adj_matrix[v][i];
                cout << "\tкуда идем: " << vto + 1 << ", расс. м.смеж: " << length << endl;
                if ((dist_matrix[vto] > dist_matrix[v] + length) && (length > 0)) {
                    dist_matrix[vto] = dist_matrix[v] + length;
                    cout << "\t\tсработал if, новое знач. расстояния: " << dist_matrix[vto] << endl;
                    priority_q.push(make_pair(-dist_matrix[vto], vto));
                }
            }
    }

    bool check_m = true;
    for (int i = 0; i < n; i++) {
        if (dist_matrix[i] == 30000) check_m = false;
        break;
    }
    if (check_m == false) cout << "Ошибка! Даннный орграф невозможно исследовать с помощью алгоритма Дейкстры";
    else {
        cout << "Кратчайшие пути от начальной вершины до всех остальных вершин орграфа: " << endl;
        for (int i = 0; i < n; i++)
            if (i != s) cout << i + 1 << "\t" << dist_matrix[i] << endl;
    }
}