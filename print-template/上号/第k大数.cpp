ll q_sort(ll* nn, ll l, ll r) {
    ll i = l, j = r, x = nn[(l+r)/2];
    while (i <= j) {
        while (nn[j] > x) j--;
        while (nn[i] < x) i++;
        if (i <= j) swap(nn[i++], nn[j--]);
    } // l <= j <= i <= r
    if (k <= j) return q_sort(l, j);
    else if (k >= i) return q_sort(i, r);
    else return nn[k + 1];
}