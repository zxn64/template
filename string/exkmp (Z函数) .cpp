#include <bit/stdc++.h>
using namespace std;
const int N=2001010;

int n1,m,n;
char s[N<<1],z[N];
int nxt[N<<1];
ll ans;

void input() {
    scanf("%s",z); m = strlen(z); //start from 0
    scanf("%s",s); n1 = strlen(s); s[n1] = '#';
    memcpy(s+n1+1,z,m);
    n = strlen(s);

    //string s,z;
    //cin>>z>>s; n1 = s.size(); s += '#';
    //s += z; n = s.size();
}

void exkmp() {
    nxt[0] = n1;
    for(int i=1,j=0;i<=n;i++) {
        if(j+nxt[j]>i) nxt[i] = min(nxt[i-j], j+nxt[j]-i);
        while(i+nxt[i]<n && s[nxt[i]]==s[i+nxt[i]]) nxt[i]++;
        if(i+nxt[i]>j+nxt[j]) j = i;
    }
    // for(int i=0;i<n;i++) cout<<nxt[i]<<" ";
}

int main() {
    input();
    exkmp();
    return 0;
}
