ll p = lg2[y - x + 1], q = y - (1<<s) + 1;
return max(ST[x][p], ST[q][p]);