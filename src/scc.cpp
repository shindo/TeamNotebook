void dfs(int v) {
	timer++;
	dfsnum[v] = lownum[v] = timer;
	st[stSize++] = v;
	inSt[v] = true;

	for(int e = head[v]; e != -1; e = nxt[e]) {
		int w = to[e];
		if(dfsnum[w] == 0) {
			dfs(w, v);
			lownum[v] = min(lownum[v], lownum[w]);
		} else if(inSt[w]) {
			lownum[v] = min(lownum[v], dfsnum[w]);
		}
	}

	if(lownum[v] == dfsnum[v]) {
		int w;
		do {
			w = st[--stSize];
			inSt[w] = false;
			comp[w] = compID;
		} while(w != v);
		compID++;
	}
}
