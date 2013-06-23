// need: graph (head, nxt, to, from, capa, cost, flow)
// pi, dist, prve
void updatePotentials() {
	memcpy(pi, dist, sizeof(int) * N);
}

bool fordBellman(int src, int dst) {
	REP(i, 0, N) dist[i] = INF;
	dist[src] = 0;
	bool changed;

	REP(phase, 0, N) {
		changed = false;
		REP(v, 0, N) {
			if(dist[v] == INF) continue;
			for(int e = head[v]; e != -1; e = nxt[e]) {
				int u = to[e];
				if(capa[e] > flow[e] && dist[u] > dist[v] + cost[e]) {
					dist[u] = dist[v] + cost[e];
					prve[u] = e;
					changed = true;
				}
			}
		}
		if(!changed) break;
	}
	return !changed;
}

set< pii > q;
bool dijkstra(int src, int dst) {
	REP(i, 0, N) dist[i] = INF;
	dist[src] = 0;
	q.insert( mp(0, 0) );

	while(size(q)) {
		pii tmp = (*q.begin());
		int v = tmp.sc, d = tmp.fs;
		q.erase(q.begin());
		if(d != dist[v]) continue;

		for(int e = head[v]; e != -1; e = nxt[e]) {
			int u = to[e];
			if(capa[e] > flow[e] && dist[u] > dist[v] + cost[e] - pi[v] + pi[u]) {
				dist[u] = dist[v] + cost[e] - pi[v] + pi[u];
				prve[u] = e;
				q.insert( mp(dist[u], u) );
			}
		}
	}
	return dist[dst] != INF;
}

pii minCostMaxFlow(int src, int dst) {
	if(!fordBellman(src, dst)) return mp(0, 0);
	int sumFlow = 0, sumCost = 0;

	do {
		int curFlow = INF, curCost = 0;
		int cur = dst;
		while(cur != src) {
			int e = prve[cur];
			curFlow = min(curFlow, capa[e] - flow[e]);
			curCost += cost[e];
			cur = from[e];
		}
		cur = dst;
		while(cur != src) {
			int e = prve[cur];
			flow[e] += curFlow;
			flow[e ^ 1] -= curFlow;
			cur = from[e];
		}
		sumCost += curFlow * curCost;
		updatePotentials();
	} while(dijkstra(src, dst));

	return mp(sumFlow, sumCost);
}
