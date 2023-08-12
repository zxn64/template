#include <bits/stdc++.h>
using namespace std;
const int N=2010101;

int nn,n,m,lst=1,cnt=1;
int cl[N];
char s[N],z[N];
int fa[N],ch[N][26],len[N];
ll ans;

inline int insert(int c) {
	int u = lst;
	if(ch[u][c]) {
		int v = ch[u][c];
		if(len[v]==len[u]+1) return v;
		int w = ++cnt; len[w] = len[u] + 1;
		memcpy(ch[w],ch[v],sizeof ch[v]);
		fa[w] = fa[v]; fa[v] = w;
		for(; ch[u][c]==v && u; u=fa[u]) ch[u][c] = w;
		return w;
	}
	int cur = ++cnt; len[cur] = len[u] + 1;
	for(; !ch[u][c] && u; u=fa[u]) ch[u][c] = cur;
	if(!u) fa[cur] = 1;
	else {
		int v = ch[u][c];
		if(len[v]==len[u]+1) fa[cur] = v;
		else {
			int w = ++cnt; len[w] = len[u] + 1;
			memcpy(ch[w],ch[v],sizeof ch[v]);
			fa[w] = fa[v]; fa[v] = fa[cur] = w;
			for(; ch[u][c]==v && u; u=fa[u]) ch[u][c] = w;
		}
	}
	return cur;
}

int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%s",s); int le = strlen(s); lst = 1;
		for(int j=0;j<le;j++) lst = insert(s[j]-'a');
	}
	return 0;
}
