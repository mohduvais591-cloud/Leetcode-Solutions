class Solution {
public:

    void remove(string s, int last_i, int last_j,
                char open, char close,
                vector<string>& ans) {

        int balance = 0;

        for (int i = last_i; i < s.size(); i++) {

            if (s[i] == open)
                balance++;
            else if (s[i] == close)
                balance--;

           
            if (balance < 0) {

                for (int j = last_j; j <= i; j++) {

                    if (s[j] == close &&
                        (j == last_j || s[j - 1] != close)) {

                        string temp = s.substr(0, j) + s.substr(j + 1);

                        remove(temp, i, j, open, close, ans);
                    }
                }

                return;
            }
        }

       
        reverse(s.begin(), s.end());

        if (open == '(') {
            remove(s, 0, 0, ')', '(', ans);
        }
        else {
            ans.push_back(s);
        }
    }

    vector<string> removeInvalidParentheses(string s) {

        vector<string> ans;

        remove(s, 0, 0, '(', ')', ans);

        return ans;
    }
};