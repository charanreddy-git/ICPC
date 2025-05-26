#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

void Solve() 
{
    int n; cin >> n;
    int ans = 0;
    
    // 0, 1, 01 
    // 0, 1, 00, 11, 01
    
    for (int i = 1; ; i++){
        // can you take all strings of length i 
        // i * 2^i and you need half of this 
        int num = 1;
        for (int j = 0; j < i; j++){
            num *= 2;
        }
        int tot = num / 2;
        tot *= i;
        
        if (n > tot){
            n -= tot;
            ans += num;
            continue;
        }
        
        int use = n / i;
        ans += 2 * use;
        n -= use * i;
        
        int need = (i + 1) / 2;
        ans += n >= need;
        break;
    }
    
    cout << ans << "\n";
}

int32_t main() 
{
    auto begin = std::chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    
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