int pa[MN][30], lgb[MN], dep[MN]; // 预处理 lgb
void LCA_dfs(int u, int fa) {
    pa[u][0] = fa, dep[u] = dep[fa] + 1;
    _fora (i, 1, lgb[dep[u]])
        pa[u][i] = pa[pa[u][i-1]][i-1];
    _fore (i, u)  if (edge[i].too != fa)
        lca_dfs(edge[i].too, u);
}
int LCA(int x, int y) {
    if (dep[x] < dep[y])  swap(x,y);
    while (dep[x] > dep[y])
        x = pa[x][lgb[dep[x]-dep[y]]];
    if (x == y)  return x;
    _forz (k, lgb[dep[x]] - 1, 0)
        if (pa[x][k] != pa[y][k])
            x = pa[x][k], y = pa[y][k];
    return pa[x][0];
}