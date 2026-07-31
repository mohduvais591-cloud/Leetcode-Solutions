class Solution {
public:
    int minimumPushes(string word) {
        vector<int> freq(26, 0);
        for(char c : word){
            freq[c- 'a']++;
        }
        sort(freq.begin(), freq.end(), greater<int>());
        int ans =0;
        for(int i=0; i<26; i++){
            if(freq[i]==0) break;
            int pu = (i/8) + 1;

            ans+=freq[i]*pu;
        }
        return ans;
        
    }
};