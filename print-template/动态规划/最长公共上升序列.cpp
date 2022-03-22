int f[MN], ma[MN], b[MN], n, len = 0;
memset(f, 0x3f, sizeof(f));  f[0] = 0;
for (int i = 1; i <= n; i++)  ma[rr()] = i;
for (int i = 1; i <= n; i++)  b[i] = rr();
for (int i = 1; i <= n; i++) {
    int l = 0,r = len;
    if (ma[b[i]] > f[len])
        f[++len] = ma[b[i]];
    else {
        while (l < r) {
            int mid = (l + r) / 2;
            if (f[mid] > ma[b[i]])  r = mid;
            else  l = mid+1;
        }
    }
    f[l] = min(ma[b[i]], f[l]);
}
