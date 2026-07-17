class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());
        vector<int> freq(mx+1, 0);
        for(int x : nums) freq[x]++;
        vector<long long> cnt(mx+1, 0);
        for(int d = 1; d<=mx; d++){
            for(int j=d; j<=mx; j+=d){
                cnt[d]+=freq[j];
            }
        }
        vector<long long> exact(mx+1, 0);
        for(int d=mx; d>=1; d--){
            exact[d] = cnt[d]*(cnt[d]-1)/2;
            for(int j=d+d; j<=mx; j+=d){
                exact[d]-=exact[j];

            }
        }
        vector<long long> pref(mx+1, 0);
        pref[0]=0;
        for(int i=1; i<=mx; i++){
            pref[i] = pref[i-1] + exact[i];

        }
        vector<int> ans;
        for(long long k : queries){
            int g = lower_bound(pref.begin()+1, pref.end(), k+1)- pref.begin();
            ans.push_back(g);
        }
        return ans;
        
    }
};