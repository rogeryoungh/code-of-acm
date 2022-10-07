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
