class Solution {
public:
    int reverseDegree(string s) {
        int sum = 0;

        for (int i = 0; i < s.length(); i++) {
            int reverseIndex = 26 - (s[i] - 'a');
            sum += reverseIndex * (i + 1);
        }

        return sum;
    }
};