while (l < r) {
    int mid = (l + r + 1) >> 1;
    if (aa[mid] <= x)  l = mid; // >=
    else  r = mid - 1;
}  return l;