#include <queue>
#include <string>

class Solution {
   public:
    int minDeletions(std::string s) {
        int c_freq[26] = {};
        int deletions = 0;
        for (const char c : s) {
            ++c_freq[c - 'a'];
        }
        std::priority_queue<int> q;
        for (size_t i = 0; i < 26; ++i) {
            if (c_freq[i] == 0) {
                continue;
            }
            q.push(c_freq[i]);
        }
        while (q.size() > 1) {
            int curr = q.top();
            q.pop();
            if (curr == q.top()) {
                ++deletions;
                if (--curr == 0) {
                    continue;
                }
                q.push(curr);
            }
        }
        return deletions;
    }
};