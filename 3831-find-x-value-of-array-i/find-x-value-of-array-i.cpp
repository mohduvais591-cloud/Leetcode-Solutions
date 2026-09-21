class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> result(k, 0);
        vector<long long> dp(k, 0);

        for (int num : nums) {
            vector<long long> curr(k, 0);

            int rem = num % k;

            // Subarray containing only the current element
            curr[rem]++;

            // Extend all previous subarrays
            for (int r = 0; r < k; r++) {
                if (dp[r] > 0) {
                    int newRem = (r * rem) % k;
                    curr[newRem] += dp[r];
                }
            }

            // Count all subarrays ending at the current position
            for (int r = 0; r < k; r++) {
                result[r] += curr[r];
            }

            dp = curr;
        }

        return result;
    }
};