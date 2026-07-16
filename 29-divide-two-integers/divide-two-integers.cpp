class Solution {
public:
    int divide(int dividend, int divisor) {
        if(dividend==INT_MIN && divisor==-1)
        return INT_MAX;
        bool negative = (dividend<0) ^ (divisor<0);
        long long dvd = llabs((long long)dividend);
        long long div = llabs((long long)divisor);
        long long qui = 0;
        while(dvd>=div){
            long long temp = div;
            long long multiple = 1;
            while((temp<<1) <=dvd){
                temp<<=1;
                multiple<<=1;
            }
            dvd-=temp;
            qui+=multiple;
        }
        if(negative){
            qui = -qui;
        }
        return (int)qui;
        
    }
};