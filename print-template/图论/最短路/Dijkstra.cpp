int dis[MN];
struct Dis {
    int dis, pos;
    bool operator < (const Dis& x) const
        { return x.dis < dis; }
};
void Dijkstra(int ss) {
    memset(dis, 0x3f, sizeof(dis));
    dis[ss] = 0;
    priority_queue<Dis> pq;  pq.push({0,ss});
    while (!pq.empty()) {
        Dis td = pq.top();  pq.pop();
        int d = td.dis, x = td.pos;
        if (d != dis[x])  continue;
        _fore (i, x) {
            int y = edge[i].too, z = d + edge[i].len;
            if (dis[y] > z)
                dis[y] = z, pq.push({dis[y],y});
        }
    }
}