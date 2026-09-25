class Solution {
public:
    string s;
    int i;

    // expression = term (',' term)*
    set<string> parseExpression() {
        set<string> res = parseTerm();

        while (i < s.size() && s[i] == ',') {
            i++;  // skip ','

            set<string> temp = parseTerm();
            res.insert(temp.begin(), temp.end());
        }

        return res;
    }

    // term = factor factor factor...
    set<string> parseTerm() {
        set<string> res;
        res.insert("");

        while (i < s.size() &&
               s[i] != ',' &&
               s[i] != '}') {

            set<string> part = parseFactor();

            set<string> next;

            for (const string &a : res) {
                for (const string &b : part) {
                    next.insert(a + b);
                }
            }

            res = move(next);
        }

        return res;
    }

    // factor = letter OR { expression }
    set<string> parseFactor() {
        set<string> res;

        if (s[i] == '{') {
            i++;  // skip '{'

            res = parseExpression();

            i++;  // skip '}'
        }
        else {
            res.insert(string(1, s[i]));
            i++;
        }

        return res;
    }

    vector<string> braceExpansionII(string expression) {
        s = expression;
        i = 0;

        set<string> ans = parseExpression();

        return vector<string>(ans.begin(), ans.end());
    }
};