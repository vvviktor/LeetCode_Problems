#include <string>
#include <vector>

class Solution {
   public:
    std::vector<std::string> readBinaryWatch(int turnedOn) {
        std::vector<std::string> ans;
        PrintCombs(ans, 0, 0, turnedOn);
        return ans;
    }

   private:
    static constexpr int TOTAL_LIGHTS_ = 10;

    void PrintCombs(std::vector<std::string>& ans, int num, int pos,
                    int cnt) {
        if (cnt == 0) {
            auto [h, m] = Convert(num);
            if (h < 12 && m < 60) {
                ans.push_back(PrintTime(h, m));
            }
            return;
        }
        for (int i = pos; i < TOTAL_LIGHTS_; ++i) {
            PrintCombs(ans, num | (1ul << i), i + 1, cnt - 1);
        }
    }

    std::pair<int, int> Convert(int num) {
        return {num >> 6ul, num & ((1ul << 6ul) - 1)};
    }

    std::string PrintTime(int h, int m) {
        return (h < 10 ? std::string(1, h + '0')
                       : std::string(1, h / 10 + '0') +
                             std::string(1, h % 10 + '0')) +
               ":" +
               (m < 10 ? "0" + std::string(1, m + '0')
                       : std::string(1, m / 10 + '0') +
                             std::string(1, m % 10 + '0'));
    }
};