#include<bits/stdc++.h>
using namespace std;
#define add(x,y) (x + y >= mod ? x + y - mod : x + y)
#define dec(x,y) (x - y < 0 ? x - y + mod : x - y)
#define chk(x) (x>=mod ? x - mod : x)
typedef long long ll;
const int maxn = 5e5+114514;
const int p = 998244353, gg = 3, ig = 332738118;
const int mod = 998244353;
template <typename T> void read(T &x)
{
    x = 0;
    T f = 1;
    char ch = getchar();
    for(;!isdigit(ch);ch=getchar())f=-1;
    for(; isdigit(ch);ch=getchar())x=x*10+(ch-48);
    x *= f;
}
int qpow(int x,int y)
{
    int res = 1;
    for(;y;y>>=1)
    {
        if(y&1)res = 1ll * res * x % mod;
        x = 1ll * x * x % mod;
    }
    return res;
}
namespace Poly
{
    typedef vector<int> poly;
    const int G = 3;
    const int inv_G = qpow(G, mod - 2);
    int RR[maxn], deer[2][22][maxn],inv[maxn];
    void init(const int t)//预处理Wn
    {
        for(int p=1;p<=t;++p)
        {
            int buf1 = qpow(G,(mod-1)/(1<<p));
            int buf0 = qpow(inv_G,(mod-1)/(1<<p));
            deer[0][p][0] = deer[1][p][0] = 1;
            for(int i=1;i<(1<<p);++i)
            {
                deer[0][p][i] = 1ll * deer[0][p][i-1] * buf0 % mod;
                deer[1][p][i] = 1ll * deer[1][p][i-1] * buf1 % mod;
            }
        }
        inv[1] = 1;
        for(int i=2;i<=(1<<t);++i)
            inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
    }
    int NTT_init(int n)
    {
        int limit = 1,len = 0;
        while(limit < n)
        {
            limit <<= 1;
            ++len;
        }
        for(int i=0;i<limit;++i)
            RR[i] = (RR[i>>1]>>1) | ((i&1) << (len - 1));
        return limit;
    }
    void NTT(poly &A,int type,int limit)
    {
        A.resize(limit);
        for(int i=0;i<limit;++i)
            if(i<RR[i])
                swap(A[i],A[RR[i]]);
        for(int mid=2,j=1;mid<=limit;mid<<=1,++j)
        {
            int len = mid >> 1;
            for(int pos = 0;pos < limit; pos += mid)
            {
                int *wn = deer[type][j];
                for(int i=pos;i<pos+len;++i,++wn)
                {
                    int tmp = 1ll * (*wn) * A[i + len] % mod;
                    A[i + len] = chk(A[i] - tmp + mod);
                    A[i] = chk(A[i] + tmp);
                }
            }
        }
        if(type == 0)
        {
            int inv_limit = qpow(limit,mod - 2);
            for(int i = 0;i < limit; ++i)
                A[i] = 1ll * A[i] * inv_limit % mod;
        }
    }
    poly poly_mul(poly &A,poly &B)
    {
        int deg = A.size() + B.size() - 1;
        int limit = NTT_init(deg);
        poly C(limit);
        NTT(A, 1, limit);
        NTT(B, 1, limit);
        for(ll i = 0;i < limit; ++i)
            C[i] = 1ll * A[i] * B[i] % mod;
        NTT(C,0,limit);
        C.resize(deg);
        return C;
    }
    void poly_inv(const poly &A,poly &res,int len)
    {
        if(len == 1)
        {
            res.resize(1);
            res[0] = qpow(A[0],mod - 2);
            return;
        }
        poly_inv(A,res,(len+1)>>1);
        int limit = NTT_init(len<<1);
        poly tmp(limit);
        res.resize(limit);
        for(int i=0;i<len;++i)
            tmp[i] = A[i];
        NTT(tmp,1,limit);
        NTT(res,1,limit);
        for(int i=0;i<limit;++i)
            res[i] = 1ll * res[i] * dec(2ll, 1ll * tmp[i] * res[i] % mod) % mod;
        NTT(res,0,limit);
        res.resize(len);
    }
    void derivative(const poly &A,poly &res,int len)
    {
        res.resize(len);
        for(int i=1;i<len;++i)
            res[i-1] = 1ll * i * A[i] % mod;
        res[len-1] = 0;
    }
    void integral(const poly &A,poly &res,int len)
    {
        res.resize(len);
        for(int i=1;i<len;++i)
            res[i] = 1ll * A[i-1] * qpow(i, mod - 2) % mod;
        res[0] = 0;
    }
    void poly_ln(const poly &A,poly &res,int len)
    {
        poly tmp;
        derivative(A,res,len);
        poly_inv(A,tmp,len);
        tmp = Poly::poly_mul(res, tmp);
        integral(tmp,res,len);
    }
}
using Poly::poly;
using Poly::poly_mul;
const int N = 214514;
int val[N],cnt[N],cnt1[N];
int coe[N];
int main()
{
    Poly::init(20);
    ios::sync_with_stdio(false);
    int n,k;
    poly f;
    cin>>n;
    for(int i=0;i<n-1;++i)
    {
        int x;
        cin>>x;
        f.push_back(x);
    }
    poly g;
    for(int i=0;i<n;++i)
        cout<<g[i]<<" ";
    return 0;
}


