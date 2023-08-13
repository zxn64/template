bool DFS(int u) {
	for(int i=1;i<=m;i++) {
		if(!lnk[u][i] || vis[i]) continue;
		vis[i] = 1;
		if(!mp[i] || DFS(mp[i])) { mp[i] = u; return 1; }
	}
	return 0;
}

for(int i=1;i<=n;i++) {
	for(int j=1;j<=m;j++) vis[j] = 0;
	ans += DFS(i);
}