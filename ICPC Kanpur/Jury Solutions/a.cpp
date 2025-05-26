#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

map <string, string> memo;

string solve(string a){
    if (memo.find(a) != memo.end()){
        return memo[a];
    }
    int n = a.size();
    string ans = a;
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++) if (a[i] != a[j]){
            string b = "";
            for (int k = 0; k < n; k++) if (k != i && k != j){
                b += a[k];
            }
            
            int m = b.size();
            char ch = (char)('A' + 'B' + 'C' - a[i] - a[j]);
            for (int k = 0; k <= m; k++){
                string c = "";
                for (int l = 0; l < k; l++){
                    c += b[l];
                }
                c += ch;
                for (int l = k; l < m; l++){
                    c += b[l];
                }
                
                ans = min(ans, solve(c));
            }
        }
    }
    
    memo[a] = ans;
    return ans;
}

string fast(string s){
    bool alleq = true;
    int n = s.size();
    for (int i = 1; i < n; i++) if (s[i] != s[i - 1]){
        alleq = false;
    }
    
    if (alleq) return s;
    
    int sum = 0;
    for (auto x : s){
        sum += x != 'A';
    }
    
    if (sum % 2 == 0){
        int sum1 = 0;
        for (auto x : s){
            sum1 += x != 'C';
        }
        
        if (sum1 % 2 == 0){
            return "AA";
        } else {
            return "A";
        }
    }
    
    // delete all B and C's except at most 1 
    // in middle is always bad? 
    // true!
    // what about ABA 
    // converts to AC which is worse, so special case when 2nd last? 
    // BC => generate A 
    // BB delete => constant but shift A 
    // CC delete => constant but shift A 
    // if still not in side, must use one operation 
    // what if deleting BC is not optimal because it forces us to delete the last 
    
    vector <int> f(3, 0);
    for (auto x : s){
        f[x - 'A']++;
    }
    
    vector <int> g(3, 0);
    
    int use = min(f[1], f[2]);
    string t = "";
    for (auto x : s){
        if (x == 'A'){
            t += "A";
            continue;
        }
        
        g[x - 'A']++;
        if (g[x - 'A'] > use){
            t += x;
        }
    }
    
    string w = "";
    for (int i = 0; i < use; i++){
        w += "A";
    }
    
    t = w + t;
    s = t;
    
    {
        int shift = 0;
        int count = 0;
        for (auto x : s){
            count += x != 'A';
        }
        
        count /= 2;
        shift = count;
        n = s.size();
        
        string p = "";
        int last = -1;
        for (int i = 0; i < n; i++){
            if (s[i] != 'A'){
                last = i;
            }
        }
        
        deque <char> yo;
        for (int i = 0; i < n; i++){
            if (s[i] == 'A' || i == last){
                yo.push_back(s[i]);
            }
        }
        
        while (shift-- && yo.back() == 'A'){
            yo.pop_back();
            yo.push_front('A');
        }
        
        string l = "";
        for (auto x : yo){
            l += x;
        }
        
        s = l;
    }
    
    // have one extra C or B 
    int pos = -1;
    n = s.size();
    for (int i = 0; i < n; i++){
        if (s[i] != 'A'){
            pos = i;
        }
    }
    
    assert(pos != -1);
    if (pos == n - 1 || (pos == n - 2 && s[pos] == 'B')){
        return s;
    }
    
    string p = "";
    for (int i = 0; i < n - 2; i++){
        p += "A";
    }
    
    char oth = (char)('B' + 'C' - s[pos]);
    p += oth;
    return p;
}

void Solve() 
{
    // for (int i = 1; i <= 10000; i++){
    //     int n = 1 + RNG() % 10;
    //     string s;
    //     for (int i = 0; i < n; i++){
    //         s += (char)('A' + RNG() % 3);
    //     }
        
    //     string ok = fast(s);
    //     string ans = solve(s);
    //     if (ok != ans && ok != "D"){
    //         cout << "ERROR\n";
    //         cout << s << "\n";
    //         cout << ok << " " << ans << "\n";
    //         exit(0);
    //     }
    // }
    
    int n; cin >> n;
    string s; cin >> s;
    
    cout << fast(s) << "\n";
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