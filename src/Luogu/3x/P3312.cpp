#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;

int ____ = cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

// @description 线性筛积性函数

vector<bool> not_p;
vector<int> primes, mu;
vector<pair<ll, int>> sigma;
void Euler(int n) {
	vector<ll> pw(n), sgm(n);
	not_p.resize(n);
	mu.resize(n);
	sigma.resize(n);
	sgm[1] = mu[1] = pw[1] = 1;
	for (int i = 2; i < n; i++) {
		if (!not_p[i]) {
			primes.push_back(i);
			pw[i] = sgm[i] = i + 1, mu[i] = -1;
		}
		for (int pj : primes) {
			if (pj > (n - 1) / i)
				break;
			not_p[i * pj] = true;
			if (i % pj == 0) {
				pw[i * pj] = pw[i] * pj + 1;
				sgm[i * pj] = sgm[i] / pw[i] * pw[i * pj];
				mu[i * pj] = 0;
				break;
			}
			pw[i * pj] = pj + 1;
			sgm[i * pj] = sgm[i] * pw[pj];
			mu[i * pj] = -mu[i];
		}
	}
	for (int i = 1; i < n; i++) {
		sigma[i] = {sgm[i], i};
	}
	sort(sigma.begin(), sigma.end());
}

// @description 区间加 & 区间更新（树状数组实现）

template <class T>
struct fwtree {
	int n;
	vector<T> v;
	fwtree(int n_ = 0) : n(n_), v(n) {}
	void add(int i, T x) {
		for (; 0 < i && i < n; i += i & -i) {
			v[i] += x;
		}
	}
	T sum(int i) const {
		T sum = T();
		for (; i > 0; i -= i & -i)
			sum += v[i];
		return sum;
	}
	T sum(int l, int r) {
		return sum(r) - sum(l - 1);
	}
};

using i4 = std::tuple<int, int, int, int>;

const int N = 2E5 + 10;
const ll P = 2147483648;

int main() {
	Euler(N);

	int T;
	cin >> T;
	vector<i4> v(T);
	for (int i = 0; i < T; i++) {
		int n, m, a;
		cin >> n >> m >> a;
		v[i] = {n, m, a, i};
	}
	sort(v.begin(), v.end(), [](const i4 &l, const i4 &r) {
		return std::get<2>(l) < std::get<2>(r);
	});

	fwtree<ll> tr(N);

	auto add = [&](int x) {
		auto [sgm, q] = sigma[x];
		for (int i = 1; i * q < N; i++) {
			tr.add(i * q, sgm * mu[i]);
		}
	};

	int pos = 1;
	vector<ll> ret(T);
	for (auto [n, m, a, i] : v) {
		while (sigma[pos].first <= a) {
			add(pos++);
		}
		for (int l = 1, r; l <= min(n, m); l = r + 1) {
			r = min(n / (n / l), m / (m / l));
			ret[i] += tr.sum(l, r) * ll(n / l) * ll(m / l) % P;
		}
	}
	for (auto ai : ret) {
		cout << ai % P << '\n';
	}

	return 0;
}
