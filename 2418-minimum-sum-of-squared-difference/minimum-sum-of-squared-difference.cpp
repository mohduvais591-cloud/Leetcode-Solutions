
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        vector<int> diff;
        long long k = 1LL * k1 + k2;
        long long sum = 0;

        for (int i = 0; i < nums1.size(); i++) {
            int d = abs(nums1[i] - nums2[i]);
            diff.push_back(d);
            sum += d;
        }

        if (sum <= k) return 0;

        int left = 0, right = 100000;

        while (left < right) {
            int mid = left + (right - left) / 2;
            long long need = 0;

            for (int d : diff) {
                if (d > mid) need += d - mid;
            }

            if (need <= k)
                right = mid;
            else
                left = mid + 1;
        }

        int level = left;
        long long remaining = k;

        for (int d : diff) {
            if (d > level) {
                remaining -= d - level;
                d = level;
            }
        }

       
        vector<int> reduced;
        for (int d : diff) {
            if (d > level) d = level;
            reduced.push_back(d);
        }

        for (int i = 0; i < (int)reduced.size() && remaining > 0; i++) {
            if (reduced[i] == level && level > 0) {
                reduced[i]--;
                remaining--;
            }
        }

        long long ans = 0;
        for (int d : reduced) ans += 1LL * d * d;

        return ans;
    }
};
