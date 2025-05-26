#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

void Solve() 
{
    int n; cin >> n;
    
    vector <int> a(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    
    vector <int> nxs(n + 1, n + 1);
    vector <int> pvs(n + 1, 0);
    
    stack <pair<int, int>> st;
    for (int i = 1; i <= n; i++){
        while (!st.empty() && st.top().first > a[i]){
            nxs[st.top().second] = i;
            st.pop();
        }
        
        st.push({a[i], i});
    }
    
    while (!st.empty()) st.pop();
    
    for (int i = n; i >= 1; i--){
        while (!st.empty() && st.top().first >= a[i]){
            pvs[st.top().second] = i;
            st.pop();
        }
        
        st.push({a[i], i});
    }
    
    vector <pair<int, int>> b;
    for (int i = 1; i <= n; i++){
        b.push_back({a[i], i});
    }
    
    sort(b.begin(), b.end());
    int p1 = -1, p2 = -1;
    set <int> mark;
    mark.insert(0);
    mark.insert(n + 1);
    
    int ans = 0;
    
    for (auto pi : b){
        int x = pi.first;
        int i = pi.second;
        while (p2 + 1 < n && b[p2 + 1].first <= 2 * x){
            p2++;
            mark.insert(b[p2].second);
        }
        
        while (p1 + 1 < n && b[p1 + 1].first <= x){
            p1++;
            mark.erase(b[p1].second);
        }
        
        auto id = mark.lower_bound(i);
        int R = *id;
        int L = *(--id);
        
        int l = pvs[i];
        int r = nxs[i];
        
        L = max(L, l);
        R = min(R, r);
        
        int type1 = (i - l) * (r - i);
        int type2 = (i - L) * (R - i);
        type1 -= type2;
        
        ans += type2 * x;
        ans += type1 * ((x - 1) / 2);
    }
    
    // auto slow = [&](vector <int> d){
    //     int mn = *min_element(d.begin(), d.end());
    //     for (auto x : d){
    //         if (x != mn && x <= 2 * mn){
    //             return ((mn - 1) / 2);
    //         }
    //     }
    //     return mn;
    // };
    
    // int brute = 0;
    
    // for (int i = 1; i <= n; i++){
    //     vector <int> d;
    //     for (int j = i; j <= n; j++){
    //         d.push_back(a[j]);
    //         brute += slow(d);
    //     }
    // }
    
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