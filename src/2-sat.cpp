// need: graph, scc
int main() {
	_(used, false);
	REP(i, 0, N)
		if (!used[i]) dfs1 (i);

	_(compID, -1);
	int id = 0;
	REPD(i, 0, N) {
		int v = order[i];
		if (comp[v] == -1) dfs2(v, id++);
	}

	REP(i, 0, N) 
		if (compID[i] == compID[i^1]) {
			puts ("NO SOLUTION");
			return 0;
		}
	REP(i, 0, N) {
		int ans = comp[i] > comp[i^1] ? i : i^1;
		printf ("%d ", ans);
	}
}
