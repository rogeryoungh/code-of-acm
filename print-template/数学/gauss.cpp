double a[N][N];

bool Gauss(int n) {
	for (int i = 0; i < n; i++) {
		int mi = i;
		for (int j = i + 1; j < n; j++) {
			if (fabs(a[j][i]) > fabs(a[mi][i])) {
				mi = j;
			}
		}
		for (int j = 0; j < n + 1; j++) {
			swap(a[i][j], a[mi][j]);
		}
		if (fabs(a[i][i]) < eps) {
			return false;
		}
		for (int j = 0; j < n; j++) {
			if (j != i) {
				double tmp = a[j][i] / a[i][i];
				for (int k = i + 1; k < n + 1; k++) {
					a[j][k] -= a[i][k] * tmp;
				}
			}
		}
	}
	return true;
}
