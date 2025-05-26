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
    int n, m; cin >> n >> m;
    
    int ans = 0;
    int last = min(n, m);
    int done = 0;
    
    for (int i = 0; i <= n; i++){
        // 1...i are all equal
        if (i > m) break;
        
        if (i == n){
            done += 1;
            break;
        }
        
        // 1 ops => next things have (m - 1) / (m) choices 
        // i + 1...last will have (m - 1) choices 
        int v1 = max(last - i, 0LL);
        int ways = power(m - 1, v1);
        int v2 = n - i - v1;
        ways *= power(m, v2);
        ways %= mod;
        
        ans += ways;
        done += ways;
        ans %= mod;
        done %= mod;
    }
    
    int tot = power(m, n);
    tot -= done;
    if (tot < 0) tot += mod;
    
    ans += 2 * tot;
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