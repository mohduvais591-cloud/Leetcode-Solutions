class Solution {
public:
    int mySqrt(int x) {
        if(x==0 || x==1) return x;
        int left = 1;
        int right = x;
        int ans = 0;
        while(left<=right){
            long long mid = left+(right-left)/2;
            long long q = mid*mid;
            if(q==x)
            return mid;
            else if(q<x){
            ans = mid;
            left = mid+1;
            }
            else{
                right = mid-1;
            }
        }
        return ans;
        
    }
};