#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

struct FenwickTree{
    int n;
    vector <int> f;
    vector <int> b;

    inline void add(int i, int x){
        b[i] += x;
        for (int j = i; j <= n; j += j & (-j)){
            f[j] += x;
        }
    }

    inline void modify(int i, int x){
        add(i, x - b[i]);
    }

    inline void init(int nn, vector <int> a){
        n = nn;
        if (a.size() == n){
            vector <int> a2;
            a2.push_back(0);
            for (auto x : a) a2.push_back(x);
            a = a2;
        }

        f.resize(n + 1);
        b.resize(n + 1);

        for (int i = 0; i <= n; i++) f[i] = 0, b[i] = 0;

        for (int i = 1; i <= n; i++){
            modify(i, a[i]);
        }
    }

    inline int query(int x){
        int ans = 0;
        for (int i = x; i; i -= i & (-i)){
            ans += f[i];
        }
        return ans;
    }

    inline int query(int l, int r){
        return query(r) - query(l - 1);
    }
};

void Solve() 
{
    int n; cin >> n;
    
    vector <int> last(n + 1, 0);
    vector <int> add(n + 1, 0);
    
    FenwickTree fen;
    vector <int> vv(n);
    fen.init(n, vv);
    
    int sum = n;
    
    for (int i = 1; i <= n; i++){
        int x; cin >> x;
        
        int v = last[x];
        
        if (v == 0){
            last[x] = i;
            fen.add(i, +1);
            sum++;
            continue;
        }
        int g = fen.query(v + 1, i);
        add[g]++;
        
        fen.add(v, -1);
        fen.add(i, +1);
        last[x] = i;
    }
    
    vector <int> ans(n + 1);
    for (int i = n; i >= 1; i--){
        sum += add[i];
        ans[i] = sum;
    }
    
    for (int i = 1; i <= n; i++){
        cout << ans[i] << " \n"[i == n];
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