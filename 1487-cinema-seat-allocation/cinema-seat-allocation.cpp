class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> mp;

        // Store reserved seats as a bitmask for each row
        for (auto &seat : reservedSeats) {
            int row = seat[0];
            int s = seat[1];

            // Only seats 2 to 9 affect the answer
            if (s >= 2 && s <= 9) {
                mp[row] |= (1 << s);
            }
        }

        // Every row can initially fit 2 families
        int ans = 2 * n;

        for (auto &[row, mask] : mp) {

            // Left block: 2,3,4,5
            bool left = !(mask & (1 << 2)) &&
                        !(mask & (1 << 3)) &&
                        !(mask & (1 << 4)) &&
                        !(mask & (1 << 5));

            // Right block: 6,7,8,9
            bool right = !(mask & (1 << 6)) &&
                         !(mask & (1 << 7)) &&
                         !(mask & (1 << 8)) &&
                         !(mask & (1 << 9));

            if (left && right) {
                // Still 2 families, so nothing to change
                continue;
            }
            else if (left || right) {
                // Only one family can fit
                ans--;
            }
            else {
                // Check middle block: 4,5,6,7
                bool middle = !(mask & (1 << 4)) &&
                              !(mask & (1 << 5)) &&
                              !(mask & (1 << 6)) &&
                              !(mask & (1 << 7));

                if (middle) {
                    ans--;
                }
                else {
                    // No family can fit
                    ans -= 2;
                }
            }
        }

        return ans;
    }
};