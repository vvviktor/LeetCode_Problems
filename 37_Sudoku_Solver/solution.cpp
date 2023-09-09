#include <cstdlib>
#include <vector>

class Solution {
   public:
    void solveSudoku(std::vector<std::vector<char>>& board) {
        h_masks_ = std::vector<int>(9);
        v_masks_ = std::vector<int>(9);
        sq_masks_ = std::vector<std::vector<int>>(3, std::vector<int>(3));
        FillMasks(board);
        Solve(board, 0, 0);
    }

   private:
    std::vector<int> h_masks_;
    std::vector<int> v_masks_;
    std::vector<std::vector<int>> sq_masks_;

    struct PtrPack {
        int* h = nullptr;
        int* v = nullptr;
        int* sq = nullptr;
    };

    PtrPack GetPtrs(int y, int x) {
        return {&h_masks_[y], &v_masks_[x], &sq_masks_[y / 3][x / 3]};
    }

    bool CanPut(int y, int x, int k) {
        auto [h_ptr, v_ptr, sq_ptr] = GetPtrs(y, x);
        if ((*h_ptr & (1 << k)) || (*v_ptr & (1 << k)) ||
            (*sq_ptr & (1 << k))) {
            return false;
        }
        return true;
    }

    void ToggleBit(int y, int x, int k) {
        auto [h_ptr, v_ptr, sq_ptr] = GetPtrs(y, x);
        *h_ptr ^= (1 << k);
        *v_ptr ^= (1 << k);
        *sq_ptr ^= (1 << k);
    }

    bool Solve(std::vector<std::vector<char>>& board, int y, int x) {
        if (y == 9) {
            return true;
        }
        if (x == 9) {
            return Solve(board, y + 1, 0);
        }
        if (board[y][x] != '.') {
            return Solve(board, y, x + 1);
        } else {
            for (int k = 1; k < 10; ++k) {
                if (CanPut(y, x, k)) {
                    board[y][x] = k + '0';
                    ToggleBit(y, x, k);
                    if (Solve(board, y, x + 1)) {
                        return true;
                    }
                    board[y][x] = '.';
                    ToggleBit(y, x, k);
                }
            }
        }
        return false;
    }

    void FillMasks(const std::vector<std::vector<char>>& board) {
        for (size_t i = 0; i < 9; ++i) {
            for (size_t j = 0; j < 9; ++j) {
                if (board[i][j] != '.') {
                    ToggleBit(i, j, board[i][j] - '0');
                }
            }
        }
    }
};