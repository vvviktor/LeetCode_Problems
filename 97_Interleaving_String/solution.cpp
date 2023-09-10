#include <cstdlib>
#include <string>
#include <vector>

class Solution {
   public:
    bool isInterleave(std::string s1, std::string s2, std::string s3) {
        size_t n = s1.size();
        size_t m = s2.size();
        if (n + m != s3.size()) {
            return false;
        }
        BitSet dp(m + 1);
        dp[0] = true;
        for (size_t i = 1; i < m + 1; ++i) {
            if (dp[i - 1] && s2[i - 1] == s3[i - 1]) {
                dp[i] = true;
            }
        }
        for (size_t i = 1; i < n + 1; ++i) {
            BitSet curr(m + 1);
            curr[0] = dp[0] && s1[i - 1] == s3[i - 1];
            for (size_t j = 1; j < m + 1; ++j) {
                size_t k = i + j;
                curr[j] = (dp[j] && s1[i - 1] == s3[k - 1]) ||
                          (curr[j - 1] && s2[j - 1] == s3[k - 1]);
            }
            if (!curr) {
                return false;
            }
            std::swap(dp, curr);
        }
        return dp[m];
    }

   private:
    class BitSet {
        class Reference {
           public:
            Reference(uint32_t& seg, uint32_t shift_val)
                : seg_(seg), shift_val_(shift_val) {}
            operator bool() const { return seg_ & (1ul << shift_val_); }

            Reference& operator=(bool key) {
                seg_ = (seg_ & ~(1ul << shift_val_)) | (key << shift_val_);
                return *this;
            }

           private:
            uint32_t& seg_;
            uint32_t shift_val_;
        };

       public:
        BitSet(size_t size) : bitset_((size + 31ul) >> 5ul) {}

        Reference operator[](size_t pos) {
            return Reference(bitset_[pos >> 5ul], pos & 31ul);
        }

        operator bool() const {
            uint32_t ans = 0;
            for (const uint32_t seg : bitset_) {
                ans |= seg;
                if (ans != 0) {
                    return true;
                }
            }
            return false;
        }

       private:
        std::vector<uint32_t> bitset_;
    };
};