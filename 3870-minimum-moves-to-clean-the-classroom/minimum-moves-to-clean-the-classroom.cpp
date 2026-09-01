class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int n = classroom.size();
        int m = classroom[0].size();

        int sr = 0, sc = 0;
        vector<pair<int, int>> litter;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                } 
                else if (classroom[i][j] == 'L') {
                    litter.push_back({i, j});
                }
            }
        }

        int k = litter.size();
        int fullMask = (1 << k) - 1;

       
        vector<vector<int>> litterId(n, vector<int>(m, -1));
        for (int i = 0; i < k; i++) {
            litterId[litter[i].first][litter[i].second] = i;
        }

        
        vector<vector<vector<int>>> best(
            n, vector<vector<int>>(m, vector<int>(1 << k, -1))
        );

        struct State {
            int r, c, mask, e, dist;
        };

        queue<State> q;
        q.push({sr, sc, 0, energy, 0});
        best[sr][sc][0] = energy;

        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto cur = q.front();
            q.pop();

            if (cur.mask == fullMask)
                return cur.dist;

            for (int d = 0; d < 4; d++) {
                int nr = cur.r + dr[d];
                int nc = cur.c + dc[d];

                if (nr < 0 || nr >= n || nc < 0 || nc >= m)
                    continue;

                if (classroom[nr][nc] == 'X')
                    continue;

               
                if (cur.e == 0)
                    continue;

                int ne = cur.e - 1;
                int nmask = cur.mask;

                if (classroom[nr][nc] == 'R')
                    ne = energy;

                if (litterId[nr][nc] != -1)
                    nmask |= (1 << litterId[nr][nc]);

                if (best[nr][nc][nmask] >= ne)
                    continue;

                best[nr][nc][nmask] = ne;
                q.push({nr, nc, nmask, ne, cur.dist + 1});
            }
        }

        return -1;
    }
};