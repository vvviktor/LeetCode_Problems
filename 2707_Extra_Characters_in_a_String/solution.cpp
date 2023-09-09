#include <algorithm>
#include <string>
#include <string_view>
#include <vector>

class Solution {
    class Trie {
       public:
        struct Node {
            int next[26] = {};
            bool is_terminal = false;
        };

        Trie() : trie_(1) {}

        void AddWord(std::string_view word) {
            size_t curr_node = 0;
            for (const char c : word) {
                if (trie_[curr_node].next[c - 'a'] == 0) {
                    trie_[curr_node].next[c - 'a'] = trie_.size();
                    trie_.push_back({});
                }
                curr_node = trie_[curr_node].next[c - 'a'];
            }
            trie_[curr_node].is_terminal = true;
        }

        const Node* Go(const Node* start, char c) const {
            const Node* curr_node = !start ? &trie_[0] : start;
            return curr_node->next[c - 'a'] != 0
                       ? &trie_[curr_node->next[c - 'a']]
                       : nullptr;
        }

       private:
        std::vector<Node> trie_;
    };

   public:
    int minExtraChar(std::string s, std::vector<std::string>& dictionary) {
        Trie dict;
        for (std::string_view s : dictionary) {
            dict.AddWord(s);
        }
        dp_ = std::vector<int>(s.size(), -1);
        return MinExtra(s, dict, 0);
    }

   private:
    std::vector<int> dp_;

    int MinExtra(const std::string& s, const Trie& dict, size_t start) {
        if (start == s.size()) {
            return 0;
        }
        if (dp_[start] != -1) {
            return dp_[start];
        }
        int ans = 1 + MinExtra(s, dict, start + 1);
        const Trie::Node* curr = nullptr;
        for (size_t i = start; i < s.size(); ++i) {
            curr = dict.Go(curr, s[i]);
            if (!curr) {
                break;
            }
            if (curr->is_terminal) {
                ans = std::min(ans, MinExtra(s, dict, i + 1));
            }
        }
        return dp_[start] = ans;
    }
};