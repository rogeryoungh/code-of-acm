template <class T, class Comp = std::less<T>>
auto sliding(const vector<T> &v, int k) {
	int l = 0, r = -1, n = v.size();
	vector<int> q(n), ret(n);
	for (int i = 0; i < n; i++) {
		while (l <= r && i - k >= q[l])
			l++;
		while (l <= r && Comp()(v[i], v[q[r]]))
			r--;
		q[++r] = i;
		ret[i] = q[l];
	}
	return ret;
}
