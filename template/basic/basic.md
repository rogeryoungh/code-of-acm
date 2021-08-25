# 基础模块

## 初始定义

```cpp
#define ACM_MOD 998244353
```

如果定义了 `ACM_MOD`，那么模板将会设置此数为默认模数，调用时可以省略。

## 快速幂 | qpow

```cpp
ll qpow(ll a, ll b, ll m = ACM_MOD) {
    ll ret = m != 1;
    for (; b; b >>= 1) {
        if (b & 1)
            ret = a * ret % m;
        a = a * a % m;
    }
    return ret;
}
```

## 乘法逆元 | inv

```cpp
ll inv(ll a, ll m = ACM_MOD) {
    return qpow(a, m - 2, m);
}
```

## 取模 | mo

```cpp
ll mo(ll n, ll m = ACM_MOD) {
    return (n + m) % m;
}

ll momo(ll n, ll m = ACM_MOD) {
    return ((n % m) + m) % m;
}
```