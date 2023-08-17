#include <bits/stdc++.h>
#define ll long long
#define ls L[now]
#define rs R[now]
const int N=1010101;

int n,m;
int a[N],rt[N],tot;
int t[N*33], L[N*33], R[N*33];

inline void pushup(int now) { t[now] = t[ls] + t[rs]; }
int built(int now,int l,int r) {
	now = ++tot;
	if(l==r) { t[now] = a[l]; return now; }
	int mid = l+r >> 1;
	ls = built(ls, l, mid);
	rs = built(rs, mid+1, r);
	pushup(now); return now;
}

int insert(int now,int pre,int l,int r,int we,int g) {
	now = ++tot;
	ls = L[pre]; rs = R[pre];
	if(l==r) { t[now] = g; return now; }
	int mid = l+r >> 1;
	if(we<=mid) ls = insert(ls, L[pre], l, mid, we, g);
	else        rs = insert(rs, R[pre], mid+1, r, we, g);
	pushup(now); return now;
}

int query(int now,int l,int r,int x,int y) {
	if(x<=l && r<=y) return t[now];
	int mid = l+r >> 1, res = 0;
	if(x<=mid) res += query(ls, l, mid, x, y);
	if(y>mid)  res += query(rs, mid+1, r, x, y);
	return res;
}

//  rt[0] = built(rt[0],1,n);