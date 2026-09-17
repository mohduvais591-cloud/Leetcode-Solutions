class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        const int INF = 1e9;

        // best[i] = minimum length of a valid subarray
        // completely inside arr[0 ... i-1]
        vector<int> best(n + 1, INF);

        int left = 0;
        long long sum = 0;
        int ans = INF;

        for (int right = 0; right < n; right++) {
            sum += arr[right];

            while (sum > target) {
                sum -= arr[left++];
            }

            if (sum == target) {
                int len = right - left + 1;

                // Find the best subarray ending before 'left'
                if (best[left] != INF) {
                    ans = min(ans, len + best[left]);
                }

                // Store the current subarray as a candidate
                best[right + 1] = min(best[right + 1], len);
            }

            // Carry forward the best answer so far
            best[right + 1] = min(best[right + 1], best[right]);
        }

        return ans == INF ? -1 : ans;
    }
};