#include <algorithm>
#include <limits>
#include <vector>

class Solution {
   public:
    int lengthOfLIS(std::vector<int>& nums) {
        std::vector<int> dp(nums.size() + 1,
                            std::numeric_limits<int>::max());
        dp[0] = std::numeric_limits<int>::min();
        size_t length = 1;
        for (size_t i = 0; i < nums.size(); ++i) {
            size_t j = std::upper_bound(dp.begin(), dp.end(), nums[i]) -
                       dp.begin();
            if (dp[j - 1] < nums[i]) {
                dp[j] = nums[i];
                length = std::max(length, j);
            }
        }
        return length;
    }
};