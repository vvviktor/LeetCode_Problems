#include <algorithm>
#include <queue>
#include <vector>

class Solution {
    struct Edge {
        int from = 0;
        int to = 0;
        int weight = 0;
        constexpr bool operator>(const Edge& rhs) const {
            return weight > rhs.weight;
        }
    };

    class UnionFind {
       public:
        UnionFind(int n) : parent_(n), sizes_(n, 1) {
            for (int i = 0; i < n; ++i) {
                parent_[i] = i;
            }
        }

        int Find(int v) {
            return parent_[v] == v ? v : parent_[v] = Find(parent_[v]);
        }

        bool Unite(int v, int u) {
            int v_P = Find(v);
            int u_P = Find(u);
            if (v_P == u_P) {
                return false;
            }
            if (sizes_[v_P] < sizes_[u_P]) {
                std::swap(v_P, u_P);
            }
            parent_[u_P] = v_P;
            sizes_[v_P] += sizes_[u_P];
            return true;
        }

       private:
        std::vector<int> parent_;
        std::vector<int> sizes_;
    };

   public:
    int minCostConnectPoints(std::vector<std::vector<int>>& points) {
        int n = points.size();
        std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>
            edges;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int weight = std::abs(points[i][0] - points[j][0]) +
                             std::abs(points[i][1] - points[j][1]);
                edges.push({i, j, weight});
            }
        }
        int ans = 0;
        int cnt = 1;
        UnionFind union_find(n);
        while (!edges.empty()) {
            Edge curr = edges.top();
            edges.pop();
            if (union_find.Unite(curr.from, curr.to)) {
                ans += curr.weight;
                if (++cnt == n) {
                    break;
                }
            }
        }
        return ans;
    }
};