int dis[MN];
void Bellman_Ford(int ss) {
    memset(dis, 0x3f, sizeof(dis)); dis[ss] = 0;
    _fora (iia, 1, n-1) { int flag = 1;
        _fora (x, 1, n) { _fore (i, x) {
            int y = edge[i].too, z = dis[x] + edge[i].len;
            if(dis[y] > z)
                dis[y] = z, flag = 0;
        } }  if(flag) return;
    }
}