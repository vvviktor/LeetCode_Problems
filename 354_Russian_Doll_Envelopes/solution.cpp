#include <algorithm>
#include <limits>
#include <vector>

class Solution {
   public:
    int maxEnvelopes(std::vector<std::vector<int>>& envelopes) {
        auto comp = [](const std::vector<int>& lhs,
                       const std::vector<int>& rhs) -> bool {
            return lhs[0] == rhs[0] ? lhs[1] > rhs[1] : lhs[0] < rhs[0];
        };
        std::sort(envelopes.begin(), envelopes.end(), comp);
        return FindHeightLIS(envelopes);
    }

   private:
    int FindHeightLIS(const std::vector<std::vector<int>>& envelopes) {
        std::vector<int> dp(envelopes.size() + 1,
                            std::numeric_limits<int>::max());
        dp[0] = std::numeric_limits<int>::min();
        size_t length = 1;
        for (size_t i = 0; i < envelopes.size(); ++i) {
            size_t j =
                std::upper_bound(dp.begin(), dp.end(), envelopes[i][1]) -
                dp.begin();
            if (dp[j - 1] < envelopes[i][1]) {
                dp[j] = envelopes[i][1];
                length = std::max(length, j);
            }
        }
        return length;
    }
};