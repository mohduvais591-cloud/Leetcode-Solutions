class Solution {
public:
    string makePalindrome(const string& half, char mid, bool odd) {
        string res = half;

        if (odd)
            res += mid;

        for (int i = (int)half.size() - 1; i >= 0; i--)
            res += half[i];

        return res;
    }

    string nextHalf(string target, vector<int> cnt) {
        int m = target.size();

        // Find the first position where target's prefix
        // can no longer be formed from cnt.
        int k = m;

        for (int i = 0; i < m; i++) {
            int c = target[i] - 'a';

            if (cnt[c] == 0) {
                k = i;
                break;
            }

            cnt[c]--;
        }

        // We need the rightmost position where we can
        // increase target[i].
        for (int i = min(k, m - 1); i >= 0; i--) {
            vector<int> rem = cnt;

            // Rebuild remaining counts after using target[0..i-1].
            rem.clear();
            rem.resize(26);

            // Start from original half counts
            // (reconstructed by the caller through this function's cnt
            // is no longer possible after modification, so handled below)
        }

        return "";
    }

    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        int m = n / 2;

        vector<int> freq(26, 0);

        for (char c : s)
            freq[c - 'a']++;

        // A palindrome can have at most one odd frequency.
        int oddCount = 0;
        char mid = 0;

        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2) {
                oddCount++;
                mid = char('a' + i);
            }
        }

        if (oddCount > 1)
            return "";

        // Counts available for the first half.
        vector<int> halfCnt(26, 0);

        for (int i = 0; i < 26; i++)
            halfCnt[i] = freq[i] / 2;

        // ---------------------------------------------------------
        // Step 1: Try to make first half exactly target[0 ... m-1]
        // ---------------------------------------------------------
        vector<int> rem = halfCnt;
        bool possible = true;

        for (int i = 0; i < m; i++) {
            int c = target[i] - 'a';

            if (rem[c] == 0) {
                possible = false;
                break;
            }

            rem[c]--;
        }

        if (possible) {
            string half = target.substr(0, m);

            string candidate = makePalindrome(
                half, mid, n % 2
            );

            if (candidate > target)
                return candidate;
        }

        // ---------------------------------------------------------
        // Step 2: Find the smallest half lexicographically
        // greater than target's first half.
        //
        // Similar to next_permutation, but with duplicate counts.
        // ---------------------------------------------------------

        // Find the longest prefix of target that can be used.
        int prefixLen = 0;
        rem = halfCnt;

        while (prefixLen < m) {
            int c = target[prefixLen] - 'a';

            if (rem[c] == 0)
                break;

            rem[c]--;
            prefixLen++;
        }

        // Try changing the rightmost possible position.
        for (int pos = min(prefixLen, m - 1); pos >= 0; pos--) {

            // Reconstruct remaining counts after
            // fixing target[0 ... pos-1].
            vector<int> available = halfCnt;

            bool ok = true;

            for (int j = 0; j < pos; j++) {
                int c = target[j] - 'a';

                if (available[c] == 0) {
                    ok = false;
                    break;
                }

                available[c]--;
            }

            if (!ok)
                continue;

            // Pick the smallest character greater than target[pos].
            int chosen = -1;

            for (int c = target[pos] - 'a' + 1; c < 26; c++) {
                if (available[c] > 0) {
                    chosen = c;
                    break;
                }
            }

            if (chosen == -1)
                continue;

            string half = target.substr(0, pos);

            half += char('a' + chosen);
            available[chosen]--;

            // Fill the rest with smallest possible characters.
            for (int c = 0; c < 26; c++) {
                while (available[c] > 0) {
                    half += char('a' + c);
                    available[c]--;
                }
            }

            string candidate = makePalindrome(
                half, mid, n % 2
            );

            if (candidate > target)
                return candidate;
        }

        return "";
    }
};