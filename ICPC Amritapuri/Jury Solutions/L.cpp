#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

void Solve() 
{
    vector <int> p(128);
    for (int i = 0; i < 128; i++){
        cin >> p[i];
    }
    reverse(p.begin(), p.end());
    
    // 1, 1, 2, 4, 8, 16, 32, 64
    vector <int> lim(8, 1);
    for (int i = 2; i < 8; i++){
        lim[i] = lim[i - 1] * 2;
    }
    vector <int> gain(8, 0);
    gain[7] = 1;
    gain[6] = 1 + 2;
    gain[5] = 1 + 2 + 3;
    gain[4] = 1 + 2 + 3 + 4;
    gain[3] = 1 + 2 + 3 + 4 + 5;
    gain[2] = 1 + 2 + 3 + 4 + 5 + 6;
    gain[1] = 1 + 2 + 3 + 4 + 5 + 6 + 7;
    gain[0] = gain[1];
    
    map <vector<int>, int> memo;
    
    auto dfs = [&](auto self, int pos, vector <int> a){
        if (memo.find(a) != memo.end()){
            return memo[a];
        }
        
        int ans = 0;
        
        for (int i = 0; i < 8; i++){
            // need to have more smaller people in prefix, then only this is allowed 
            int sum = 0;
            for (int j = 0; j < i; j++){
                sum += a[j];
            }
            
            if (pos == 0 && i != 0) continue;
            if (pos != 0){
                if (sum < a[i] + 1) continue;
            }
            
            auto b = a;
            b[i]++;
            int gg = gain[i] * p[pos];
            gg += self(self, pos + 1, b);
            
            ans = max(ans, gg);
        }
        
        memo[a] = ans;
        
        return ans;
    };
    
    vector <int> a(8, 0);
    int ans = dfs(dfs, 0, a);
    
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