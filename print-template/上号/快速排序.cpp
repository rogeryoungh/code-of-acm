template <class iter>
void quick_sort(iter first, iter last) {
	auto l = first, r = last - 1;
	if (l >= r)  return;
	auto x = *(l + (r - l) / 2);
	while (l <= r) {
		while (*l < x)  l++;
		while (*r > x)  r--;
		if (l <= r)     swap(*l++, *r--);
	}
	quick_sort(first, r + 1);
	quick_sort(l, last);
}
