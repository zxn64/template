//
//Pollard-Rho LUOGU P4178
//
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll ans,n;
const vector<ll> bases = {2,3,5,7,11,13,19,61,2333,24251};
ll gcd(ll a,ll b)
{
    if(!b)
        return a;
    return gcd(b, a % b);
}
ll qpow(ll x,ll y,ll mod)
{
    ll ret = 1;
    for(;y;y>>=1){
        if(y&1) ret = (__int128)ret * x % mod;
        x = (__int128)x * x % mod;
    }
    return ret;
}
bool Miller_Rabin(ll p)
{
    if(p < 2 || p == 46856248255981ll) return false;
    if(p==2 || p==3 || p==7 || p==61 || p==24251) return true;
    ll d = p - 1, r = 0;
    while(d % 2 == 0)d >>= 1, ++ r;
    for(ll a : bases){
        a = a % (p - 2) + 2;
        ll v = qpow(a, d, p);
        if(v == 1 || v == p - 1) continue;
        for(ll s = 0; s < r - 1; ++s){
            v = (__int128)v * v % p;
            if(v == p - 1)break;
        }
        if(v != p - 1)return false;
    }
    return true;
}
ll pollardRho(ll x)
{
    ll s = 0, t = 0;
    ll c = (ll)rand() % (x - 1) + 1;
    ll val = 1;
    for(int k=1;;k<<=1,s=t,val=1) {
        //cout<<k<<" "<<x<<endl;
        for (int i = 1; i <= k; ++i) {
            t = ((__int128) t * t + c) % x;
            val = (__int128) val * abs(t - s) % x;
            if (t % 128 == 0) {
                ll d = gcd(val, x);
                if (d > 1) return d;
            }
        }
        ll d= gcd(val, x);
        if(d>1)return d;
    }
}
ll fac(ll x)
{
    if(x <= ans || x < 2) return ans;
    if(Miller_Rabin(x))
        return ans = max(ans, x);
    ll p = x;
    while(p >= x)p = pollardRho(x);
    while((x % p) == 0)x /= p;
    fac(x);
    fac(p);
}
int main()
{
    ios::sync_with_stdio(false);
    ll T,n;
    cin>>T;
    while(T--){
        srand(time(NULL));
        ans = 0;
        cin>>n;
        fac(n);
        if(ans == n) cout<<"Prime\n";
        else cout<<ans<<"\n";
    }
    return 0;
}