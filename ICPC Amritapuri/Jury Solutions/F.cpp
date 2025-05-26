#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

void Solve() 
{
    int n, m; cin >> n >> m;
    
    vector<vector<int>> a(n, vector<int>(m));
    for (auto &x : a){
        for (auto &y : x){
            cin >> y;
        }
    }
    
    for (auto &x : a){
        for (auto &y : x){
            int z;  cin >> z;
            y ^= z;
        }
    }
    
    if (n == 2 && m == 2){
        int sum = 0;
        for (auto x : a) for (auto y : x){
            sum += y;
        }
        
        if (sum >= 1 && sum <= 3){
            cout << -1 << "\n";
            return;
        }
        
        if (sum == 4){
            cout << "1\n";
            cout << 4 << "\n";
            cout << "1 1 1 2 2 2 2 1\n";
        } else {
            cout << 0 << '\n';
        }
        return;
    } 
    
    vector<vector<int>> ans;
    
    auto work = [&](vector <int> v){
        ans.push_back(v);
        
        int k = (int)v.size() / 2;
        for (int i = 0; i < k; i++){
            int x = v[2 * i];
            int y = v[2 * i + 1];
            
            a[x][y] ^= 1;
        }
    };
    
    if (n == 2){
        for (int i = 0; i < m; i++){
            if (a[0][i] != a[1][i]){
                cout << -1 << "\n";
                return;
            }
        }
        
        for (int i = 0; i < m; i++){
            if (a[0][i] == 1){
                if (i + 1 == m){
                    work({0, i, 0, i - 1, 0, i - 2, 1, i - 2, 1, i - 1, 1, i});
                    work({0, i - 1, 0, i - 2, 1, i - 2, 1, i - 1});
                } else {
                    work({0, i, 0, i + 1, 1, i + 1, 1, i});
                }
            }
        }
    } else if (m == 2){
        for (int i = 0; i < n; i++){
            if (a[i][0] != a[i][1]){
                cout << -1 << "\n";
                return;
            }
        }
        
        for (int i = 0; i < n; i++){
            if (a[i][0] == 1){
                if (i + 1 == n){
                    work({i, 0, i - 1, 0, i - 2, 0, i - 2, 1, i - 1, 1, i, 1});
                    work({i - 1, 0, i - 2, 0, i - 2, 1, i - 1, 1});
                } else {
                    work({i, 0, i + 1, 0, i + 1, 1, i, 1});
                }
            }
        }
    } else {
        int sum = 0;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                sum += a[i][j];
            }
        }
        
        if (sum % 2 == 1){
            cout << -1 << "\n";
            return;
        }
        
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                if (a[i][j] == 1){
                    if (j + 1 != m){
                        // swap it with next 
                        if (i + 1 != n){
                            work({i, j, i, j + 1, i + 1, j + 1, i + 1, j});
                        } else {
                            work({i, j, i, j + 1, i - 1, j + 1, i - 2, j + 1, i - 2, j, i - 1, j});
                            work({i - 1, j + 1, i - 2, j + 1, i - 2, j, i - 1, j});
                        }
                    } else {
                        work({i, j - 2, i, j - 1, i, j, i + 1, j, i + 1, j - 1, i + 1, j - 2});
                        work({i, j - 2, i, j - 1, i + 1, j - 1, i + 1, j - 2});
                    }
                }
            }
        }
    }
    
    cout << ans.size() << "\n";
    
    for (auto x : ans){
        int sz = x.size();
        cout << (sz / 2) << "\n";
        for (auto y : x){
            cout << (y + 1) << " ";
        }
        cout << "\n";
    }
    
    for (auto x : a){
        for (auto y : x){
            if (y){
                cout << "NOOB\n";
                return;
            }
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