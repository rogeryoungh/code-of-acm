ll h = 1, t = 0;
for (int i = 1; i <= n; i++) {
    while (h <= t && i + 1 - k > qq[h])
        h++;
    while (h <= t && aa[i] <= aa[qq[t]]) // aa[i] >= aa[qq[t]]
        t--;
    qq[++t] = i;
    if (i >= k) {
        printf("%lld ", aa[qq[h]]);
    }
}