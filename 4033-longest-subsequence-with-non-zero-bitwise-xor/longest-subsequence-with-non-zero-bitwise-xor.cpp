class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int n = nums.size();
        int a = 0;
        bool hasNonZero = false;
        for(int x : nums){
            a^=x;
            if(x!=0){
                hasNonZero = true;
            }
        }
        if(!hasNonZero){
            return 0;
        }
        if(a !=0){
            return n;
        }
        return n-1;
        
    }
};