int n,m,s,t;
struct E{
	int to,nxt,cap;
}e[qwq];
int cnt = 1;
int head[N],cur[N];
int dep[N],vis[N];
queue <int> q;

inline bool SPFA() {
	memset(dep,0x3f,sizeof(dep));
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++) cur[i] = head[i];
	int now = dep[1]; q.push(s);
	dep[s] = 0;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		vis[u] = 0;
		for(int i=head[u]; i; i=e[i].nxt) {
			int v = e[i].to;
			if(dep[v] > dep[u] + 1 && e[i].cap) {
				dep[v] = dep[u] + 1;
				if(vis[v]) continue;
				q.push(v);
				vis[v] = 1;
			}
		}
	}
	if(dep[t] == now) return 0;
	return 1;
}

int DFS(int u,int flow) {
	int res = 0, f;
	if(u==t || !flow) return flow;
	for(int i=cur[u]; i; i=e[i].nxt) {
		cur[u] = i;
		int v = e[i].to;
		if(e[i].cap && (dep[v] == dep[u]+1)) {
			f = DFS(v,min(flow-res,e[i].cap));
			if(f) {
				res += f;
				e[i].cap -= f;
				e[i^1].cap += f;
				if(res==flow) break;
			}
		}
	}
	return res;
}