class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();
        int left = 0;
        int ones = 0;
        int bestLen = n+1;
        string ans = "";
        for(int right = 0; right<n; right++){
            if(s[right]=='1'){
                ones++;

            }
            while(ones>k){
                if(s[left]=='1'){
                    ones--;
                }
                left++;
            }
            if(ones==k){
                while(left<=right && s[left]=='0'){
                    left++;
                }
                int len = right-left+1;
                string cur = s.substr(left, len);
                if(len<bestLen || (len==bestLen && cur<ans)){
                    bestLen = len;
                    ans = cur;
                }
            }
        }
        return ans;
        
    }
};