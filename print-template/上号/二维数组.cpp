template <class T>
struct VV {
	int x, y;
	vector<T> m;
	VV(int a, int b, const T &v = T())
		: x(a), y(b), m(x * y, v) {}
	auto operator[](int i) /* const */ {
		return m.begin() + i * y;
	}
};
