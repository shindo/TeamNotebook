// 1-indexation
void set(int x, int v) {
  while(x <= N) {
    tree[x] += v;
    x += (x & -x);
  }
}
int get(int x) {
  int res = 0;
  while(x) {
    res += tree[x];
    x -= (x & -x);
  }
  return res;
}

// 0-indexation
int sum(int r) {
	int res = 0;
	for (; r >= 0; r = (r & (r+1)) - 1)
		res += t[r];
	return res;
}
void inc(int i, int val) {
	for (; i < n; i = (i | (i+1)))
		t[i] += val;
}
