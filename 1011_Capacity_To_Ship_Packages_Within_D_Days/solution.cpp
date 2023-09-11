#include <algorithm>
#include <vector>

class Solution {
   public:
    int shipWithinDays(std::vector<int>& weights, int days) {
        int min = 0;
        int max = 0;
        for (const int weight : weights) {
            min = std::max(min, weight);
            max += weight;
        }
        while (min < max) {
            int mid = min + ((max - min) >> 1);
            if (Check(weights, mid, days)) {
                max = mid;
            } else {
                min = mid + 1;
            }
        }
        return min;
    }

   private:
    bool Check(const std::vector<int>& weights, int max_weight, int days) {
        int sum = 0;
        size_t pos = 0;
        while (pos < weights.size()) {
            if (sum + weights[pos] <= max_weight) {
                sum += weights[pos];
            } else {
                sum = weights[pos];
                --days;
            }
            ++pos;
        }
        return days > 0;
    }
};