#ifndef ACM_BASIC_MO_H
#define ACM_BASIC_MO_H


template <std::uint32_t P>
struct MontgomeryModInt32 {
public:
    using i32 = std::int32_t;
    using u32 = std::uint32_t;
    using i64 = std::int64_t;
    using u64 = std::uint64_t;

private:
    u32 v;

    static constexpr u32 get_r() {
        u32 iv = P;
        for (u32 i = 0; i != 4; ++i) iv *= 2U - P * iv;
        return -iv;
    }

    static constexpr u32 r = get_r(), r2 = -u64(P) % P;

    static_assert((P & 1) == 1);
    static_assert(-r * P == 1);
    static_assert(P < (1 << 30));

public:
    static constexpr u32 pow_mod(u32 x, u64 y) {
        if ((y %= P - 1) < 0)
            y += P - 1;
        u32 res = 1;
        for (; y != 0; y >>= 1, x = u64(x) * x % P)
            if (y & 1)
                res = u64(res) * x % P;
        return res;
    }

    static constexpr u32 get_pr() {
        u32 tmp[32] = {}, cnt = 0;
        const u64 phi = P - 1;
        u64 m = phi;
        for (u64 i = 2; i * i <= m; ++i) {
            if (m % i == 0) {
                tmp[cnt++] = i;
                while (m % i == 0) m /= i;
            }
        }
        if (m > 1)
            tmp[cnt++] = m;
        for (u64 res = 2; res <= phi; ++res) {
            bool flag = true;
            for (u32 i = 0; i != cnt && flag; ++i) flag &= pow_mod(res, phi / tmp[i]) != 1;
            if (flag)
                return res;
        }
        return 0;
    }

    MontgomeryModInt32() = default;

    ~MontgomeryModInt32() = default;

    constexpr MontgomeryModInt32(u32 v) : v(reduce(u64(v) * r2)) {}

    constexpr MontgomeryModInt32(const MontgomeryModInt32 &rhs) : v(rhs.v) {}

    static constexpr u32 reduce(u64 x) { return x + (u64(u32(x) * r) * P) >> 32; }

    static constexpr u32 norm(u32 x) { return x - (P & -(x >= P)); }

    constexpr u32 get() const {
        u32 res = reduce(v) - P;
        return res + (P & -(res >> 31));
    }

    explicit constexpr operator u32() const { return get(); }

    explicit constexpr operator i32() const { return i32(get()); }

    constexpr MontgomeryModInt32 &operator=(const MontgomeryModInt32 &rhs) { return v = rhs.v, *this; }

    constexpr MontgomeryModInt32 operator-() const {
        MontgomeryModInt32 res;
        return res.v = (P << 1 & -(v != 0)) - v, res;
    }

    constexpr MontgomeryModInt32 inv() const { return pow(-1); }

    constexpr MontgomeryModInt32 &operator+=(const MontgomeryModInt32 &rhs) {
        return v += rhs.v - (P << 1), v += P << 1 & -(v >> 31), *this;
    }

    constexpr MontgomeryModInt32 &operator-=(const MontgomeryModInt32 &rhs) {
        return v -= rhs.v, v += P << 1 & -(v >> 31), *this;
    }

    constexpr MontgomeryModInt32 &operator*=(const MontgomeryModInt32 &rhs) {
        return v = reduce(u64(v) * rhs.v), *this;
    }

    constexpr MontgomeryModInt32 &operator/=(const MontgomeryModInt32 &rhs) {
        return this->operator*=(rhs.inv());
    }

    friend MontgomeryModInt32 operator+(const MontgomeryModInt32 &lhs, const MontgomeryModInt32 &rhs) {
        return MontgomeryModInt32(lhs) += rhs;
    }

    friend MontgomeryModInt32 operator-(const MontgomeryModInt32 &lhs, const MontgomeryModInt32 &rhs) {
        return MontgomeryModInt32(lhs) -= rhs;
    }

    friend MontgomeryModInt32 operator*(const MontgomeryModInt32 &lhs, const MontgomeryModInt32 &rhs) {
        return MontgomeryModInt32(lhs) *= rhs;
    }

    friend MontgomeryModInt32 operator/(const MontgomeryModInt32 &lhs, const MontgomeryModInt32 &rhs) {
        return MontgomeryModInt32(lhs) /= rhs;
    }

    friend bool operator==(const MontgomeryModInt32 &lhs, const MontgomeryModInt32 &rhs) {
        return norm(lhs.v) == norm(rhs.v);
    }

    friend bool operator!=(const MontgomeryModInt32 &lhs, const MontgomeryModInt32 &rhs) {
        return norm(lhs.v) != norm(rhs.v);
    }

    friend std::istream &operator>>(std::istream &is, MontgomeryModInt32 &rhs) {
        return is >> rhs.v, rhs.v = reduce(u64(rhs.v) * r2), is;
    }

    friend std::ostream &operator<<(std::ostream &os, const MontgomeryModInt32 &rhs) {
        return os << rhs.get();
    }

    constexpr MontgomeryModInt32 pow(i64 y) const {
        if ((y %= P - 1) < 0)
            y += P - 1;  // phi(P) = P - 1, assume P is a prime number
        MontgomeryModInt32 res(1), x(*this);
        for (; y != 0; y >>= 1, x *= x)
            if (y & 1)
                res *= x;
        return res;
    }

    constexpr MontgomeryModInt32 sqrt() const {
#ifdef ACM_MATH_CIPOLLA_H
        return Cipolla(get(), P).first;
#else
        return 1;
#endif
    }
};

using m32 = MontgomeryModInt32<P>;

#endif
