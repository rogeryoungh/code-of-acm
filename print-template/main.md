---
title: ACM 模板
date: \today
author: \href{https://github.com/rogeryoungh}{rogeryoungh}
toc: true
book: true
multicols: true
horizontal: true
---

# 上号

尝试使用 C++ 17 的新特性。

## 头文件

```cpp
#include <bits/stdc++.h>
using ll = long long;
using namespace std;

#define dbg(x) #x << " = " << (x) << ", "
int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
```

## 进制转换

```cpp
void pr(ll n, ll x) {
  if (n >= x)  pr(n / x, x);
  putchar(n % x + (n % x > 10 ? 'A' - 10 : '0'));
}
void pr(ll n) {
  if (n >= 10)  pr(n / 10);
  putchar(n % 10 + '0');
}
```

## 常见技巧

向上取整 $p/q$ 为 `(p-1)/q+1` 。

预计算 $\log_n$，只需 `_fora(i, n, MN) logn[i] = logn[i/n] + 1;`。

字典序 `strcmp(x,y) < 0`。

大根堆（优先队列）：`priority_queue<pii, vector<pii>, greater<pii>>`。

## 二分查找

##### STL 二分 {#stl-二分 .unnumbered}

在 $[l,r)$ 查找 $\geqslant v$ 中最前的一个，找不到则返回 $r$ 。支持 cmp
函数。

```cpp
T* lower_bound(T* l, T* r, const T& v, Comp cmp);
```

在 $[l,r)$ 查找 $> value$ 中最前的一个，找不到则返回 $r$ 。支持 cmp
函数。

```cpp
T* upper_bound(T* l, T* r, const T& v, Comp cmp);
```

##### 手写二分 {#手写二分 .unnumbered}

在 `true -> false` 的开区间 $[l, r)$ 中，找到最后一个 `true`。

```cpp
template <class Comp> // last true
ll lower(ll l, ll r, Comp check) {
  if (l >= r or not check(l))
    return r;
  while (r - l > 1) {
    ll m = l + (r - l) / 2;
    (check(m) ? l : r) = m;
  }
  return l;
}
```

在 `false -> true` 的开区间 $[l, r)$ 中，找到第一个 `true`。

```cpp
template <class Comp> // first true
ll upper(ll l, ll r, Comp check) {
  if (l >= r or not check(r - 1))
    return r;
  while (r - l > 1) {
    ll m = l + (r - l) / 2;
    (check(m - 1) ? r : l) = m;
  }
  return l;
}
```

对于上凸（$\wedge$
形）函数，可以使用三分法来查找最大值。对于下凸（$\vee$ 形）变号即可

```cpp
double l = 0, r = 10, eps = 1E-9;
for (int i = 0; i < 200; i++) {
  double mid = (r + l) / 2;
  if (f(mid + eps) > f(mid - eps))
    l = mid;
  else
    r = mid;
}
```

## 二维数组

基于 `vector` 的二维数组。

```cpp
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
```

## 矩阵乘法

构建一个 $p$ 行 $q$ 列的矩阵。

```cpp
template <class T>
VV<T> operator*(const VV<T> &lhs, const VV<T> &rhs) {
  assert(lhs.y == rhs.x);
  VV<T> u(lhs.x, rhs.y);
  for (int i = 0; i < lhs.x; i++) {
    for (int k = 0; k < rhs.x; k++) {
      T t = lhs[i][k];
      for (int j = 0; j < rhs.y; j++)
        u[i][j] += rhs[k][j] * t;
    }
  }
  return u;
}
```

矩阵的输入、输出。

```cpp
template <class T>
istream &operator>>(istream &is, VV<T> &m) {
  for (int i = 0; i < m.x * m.y; i++)
    is >> m.m[i];
  return is;
}

template <class T>
ostream &operator<<(ostream &os, const VV<T> &m) {
  for (int i = 0; i < m.x * m.y; i++)
    os << m.m[i] << " \n"[(i + 1) % m.y == 0];
  return os;
}
```

## 快速幂

```cpp
ll qpow(ll a, ll b = P - 2, ll p = P) {
  ll ret = p != 1;
  for (; b > 0; b >>= 1) {
    if (b & 1)
      ret = a * ret % p;
    a = a * a % p
  }
  return ret;
}
```

```cpp
template <class T>
auto make_matrix_E(int n) {
  VV<T> ret(n, n);
  for (int i = 0; i < n; i++)
    ret[i][i] = 1;
  return ret;
}

template <class T>
auto matrix_pow(VV<T> a, ll w) {
  auto ret = make_matrix_E<T>(a.x);
  for (; w > 0; w >>= 1) {
    if (w & 1)
      ret = a * ret;
    a = a * a;
  }
  return ret;
}
```

## 快速排序

```cpp
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
```

## 第 $k$ 大数

```cpp
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
```

## 归并排序求逆序对

```cpp
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
```

## 取模整数

```cpp
#define OPERATOR(U, V, op)                              \
  friend inline U operator op(const U &l, const V &r) { \
    return U(l) op##= r;                                \
  }

struct Z {
  int v;
  Z(ll a = 0) : v(a %= P < 0 ? a + P : P) {}
  Z &operator=(const int &m) {
    v = m;
    return *this;
  }
  Z &operator+=(const Z &m) {
    v = (v += m.v) >= P ? v - P : v;
    return *this;
  }
  Z &operator-=(const Z &m) {
    v = (v -= m.v) < 0 ? v + P : v;
    return *this;
  }
  Z &operator*=(const Z &m) {
    v = 1ll * v * m.v % P;
    return *this;
  }
  OPERATOR(Z, Z, +);
  OPERATOR(Z, Z, -);
  OPERATOR(Z, Z, *);
  Z pow(int n) const {
    return qpow(v, n);
  }
  Z inv() const {
    return pow(P - 2);
  }
  // useless
  Z operator-() const {
    return v == 0 ? 0 : P - v;
  }
  Z &operator/=(const Z &m) {
    return *this *= m.inv();
  }
  OPERATOR(Z, Z, /);
  auto approx(int A = 1E3) {
    int x = v, y = P, a = 1, b = 0;
    while (x > A) {
      swap(x, y), swap(a, b);
      a -= x / y * b, x %= y;
    }
    return make_pair(x, a);
  }
};

std::vector<Z> iv, fac, ifac;

void pre_all(int u) {
  int l = iv.size(), n = l * 2;
  if (u <= l)
    return;
  iv = fac = ifac = std::vector<Z>(n + 1, 1);
  for (int i = 1; i <= n; i++) {
    fac[i] = fac[i - 1] * i;
  }
  ifac[n] = fac[n].inv(), iv[n] = Z(n).inv();
  for (int i = n - 1; i > 0; i--) {
    ifac[i] = ifac[i + 1] * (i + 1);
    iv[i] = ifac[i] * fac[i - 1];
  }
  pre_all(u);
}
```

# 数学

## GCD & LCM & EXGCD

##### GCD & LCM

自 CPP17 之后，头文件 numeric 中已经实现了二进制

```cpp
ll gcd(ll a, ll b) {
  return a ? gcd(b % a, a) : b;
}
ll lcm(ll a, ll b) {
  return a / gcd(b % a, a) * b;
}
ll gcd(ll a, ll b) {
  while (b)
    a %= b, swap(a, b);
  return a;
}
int bgcd(int a, int b) {
  int az = __builtin_ctz(a);
  int bz = __builtin_ctz(b);
  int z = min(az, bz);
  b >>= bz;
  while (a) {
    a >>= az;
    int diff = a - b;
    az = __builtin_ctz(diff);
    b = min(a, b), a = abs(diff);
  }
  return b << z;
}
```

对于方程 $$ax+by=\gcd(a,b)$$ 可通过 $\rm exgcd$ 求出一个整数解。

```cpp
tuple<ll, ll, ll> exgcd(ll a, ll b) {
  if (b == 0) {
    return {1, 0, a};
  } else {
    auto [y, x, g] = exgcd(b, a % b);
    return {x, y - a / b * x, g};
  }
}
```

方程 $ax+by=c$ 有解的充要条件是 $\gcd(a,b) \mid c$。

## 乘法逆元

方程 $ax \equiv 1 \pmod p$ 有解的充要条件是 $\gcd(a,p) = 1$。

容易想到它与方程 $ax + py = c$ 等价，于是可以利用 $\rm exgcd$
求最小正解。

```cpp
ll inv_gcd(ll a, ll p) {
  return (std::get<0>(exgcd(a, p)) % p + p) % p;
}
```

仅当 $p$ 为质数时，由 Fermat 小定理知 $x \equiv a^{p-2} \pmod p$。

```cpp
ll inv(ll a, ll p) {
  return qpow(a, p - 2, p);
}
```

## 筛法

##### Eratosthenes 筛

复杂度 $O(n\log \log n)$。

```cpp
vector<bool> not_p;
vector<int> primes;
void Eratosthenes(int n) {
  not_p.resize(n);
  for (int i = 2; i < n; i++) {
    if (not not_p[i]) {
      primes.push_back(i);
      for (int j = i; j <= (n - 1) / i; j++)
        not_p[i * j] = true;
    }
  }
}
```

##### Euler 筛（LPF）

复杂度 $O(n)$，每个合数只会被筛一次。

```cpp
vector<int> lpf, primes;
void Euler(int n) {
  lpf.resize(n);
  for (int i = 2; i < n; i++) {
    if (!lpf[i])
      lpf[i] = i, primes.push_back(i);
    for (auto pj : primes) {
      if (pj > (n - 1) / i)
        break;
      lpf[i * pj] = pj;
      if (i % pj == 0)
        break;
    }
  }
}
```

##### Euler 筛 + MobiusMu + EulerPhi

由于 Euler
筛过程中会把每一个数拆分成两个互质的因数，因此可以用来预处理积性函数和加性函数。如
Euler 筛 + $\mu(m)$ + $\varphi(m)$，复杂度 $O(n)$。

```cpp
vector<bool> not_p;
vector<int> primes, phi, mu;
void Euler(int n) {
  not_p.resize(n + 1);
  phi.resize(n + 1);
  mu.resize(n + 1);
  mu[1] = phi[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!not_p[i]) {
      primes.push_back(i);
      phi[i] = i - 1, mu[i] = -1;
    }
    for (auto pj : primes) {
      if (pj > n / i)
        break;
      not_p[i * pj] = true;
      if (i % pj == 0) {
        phi[i * pj] = phi[i] * pj;
        mu[i * pj] = 0;
        break;
      }
      phi[i * pj] = phi[i] * (pj - 1);
      mu[i * pj] = -mu[i];
    }
  }
}
```

##### 杜教筛

当卷积可以求和时可以拆杜教筛。

```cpp
struct SumMuPhi {
  ll n;
  vector<ll> sum;
  SumMuPhi(ll u) : n(u), sum(u / smu.size() + 1) {}
  ll Smu(ll u) {
    if (u < smu.size()) {
      return smu[u];
    }
    if (sum[n / u] != 0) {
      return sum[n / u];
    }
    ll ret = 1;
    for (ll l = 2, r; l <= u; l = r + 1) {
      r = u / (u / l);
      ret -= (r - l + 1) * Smu(u / l);
    }
    return sum[n / u] = ret;
  }
  ll Sphi(ll u) {
    ll ret = 0;
    for (ll l = 1, r; l <= u; l = r + 1) {
      r = u / (u / l);
      ret += (Smu(r) - Smu(l - 1)) * (u / l) * (u / l);
    }
    return (ret + 1) / 2;
  }
};
```

##### Min25 筛

当函数可以拆多项式时。

```cpp
struct Min25 {
  ll n, sn, m = 0;
  vector<bool> not_p;
  vector<int> pri;
  vector<Z> sum;
  Z fp(ll pk) {
    return Z(pk) * ((pk - 1) % P);
  }
  int id(ll x) {
    return x <= sn ? x : m - (n / x) + 1;
  }
  Min25(ll u) : n(u), sn(sqrt(n) + 1), not_p(sn + 1), sum(sn * 2 + 5) {
    vector<Z> s2(sn * 2 + 5), s1(sn * 2 + 5);
    vector<ll> w(sn * 2 + 5);
    for (ll l = 1, r; l <= n; l = r + 1) {
      w[++m] = r = n / (n / l);
      Z mr = r % P;
      s1[m] = mr * (mr + 1) / 2 - 1;
      s2[m] = mr * (mr + 1) * (2 * mr + 1) / 6 - 1;
    }
    pri = primes, pri.insert(pri.begin(), 0);
    int cnt = 0;
    for (int i = 1, pi = pri[i]; pi <= sn; pi = pri[++i], cnt = i) {
      for (int j = m; pi <= w[j] / pi; j--) {
        s1[j] -= pi * (s1[id(w[j] / pi)] - s1[pri[i - 1]]);
        s2[j] -= Z(pi) * pi * (s2[id(w[j] / pi)] - s2[pri[i - 1]]);
      }
    }
    for (int i = 2; i <= m; i++) {
      sum[i] = s1[i] = s2[i] - s1[i];
    }
    for (int i = cnt, pi = pri[i]; i >= 1; pi = pri[--i]) {
      for (int j = m; pi <= w[j] / pi; j--) {
        ll pw = pi;
        for (int k = 1; pw <= w[j] / pi; k++, pw *= pi) {
          sum[j] += fp(pw) * (sum[id(w[j] / pw)] - s1[pi]) + fp(pw * pi);
        }
      }
    }
  }
  Z eval(ll u) {
    return sum[id(u)] + 1;
  }
};
```

##### PN 筛

PN 的个数只有 $O(\sqrt n)$。

```cpp
struct PN {
  ll n;
  SumPhi sp;
  Z ans;
  PN(ll u) : n(u), sp(u), ans(sp.S(n)) {}
  Z hpc(ll pc, int p, int c) {
    return Z(pc % P) * (p - 1) * (c - 1);
  }
  Z S() {
    dfs(1, 0, 1);
    return ans;
  }
  void dfs(ll d, int pid, Z hpast) {
    for (int i = pid; i < primes.size(); i++) {
      int c = 2, pi = primes[i];
      if (d > n / pi / pi)
        return;
      ll pc = 1ll * pi * pi;
      for (ll x = d * pi * pi; x <= n; x *= pi, pc *= pi, c++) {
        // cerr << x << '\n';
        Z hnow = hpast * hpc(pc, pi, c);
        ans += hnow * sp.S(n / x);
        dfs(x, i + 1, hnow);
      }
    }
  }
};
```

## 素性测试 & 质因分解

### 试除法

```cpp
bool isprime(ll n) {
  if (n < 3)  return n == 2;
  if (n % 2 == 0)  return false;
  ll sn = sqrt(n * 1.0);
  for (ll i = 3; i <= sn; i += 2)
    if (n % i == 0)  return false;
  return true;
}
```

### Miller Rabbin

```cpp
bool miller_rabbin(ll n) {
  if (n <= 3)
    return n >= 2;
  if (n % 2 == 0)
    return false;
  ll a = n - 1;
  a /= a & -a;
  for (int p : {2, 3, 5, 7, 11, 13, 17, 19, 23}) {
    if (n <= p)
      return true;
    ll t = a, v = qpow128(p, t, n);
    while (t != n - 1 && v != 1 && v != n - 1)
      v = i128(v) * v % n, t *= 2;
    if (v != n - 1 && t % 2 == 0)
      return false;
  }
  return true;
}
```

### Pollard Rho

```cpp
ll pollard_rho(ll N) {
  if (N % 2 == 0)
    return 2;
  if (miller_rabbin(N))
    return N;
  while (true) {
    auto f = [N, c = rand() % (N - 1) + 1](ll x) {
      return (i128(x) * x + c) % N;
    };
    ll x = 0, y = 0, p = 1, q = 1;
    do {
      int w = 128;
      do {
        p = q, x = f(x), y = f(f(y));
        q = i128(p) * abs(x - y) % N;
      } while (w-- && q != 0);
      ll d = std::__gcd(p, N);
      if (d > 1 && d != N)
        return d;
    } while (x != y);
  }
}

auto factor(ll x) {
  vector<ll> v;
  if (x == 1)
    return v;
  std::function<void(ll)> dfs = [&](ll u) {
    ll fac = pollard_rho(u);
    if (fac == u)
      v.push_back(u);
    else
      dfs(fac), dfs(u / fac);
  };
  dfs(x);
  sort(v.begin(), v.end());
  return v;
}
```

### 排列组合

### Lucas 定理

当 $n,m$ 很大而 $p$ 较小的时候，有
$$\binom{n}{m}\bmod p = \binom{\left\lfloor n/p \right\rfloor}{\left\lfloor m/p\right\rfloor}\cdot\binom{n\bmod p}{m\bmod p}\bmod p$$

```cpp
ll Lucas(ll n, ll m, int p) {
  if (!m)  return 1;
  return Lucas(n / p, m / p, p) * comb(n % p, m % p, p) % p;
}
```

## 约瑟夫 Josephus 问题

对 $n$ 个人进行标号 $0,\cdots,n-1$，顺时针站一圈。从 $0$
号开始，每一次从当前的人继续顺时针数 $k$
个，然后让这个人出局，如此反复。

设最后剩下的人的编号为 $J(n,k)$，有递推式
$$J(n+1,k) = (J(n,k)+k) \bmod (n+1)$$ 踢出第一个人 $k$ 后，即转化为
$J(n,k)$ 的情景，还原编号只需增加相对位移 $k$。

```cpp
int Josephus(int n, int k) {
    int ret = 0;
    for (int i = 1; i <= n; i++)
        ret = (ret + k) % i;
    return ret;
}
```

## 同余

##### 中国剩余定理

若 $n_i$ 中任意两个互质，求方程组的解
$$x \equiv a_i \pmod {n_i} , \quad i \in \{ 1,2,\cdots,k \}$$

```cpp
template <class PAIR>
ll crt(const vector<PAIR> &am) {
  ll prod = 1, ret = 0;
  for (auto [a, m] : am)
    prod *= m;
  for (auto [a, m] : am) {
    ll u = prod / m, v = inv_gcd(u, m);
    ret = (ret + a * u * v) % prod;
  }
  return ret;
}
```

##### 扩展中国剩余定理

若 $n_i$ 中不互质，需要 excrt

```cpp
template<class PAIR>
ll excrt(const vector<PAIR> &am) {
  auto [ans, M] = am[0];
  for (auto [a, m] : am) {
    if (M % m == 0 && ans % m == a)
      continue;
    ll B = (a - ans % m + m) % m;
    auto [x, y, g] = exgcd(M, m);
    if (B % g != 0)
      return -1;
    x = i128(x) * (B / g) % (m / g);
    ans += M * x, M *= m /g;
    ans = (ans + M) % M;
  }
  return ans;
}
```

##### 二次剩余

求 $x^2 \equiv n$，可以使用 Cipolla 算法。

```cpp
int legendre(int a, int p) {
  return qpow(a, (p - 1) / 2, p);
}

int cipolla(int n, int p) {
  if (n == 0)
    return 0;
  if (legendre(n, p) != 1)
    return -1;
  if (p == 2)
    return 1;
  for (int a = 0; a < p; a++) {
    int i = (a * a - n + p) % p;
    using FP2 = pair<ll, ll>;
    auto mul = [p, i](const FP2 &l, const FP2 &r) {
      auto [la, lb] = l;
      auto [ra, rb] = r;
      return FP2{(la * ra + lb * rb % p * i) % p, (lb * ra + la * rb) % p};
    };
    if (legendre(i, p) == p - 1) {
      FP2 x = {1, 1}, u = {a, 1};
      for (int b = (p + 1) / 2; b; b /= 2) {
        if (b % 2 == 1)
          x = mul(x, u);
        u = mul(u, u);
      }
      return min(x.first, p - x.first);
    }
  }
  return -1;
}
```

## 整除分块

令 $A = \{ \lfloor n/d \rfloor \mid 1 \leqslant d \leqslant n \}$，则
$|A| \leqslant 2\sqrt{n}$，即整除求和时可以做到 $\sqrt{n}$ 的速度。

```cpp
for (ll l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    ll t = (r - l + 1);
    // ..
}
```

假如求和的是
$\sum\limits_{i=1}^{\min(n,m)} \left\lfloor \frac{n}{i} \right\rfloor\left\lfloor \frac{m}{i} \right\rfloor$，则可以用二维分块的技巧

```cpp
for (ll l = 1, r; l <= n; l = r + 1) {
    r = min(n / (n / l), m / (m / l);
    ll t = (r - l + 1);
    // ..
}
```

## 博弈

下面都是石子游戏，轮流取走物品。方便起见，称场上 $n$ 堆石子
$a_1,\cdots,a_n$ 为局势。先手必输的局势称为奇异局势

### Nim 博弈

有 $n$ 堆分别有 $a_i$
个物品，两人轮流取走任意一堆的任意个物品，不能不取，最后取光者获胜。奇异局势判定
$$a_1 \oplus \cdots \oplus a_n =0$$

### Wythoff 博奕

两堆分别有 $a,b$
各物品，两个人轮流从某一堆或同时从两堆中取同样多的物品，不可不取，最后取光者获胜。

```cpp
const double phi = (sqrt(5.0) + 1) / 2;
bool Wythoff(ll a, ll b) {  // 判先手输赢
    return ll(abs(b - a) * phi) != a;
}
```

特点：所有自然数都出现在奇异局势中，不重不漏。

## 多项式 NTT

多项式好难。

### 核心

```cpp
struct Poly : vector<int> {
  using vector::vector;
  static Poly &mul(Poly &f, Poly &g, int n);
};
Poly w{1, 1};
inline int get_lim(int m) {
  return 1 << std::__lg(m * 2 - 1);
}
inline int mo(int u) {
  return u >= P ? u - P : u;
}
void pre_w(int n) {
  int l = w.size(), l2 = l * 2;
  if (n <= l)
    return;
  w.resize(l2);
  int p = qpow(3, (P - 1) / l2);
  for (int i = l; i < l2; i += 2) {
    w[i] = w[i / 2];
    w[i + 1] = 1ll * w[i] * p % P;
  }
  pre_w(n);
}

static int ntt_size = 0;

void ntt(auto f, int n) {
  pre_w(n), ntt_size += n;
  for (int l = n / 2; l; l /= 2)
    for (int i = 0; i < n; i += l * 2)
      for (int j = 0; j < l; j++) {
        int x = f[i + j], y = f[i + j + l];
        f[i + j + l] = 1ll * (x - y + P) * w[j + l] % P;
        f[i + j] = mo(x + y);
      }
}

void intt(auto f, int n) {
  pre_w(n), ntt_size += n;
  for (int l = 1; l < n; l *= 2)
    for (int i = 0; i < n; i += l * 2)
      for (int j = 0; j < l; j++) {
        int x = f[i + j];
        int y = 1ll * w[j + l] * f[i + j + l] % P;
        f[i + j] = mo(x + y), f[i + j + l] = mo(x - y + P);
      }
  const int ivn = P - (P - 1) / n;
  for (int i = 0; i < n; i++)
    f[i] = 1ll * f[i] * ivn % P;
  reverse(f + 1, f + n);
}

Poly &Poly::mul(Poly &f, Poly &g, int n) {
  f.resize(n), g.resize(n);
  ntt(f.begin(), n), ntt(g.begin(), n);
  for (int i = 0; i < n; i++)
    f[i] = 1ll * f[i] * g[i] % P;
  return intt(f.begin(), n), f;
}

Poly operator*(Poly f, Poly g) {
  int m = f.size() + g.size() - 1;
  Poly::mul(f, g, get_lim(m));
  return f.resize(m), f;
}
```

### 形式幂级数

```cpp
vector<Z> w{1, 1};

inline int get_lim(int m) {
  return 1 << std::__lg(m * 2 - 1);
}

void pre_w(int n) {
  int l = w.size(), l2 = l * 2;
  if (n <= l)
    return;
  w.resize(l2);
  Z p = Z(3).pow((P - 1) / l2);
  for (int i = l; i < l2; i += 2) {
    w[i] = w[i / 2];
    w[i + 1] = w[i] * p;
  }
  pre_w(n);
}

static int ntt_size = 0;

void ntt(auto f, int n) {
  pre_w(n), ntt_size += n;
  for (int l = n / 2; l; l /= 2)
    for (int i = 0; i < n; i += l * 2)
      for (int j = 0; j < l; j++) {
        Z x = f[i + j], y = f[i + j + l];
        f[i + j + l] = w[j + l] * (x - y);
        f[i + j] = x + y;
      }
}

void intt(auto f, int n) {
  pre_w(n), ntt_size += n;
  for (int l = 1; l < n; l *= 2)
    for (int i = 0; i < n; i += l * 2)
      for (int j = 0; j < l; j++) {
        Z x = f[i + j], y = w[j + l] * f[i + j + l];
        f[i + j] = x + y, f[i + j + l] = x - y;
      }
  const int ivn = P - (P - 1) / n;
  for (int i = 0; i < n; i++)
    f[i] *= ivn;
  reverse(f + 1, f + n);
}

struct Poly : vector<Z> { // 大常数板子
  using vector::vector;
#define T (*this)
  int deg() const {
    return size();
  }
  Poly &redeg(int m) {
    return resize(m), T;
  }
  Poly cut(int m, int l = 0) const {
    return {begin() + l, begin() + min(m + l, deg())};
  }
  Poly &operator+=(const Poly &g) {
    redeg(max(deg(), g.deg()));
    for (int i = 0; i < g.deg(); i++)
      T[i] += g[i];
    return T;
  }
  Poly &operator-=(const Poly &g) {
    redeg(max(deg(), g.deg()));
    for (int i = 0; i < g.deg(); i++)
      T[i] -= g[i];
    return T;
  }
  Poly &operator*=(Z k) {
    for (Z &fi : T)
      fi *= k;
    return T;
  }
  OPERATOR(Poly, Poly, +);
  OPERATOR(Poly, Poly, -);
  OPERATOR(Poly, Z, *);
  OPERATOR(Poly, Poly, *);
  Poly &ntt(int n) {
    return redeg(n), ::ntt(begin(), n), T;
  }
  Poly &intt(int n) {
    return ::intt(begin(), n), T;
  }
  static Poly &mul(Poly &f, Poly &g, int n) {
    f.ntt(n), g.ntt(n);
    for (int i = 0; i < n; i++)
      f[i] *= g[i];
    return f.intt(n);
  }
  Poly &operator*=(Poly g) {
    int m = T.deg() + g.deg() - 1;
    return mul(T, g, get_lim(m)).redeg(m);
  }
///////// IMPL /////////


#undef T
};
```

### 牛顿迭代

给定多项式 $f$，考虑求 $A(g) = 0$。假若我们已经求得
$g_0 = g \bmod x^n$，那么在 $A(g)$ 处做泰勒展开
$$0 \equiv A(g) \equiv A(g_0) + A'(g_0) \ast (g - g_0) \pmod{x^{2n}}$$
因此
$$g \equiv g_0 - \frac{A(g_0)}{\frac{\partial A}{\partial g}(g_0)} \pmod{x^{2n}}$$
令 $A(g) = f \ast g$ 可以求 inv，令 $A(g) = f \ast g - h$ 可以求 div，令
$A(g) = \ln g - f$ 可以求 exp。

```cpp
Poly deriv(int m) const {
  Poly f(m);
  for (int i = 1; i < min(deg(), m + 1); i++)
    f[i - 1] = T[i] * i;
  return f;
}
Poly integr(int m) const {
  Poly f(m);
  for (int i = min(deg(), m - 1); i > 0; --i)
    f[i] = iv[i] * T[i - 1];
  return f;
}
Poly inv(int m) const { // 12E
  Poly x = {T[0].inv()};
  for (int t = 2; t < m * 2; t *= 2) {
    Poly u = cut(t).ntt(t * 2);
    x.ntt(t * 2);
    for (int i = 0; i < t * 2; i++)
      x[i] = (2 - u[i] * x[i]) * x[i];
    x.intt(t * 2).redeg(t);
  }
  return x.redeg(m);
}
Poly div(int m, const Poly &g) const { // 18E
  if (deg() == 0)
    return {};
  return (cut(m) * g.inv(m)).redeg(m);
}
Poly ln(int m) const {
  assert(T[0].v == 1);
  return deriv(m).div(m - 1, cut(m)).integr(m);
}
Poly exp(int m) const { // 48E
  assert(T[0].v == 0);
  Poly x = {1};
  for (int t = 2; t < m * 2; t *= 2) {
    x = x * (cut(t) - x.ln(t) + Poly{1}), x.redeg(t);
  }
  return x.redeg(m);
}
Poly sqrt(int m) const { // 36E
  Poly x = {1};
  for (int t = 2; t < m * 2; t *= 2) {
    x = (x + cut(t).div(t, x)) * ((P + 1) / 2);
  }
  return x.redeg(m);
}
Poly pow(int m, int k) const {
  return (ln(m) * k).exp(m);
}
Poly rev() const {
  return {rbegin(), rend()};
}
friend Poly operator/(const Poly &f, const Poly &g) {
  int m = f.deg() - g.deg() + 1;
  return f.rev().div(m, g.rev()).rev();
}
friend auto operator%(const Poly &f, const Poly &g) {
  Poly Q = f / g;
  return make_pair(Q, (f - Q * g).redeg(g.deg() - 1));
}
```

### 多项式平移

```cpp
Poly taylor_shift(const Poly &f, Z c) {
  int n = f.deg();
  Poly A(n), B(n);
  Z ci = 1;
  for (int i = 0; i < n; i++) {
    A[i] = f[i] * fac[i];
    B[i] = ci * ifac[i];
    ci *= c;
  }
  reverse(A.begin(), A.end());
  A = A * B;
  for (int i = 0; i < n; i++) {
    B[i] = A[n - i - 1] * ifac[i];
  }
  return B;
}
```

### Chirp Z 变换

```cpp
Poly chirpz(const Poly &f, int m, Z c) {
  int n = f.deg(), N = get_lim(n + m - 1);
  Poly A = f, pw(n + m, 1), ipw(n + m, 1);
  Z ci = c, ivc = c.inv(), ici = ivc;
  for (int i = 2; i < n + m; i++) {
    pw[i] = pw[i - 1] * ci;
    ipw[i] = ipw[i - 1] * ici;
    ci *= c, ici *= ivc;
  }
  for (int i = 0; i < n; i++)
    A[i] *= ipw[i];
  reverse(A.begin(), A.end());
  Poly::mul(A, pw, N);
  Poly x(m);
  for (int i = 0; i < m; i++) {
    x[i] = A[i + n - 1] * ipw[i];
  }
  return x;
}
```

### 三模 NTT

```cpp
using Poly = vector<int>;

inline int get_lim(int m) {
  return 1 << std::__lg(m * 2 - 1);
}

template <int P>
struct NTT {
  inline static Poly w{1, 1};

  inline static int ntt_size = 0;

  static inline int mo(int u) {
    return u >= P ? u - P : u;
  }

  static void pre_w(int n) {
    int l = w.size(), l2 = l * 2;
    if (n <= l)
      return;
    w.resize(l2);
    int p = qpow(3, (P - 1) / l2, P);
    for (int i = l; i < l2; i += 2) {
      w[i] = w[i / 2];
      w[i + 1] = 1ll * w[i] * p % P;
    }
    pre_w(n);
  }

  static void ntt(auto f, int n) {
    pre_w(n), ntt_size += n;
    for (int l = n / 2; l; l /= 2)
      for (int i = 0; i < n; i += l * 2)
        for (int j = 0; j < l; j++) {
          int x = f[i + j], y = f[i + j + l];
          f[i + j + l] = 1ll * (x - y + P) * w[j + l] % P;
          f[i + j] = mo(x + y);
        }
  }

  static void intt(auto f, int n) {
    pre_w(n), ntt_size += n;
    for (int l = 1; l < n; l *= 2)
      for (int i = 0; i < n; i += l * 2)
        for (int j = 0; j < l; j++) {
          int x = f[i + j];
          int y = 1ll * w[j + l] * f[i + j + l] % P;
          f[i + j] = mo(x + y), f[i + j + l] = mo(x - y + P);
        }
    const int ivn = P - (P - 1) / n;
    for (int i = 0; i < n; i++)
      f[i] = 1ll * f[i] * ivn % P;
    reverse(f + 1, f + n);
  };
};

template <int P>
Poly mul(Poly &f, Poly g, int n) {
  for (int i = 0; i < n; i++)
    f[i] %= P, g[i] %= P;
  NTT<P>::ntt(f.begin(), n), NTT<P>::ntt(g.begin(), n);
  for (int i = 0; i < n; i++)
    f[i] = 1ll * f[i] * g[i] % P;
  return NTT<P>::intt(f.begin(), n), f;
}

Poly mul3(Poly f, Poly g, int p) {
  constexpr array<int, 3> M = {985661441, 998244353, 1004535809};
  int m = f.size() + g.size() - 1, N = get_lim(m);
  f.resize(N), g.resize(N);

  array<Poly, 3> a = {f, f, f};
  mul<M[0]>(a[0], g, N);
  mul<M[1]>(a[1], g, N);
  mul<M[2]>(a[2], g, N);

  Poly ans(m);

  const ll M12 = ll(M[0]) * M[1] % p;
  const ll inv_1 = qpow(M[0], M[1] - 2, M[1]);
  const ll inv_2 = qpow(ll(M[0]) * M[1] % M[2], M[2] - 2, M[2]);

  for (int i = 0; i < m; i++) {
    ll x = (a[1][i] - a[0][i] + M[1]) * inv_1 % M[1] * M[0] + a[0][i];
    ans[i] = ((a[2][i] - x % M[2] + M[2]) * inv_2 % M[2] * M12 + x) % p;
  }
  return ans;
}
```

### 在线卷积

当 $f$ 已经给出时，若要逐点的计算 $f \ast g$，可以使用半在线卷积算法。

```cpp
struct PolySemi {
  int now = 0;
  enum : int { M = 32 };
  const Poly &F;
  Poly G, conv;
  map<int, Poly> nf;
  PolySemi(const Poly &f) : F(f), G(M), conv(M) {}
  void set(Z v) {
    G[now] = v;
    conv[now] += G[now] * F[0];
    now++;
  }
  Z next() { // return  (F * G)[now] - F[0] G[now]
    int len = now & -now, l = now - len;
    if (len < M) {
      for (int j = now & -M; j < now; ++j)
        conv[now] += G[j] * F[now - j];
    } else {
      Poly a = G.cut(len, l).ntt(len * 2), &b = nf[len];
      if (l == 0) {
        b = F.cut(len * 2).ntt(len * 2);
        conv.redeg(now * 2);
        G.redeg(now * 2);
      }
      for (int i = 0; i < len * 2; i++)
        a[i] *= b[i];
      a.intt(len * 2);
      for (int i = len; i < len * 2; i++)
        conv[l + i] += a[i];
    }
    return conv[now];
  }
};

Poly semi_inv(Poly F, int m) {
  PolySemi X(F.redeg(m));
  Z iv0 = -F[0].inv();
  X.set(-iv0);
  for (int i = 1; i < m; i++) {
    X.set(iv0 * X.next());
  }
  return X.G.redeg(m);
}

Poly semi_inv(Poly H, Poly F, int m) {
  PolySemi X(F.redeg(m));
  Z iv0 = F[0].inv();
  X.set(iv0 * H[0]);
  for (int i = 1; i < m; i++)
    X.set(iv0 * (H[i] - X.next()));
  return X.G.redeg(m);
}

Poly semi_exp(Poly F, int m) {
  for (int i = 0; i < F.size(); i++)
    F[i] *= i;
  PolySemi X(F);
  X.set(1);
  for (int i = 1; i < m; i++)
    X.set(iv[i] * X.next());
  return X.G.redeg(m);
}
```

当 $f$ 和 $g$ 都未给出时，可以使用全在线卷积。

```cpp
struct PolyRelax {
  int now = 0;
  enum : int { M0 = 1024, M = 32 };
  Poly F, G, conv;
  map<int, Poly> nf, ng;

  PolyRelax() : F(M0), G(M0), conv(M0) {}

  Poly &getNf(int len) {
    auto &u = nf[len];
    if (u.empty())
      u = F.cut(len).ntt(len);
    return u;
  }

  Poly &getNg(int len) {
    auto &u = ng[len];
    if (u.empty())
      u = G.cut(len).ntt(len);
    return u;
  }

  void set(Z v1, Z v2) {
    F[now] = v1, G[now] = v2;
    conv[now] += G[now] * F[0];
    if (now != 0)
      conv[now] += F[now] * G[0];
    now++;
  }

  Z next() { // return (F * G)[now] - F[0] G[now] - F[now] G[0]
    int len = now & -now, l = now - len;
    if (now < M0) {
      for (int j = (now & -M0) + 1; j < now; ++j)
        conv[now] += G[j] * F[now - j];
    } else if (len == now) {
      conv.redeg(len * 2);
      F.redeg(len * 2);
      G.redeg(len * 2);
      Poly a = getNg(len), &b = getNf(len);
      for (int i = 0; i < len; i++)
        a[i] *= b[i];
      a.intt(len);
      for (int i = len; i < len * 2; i++)
        conv[i] += a[i - len] - conv[i - len];
    } else if (len < M) {
      for (int j = now & -M; j < now; ++j) {
        conv[now] += G[j] * F[now - j] + F[j] * G[now - j];
      }
    } else {
      Poly a = G.cut(len, l), &b = getNf(len * 2);
      Poly c = F.cut(len, l), &d = getNg(len * 2);
      a.ntt(len * 2), c.ntt(len * 2);
      for (int i = 0; i < len * 2; ++i)
        a[i] = a[i] * b[i] + c[i] * d[i];
      a.intt(len * 2);
      for (int i = len; i < len * 2; i++)
        conv[l + i] += a[i];
    }
    return conv[now];
  }
};

Poly relax_inv(Poly F, int m) {
  F.redeg(m);
  PolyRelax X;
  Z iv0 = -F[0].inv();
  X.set(F[0], -iv0);
  for (int i = 1; i < m; i++)
    X.set(F[i], iv0 * (X.next() - F[i] * iv0));
  return X.G.redeg(m);
}

Poly relax_div(Poly H, Poly F, int m) {
  F.redeg(m);
  PolyRelax X;
  Z iv0 = F[0].inv();
  X.set(F[0], iv0 * H[0]);
  for (int i = 1; i < m; i++)
    X.set(F[i], iv0 * (H[i] - X.next()));
  return X.G.redeg(m);
}

Poly relax_exp(Poly F, int m) {
  F.redeg(m);
  PolyRelax X;
  for (int i = 0; i < F.deg(); i++)
    F[i] *= i;
  X.set(F[0], 1);
  for (int i = 1; i < m; i++)
    X.set(F[i], iv[i] * (X.next() + F[i]));
  return X.G.redeg(m);
}

Poly relax_sqrt(Poly F, int m) {
  F.redeg(m);
  PolyRelax X;
  Z iv0 = 1; // F[0].sqrt()
  X.set(iv0, iv0);
  iv0 = (iv0 * 2).inv();
  for (int i = 1; i < m; i++) {
    Z t = (F[i] - X.next()) * iv0;
    X.set(t, t);
  }
  return X.F.redeg(m);
}
```

### 多点求值 ・ 快速插值

```cpp
struct PolyEI {
  int raw_n, n;
  vector<Poly> p;
  PolyEI(Poly a) : raw_n(a.deg()), n(get_lim(raw_n)), p(n * 2) {
    a.redeg(n);
    for (int i = 0; i < n; i++)
      p[i + n] = {1, -a[i]};
    for (int i = n - 1; i; i--) {
      int ls = i * 2, rs = i * 2 + 1;
      int len = get_lim(p[ls].deg());
      p[ls].ntt(len), p[rs].ntt(len), p[i].redeg(len);
      for (int j = 0; j < len; j++)
        p[i][j] = p[ls][j] * p[rs][j];
      p[i].intt(len);
      p[i].push_back(p[i][0] - 1), p[i][0] = 1;
    }
  }
  Poly eval(const Poly &f) { // PolyEI(x).eval(f)
    int m = f.deg();
    if (m == 1)
      return Poly(raw_n, f[0]);
    Poly q = f.rev().div(m, p[1]).redeg(n);
    rotate(q.begin(), q.begin() + m, q.end());
    for (int k = n, o = 1; k > 1; k >>= 1)
      for (int i = 0; i < n; i += k, o++) {
        if (i >= raw_n)
          continue;
        Poly foo(k), bar(k);
        auto qi = q.begin() + i;
        ntt(qi, k);
        for (int j = 0; j < k; j++) {
          foo[j] = qi[j] * p[o * 2 + 1][j];
          bar[j] = qi[j] * p[o * 2][j];
        }
        foo.intt(k), bar.intt(k);
        copy(foo.begin() + k / 2, foo.end(), qi);
        copy(bar.begin() + k / 2, bar.end(), qi + k / 2);
      }
    return q.cut(raw_n);
  }
  Poly inter(const Poly &y) { // PolyEI(x).inter(y)
    Poly q = Poly(p[1]).redeg(raw_n + 1);
    q = eval(q.rev().deriv()).redeg(n);
    for (int i = 0; i < raw_n; i++)
      q[i] = y[i] / q[i];
    for (int k = 1, h = n / 2; k < n; k *= 2, h >>= 1)
      for (int i = 0, o = h; i < n; i += k * 2, o++) {
        if (i >= raw_n)
          continue;
        auto qi = q.begin() + i;
        Poly foo(qi, qi + k), bar(qi + k, qi + k * 2);
        foo.ntt(k * 2), bar.ntt(k * 2);
        for (int j = 0; j < k * 2; j++) {
          qi[j] = foo[j] * p[o * 2 + 1][j] + bar[j] * p[o * 2][j];
        }
        intt(qi, k * 2);
      }
    return q.cut(raw_n).rev();
  }
};
```

### Berlekamp--Massey

```cpp
Poly bm(const Poly &a) {
  Poly p = {1}, q = {1};
  int l = 0;
  for (int r = 1; r <= a.deg(); r++) {
    Z delta = 0;
    for (int j = 0; j <= l; j++)
      delta += a[r - 1 - j] * p[j];
    q.insert(q.begin(), 0);
    if (delta.v == 0)
      continue;
    Poly t = p;
    if (q.deg() > t.deg())
      t.redeg(q.deg());
    for (int i = 0; i < q.deg(); i++)
      t[i] -= delta * q[i];
    if (2 * l <= r - 1) {
      q = p;
      Z od = delta.inv();
      for (Z &x : q)
        x *= od;
      l = r - l;
    }
    swap(p, t);
  }
  assert(p.deg() == l + 1);
  reverse(p.begin(), p.end());
  return p;
}

Z mulAt(const Poly &F, const Poly &G, int u) {
  int n = F.size() - 1, m = G.size() - 1;
  int a = max(0, u - m), b = min(u, n);
  Z ans = 0;
  for (int i = a; i <= b; i++)
    ans += F[i] * G[u - i];
  return ans;
}

// [x^n] F(x)/G(x)
Z divAt(Poly F, Poly G, ll n) {
  int len = max(F.deg(), G.deg()), m = get_lim(len);
  for (; n > m; n >>= 1) {
    F.ntt(m * 2), G.ntt(m * 2);
    for (int i = 0; i < m * 2; i++)
      F[i] = F[i] * G[i ^ 1];
    for (int i = 0; i < m; i++)
      G[i] = G[i * 2] * G[i * 2 + 1];
    G.redeg(m);
    F.intt(m * 2), G.intt(m);
    for (int i = 0, j = n & 1; i < len; i++, j += 2)
      F[i] = F[j];
    F.redeg(len), G.redeg(len);
  }
  return mulAt(F, G.inv(m), n);
}

// 特征方程 F(x) 和初值 {Ai}，求 An
Z getAn(Poly F, const Poly &A, ll n) {
  reverse(F.begin(), F.end());
  assert(F[0].v == 1);
  Poly f = (A * F).cut(A.deg());
  return divAt(f, F, n);
}
```

### FFT

```cpp
using img = complex<f64>;
using Poly = vector<int>;

vector<img> w{{1, 0}, {1, 0}};

inline int get_lim(int m) {
  return 1 << std::__lg(m * 2 - 1);
}

const f64 PI = acos(-1.0);

void pre_w(int u) {
  int l = w.size(), l2 = l * 2;
  if (u <= l)
    return;
  w.resize(l2);
  img p = img(cos(PI / l), sin(PI / l));
  for (int i = l; i < l2; i += 2) {
    w[i] = w[i / 2];
    w[i + 1] = w[i] * p;
  }
  pre_w(u);
}

static int ntt_size = 0;

void fft(auto f, int n) {
  pre_w(n), ntt_size += n;
  for (int l = n / 2; l; l /= 2)
    for (int i = 0; i < n; i += l * 2)
      for (int j = 0; j < l; j++) {
        img x = f[i + j] + f[i + j + l];
        f[i + j + l] = w[j + l] * (f[i + j] - f[i + j + l]);
        f[i + j] = x;
      }
}

void ifft(auto f, int n) {
  pre_w(n), ntt_size += n;
  for (int l = 1; l < n; l *= 2)
    for (int i = 0; i < n; i += l * 2)
      for (int j = 0; j < l; j++) {
        img x = f[i + j], y = f[i + j + l] * w[j + l];
        f[i + j] = x + y, f[i + j + l] = x - y;
      }
  for (int i = 0; i < n; i++)
    f[i] /= n;
  reverse(f + 1, f + n);
}

Poly mul(const Poly &a, const Poly &b) {
  int n = a.size(), m = b.size(), N = get_lim(n + m - 1);
  vector<img> f(N);
  for (int i = 0; i < n; i++)
    f[i] += img(a[i], 0);
  for (int i = 0; i < m; i++)
    f[i] += img(0, b[i]);
  fft(f.begin(), N);
  for (int i = 0; i < N; i++)
    f[i] *= f[i];
  ifft(f.begin(), N);
  Poly ans(n + m - 1);
  for (int i = 0; i < n + m - 1; i++)
    ans[i] = int(f[i].imag() / 2 + 0.5);
  return ans;
}

Poly mul5(const Poly &a, const Poly &b, int p) {
  enum : int { B = 1 << 15 };
  int n = a.size(), m = b.size(), N = get_lim(n + m - 1);
  vector<img> a0(N), a1(N), Q(N);
  for (int i = 0; i < n; i++)
    a0[i] = a[i] % B, a1[i] = a[i] / B;
  for (int i = 0; i < m; i++)
    Q[i] = img(b[i] % B, b[i] / B);
  fft(a0.begin(), N), fft(a1.begin(), N), fft(Q.begin(), N);
  for (int i = 0; i < N; i++)
    a0[i] *= Q[i], a1[i] *= Q[i];
  ifft(a0.begin(), N), ifft(a1.begin(), N);
  Poly ans(n + m - 1);
  for (int i = 0; i < m + n - 1; i++) {
    ll a1b1 = a1[i].imag() + .5;
    ll a1b0 = a1[i].real() + .5;
    ll a0b1 = a0[i].imag() + .5;
    ll a0b0 = a0[i].real() + .5;
    ans[i] = ((a1b1 * B % p + a0b1 + a1b0) * B + a0b0) % p;
  }
  return ans;
}
```

## 线性代数

高斯消元。

```cpp
auto Gauss(VV<double> v) {
  assert(v.x == v.y - 1);
  int n = v.x;
  for (int i = 0; i < n; i++) {
    int mi = i;
    for (int j = i + 1; j < n; j++)
      if (fabs(v[j][i]) > fabs(v[mi][i]))
        mi = j;
    for (int j = 0; j < n + 1; j++)
      swap(v[i][j], v[mi][j]);
    if (fabs(v[i][i]) < eps)
      return VV<double>(0, 0);
    for (int j = 0; j < n; j++) {
      if (j != i) {
        double tmp = v[j][i] / v[i][i];
        for (int k = i + 1; k < n + 1; k++)
          v[j][k] -= v[i][k] * tmp;
      }
    }
  }
  return v;
}
```

拉格朗日插值。

```cpp
Z lagrange(const vector<Z> &x, const vector<Z> &y, Z k) {
  int n = x.size();
  Z sum = 0;
  for (int i = 0; i < n; i++) {
    Z s1 = 1, s2 = 1;
    for (int j = 0; j < n; j++) {
      if (j == i)
        continue;
      s1 *= k - x[j], s2 *= x[i] - x[j];
    }
    sum += s1 / s2 * y[i];
  }
  return sum;
}
```

线性基。

```cpp
struct Basis {
  enum : int { U = 60 };
  std::array<ll, U + 2> a{};
  void insert(ll x) {
    for (int i = U; i >= 0 && x; --i)
      if (x & (1ll << i)) {
        if (a[i]) {
          x ^= a[i];
        } else {
          a[i] = x;
          break;
        }
      }
  }
  ll query(ll x) {
    for (int i = U; i >= 0; i--)
      if ((x ^ a[i]) > x)
        x = x ^ a[i];
    return x;
  }
};
```

## 数学常数

### 幂塔

```cpp
int tetration_mod(int a, int b, int m) {
  if (m == 1)   return 0;
  if (a == 0)   return (b + 1) % 2;
  if (b == 0)   return 1;
  if (b == 1)   return a % m;
  if (a == 2 && b <= 4) {
    static const array ans = {1, 2, 4, 16, 65536};
    return ans[b] % m;
  }
  int phi = euler_phi(m);
  int d = tetration_mod(a, b - 1, phi) + phi;
  return qpow(a % m, d, m);
}
```

### 斯特林数

```cpp
Poly pow_safe(const Poly &g, int m, int k1, int k2) { // k % P, k % (P - 1)
  int pos = 0;
  while (pos < g.deg() && g[pos].v == 0) {
    ++pos;
  }
  if (pos == g.deg() || pos > (m - 1) / k1) {
    return Poly(m, 0);
  }
  Z x = g[pos];
  Poly f = Poly(g.begin() + pos, g.end()) * x.inv();
  f = f.pow(m - pos * k1, k1) * x.pow(k2);
  f.insert(f.begin(), pos * k1, 0);
  assert(f.deg() == m);
  return f;
}

Poly stirling1st_row(int n) {
  if (n == 0)
    return {0};
  Poly f = stirling1st_row(n / 2);
  Poly r = f * taylor_shift(f, n / 2);
  if (n % 2 == 1) {
    r *= Poly{n - 1, 1};
  }
  return r;
}

Poly stirling1st_col(int n, int k) {
  n++;
  Poly r = {1, P - 1};
  r = pow_safe(r.ln(n), n, k, k);
  Z xk = Z(P - 1).pow(k) * ifac[k];
  for (int i = 0; i < n; i++) {
    r[i] *= fac[i] * xk;
  }
  return r;
}

Poly stirling2st_row(int n) {
  n++;
  Poly A(n), B(n);
  for (int i = 0; i < n; i++) {
    A[i] = i % 2 == 1 ? -ifac[i] : ifac[i];
    B[i] = Z(i).pow(n - 1) * ifac[i];
  }
  return (A * B).redeg(n);
}

Poly stirling2st_col(int n, int k) {
  if (n < k)
    return Poly(n + 1);
  std::function<Poly(int)> sol = [&](int u) -> Poly {
    if (u == 0)
      return {1};
    Poly f = sol(u / 2);
    f *= taylor_shift(f, P - u / 2);
    if (u % 2 == 1)
      f *= Poly{-u, 1};
    return f;
  };
  Poly f = sol(k).rev().inv(n - k + 1);
  f.insert(f.begin(), k, 0);
  return f;
}
```

### 幂表

```cpp
auto powers(int n, int k, int mod) {
  vector<bool> isp(n + 1, true);
  vector<int> pw(n + 1, 1);
  for (int p = 2; p <= n; ++p)
    if (isp[p]) {
      for (ll j = ll(p) * p; j <= n; j += p)
        isp[j] = false;
      int q = qpow(p, k, mod);
      for (int i = 1; i <= n / p; ++i)
        pw[i * p] = ll(q) * pw[i] % mod;
    }
  pw[0] = qpow(0, k, mod);
  return pw;
}
```

# 图论

## 链式前项星

现在更常用 `vector<int>`，很方便快捷。

```cpp
const int MN = 10005;
int head[MN];
struct Edge {
  int too, nxt, len;
} edge[MN * 2];
void add(int frm, int too, int len) {
  static int cnt = 0;
  edge[++cnt] = {too, head[frm], len};
  head[frm] = cnt;
}
void dfs(int x, int fa) {
  _fore(i, x) if (edge[i].too != fa)
        dfs(edge[i].too, x);
}
```

## 最短路

### Dijkstra

权值必须是非负，复杂度 $O(E\log E)$。

```cpp
template <class D>
auto dijkstra(const Graph<D> &G, int s) {
  int n = G.size();
  vector<D> dis(n, std::numeric_limits<D>::max() / 2);
  vector<int> from(n, -1);
  vector<bool> vis(n);
  dis[s] = 0, from[s] = s;
  using pdi = pair<D, int>;
  priority_queue<pdi, vector<pdi>, greater<pdi>> pq;
  pq.emplace(0, s);
  while (!pq.empty()) {
    auto [w, u] = pq.top();
    pq.pop();
    if (vis[u])
      continue;
    vis[u] = true;
    for (auto [v, wi] : G[u]) {
      D d2 = w + wi;
      if (dis[v] > d2)
        dis[v] = d2, from[v] = u, pq.emplace(d2, v);
    }
  }
  return make_pair(dis, from);
}
```

### Bellman-Ford

复杂度 $O(VE)$。

```cpp
template <class D>
auto bellman_ford(const Graph<D> &G, int s) {
  int n = G.size();
  vector<D> dis(n, std::numeric_limits<D>::max() / 2);
  vector<int> from(n, -1);
  dis[s] = 0, from[s] = s;
  bool flag = true;
  for (int k = 0; k < n && flag; k++) {
    flag = false;
    for (int u = 0; u < n; u++) {
      for (auto [v, w] : G[u]) {
        int d2 = dis[u] + w;
        if (dis[v] > d2)
          dis[v] = d2, from[v] = u, flag = true;
      }
    }
  }
  return make_pair(dis, from);
}
```

### Floyd

起始条件 $f(i,j)={\rm edge}(i,j)$，$f(i,i)=0$。

```cpp
template <class D>
auto floyd(const Graph<D> &G) {
  int n = G.x;
  auto f = G;
  VV<int> pass(n, n, -1);
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        D d2 = f[i][k] + f[k][j];
        if (f[i][j] > d2)
          f[i][j] = d2, pass[i][j] = k;
      }
    }
  }
  return make_pair(f, pass);
}
```

## 最近公共祖先 LCA

```cpp
struct LCA {
  const int lgn;
  VV<int> f;
  vector<int> dep;
  LCA(int n, int s = 1) : lgn(1 + std::__lg(n)), f(n, lgn), dep(n) {
    dfs(s, 0);
    for (int i = 1; i < lgn; i++) {
      for (int j = 0; j < n; j++) {
        f[j][i] = f[f[j][i - 1]][i - 1];
      }
    }
  }
  void dfs(int x, int fa) {
    f[x][0] = fa;
    dep[x] = dep[fa] + 1;
    for (int u : G[x]) {
      if (u != fa) {
        dfs(u, x);
      }
    }
  }
  int query(int x, int y) {
    if (dep[x] > dep[y])
      swap(x, y);
    while (dep[x] < dep[y]) {
      y = f[y][std::__lg(dep[y] - dep[x])];
    }
    for (int i = lgn - 1; i >= 0; i--) {
      if (f[x][i] != f[y][i]) {
        x = f[x][i], y = f[y][i];
      }
    }
    return x == y ? x : f[x][0];
  }
};
```

## 树链剖分

```cpp
struct HLD {
  vector<int> sz, dep, fa, son, top, dfn;
  int cnt = 0;
  HLD(int n, int r = 1) : sz(n), dep(n), fa(n), son(n), top(n), dfn(n) {
    dfs1(r), dfs2(r, r);
  }
  void dfs1(int u, int f = 0) {
    dep[u] = dep[f] + 1;
    fa[u] = f, sz[u] = 1, top[u] = u;
    for (int v : G[u]) {
      if (v != f) {
        dfs1(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) {
          son[u] = v;
        }
      }
    }
  }
  void dfs2(int u, int tp, int f = 0) {
    top[u] = tp, dfn[u] = ++cnt;
    if (son[u] != 0) {
      dfs2(son[u], tp, u);
      for (int v : G[u]) {
        if (v != f && v != son[u]) {
          dfs2(v, v, u);
        }
      }
    }
  }
  int qpath(int x, int y) {
    while (top[x] != top[y]) {
      if (dep[top[x]] > dep[top[y]]) {
        swap(x, y);
      }
      y = fa[top[y]];
    }

    return dep[x] < dep[y] ? x : y;
  }
};
```

## Tarjan

```cpp
using Vertex = std::vector<int>;
using Edges = std::vector<Vertex>;

struct SCC {
  std::vector<int> id;
  std::vector<Vertex> group;
  SCC(int n) : id(n) {}
};

struct SCCImpl : SCC {
  const int n;
  const Edges &E;
  std::vector<int> low, dfn, stk;
  std::vector<bool> flag;
  int cnt = 0;
  void tarjan(int u) {
    low[u] = dfn[u] = ++cnt;
    stk.push_back(u), flag[u] = true;
    for (int v : E[u]) {
      if (dfn[v] == 0) {
        tarjan(v);
        low[u] = std::min(low[u], low[v]);
      } else if (flag[v]) {
        low[u] = std::min(low[u], dfn[v]);
      }
    }
    if (dfn[u] == low[u]) {
      Vertex g;
      while (true) {
        int v = stk.back();
        stk.pop_back();
        g.push_back(v);
        flag[v] = false;
        if (u == v)
          break;
      }
      group.push_back(g);
    }
  }
  SCCImpl(const Edges &E_) : SCC(E_.size()), n(E_.size()), E(E_), low(n), dfn(n), flag(n) {
    for (int i = 1; i < n; i++) {
      if (dfn[i] == 0)
        tarjan(i);
    }
    group.emplace_back(); // 占位，保证 id > 0
    std::reverse(group.begin(), group.end());
    for (int i = 0; i < group.size(); i++) {
      for (int u : group[i]) {
        id[u] = i;
      }
    }
  }
};
```

# 动态规划

## 背包

### 01 背包

给定体积为 $v_i$，价值 $w_i$ 的 $N$ 个物品，背包容积为
$M$，每个物品只能取 $1$ 个，求最大价值。

```cpp
for (int i = 1; i <= n; i++)
  for (int j = m; j >= v[i]; j--)
    dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
for (int j = 1; j <= m; j++)
  ans = max(ans, dp[j]);
```

### 完全背包

给定体积为 $v_i$，价值 $w_i$ 的 $n$ 个物品，背包容积为
$v$，每个物品任意取，求最大价值。

```cpp
for (int i = 1; i <= n; i++)
    for (int j = v[i]; j <= m; j++)
        dp[j] = max(dp[j], dp[j-v[i]] + w[i]);
for (int j = 1; j <= m; j++)
    ans = max(ans, dp[j]);
```

### 多重背包

给定体积为 $v_i$，价值 $w_i$ 的 $N$ 个物品，背包容积为 $M$，每个物品有
$c_i$ 个，求最大价值。

如各种背包组合（如洛谷 P1833 樱花），通常把完全背包转为 $99999$
个（适当调节）多重背包，再按 01 背包来。

```cpp
int tm = 1;
for (int i = 1; i <= n; i++) {
    int vi = rr(), ci = rr(), wi = rr();
    if (wi == 0)
        wi = 99999;
    int b = 1;
    for (int b = 1; b < wi; b *= 2) {
        v[tm] = vi * b, w[tm] = ci * b;
        wi -= b, tm++;
    }
    v[tm] = vi * wi, w[tm] = ci * wi;
    tm++;
}
for (int i = 1; i <= tm - 1; i++)
    for (int j = tsum; j >= v[i]; j--)
        dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
ll ans = 0;
for (int i  = 0; i <= tsum; i++)
    ans = max(dp[i], ans);
```

## 最长公共上升序列

给出 $1,2,\ldots,n$ 的两个排列 $a$ 和 $b$ ，求它们的最长公共子序列。

```cpp
int f[MN], ma[MN], b[MN], n, len = 0;
memset(f, 0x3f, sizeof(f));  f[0] = 0;
for (int i = 1; i <= n; i++)  ma[rr()] = i;
for (int i = 1; i <= n; i++)  b[i] = rr();
for (int i = 1; i <= n; i++) {
    int l = 0,r = len;
    if (ma[b[i]] > f[len])
        f[++len] = ma[b[i]];
    else {
        while (l < r) {
            int mid = (l + r) / 2;
            if (f[mid] > ma[b[i]])  r = mid;
            else  l = mid+1;
        }
    }
    f[l] = min(ma[b[i]], f[l]);
}
```

## 数字计数

试计算在区间 $1$ 到 $n$ 的所有整数中，数码
$x(0 \leqslant x \leqslant 9)$ 共出现了多少次？

```cpp
int addup(int n, int x) {
    int ans = 0, m = 1;
    while (m <= n){
        int a = n / (m * 10), b = n / m % 10, c = n % m;
        if (x > 0){
            if (b > x) ans += m;
            else if (b == x) ans += c + 1;
        } else if (b == 0) {
            ans += c + 1 - m;
        }  ans += a * m, m *= 10;
    }  return ans;
}
```

试计算在区间 $1$ 到 $n$ 的所有整数中，出现数码
$x(0 \leqslant x \leqslant 9)$ 的数字有多少？

```cpp
// 预计算
ll dp[20], m = 1;
for (int i = 1; i <= 9; i++) {
    dp[i] = dp[i - 1] * 9 + m;
    m *= 10;
}
ll addup(ll n, ll x) {
    ll m = 1, i = 0;
    while (m <= n)  i++, m *= 10;
    ll ans = 0, t;
    while (m) {
        t = n / m, n = n % m;
        ans += t * dp[i];
        if (t == x) {
            ans += n + 1;
            break;
        } else if (t > x) {
            ans += - dp[i] + m;
        }  i--, m /= 10;
    }  return ans;
}
```

# 数据结构

## 链表

```cpp
struct Node { int val; Node *prev, *next; };
struct List {
    Node *head, *tail; int len;
    List() {
        head = new Node(); tail = new Node();
        head->next = tail; tail->prev - head;
        len = 0;
    } // 在节点后 p 后插入值 v
    void insert(Node *p,int v) {
        Node *q = new Node(); q->val = v;
        p->next->prev = q; q->next = p->next;
        p->next = q; q->prev = p;
        len++;
    } // 删除节点 p
    void erase(Node *p) {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p; len--;
    } // 清空链表
    ~List() {
        while(head != tail) {
            head = head->next;
            delete head->prev;
        } delete tail; len = 0;
    }
};
```

链表的遍历。

```cpp
for(Node *p=l->head->next; p!=l->tail; p=p->next)
    //正序遍历
for(Node *p=l->tail->prev; p!=l->head; p=p->prev)
    //逆序遍历
```

## 滑动窗口

```cpp
template <class T>
auto sliding(const vector<T> &v, int k) {
  int l = 0, r = -1, n = v.size();
  vector<int> q(n), ret(n);
  for (int i = 0; i < n; i++) {
    while (l <= r && i - k >= q[l])
      l++;
    while (l <= r && v[i] < v[q[r]])
      r--;
    q[++r] = i;
    ret[i] = q[l];
  }
  return ret;
}
```

## 并查集

```cpp
struct DSU {
  vector<int> fa;
  DSU(int n) : fa(n) {
    for (int i = 0; i < n; i++)
      fa[i] = i;
  }
  int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
  }
  bool same(int x, int y) {
    return find(x) == find(y);
  }
  void merge(int x, int y) {
    x = find(x), y = find(y);
    fa[x] = y;
  }
};
```

## 树状数组

树状数组可以维护数组 $a$ 实现：1. 将某个数加上 $x$。2. 前缀和。

```cpp
template <class T>
struct fwtree_1 {
  vector<T> v;
  fwtree_1(int n = 0) : v(n) {}
  int len() {
    return v.size();
  }
  void add(int i, T x) {
    for (; 0 < i && i < len(); i += i & -i)
      v[i] += x;
  }
  void init(const vector<T> &a) {
    for (int i = 1; i < len(); i++) {
      v[i] += a[i];
      int j = i + (i & -i);
      if (j < len())
        v[j] += v[i];
    }
  }
  T sum(int i) {
    T sum = 0;
    for (; i > 0; i -= i & -i)
      sum += v[i];
    return sum;
  }
  T sum(int l, int r) {
    return sum(r) - sum(l - 1);
  }
};
```

##### 区间加 & 区间求和

维护数组 $a$ 的额外差分数组 $b$，当我们对 $a$ 的前缀 $r$ 求和时有
$$\sum_{i=1}^r \sum_{j=1}^i b_j = \sum_{i=1}^rb_i(r-i+1) = (r+1)\sum_{i=1}^rb_i - \sum_{i=1}^rb_ii$$
因此还需要两个树状数组来维护 $\sum b_i$ 和 $\sum b_ii$。

```cpp
template <class T>
struct fwtree_2 {
  int len;
  vector<T> v1, v2, u;
  fwtree_2(int l = 0) : len(l), u(len), v1(len), v2(len) {}
  void init(const vector<T> &a) {
    for (int i = 1; i < len; i++) {
      u[i] += a[i];
      int j = i + (i & -i);
      if (j < len)
        u[j] += u[i];
    }
  }
  void add(int l, int r, T k) {
    add(v1, l, k);
    add(v1, r + 1, -k);
    add(v2, l, l * k);
    add(v2, r + 1, -(r + 1) * k);
  }
  T sum(int l, int r) {
    return sum(r) - sum(l - 1);
  }
  private:
  void add(vector<T> &v, int i, T x) {
    for (; i < len; i += i & -i)
      v[i] += x;
  }
  T sum(vector<T> &v, int i) {
    T sum = 0;
    for (; i > 0; i -= i & -i)
      sum += v[i];
    return sum;
  }
  T sum(int i) {
    return T(i + 1) * sum(v1, i) + sum(u, i) - sum(v2, i);
  }
};
```

## ST 表

因为 `std::__lg(n)`，不需要预处理 $\log_2$。令 $st(i,j)$ 表示区间
$[i,i+2^j-1]$ 的最大值，显然 $ST(i,0)=a_i$。状态转移方程
$$ST(i,j+1) = \max(f(i,j) , f(i+2^{j},j))$$ 对于 RMQ 问题，记
$s = \lfloor\log_2(r-l+1)\rfloor$，我们总是可以用两个区间 $[l,l+2^s-1]$
和 $[r-2^s+1,r]$ 来覆盖所查询区间。

```cpp
template <class T>
struct SparseTable {
  int n, lgn;
  VV<T> v;
  SparseTable(int a) : n(a), lgn(1 + std::__lg(n)), v(lgn, n) {}
  template <class iter>
  void init(iter first, iter last) {
    copy(first, last, v[0]);
    for (int i = 1; i < lgn; i++) {
      int ti = 1 << (i - 1);
      for (int j = 0; j <= n - 2 * ti; j++) {
        v[i][j] = max(v[i - 1][j], v[i - 1][j + ti]);
      }
    }
  }
  T query(int l, int r) {
    int s = std::__lg(r - l + 1);
    return max(v[s][l], v[s][r - (1 << s) + 1]);
  }
};
```

## 线段树

单点修改，区间查询。

```cpp
template <class Val>
struct SegmentTree {
  const int N;
  vector<Val> val;
  // 0 ~ N - 1
  SegmentTree(int n) : N(2 << std::__lg(n)), val(N * 2) {
    assert(n > 0);
  }
  template <class iter>
  void build(iter first, iter last) {
    std::copy(first, last, val.begin() + N);
    for (int i = N - 1; i >= 1; i--)
      pull(i);
  }
  void modify(int i, Val x) {
    modify(i, x, 1, 0, N);
  }
  Val query(int l, int r) {
    return query(l, r + 1, 1, 0, N);
  }
#define lson p * 2
#define rson p * 2 + 1
  private:
  void pull(int p) {
    val[p] = val[lson] + val[rson];
  }
  void modify(int i, Val x, int p, int L, int R) {
    if (R - L == 1) {
      val[p] += x;
    } else {
      int M = (L + R) / 2;
      if (i < M)
        modify(i, x, lson, L, M);
      if (i >= M)
        modify(i, x, rson, M, R);
      pull(p);
    }
  }
  Val query(int l, int r, int p, int L, int R) {
    if (l <= L && R <= r) {
      return val[p];
    } else {
      int M = (L + R) / 2;
      Val ret = Val();
      if (l < M)
        ret = ret + query(l, r, lson, L, M);
      if (r > M)
        ret = ret + query(l, r, rson, M, R);
      return ret;
    }
  }
#undef lson
#undef rson
};
```

区间修改，区间查询。

```cpp
template <class Val, class Tag>
struct LazySegmentTree {
  const int N;
  vector<Val> val;
  vector<Tag> tag;
  // 0 ~ N - 1
  LazySegmentTree(int n) : N(2 << std::__lg(n)), val(N * 2), tag(N * 2) {
    assert(n > 0);
  }
  template <class iter>
  void build(iter first, iter last) {
    std::copy(first, last, val.begin() + N);
    for (int i = N - 1; i >= 1; i--)
      pull(i);
  }
  void modify(int l, int r, Tag t) {
    modify(l, r + 1, t, 1, 0, N);
  }
  Val query(int l, int r) {
    return query(l, r + 1, 1, 0, N);
  }
#define lson p * 2
#define rson p * 2 + 1
  private:
  void pull(int p) {
    val[p] = val[lson] + val[rson];
  }
  void push(int p) {
    Tag &tp = tag[p];
    if (tp.flag) {
      val[lson].apply(tp), tag[lson].apply(tp);
      val[rson].apply(tp), tag[rson].apply(tp);
      tp.flag = false;
    }
  }
  void modify(int l, int r, Tag t, int p, int L, int R) {
    if (l <= L && R <= r) {
      val[p].apply(t);
      tag[p].apply(t);
    } else {
      int M = (L + R) / 2;
      push(p);
      if (l < M)
        modify(l, r, t, lson, L, M);
      if (r > M)
        modify(l, r, t, rson, M, R);
      pull(p);
    }
  }
  Val query(int l, int r, int p, int L, int R) {
    if (l <= L && R <= r) {
      return val[p];
    } else {
      int M = (L + R) / 2;
      Val ret = Val();
      push(p);
      if (l < M)
        ret = ret + query(l, r, lson, L, M);
      if (r > M)
        ret = ret + query(l, r, rson, M, R);
      return ret;
    }
  }
#undef lson
#undef rson
};
```

# 字符串

## KMP

##### 前缀函数

对于长为 $n$ 的字符串 $s$，定义每个位置的前缀函数 $\pi(i)$，值为
$s(0,i)$ 的真后缀与 $s$ 的真前缀中相等的最长的长度。

设最长的长度为 $j_1=\pi(i)$，如何找到其次长 $j_2$？

注意到后缀 $j_1$ 位与前缀 $j_1$ 位完全相同，故 $j_2$ 为前缀 $j_1$
中相等真前缀与真后缀中最长的，即 $$j_{n+1} = \pi(j_n-1)$$

```cpp
auto pre_kmp(const string &s) {
  int n = s.length();
  vector<int> pi(n + 1);
  for (int i = 1; i < n; i++) {
    int j = pi[i];
    while (j > 0 && s[i] != s[j])
      j = pi[j];
    pi[i + 1] = j + (s[i] == s[j]);
  }
  return pi;
}
```

##### Knuth - Morris - Pratt

给定一个文本 $t$ 和一个字符串 $s$ （模式串），尝试找到 $s$ 在 $t$
中所有出现。

构造字符串 $s+*+t$，其中 $*$
为不出现在两个字符串中的特殊字符，此时字符串 $t$ 的前缀恰为
$s$，$\pi(i)$ 的意义为 $s$ 在此处的出现长度。

当 $\pi(i)=|s|$ 时，$s$ 在此处完全出现。

当字符串已经合并时，直接计算 $\pi(i)$ 函数即可，字符串出现位置是
$i-2|s|$。

```cpp
auto kmp(const string &s, const string &t) {
  auto pi = pre_kmp(s);
  int n = t.length();
  vector<int> p(n + 1);
  for (int i = 0; i < n; i++) {
    int j = p[i];
    while (j > 0 && t[i] != s[j])
      j = pi[j];
    p[i + 1] = j + (t[i] == s[j]);
  }
  return make_pair(pi, p);
}
```

##### EXKMP

对于长为 $n$ 的字符串 $s$，定义每个位置的后缀函数 $z(i)$，值为
$s(i,n-1)$ 的真前缀与 $s$ 真前缀中相等的最长的长度。

```cpp
auto pre_z_algo(const string &s) {
  int n = s.length();
  vector<int> z(n + 1);
  for (int i = 1, l = 0, r = 0; i <= n; i++) {
    int &k = z[i], u = r - i;
    if (u > 0)
      k = min(u, z[i - l]);
    while (i + k < n && s[k] == s[i + k])
      k++;
    if (i + k > r)
      l = i, r = i + k;
  }
  z[0] = n;
  return z;
}

auto z_algo(const string &s, const string &t) {
  auto z = pre_z_algo(s);
  int n = t.length();
  vector<int> z2(n + 1);
  for (int i = 0, l = 0, r = 0; i <= n; i++) {
    int &k = z2[i], u = r - i;
    if (u > 0)
      k = min(u, z[i - l]);
    while (i + k < n && s[k] == t[i + k])
      k++;
    if (i + k > r)
      l = i, r = i + k;
  }
  return make_pair(z, z2);
}
```

## Manacher

```cpp
template <int off>
auto manacher(const string &s) {
  int n = s.size();
  vector<int> m(n);
  m[0] = off == 0;
  for (int i = 1, l = 0, r = 0; i < n; i++) {
    int &k = m[i], u = r - i;
    if (u > 0)
      k = min(u, m[2 * l - i]);
    while (0 <= i - k - off && i + k < n
            && s[i - k - off] == s[i + k])
      k++;
    if (i + k > r)
      l = i, r = i + k;
  }
  return m;
}

vector<int> manacher_odd(const string &s) {
  return manacher<0>(s);
}

vector<int> manacher_even(const string &s) {
  return manacher<1>(s);
}
```

## 后缀数组

```cpp
auto sa_doubleing(auto first, auto last, int m = 128) {
  int n = last - first;
  std::vector<int> cnt(std::max(n, m)), sa(n), rk(n + 1, -1), id(n + 1, -1);
  std::copy(first, last, rk.begin());
  for (int i = 0; i < n; i++)
    cnt[rk[i]]++;
  for (int i = 1; i < m; i++)
    cnt[i] += cnt[i - 1];
  for (int i = n - 1; i >= 0; i--)
    sa[--cnt[rk[i]]] = i;
  for (int k = 1; k < n; k *= 2) {
    int p = 0;
    for (int i = n - k; i < n; i++)
      id[p++] = i;
    for (int i = 0; i < n; i++)
      if (sa[i] >= k)
        id[p++] = sa[i] - k;
    std::fill(cnt.begin(), cnt.end(), 0);
    for (int i = 0; i < n; i++)
      cnt[rk[i]]++;
    for (int i = 1; i < m; i++)
      cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--)
      sa[--cnt[rk[id[i]]]] = id[i];
    std::fill(id.begin(), id.end(), -1);
    std::swap(rk, id);
    rk[sa[0]] = 0, p = 0;
    for (int i = 1; i < n; i++) {
      bool f = id[sa[i]] == id[sa[i - 1]] && id[sa[i] + k] == id[sa[i - 1] + k];
      rk[sa[i]] = f ? p : ++p;
    }
    if (p == n - 1)
      break;
    m = p + 1;
  }
  return sa;
}
```
