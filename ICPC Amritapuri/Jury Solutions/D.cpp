#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

map <string, int> memo;

int slow(string s){
    if (memo.find(s) != memo.end()) return memo[s];
    
    int ans = s.size();
    for (int i = 1; i + 1 < s.size(); i++){
        if (s[i - 1] == s[i + 1]){
            string t = "";
            for (int j = 0; j < s.size(); j++){
                if (j != i){
                    t += s[j];
                }
            }
            
            ans = min(ans, slow(t));
        }
    }
    
    memo[s] = ans;
    return ans;
}

int fast(string s){
    int n = s.size();
    if (n == 1){
        return 1;
    }
    for (int i = 1; i < n; i++){
        if (s[i] == s[i - 1]){
            break;
        }
        
        if (i + 1 == n){
            if (n <= 2) return n;
            if (n % 2 == 1){
                return 2;
            }
            return 3;
        }
    }
    
    int runs = 0;
    int last = -1;
    for (int i = 0; i < n; i++){
        int j = i;
        while (j + 1 < n && s[j + 1] == s[i]){
            j++;
        }
        
        if (j > i){
            if (s[j] != last){
                runs++;
                last = s[j];
            }
        }
        
        i = j;
    }
    
    int ans = 2 * runs;
    if (s[0] != s[1]){
        int p = 0;
        while (s[p] != s[p + 1]){
            p++;
        }
        
        if (s[p] != s[0]){
            ans++;
        }
    }
    
    if (s[n - 1] != s[n - 2]){
        int p = n - 1;
        while (s[p] != s[p - 1]){
            p--;
        }
        
        if (s[p] != s[n - 1]){
            ans++;
        }
    }
    
    return ans;
}

void Solve() 
{
    int n; cin >> n;
    string s; cin >> s;
    
    cout << fast(s) << "\n";
    
    // int n = 1 + RNG() % 10;
    // string s = "";
    // for (int i = 0; i < n; i++){
    //     s += (char)('0' + RNG() % 2);
    // }
    
    // int ans = fast(s);
    // int brute = slow(s);
    
    // if (ans != brute){
    //     cout << "WA\n";
    //     cout << s << "\n";
    //     cout << ans << " " << brute << "\n";
    //     exit(0);
    // }
    
    // cout << ans << "\n";
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