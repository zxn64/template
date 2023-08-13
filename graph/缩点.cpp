void tarjan(int u) {
	dfn[u] = low[u] = ++tim;
	st[++cnt] = u; in[u] = 1;
	FOR() {
		int v = e[u][i];
		if(!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u],low[v]);
		}
		else if(in[v]) low[u] = min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]) {
		tot++;
		while(1) {
			int v = st[cnt--]; in[v] = 0;
			belong[v] = tot;
			if(v==u) break;
		}
	}
}