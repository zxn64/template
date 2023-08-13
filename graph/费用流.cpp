inline void add(int u,int v,int w,int z) {
	e[++cnt] = (E){ v,head[u],w,z };  head[u] = cnt;
	e[++cnt] = (E){ u,head[v],0,-z }; head[v] = cnt;
}

bool SPFA() {
	memset(dep,0x3f,sizeof(dep));
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++) cur[i] = head[i];
	dep[s] = 0; q.push(s);
	while(!q.empty()) {
		int u = q.front(); q.pop(); vis[u] = 0;
		for(int i=head[u]; i; i=e[i].nxt) {
			int v = e[i].to, w = e[i].we;
			if(e[i].cap && dep[v] > dep[u]+w) {
				dep[v] = dep[u]+w;
				if(vis[v]) continue;
				q.push(v); vis[v] = 1;
			}
		}
	}
	return dep[t] != inf;
}

int DFS(int u,int flow) {
	int res = 0, f;
	if(u==t || !flow) return flow;
	vis[u] = 1;
	for(int i=cur[u]; i; i=e[i].nxt) {
		cur[u] = i;
		int v = e[i].to, w = e[i].we;
		if(vis[v]) continue;
		if(e[i].cap && dep[v]==dep[u]+w) {
			f = DFS( v, min(e[i].cap,flow-res) );
			if(f) {
				res += f;
				e[i].cap -= f;
				e[i^1].cap += f;
				mincost += f * w;
				if(res==flow) break;
			}
		}
	}
	return res;
}