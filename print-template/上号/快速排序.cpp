void quick_sort(ll* nn, ll l, ll r) {
    if(l >= r)  return;
    ll i = l, j = r;
    ll x = nn[(l+r)/2];
    while (i <= j) {
        while (nn[j] > x)  j--;
        while (nn[i] < x)  i++;
        if(i <= j)  swap(nn[i++], nn[j--]);
    }
    quick_sort(nn, l, j); quick_sort(nn, i, r);
}