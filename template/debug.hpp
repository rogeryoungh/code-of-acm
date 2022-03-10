#define dbg(x) #x << " = " << (x) << ", "

template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
	os << "[";
	for (int i = 0; i < v.size(); i++) {
		os << v[i] << (i == v.size() - 1 ? "" : ", ");
	}
	return os << "]";
}

template <class S, class T>
ostream &operator<<(ostream &os, const pair<S, T> &p) {
	return os << "(" << p.first << ", " << p.second << ")";
}
