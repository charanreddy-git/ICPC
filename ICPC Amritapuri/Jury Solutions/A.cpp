#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

void Solve() 
{
    int n; cin >> n;
    
    vector <int> a(3 * n);
    for (auto &x : a) cin >> x;
    int sum = accumulate(a.begin(), a.end(), 0LL);
    
    if (sum % n != 0){
        cout << "No\n";
        return;
    }
    
    sum /= n;
    assert(3 <= sum && sum <= 9);
    
    if (sum == 3 || sum == 9){
        cout << "Yes\n";
        return;
    }
    
    vector <int> f(3, 0);
    for (auto x : a){
        f[x - 1]++;
    }
    
    vector <int> v1, v2;
    if (sum == 4){
        v1 = {2, 1, 0};
        v2 = {0, 0, 0};
    } else if (sum == 8){
        v1 = {0, 1, 2};
        v2 = {0, 0, 0};
    } else if (sum == 5){
        v1 = {2, 0, 1};
        v2 = {1, 2, 0};
    } else if (sum == 7){
        v1 = {1, 0, 2};
        v2 = {0, 2, 1};
    } else {
        v1 = {1, 1, 1};
        v2 = {0, 3, 0};
    }
    
    for (int i = 0; i <= n; i++){
        vector <int> res(3);
        for (int j = 0; j < 3; j++){
            res[j] = i * v1[j] + (n - i) * v2[j];
        }
        
        if (res == f){
            cout << "Yes\n";
            return;
        }
    }
    
    cout << "No" << "\n";
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