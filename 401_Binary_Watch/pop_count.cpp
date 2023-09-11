#include <string>
#include <vector>

class Solution {
   public:
    std::vector<std::string> readBinaryWatch(int turnedOn) {
        std::vector<std::string> ans;
        for (int h = 0; h < 12; ++h) {
            for (int m = 0; m < 60; ++m) {
                if (PopCount(h) + PopCount(m) == turnedOn) {
                    ans.push_back(PrintTime(h, m));
                }
            }
        }
        return ans;
    }

   private:
    int PopCount(int n) {
        return n == 0 ? 0 : (n & 1ul) + PopCount(n >> 1ul);
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