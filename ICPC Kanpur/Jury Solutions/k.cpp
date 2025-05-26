#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

const int mod = 998244353;

int power(int x, int y){
    if (y == 0) return 1;

    int v = power(x, y / 2);
    v = 1LL * v * v % mod;

    if (y & 1) return 1LL * v * x % mod;
    else return v;
}

void Solve() 
{
    int n; cin >> n;
    
    vector <int> p(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> p[i];
    }
    
    bool bad = false;
    for (int i = 1; i <= n; i++){
        if (p[i] != i){
            bad = true;
        }
    }
    
    if (!bad){
        cout << n << "\n";
        return;
    }
   
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(n + 1, vector<int>(n + 1, 0)));
    // dp[i][posssible replacements][length of sequence] = ways 
    
    for (int i = 1; i <= n; i++){
        int rep = 0;
        for (int j = 1; j < i; j++) if (p[j] > p[i]){
            rep++;
        }
        
        dp[i][1][rep] = 1;
    }
    
    for (int i = 2; i <= n; i++){
        for (int j = 1; j < i; j++) if (p[i] > p[j]){
            int add = 0;
            for (int k = j + 1; k < i; k++){
                if (p[k] > p[i] || p[k] < p[j]) add++;
            }
            for (int len = 1; len < n; len++){
                for (int crep = 0; crep + add <= n; crep++){
                    dp[i][len + 1][crep + add] += dp[j][len][crep];
                    dp[i][len + 1][crep + add] %= mod;
                }
            }
        }
    }
    
    vector<vector<int>> f(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++){
        int add = 0;
        for (int k = i + 1; k <= n; k++){
            if (p[k] < p[i]) add++;
        }
        for (int rep = 0; rep + add <= n; rep++){
            for (int len = 1; len <= n; len++){
                f[rep + add][len] += dp[i][len][rep];
                f[rep + add][len] %= mod;
            }
        }
    }
    
    int ans = 0;
    vector <int> g(n + 1, 1);
    for (int i = 1; i <= n; i++){
        g[i] = g[i - 1] * i % mod;
    }
    
    for (int rep = 1; rep <= n; rep++){
        for (int len = 1; len <= n; len++){
            int ways = g[len] * g[n - len - 1] % mod * rep % mod;
            
            ways *= f[rep][len];
            ways %= mod;
            
            ans += ways * len;
            ans %= mod;
        }
    }
    
    // vector <int> ord(n);
    // iota(ord.begin(), ord.end(), 1);
    // int sum_len = 0;
    
    // do {
    //     auto a = p;
    //     auto c = a;
    //     sort(c.begin(), c.end());
    //     if (c == a){
    //         sum_len += (int)a.size() - 1;
    //         continue;
    //     }
    //     for (auto x : ord){
    //         vector <int> b;
    //         for (auto y : a) if (y != x) b.push_back(y);
    //         a = b;
    //         auto c = a;
    //         sort(c.begin(), c.end());
            
    //         if (c == a){
    //             break;
    //         }
    //     }
        
    //     sum_len += (int)a.size() - 1;
    // } while (next_permutation(ord.begin(), ord.end()));
    
    ans *= power(g[n], mod - 2);
    ans %= mod;
    
    cout << ans << "\n";
}

int32_t main() 
{
    auto begin = std::chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // freopen("in",  "r", stdin);
    // freopen("out", "w", stdout);
    
    cin >> t;
    for(int i = 1; i <= t; i++) 
    {
        //cout << "Case #" << i << ": ";
        Solve();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n"; 
    return 0;
}