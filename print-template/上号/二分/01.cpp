while (l < r) {
    int mid = (l + r) >> 1;
    if (aa[mid] >= x)  r = mid; // <=
    else  l = mid + 1;
}  return l;