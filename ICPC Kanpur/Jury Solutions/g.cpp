#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

struct SparseTable{
    int n, l;
    vector<vector<int>> sp;

    inline int combine(int x, int y){
        // fill this in
        return max(x, y);
    }

    inline void init(int nn, vector <int> v){
        n = nn;
        if (v.size() == n){
            vector <int> v2;
            v2.push_back(0);
            for (auto x : v) v2.push_back(x);
            v = v2;
        }

        l = 0;
        while ((1 << l) <= n){
            l++;
        }
        sp = vector<vector<int>>(l, vector<int>(n + 1));

        for (int i = 1; i <= n; i++){
            sp[0][i] = v[i];
        }

        for (int j = 1; j < l; j++){
            for (int i = 1; i <= n; i++){
                int who = i + (1 << (j - 1));
                if (who <= n)
                sp[j][i] = combine(sp[j - 1][i], sp[j - 1][who]);
            }
        }
    }

    inline int query(int l, int r){
        int i = log2(r - l + 1);
        int v = combine(sp[i][l], sp[i][r + 1 - (1 << i)]);
        return v;
    }
};

void Solve() 
{
    int n, q; cin >> n >> q;
    string s; cin >> s;
    
    vector <int> p(n + 1, 0);
    for (int i = 1; i <= n; i++){
        p[i] = p[i - 1];
        if (s[i - 1] == 'A') p[i]++;
        else p[i]--;
    }
    
    SparseTable st;
    st.init(n, p);
    
    while (q--){
        int l, r; cin >> l >> r;
        
        int sum = p[r] - p[l - 1];
        int max_prefix = st.query(l, r) - p[l - 1];
        if (sum + (r - l + 1) == 0){
            cout << -1 << "\n";
            continue;
        }
        
        int ans = 0;
        
        // ensure prefix sum becomes > 0, then we can abuse majority to change 2 
        if (max_prefix < 1){
            int use = 1 - max_prefix;
            ans += use;
            sum += use;
        }
        
        if (sum <= 0){
            int use = 1 - sum;
            use = (use + 1) / 2;
            ans += use;
        }
        
        cout << ans << "\n";
    }
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