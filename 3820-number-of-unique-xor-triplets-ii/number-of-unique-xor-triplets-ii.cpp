class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048;
        vector<vector<bool>> dp(4, vector<bool>(MAXX, false));
        dp[0][0] = true;
        for(int val : nums){
            vector<vector<bool>> ndp = dp;
            for(int used = 0; used<=3; used++){
                for(int x=0; x<MAXX; x++){
                    if(!dp[used][x]) continue;
                    for(int t=1; t+used<=3; t++){
                        int nx = x^((t&1)? val : 0);
                        ndp[used+t][nx] = true;
                    }
                }
            }
            dp.swap(ndp);
        }
        int ans = 0;
        for(bool ok : dp[3]){
            if(ok) ans++;
        }
        return ans;
        
    }
};