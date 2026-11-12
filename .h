#pragma once
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <limits>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class RoadGraph {
public:
    static constexpr int N = 25;

    struct Edge {
        int a, b, length;
    };

    // Матрица смежности.
    // 0 — ребра нет, положительное число — длина дороги.
    int adjacency[N][N]{};
    double traffic[N][N]{};

    const std::vector<Edge>& edges() const {
        return edges_;
    }

    RoadGraph() {
        reset();
    }

    // Восстановление исходного графа.
    void reset() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                adjacency[i][j] = 0;
                traffic[i][j] = 1.0;
            }
        }

        edges_ = {
            {0,1,2},{0,13,2},{0,9,1},{1,2,2},{1,9,1},
            {2,3,2},{2,12,3},{3,4,3},{4,6,2},{4,19,4},
            {5,6,1},{6,7,2},{6,20,3},{7,8,2},{7,21,4},
            {8,10,1},{9,11,2},{9,13,1},{11,12,1},{11,14,2},
            {12,3,2},{13,16,2},{14,15,1},{14,17,2},{16,17,1},
            {16,18,1},{17,19,4},{18,22,2},{19,20,2},{20,21,1},
            {21,23,2},{23,10,3},{22,24,4}
        };

        for (const auto& e : edges_) {
            adjacency[e.a][e.b] = adjacency[e.b][e.a] = e.length;
            traffic[e.a][e.b] = traffic[e.b][e.a] = 1.0;
        }
    }

    bool hasEdge(int a, int b) const {
        return valid(a) && valid(b) && adjacency[a][b] > 0;
    }

    // Удаление ребра.
    bool removeEdge(int a, int b) {
        if (!valid(a) || !valid(b) || a == b || adjacency[a][b] == 0)
            return false;

        adjacency[a][b] = adjacency[b][a] = 0;
        traffic[a][b] = traffic[b][a] = 1.0;

        return true;
    }

    // Случайная загруженность дорог.
    void randomizeTraffic(unsigned seed = std::random_device{}()) {
        static const double factors[] = {0.8, 1.2, 1.9, 3.3};

        std::mt19937 gen(seed);
        std::uniform_int_distribution<int> pick(0, 3);

        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                if (adjacency[i][j] > 0) {
                    traffic[i][j] = traffic[j][i] = factors[pick(gen)];
                }
            }
        }
    }

    // Стоимость прохождения дороги.
    double cost(int a, int b) const {
        return adjacency[a][b] * traffic[a][b];
    }

    // Поиск кратчайшего пути алгоритмом Дейкстры.
    bool shortestPath(
        int start,
        int finish,
        std::vector<int>& path,
        double& totalCost,
        std::string& error
    ) const {

        path.clear();
        totalCost = 0.0;

        if (!valid(start) || !valid(finish)) {
            error = "Выбрана несуществующая вершина.";
            return false;
        }

        if (start == finish) {
            error = "Начальная и конечная точки совпадают. Выберите две разные точки.";
            return false;
        }

        const double INF = std::numeric_limits<double>::infinity();

        double dist[N];
        int prev[N];
        bool used[N]{};

        for (int i = 0; i < N; ++i) {
            dist[i] = INF;
            prev[i] = -1;
        }

        dist[start] = 0.0;

        for (int step = 0; step < N; ++step) {
            int v = -1;

            for (int i = 0; i < N; ++i) {
                if (!used[i] && (v == -1 || dist[i] < dist[v]))
                    v = i;
            }

            if (v == -1 || !std::isfinite(dist[v]))
                break;

            used[v] = true;

            if (v == finish)
                break;

            for (int to = 0; to < N; ++to) {
                if (adjacency[v][to] <= 0 || used[to])
                    continue;

                double candidate = dist[v] + cost(v, to);

                if (candidate < dist[to]) {
                    dist[to] = candidate;
                    prev[to] = v;
                }
            }
        }

        // Проверка существования пути.
        if (!std::isfinite(dist[finish])) {
            error = "Маршрут отсутствует: между выбранными точками нет пути.";
            return false;
        }

        // Восстановление маршрута.
        for (int v = finish; v != -1; v = prev[v])
            path.push_back(v);

        std::reverse(path.begin(), path.end());

        totalCost = dist[finish];

        return true;
    }

    static bool valid(int v) {
        return v >= 0 && v < N;
    }

    // Форматирование чисел.
    static std::string number(double x) {
        std::ostringstream out;
        out << std::fixed << std::setprecision(1) << x;

        std::string s = out.str();

        if (!s.empty() && s.back() == '0')
            s.pop_back();

        if (!s.empty() && s.back() == '.')
            s.pop_back();

        std::replace(s.begin(), s.end(), '.', ',');

        return s;
    }

private:
    std::vector<Edge> edges_;
};