void dfs(int v, int u) {
	timer++;
	dfsnum[v] = lownum[v] = timer;
	int sons = 0;

	for(int e = head[v]; e != -1; e = nxt[e]) {
		int w = to[e];
		if(dfsnum[w] == 0) { // (v, w) is tree edge
			st[stSize++] = e;
			sons++;
			dfs(w, v);
			lownum[v] = min(lownum[v], lownum[w]);
			if( lownum[w] >= dfsnum[v] ) { // v is root or cut point
				if(u != -1) cutPoint[v] = true;

				// All edges from stack up to edge (v, w) form
				// new biconnected component
			}
		} else if(dfsnum[w] < dfsnum[v] && w != u) { // (v, w) is back edge
			st[stSize++] = e;
			lownum[v] = min(lownum[v], dfsnum[w]);
		}
	}

	if(u == -1 && sons > 1) cutPoint[v] = true;

	if(u != -1 && lownum[v] > dfsnum[u]) {
		// (v, u) is bridge
	}
}
