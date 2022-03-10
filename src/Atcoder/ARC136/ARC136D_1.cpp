#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

const int M = 10;
using DP_t = ll[M][M][M][M][M][M];
DP_t dp1, &dp2 = dp1;

int main() {
	int N;
	cin >> N;
	vector<int> A(N);
	int v[10];
	for (int i = 0; i < N; i++) {
		int t;
		cin >> t;
		A[i] = t;
		for (int j = 0; j < 6; j++) {
			v[j] = t % 10;
			t /= 10;
		}
		dp1[v[0]][v[1]][v[2]][v[3]][v[4]][v[5]]++;
	}
	for (v[0] = 0; v[0] < M; v[0]++) {
		for (v[1] = 0; v[1] < M; v[1]++) {
			for (v[2] = 0; v[2] < M; v[2]++) {
				for (v[3] = 0; v[3] < M; v[3]++) {
					for (v[4] = 0; v[4] < M; v[4]++) {
						for (v[5] = 0; v[5] < M; v[5]++) {
							// if (v[3] > 0)
							// 	goto end;

							auto &dp_ = dp2[v[0]][v[1]][v[2]][v[3]][v[4]][v[5]];
							for (int j = 1; j < (1 << 6); j++) {
								for (int k = 0; k < 6; k++) {
									if ((j >> k) & 1)
										v[k]--;
								}
								bool flag = true;
								for (int k = 0; k < 6; k++) {
									flag = flag && (v[k] >= 0);
								}
								if (flag) {
									if (__builtin_popcount(j) % 2) {
										dp_ += dp2[v[0]][v[1]][v[2]][v[3]][v[4]][v[5]];
									} else {
										dp_ -= dp2[v[0]][v[1]][v[2]][v[3]][v[4]][v[5]];
									}
								}
								for (int k = 0; k < 6; k++) {
									if ((j >> k) & 1)
										v[k]++;
								}
							}
						}
					}
				}
			}
		}
	}

	// end:
	ll ans = 0;
	for (int i = 0; i < N; i++) {
		int t = A[i];
		bool flag = true;
		for (int j = 0; j < 6; j++) {
			v[j] = 9 - (t % 10);
			flag = flag && ((t % 10) * 2 < 10);
			t /= 10;
		}
		// cerr << v[0] << " " << v[1] << " " << v[2] << " " << v[3] << " " << v[4] << " " << v[5]
		// 	 << "\n";
		ans += dp2[v[0]][v[1]][v[2]][v[3]][v[4]][v[5]];
		if (flag)
			ans--;
	}

	cout << ans / 2;

	return 0;
}
