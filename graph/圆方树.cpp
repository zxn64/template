void tarjan(int u) {
	dfn[u] = low[u] = ++tim;
	st[++cnt] = u;
	FOR() {
		int v = e[u][i];
		if(!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u],low[v]);
			if(low[v]==dfn[u]) {
				++tot;
				while(1) {
					int now = st[cnt--];
					d[tot].push_back(now); d[now].push_back(tot);
					if(now==v) break;
				}
				d[tot].push_back(u);
				d[u].push_back(tot);
			}
		}
		else low[u] = min(low[u],dfn[v]);
	}
}

//u>n 方点 siz==2为割边
//u<=n 圆点 siz>=2为割点