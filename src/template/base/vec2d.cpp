template <class T>
struct vec2d {
	int x, y;
	std::vector<T> m;
	VV(int x, int y, const T &v = T()) : x(x), y(y), m(a * b, v) {}
	auto operator[](int i) {
		return m.begin() + i * y;
	}
	auto operator[](int i) const {
		return m.begin() + i * y;
	}
};
