int T;
int n,m;
int ans = inf, a[N];
int dis[N][N];
int belong[N],vis[N],w[N];

void SW() {  //已知无向图两两距离dis即可使用
    for(int h=n;h>=2;h--) {
        memset(vis,0,sizeof(vis));
        memset(w,0,sizeof(w));
        int t = 0, s = 0;
        for(int i=1;i<=h;i++) {
            s = t; t = 0;
            for(int j=1;j<=n;j++) {
                if(!belong[j] && !vis[j] && w[j]>=w[t]) t = j;
            }
            vis[t] = 1;
            for(int j=1;j<=n;j++) {
                if(!belong[j] && !vis[j]) w[j] += dis[t][j];
            }
        }
        belong[t] = s;
        ans = min(ans,w[t]);
        for(int j=1;j<=n;j++) {
            dis[s][j] += dis[t][j];
            dis[j][s] += dis[j][t];
        }
    }
}