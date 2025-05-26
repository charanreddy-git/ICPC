#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

struct ufds{
    vector <int> root, sz;
    int n;
 
    void init(int nn){
        n = nn;
        root.resize(n + 1);
        sz.resize(n + 1, 1);
        for (int i = 1; i <= n; i++) root[i] = i;
    }
 
    int find(int x){
        if (root[x] == x) return x;
        return root[x] = find(root[x]);
    }
 
    bool unite(int x, int y){
        x = find(x); y = find(y);
        if (x == y) return false;
 
        if (sz[y] > sz[x]) swap(x, y);
        sz[x] += sz[y];
        root[y] = x;
        return true;
    }
};

void Solve() 
{
    int n, m; cin >> n >> m;
    string s; cin >> s;
    s = "0" + s;
    
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= m; i++){
        int u, v; cin >> u >> v;
        
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    ufds uf;
    uf.init(n + 1);
    
    // for each node, store minimum distance and guy creating minimum distance 
    vector <array<int, 2>> dp(n + 1, {INF, -1});
    priority_queue <array<int, 3>> pq;
    for (int i = 1; i <= n; i++) if (s[i] == '1'){
        dp[i] = {0, i};
        pq.push({0, i, i});
    }
    
    int ans = 0;
    
    auto try_merge = [&](int u, int v, int w){
       // cout << "MERGING " << u << " " << v << " " << w << "\n";
        if (uf.unite(u, v)){
            ans += w;
           // cout << "DONE\n";
        }  
    };
    
    vector <array<int, 3>> ab;
    
    while (!pq.empty()){
        auto pi = pq.top(); pq.pop();
        
        int ds = -pi[0];
        int u = pi[1];
        int who = pi[2];
        
      //  cout << "NODE " << u << "\n";
        
        if (dp[u][0] != ds || dp[u][1] != who) continue;
        
        for (int v : adj[u]){
            // try to merge with current distance 
            if (dp[v][1] != -1){
             //   cout << "GOT " << v << " " << ds << " " << dp[v][0] << "\n";
                // try_merge(who, dp[v][1], ds + dp[v][0] + 1);
                ab.push_back({ds + dp[v][0] + 1, who, dp[v][1]});
            }
            int nds = ds + 1;
            if (dp[v][0] > nds){
                dp[v][0] = nds;
                dp[v][1] = who;
                pq.push({-nds, v, who});
            }
        }
    }
    
    sort(ab.begin(), ab.end());
    for (auto &x : ab){
        try_merge(x[1], x[2], x[0]);
    }
    
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