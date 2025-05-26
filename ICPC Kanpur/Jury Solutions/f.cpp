#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

void Solve() 
{
    int n, q; cin >> n >> q;
    
    string s; cin >> s;
    s = "0" + s;
    
    vector <int> nx(n + 1, -1);
    vector <int> prev(n + 1, -1);
    for (int i = 1; i <= n; i++){
        int j = i;
        while (j + 1 <= n && s[j + 1] == s[i]){
            j++;
        }
        
        for (int k = i; k <= j; k++){
            nx[k] = j + 1;
            prev[k] = i;
        }
        i = j;
    }
    
    vector <int> good_ind;
    for (int i = 1; i <= n; i++){
        if (nx[i] == n + 1){
            good_ind.push_back(i);
        } else if (s[i] < s[nx[i]]){
            good_ind.push_back(i);
        }
    }
    
    for (int i = 1; i <= q; i++){
        int l, r; cin >> l >> r;
        
        int m = lower_bound(good_ind.begin(), good_ind.end(), l) - good_ind.begin();
        int pos = good_ind[m];
        
        if (pos > r){
            cout << max(l, prev[r]) << "\n";
        } else {
            cout << pos << "\n";
        }
    }
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