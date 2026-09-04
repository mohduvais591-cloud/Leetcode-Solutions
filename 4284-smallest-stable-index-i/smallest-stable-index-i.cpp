class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            int leftMax = nums[0];
            int rightMin = nums[i];
            for (int j = 0; j <= i; j++) {
                leftMax = max(leftMax, nums[j]);
            }
            for (int j = i; j < n; j++) {
                rightMin = min(rightMin, nums[j]);
            }
            if (leftMax - rightMin <= k) {
                return i;
            }
        }

        return -1;
    }
};