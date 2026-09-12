class Solution {
public:
    struct State {
        long long score = -1;
        vector<int> indices;
    };

    
    bool smaller(const vector<int>& a, const vector<int>& b) {
        return lexicographical_compare(
            a.begin(), a.end(),
            b.begin(), b.end()
        );
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

       
        vector<array<long long, 4>> a;

        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        
        sort(a.begin(), a.end(), [](const auto& x, const auto& y) {
            if (x[1] != y[1])
                return x[1] < y[1];
            return x[0] < y[0];
        });

        vector<long long> ends(n);
        for (int i = 0; i < n; i++)
            ends[i] = a[i][1];

 
        vector<int> prev(n);

        for (int i = 0; i < n; i++) {
            // Need r < l
            prev[i] = lower_bound(
                ends.begin(),
                ends.begin() + i,
                a[i][0]
            ) - ends.begin();
        }

       
        vector<array<State, 5>> dp(n + 1);

        
        for (int k = 0; k <= 4; k++) {
            dp[0][k].score = 0;
        }

        for (int i = 1; i <= n; i++) {
            int id = i - 1;

            for (int k = 0; k <= 4; k++) {

                
                dp[i][k] = dp[i - 1][k];

                
                if (k > 0) {
                    int p = prev[id];

                    
                    if (dp[p][k - 1].score >= 0) {

                        State take;
                        take.score =
                            dp[p][k - 1].score + a[id][2];

                        take.indices = dp[p][k - 1].indices;
                        take.indices.push_back((int)a[id][3]);

                       
                        sort(take.indices.begin(), take.indices.end());

                        if (take.score > dp[i][k].score ||
                            (take.score == dp[i][k].score &&
                             smaller(take.indices,
                                     dp[i][k].indices))) {
                            dp[i][k] = take;
                        }
                    }
                }
            }
        }

      
        State ans = dp[n][0];

        for (int k = 1; k <= 4; k++) {
            if (dp[n][k].score > ans.score ||
                (dp[n][k].score == ans.score &&
                 smaller(dp[n][k].indices, ans.indices))) {
                ans = dp[n][k];
            }
        }

        return ans.indices;
    }
};