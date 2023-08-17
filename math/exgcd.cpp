#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define FOR() int le=e[u].size();for(int i=0;i<le;i++)
#define QWQ cout<<"QwQ\n";
#define ll long long
#include <vector>
#include <queue>
#include <map>

using namespace std;
const int N=501010;
const int qwq=303030;
const int inf=0x3f3f3f3f;

int X,Y;

int _exgcd(int A,int B) {
    if(!B) { X = Y = 0; return A; }
    int res = _exgcd(B,A%B);
    X = Y; Y = (res - A*X) / B;
    return res;
}

int exgcd(int A,int B) {
    if(!B) { X=1; Y=0; return A; }
    int res = exgcd(B,A%B);
    int t = X; X = Y; Y = t-A/B*Y;
    return res;
}

int main() {
    int a,b;
    cin>>a>>b;
    int d = exgcd(a,b);
    cout<<a<<"*"<<X<<" + "<<b<<"*"<<Y<<" = "<<d<<"\n";
    return 0;
}
