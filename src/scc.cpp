// need: graph (head, to, nxt), reverse graph (rhead, rto, rnxt)
// used, compID, order
void dfs1(int v) {
	used[v] = true;
	for(int e = head[v]; e != -1; e = nxt[e]) {
		if(!used[to[e]]) dfs1(to[e]);
	}
	order.pb(v);
}
void dfs2(int v, int id) {
	used[v] = true;
	compID[v] = id;
	for(int e = rhead[v]; e != -1; e = rnxt[e]) {
		if(!used[ rto[e] ]) dfs2(rto[e]);
	}
}
void main() {
	_(used, false);
	REP(i, 0, N)
		if(!used[i]) dfs1(i);
	_(used, false);
	int id = 0;
	REPD(i, 0, N) {
		int v = order[i];
		if(!used[v]) dfs2(v, id++);
	}
}
