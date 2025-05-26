#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

void Solve() 
{
    int n, m; cin >> n >> m;
    
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= m; i++){
        int u, v; cin >> u >> v;
        
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    if (n % 2 == 1){
        int v = 1 * (n - 1);
        if (v % 2 == m % 2){
            // Alice loses 
            cout << "Bob\n";
        } else {
            cout << "Alice\n";
        }
        return;
    }
    
    int oe = 0;
    
    vector <int> col(n + 1, -1);
    int num = 0;
    int s = 0;
    int v1 = 0, v2 = 0;
    int oo = 0;
    
    auto dfs = [&](auto self, int u, int c) -> void{
        num++;
        col[u] = c;
        if (c == 0){
            v1++;
        } else {
            v2++;
        }
        for (int v : adj[u]) if (col[v] == -1){
            self(self, v, c ^ 1);
        }
    };
    
    for (int i = 1; i <= n; i++) if (col[i] == -1){
        num = 0;
        v1 = 0;
        v2 = 0;
        dfs(dfs, i, 0);
        if (num & 1){
            oe++;
        }
        if (num == 1){
            oe--;
            s++;
        }
        if (v1 % 2 == 1 && v2 % 2 == 1){
            oo++;
        }
    }
    
    if (oe == 0){
        int par = (oo + (s / 2) + m);
        if (par % 2 == 1) cout << "Alice\n";
        else cout << "Bob\n";
    } else if (oe <= 2){
        cout << "Alice\n";
    } else {
        if (m % 2 == 1) cout << "Alice\n";
        else cout << "Bob\n";
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