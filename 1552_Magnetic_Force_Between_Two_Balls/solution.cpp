#include <algorithm>
#include <vector>

class Solution {
   public:
    int maxDistance(std::vector<int>& position, int m) {
        std::sort(position.begin(), position.end());
        int min = 1, max = position.back() - position[0];
        while (min < max) {
            int mid = min + ((max - min + 1) >> 1);
            if (Check(position, mid, m)) {
                min = mid;
            } else {
                max = mid - 1;
            }
        }
        return min;
    }

   private:
    bool Check(const std::vector<int>& position, int force, int m) {
        int l_val = position[0];
        --m;
        for (size_t r = 1; r < position.size(); ++r) {
            int diff = position[r] - l_val;
            if (diff >= force) {
                --m;
                l_val = position[r];
            }
        }
        return m <= 0;
    }
};