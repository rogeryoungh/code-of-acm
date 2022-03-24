double l = 0, r = 10, eps = 1E-9;
for (int i = 0; i < 200; i++) {
	double mid = (r + l) / 2;
	if (f(mid + eps) > f(mid - eps))
		l = mid;
	else
		r = mid;
}
