#include <vector>

class Solution {
   public:
    double findMedianSortedArrays(std::vector<int>& nums1,
                                  std::vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size(), k = (n1 + n2) / 2;
        if ((n1 + n2) % 2) {
            return FindVal(nums1, nums2, k, 0, n1, 0, n2);
        }
        return (FindVal(nums1, nums2, k, 0, n1, 0, n2) +
                FindVal(nums1, nums2, k - 1, 0, n1, 0, n2)) /
               2.0;
    }

   private:
    double FindVal(const std::vector<int>& nums1,
                   const std::vector<int>& nums2, int k, int l1, int r1,
                   int l2, int r2) {
        if (l1 == r1) {
            return nums2[k - r1];
        }
        if (l2 == r2) {
            return nums1[k - r2];
        }
        int mid1 = l1 + (r1 - l1) / 2;
        int mid2 = l2 + (r2 - l2) / 2;
        if (mid1 + mid2 < k) {
            if (nums1[mid1] <= nums2[mid2]) {
                return FindVal(nums1, nums2, k, mid1 + 1, r1, l2, r2);
            }
            return FindVal(nums1, nums2, k, l1, r1, mid2 + 1, r2);
        }
        if (nums1[mid1] <= nums2[mid2]) {
            return FindVal(nums1, nums2, k, l1, r1, l2, mid2);
        }
        return FindVal(nums1, nums2, k, l1, mid1, l2, r2);
    }
};