#include <algorithm>
#include <queue>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class Solution {
   public:
    std::vector<std::string> findItinerary(
        std::vector<std::vector<std::string>>& tickets) {
        std::vector<std::string> ans;
        std::unordered_map<
            std::string_view,
            std::priority_queue<std::string_view,
                                std::vector<std::string_view>,
                                std::greater<std::string_view>>>
            edges;
        for (const auto& ticket : tickets) {
            edges[ticket[0]].push(ticket[1]);
        }
        std::stack<std::string_view> planned;
        planned.push("JFK");
        while (!planned.empty()) {
            std::string_view curr = planned.top();
            if (!edges[curr].empty()) {
                planned.push(edges[curr].top());
                edges[curr].pop();
            } else {
                ans.push_back(std::string(curr));
                planned.pop();
            }
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};