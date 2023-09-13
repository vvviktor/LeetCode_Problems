#include <cstdlib>
#include <queue>
#include <vector>

class Solution {
   public:
    int minTaps(int n, std::vector<int>& ranges) {
        auto comp = [](const std::pair<int, int>& lhs,
                       const std::pair<int, int>& rhs) -> bool {
            return lhs.first > rhs.first;
        };
        std::priority_queue<std::pair<int, int>,
                            std::vector<std::pair<int, int>>,
                            decltype(comp)>
            q(comp);
        for (int i = 0; i < n + 1; ++i) {
            q.push({i - ranges[i], i + ranges[i]});
        }
        int cnt = 1;
        int curr_end = 0;
        int next_end = 0;
        while (!q.empty()) {
            std::pair<int, int> interval = q.top();
            q.pop();
            if (interval.first > next_end) {
                return -1;
            }
            if (interval.first > curr_end) {
                ++cnt;
                curr_end = next_end;
            }
            next_end = std::max(next_end, interval.second);
            if (next_end >= n) {
                break;
            }
        }
        return cnt;
    }
};