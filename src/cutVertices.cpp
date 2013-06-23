// need: graph (head, to, nxt), tin, fup, used, timer
void dfs (int v, int par = -1) {
	used[v] = true;
	tin[v] = fup[v] = timer++;
	int children = 0;
	for(int e = head[v]; e != -1; e = nxt[e]) {
		int u = to[e];
		if (u == par)  continue;
		if (used[u])
			fup[v] = min (fup[v], tin[u]);
		else {
			dfs (u, v);
			fup[v] = min (fup[v], fup[u]);
			if (fup[u] >= tin[v] && p != -1)
				IS_CUTPOINT(v);
			++children;
		}
	}
	if (p == -1 && children > 1)
		IS_CUTPOINT(v);
}
 
int main() {
	timer = 0;
	_(used, 0);
	dfs (0);
}
