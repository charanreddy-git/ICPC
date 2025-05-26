#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

void Solve() 
{
    string a, b; cin >> a >> b;
    
    vector <int> f(26, 0), g(26, 0);
    for (auto &x : a){
        f[x - 'a']++;
    }
    for (auto &x : b){
        g[x - 'a']++;
    }
    
    int ans = 0;
    for (auto x : f) ans += x > 0;
    for (auto x : g) ans += x > 0;
    for (int i = 0; i < 26; i++){
        if (f[i] > 0 && g[i] > 0){
            ans--;
            break;
        }
    }
    ans--;
    
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