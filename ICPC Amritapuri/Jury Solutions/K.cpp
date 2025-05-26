#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(c) ((c).begin()), ((c).end())
#define sz(x) ((int)(x).size())

#ifdef LOCAL
#include <print.h>
#else
#define trace(...)
#define endl '\n' // remove in interactive
#endif


long long inverse(long long a, long long b){
 return 1<a ? b - inverse(b%a,a)*b/a : 1;
}

void solve(){
    ll n, m, q;
    cin >> n >> m >> q;
    // max y * i % M, over i in [L, R]
    function<ll(ll, ll, ll, ll, ll)> get = [&](ll x, ll y, ll L, ll R, ll M){
        assert(L <= R);
        // if(R - L + 1 >= M) return M - 1;
        if(y == 0) return x;
        if(x != 0){
            ll L2 = L + (x * inverse(y, M) % M);
            R = L2 + R - L;
            L = L2;
            x = 0;
        }
        if(2 * y > M){
            ll T = (y * R) % M;
            return get(T, M - y, 0, R - L, M);
        }
        ll ret = max((y * L) % M, (y * R) % M);
        ll P = (y * L) / M, Q = (y * R) / M;
        if(P == Q) return ret;
        ll h = ((-M) % y); if(h < 0) h += y;
        return max(ret, M - y + get(0, h, P + 1, Q, y));
    };
    ll x = 0, y = 0;
    while(q--){
        ll t, a, b; cin >> t>>a >> b;
        if(t==1){
            x += a; x %= m;
            y += b; y %= m;
        } else{
            cout << get(x, y, a-1, b - 1, m) << endl;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL); // Remove in interactive problems
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}