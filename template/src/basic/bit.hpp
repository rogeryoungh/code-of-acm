#include "basic/index.hpp"

inline int popcnt(std::uint64_t x) {
	return __builtin_popcountll(x);
}

inline int bsr(std::uint32_t x) {
	return 31 - __builtin_clz(x);
}

inline int bsr(std::uint64_t x) {
	return 63 - __builtin_clzll(x);
}

inline int bsf(std::uint64_t x) {
	return __builtin_ctzll(x);
}
