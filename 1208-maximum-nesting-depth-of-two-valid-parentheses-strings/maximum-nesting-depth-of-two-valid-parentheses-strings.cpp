class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        vector<int> ans;
        int depth = 0;

        for (char c : seq) {
            if (c == '(') {
                
                ans.push_back(depth % 2);
                depth++;
            } 
            else {
                depth--;
                
                ans.push_back(depth % 2);
            }
        }

        return ans;
    }
};