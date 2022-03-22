const int MN = 10005; int head[MN];
struct Edge { int too,nxt,len; } edge[MN*2];
void add(int frm, int too, int len) {
    static int cnt = 0;
    edge[++cnt] = { too, head[frm], len };
    head[frm] = cnt;
}
void dfs(int x,int fa) {
    _fore(i,x)  if(edge[i].too != fa)
        dfs(edge[i].too,x);
}
