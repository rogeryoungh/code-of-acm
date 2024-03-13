#pragma once
#include "../base.hpp"

// #region snippet
bool is_prime_small(i64 n) {
	if (n < 64)
		return (0x28208a20a08a28ac >> n) & 1;
	if ((0xdf75d77d >> (n % 30)) & 1)
		return false;
	if (n % 7 == 0 || n % 11 == 0)
		return false;
	return true;
}
// #endregion snippet
