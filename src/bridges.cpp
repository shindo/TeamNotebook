// need: graph( head, to, nxt ), used, tin, fup, timer
void dfs (int v, int par = -1) {
	used[v] = true;
	tin[v] = fup[v] = timer++;
	for(int e = head[v]; e != -1; e = nxt[e]) {
		int u = to[e];
		if (u == par)  continue;
		if (used[u])
			fup[v] = min (fup[v], tin[u]);
		else {
			dfs (u, v);
			fup[v] = min (fup[v], fup[u]);
			if (fup[u] > tin[v])
				IS_BRIDGE(v, u);
		}
	}
}
 
void find_bridges() {
	timer = 0;
	_(used, 0)
	REP(i, 0, N)
		if (!used[i]) dfs (i);
}
