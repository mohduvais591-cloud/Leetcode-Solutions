class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int candidates = 0;
        int count = 0;
        for(int num : nums){
            if(count==0){
                candidates = num;
            }
            if(num == candidates){
                count++;
            }else{
                count--;
            }
        }
        return candidates;

        
    }
};