ll aa[N], tt[N], ans = 0;
void merge_sort(int l, int r) {
	if (r - l <= 1)  return;
	int mid = (l + r) >> 1;
	merge_sort(l, mid);
	merge_sort(mid, r);
	int p = l, q = mid, s = l;
	while (s < r) {
		if (p >= mid || (q < r && aa[p] > aa[q]))
			tt[s++] = aa[q++], ans += mid - p;
		else
			tt[s++] = aa[p++];
	}
	for (int i = l; i < r; i++)
		aa[i] = tt[i];
}