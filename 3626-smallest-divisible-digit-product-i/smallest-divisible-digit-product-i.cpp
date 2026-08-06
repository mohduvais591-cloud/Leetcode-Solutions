class Solution {
public:
    int digitProduct(int x){
        int product = 1;
        while(x>0){
            product *=(x%10);
            x/=10;
        }
        return product;
    }
    int smallestNumber(int n, int t) {
        for(int i=n; ; i++){
            if(digitProduct(i)%t==0)
            return i;

        }
        
    }
};