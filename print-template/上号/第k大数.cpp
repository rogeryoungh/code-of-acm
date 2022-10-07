template <class iter>
void kth_sort(iter first, iter pos, iter last) {
	auto l = first, r = last - 1;
	if (l >= r)  return;
	auto x = *(l + (r - l) / 2);
	while (l <= r) {
		while (*l < x)  l++;
		while (*r > x)  r--;
		if (l <= r)     swap(*l++, *r--);
	} // first <= r <= l <= last
	if (pos <= r)
		kth_sort(first, pos, r + 1);
	else if (pos >= l)
		kth_sort(l, pos, last);
}
