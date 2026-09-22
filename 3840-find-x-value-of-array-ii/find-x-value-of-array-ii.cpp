class Solution {
public:
    struct Node {
        int prod;
        int len;
        int pref[5];

        Node() {
            prod = 1;
            len = 0;

            for (int i = 0; i < 5; i++) {
                pref[i] = 0;
            }
        }
    };

    int k, n, size;
    vector<Node> seg;

    Node merge(Node &a, Node &b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;

        res.len = a.len + b.len;
        res.prod = (a.prod * b.prod) % k;

        // Prefixes completely inside the left segment
        for (int r = 0; r < k; r++) {
            res.pref[r] = a.pref[r];
        }

        // Prefixes extending into the right segment
        for (int r = 0; r < k; r++) {
            int rem = (a.prod * r) % k;
            res.pref[rem] += b.pref[r];
        }

        return res;
    }

    Node makeNode(int val) {
        Node res;

        res.len = 1;
        res.prod = val % k;
        res.pref[res.prod] = 1;

        return res;
    }

    void update(int pos, int val) {
        pos += size;

        seg[pos] = makeNode(val);

        // Update ancestors
        for (pos /= 2; pos > 0; pos /= 2) {
            seg[pos] = merge(seg[pos * 2], seg[pos * 2 + 1]);
        }
    }

    Node query(int l, int r) {
        Node left, right;

        l += size;
        r += size;

        while (l < r) {
            if (l & 1) {
                left = merge(left, seg[l]);
                l++;
            }

            if (r & 1) {
                r--;
                right = merge(seg[r], right);
            }

            l /= 2;
            r /= 2;
        }

        return merge(left, right);
    }

    vector<int> resultArray(vector<int>& nums, int K,
                            vector<vector<int>>& queries) {
        k = K;
        n = nums.size();

        // Build iterative segment tree
        size = 1;
        while (size < n) {
            size *= 2;
        }

        seg.assign(2 * size, Node());

        // Initialize leaves
        for (int i = 0; i < n; i++) {
            seg[size + i] = makeNode(nums[i]);
        }

        // Build internal nodes
        for (int i = size - 1; i > 0; i--) {
            seg[i] = merge(seg[2 * i], seg[2 * i + 1]);
        }

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto &q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Apply persistent update
            nums[index] = value;
            update(index, value);

            // Query the range [start, n)
            Node res = query(start, n);

            ans.push_back(res.pref[x]);
        }

        return ans;
    }
};