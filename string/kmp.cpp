#include <bits/stdc++.h>
using namespace std;
const int N=1001010;

int n1,m,n;
char s[N<<1],z[N];
int nxt[N<<1];

void input() {
    scanf("%s",z+1); m = strlen(z+1);  //start from 1
    scanf("%s",s+1); n1 = strlen(s+1); s[n1+1] = '#';
    memcpy(s+n1+2,z+1,m);
    n = strlen(s+1);
}

void kmp() {
    for(int i=2,j=0;i<=n;i++) {
        while(j && s[i]!=s[j+1]) j = nxt[j];
        if(s[i]==s[j+1]) j++;
        nxt[i] = j;
    }
}

int main() {
    input();
    kmp();
    // for(int i=1;i<=n;i++) cout<<nxt[i]<<" ";
    return 0;
}
