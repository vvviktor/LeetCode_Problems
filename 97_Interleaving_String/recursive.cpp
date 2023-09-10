#include <string>
#include <string_view>
#include <vector>

class Solution {
   public:
    bool isInterleave(std::string s1, std::string s2, std::string s3) {
        s1_ = s1;
        s2_ = s2;
        s3_ = s3;
        size_t n = s1_.size();
        size_t m = s2_.size();
        if (n + m != s3_.size()) {
            return false;
        }
        dp_ = std::vector<std::vector<int>>(
            s1_.size() + 1, std::vector<int>(s2_.size() + 1, -1));
        dp_[0][0] = 1;
        for (size_t i = 1; i < m + 1; ++i) {
            if (dp_[0][i - 1] == 1 && s2_[i - 1] == s3_[i - 1]) {
                dp_[0][i] = 1;
            } else {
                dp_[0][i] = 0;
            }
        }
        for (size_t i = 1; i < n + 1; ++i) {
            if (dp_[i - 1][0] == 1 && s1_[i - 1] == s3_[i - 1]) {
                dp_[i][0] = 1;
            } else {
                dp_[i][0] = 0;
            }
        }
        return IsInterleaved(s1_.size(), s2_.size());
    }

   private:
    std::string_view s1_;
    std::string_view s2_;
    std::string_view s3_;
    std::vector<std::vector<int>> dp_;

    bool IsInterleaved(int idx1, int idx2) {
        if (dp_[idx1][idx2] != -1) {
            return dp_[idx1][idx2];
        }
        return dp_[idx1][idx2] = (IsInterleaved(idx1 - 1, idx2) &&
                                  s3_[idx1 + idx2 - 1] == s1_[idx1 - 1]) ||
                                 (IsInterleaved(idx1, idx2 - 1) &&
                                  s3_[idx1 + idx2 - 1] == s2_[idx2 - 1]);
    }
};