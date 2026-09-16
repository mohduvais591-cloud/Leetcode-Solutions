class Solution {
public:
    int numberOfSets(int n, int k) {
        const long long MOD = 1e9 + 7;

        // We need C(n + k - 1, 2k)
        int N = n + k - 1;
        int R = 2 * k;

        // factorial
        vector<long long> fact(N + 1), invFact(N + 1);

        fact[0] = 1;

        for (int i = 1; i <= N; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }

        // Fast power for modular inverse
        auto power = [&](long long a, long long b) {
            long long ans = 1;

            while (b > 0) {
                if (b & 1)
                    ans = ans * a % MOD;

                a = a * a % MOD;
                b >>= 1;
            }

            return ans;
        };

        invFact[N] = power(fact[N], MOD - 2);

        for (int i = N - 1; i >= 0; i--) {
            invFact[i] = invFact[i + 1] * (i + 1) % MOD;
        }

        // C(N, R)
        long long ans = fact[N];

        ans = ans * invFact[R] % MOD;
        ans = ans * invFact[N - R] % MOD;

        return ans;
    }
};