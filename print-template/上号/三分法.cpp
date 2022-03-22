while (r - l > eps) {
    double mid = (r + l) / 2;
    if (f(mid + eps) > f(mid - eps))
        l = mid;
    else
        r = mid;
}