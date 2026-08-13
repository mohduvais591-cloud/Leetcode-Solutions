class Solution {
public:
    struct Node {
        char lc, rc;
        int pref, suff, best, len;
    };

    vector<Node> seg;
    string s;

    Node merge(Node a, Node b) {
        Node res;
        res.len = a.len + b.len;
        res.lc = a.lc;
        res.rc = b.rc;

        res.pref = a.pref;
        if (a.pref == a.len && a.rc == b.lc)
            res.pref = a.len + b.pref;

        res.suff = b.suff;
        if (b.suff == b.len && a.rc == b.lc)
            res.suff = b.len + a.suff;

        res.best = max(a.best, b.best);
        if (a.rc == b.lc)
            res.best = max(res.best, a.suff + b.pref);

        return res;
    }

    void build(int idx, int l, int r) {
        if (l == r) {
            seg[idx] = {s[l], s[l], 1, 1, 1, 1};
            return;
        }

        int mid = (l + r) / 2;
        build(idx * 2, l, mid);
        build(idx * 2 + 1, mid + 1, r);

        seg[idx] = merge(seg[idx * 2], seg[idx * 2 + 1]);
    }

    void update(int idx, int l, int r, int pos, char c) {
        if (l == r) {
            s[pos] = c;
            seg[idx] = {c, c, 1, 1, 1, 1};
            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
            update(idx * 2, l, mid, pos, c);
        else
            update(idx * 2 + 1, mid + 1, r, pos, c);

        seg[idx] = merge(seg[idx * 2], seg[idx * 2 + 1]);
    }

    vector<int> longestRepeating(string str,
                                 string queryCharacters,
                                 vector<int>& queryIndices) {

        s = str;
        int n = s.size();

        seg.resize(4 * n + 5);

        build(1, 0, n - 1);

        vector<int> ans;

        for (int i = 0; i < queryIndices.size(); i++) {
            update(1, 0, n - 1, queryIndices[i], queryCharacters[i]);
            ans.push_back(seg[1].best);
        }

        return ans;
    }
};