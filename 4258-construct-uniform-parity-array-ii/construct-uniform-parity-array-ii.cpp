class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int minOdd = INT_MAX, minEven = INT_MAX;
        int oddCount = 0, evenCount = 0;

        for (int x : nums1) {
            if (x % 2 == 0) {
                evenCount++;
                minEven = min(minEven, x);
            } else {
                oddCount++;
                minOdd = min(minOdd, x);
            }
        }

        bool allEvenPossible = (oddCount == 0);
        bool allOddPossible  = (evenCount == 0) || (oddCount > 0 && minOdd < minEven);

        return allEvenPossible || allOddPossible;
    }
};