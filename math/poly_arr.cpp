//
// Created by PC on 2023/10/19.
//
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=100005*3;
ll n,f[N],g[N];
namespace Poly{
    const ll P=998244353,G=3;
    ll lmt,rev[N],a[N],b[N],c[N],d[N],e[N];
    inline ll qpow(ll a,ll k){
        ll ret=1;
        while(k){
            if(k&1)ret=ret*a%P;
            a=(a*a)%P;
            k>>=1;
        }
        return ret%P;
    }
    inline void init(ll n){
        lmt=1;ll t=0;
        while(lmt<n)lmt<<=1,t++;
        for(ll i=1;i<lmt;i++)rev[i]=(rev[i>>1]>>1)|(i&1)<<(t-1);
    }
    inline void NTT(ll *A,ll lmt,ll tp){
        for(ll i=0;i<lmt;i++)if(i<rev[i])swap(A[i],A[rev[i]]);
        for(ll m=1;m<lmt;m<<=1)
            for(ll j=0,Wn=qpow(G,(P-1)/(m<<1));j<lmt;j+=m<<1)
                for(ll k=0,w=1,x,y;k<m;k++,w=w*Wn%P)
                    x=A[j+k],y=w*A[j+k+m]%P,A[j+k]=(x+y)%P,A[j+k+m]=(x-y+P)%P;
        if(tp==1)return;
        reverse(A+1,A+lmt);
        for(ll i=0,inv=qpow(lmt,P-2);i<=lmt;i++)A[i]=A[i]*inv%P;
    }
    inline void mul(ll *f,ll *g,ll len){
        init(len);
        NTT(f,lmt,1);NTT(g,lmt,1);
        for(ll i=0;i<lmt;i++)f[i]=(f[i]*g[i])%P;
        NTT(f,lmt,-1);
    }
    void getinv(ll*f,ll*g,ll len){
        if(len==1){g[0]=qpow(f[0],P-2);return;}
        getinv(f,g,len+1>>1);
        init(len<<1);
        for(ll i=0;i<len;i++)c[i]=f[i];
        for(ll i=len;i<lmt;i++)c[i]=0;
        NTT(c,lmt,1),NTT(g,lmt,1);
        for(ll i=0;i<lmt;i++)g[i]=(2LL-g[i]*c[i]%P+P)%P*g[i]%P;
        NTT(g,lmt,-1);
        for(ll i=len;i<lmt;i++)g[i]=0;
    }
    void fzNTT(ll*f,ll*g,ll len)//f_i = \sum_{j=1}^i f_{i-j} g_i f_0 = 1
    {
        g[0] = (1 - g[0] + P) % P;
        for(int i=1;i<len;++i)
            g[i] = P - g[i];
        getinv(g,f,len);
    }
    void getdev(ll*f,ll*g,ll len){
        for(ll i=1;i<len;i++)g[i-1]=i*f[i]%P;
        g[len-1]=0;
    }
    void getinvdev(ll*f,ll*g,ll len){
        for(ll i=1;i<len;i++)g[i]=f[i-1]*qpow(i,P-2)%P;
        g[0]=0;
    }
    void getln(ll*f,ll*g,ll len){
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        getdev(f,a,len);
        getinv(f,b,len);
        mul(a,b,len<<1);
        getinvdev(a,g,len);
    }
    void getexp(ll*f,ll*g,ll len){
        if(len==1){g[0]=1;return;}
        getexp(f,g,len+1>>1);
        init(len<<1);
        for(ll i=0;i<(len<<1);i++)d[i]=e[i]=0;
        getln(g,d,len);
        for(ll i=0;i<len;i++)e[i]=f[i];
        NTT(g,lmt,1),NTT(d,lmt,1),NTT(e,lmt,1);
        for(ll i=0;i<lmt;i++)g[i]=(1-d[i]+e[i]+P)*g[i]%P;
        NTT(g,lmt,-1);
        for(ll i=len;i<lmt;i++)g[i]=0;
    }
}
using Poly::fzNTT;
int main(){
    scanf("%lld",&n);
    //g[0]=1;
    for(ll i=1;i<n;i++)scanf("%lld",&g[i]);
    fzNTT(f,g,n);
    for(ll i=0;i<n;i++)printf("%lld ",f[i]);
    return 0;
}