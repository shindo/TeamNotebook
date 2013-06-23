// need: graph( head, nxt, to, capa, flow ), dist, q
bool bfs(int src, int dest) {
    _(dist, -1);
    dist[src] = 0;
    int H = 0;
    q[H ++] = src;
    REP(i, 0, H) {
        int cur = q[i];
        for(int e = head[cur]; e != -1; e = nxt[e]) {
            if (capa[e] > flow[e] && dist[to[e]] == -1) {
                dist[to[e]] = dist[cur] + 1;
                q[H ++] = to[e];
            }
        }
    }
    return dist[dest] >= 0;
}

int dfs(int cur, int curflow) {
    if (cur == dest) return curflow;
    int d ;
    for(int& e = work[cur]; e != -1; e = nxt[e]) {
        if (capa[e] > flow[e] && (dist[to[e]] == dist[cur] + 1) &&
                (d = dfs(to[e], min(curflow, capa[e] - flow[e])))) {
            flow[e] += d;
            flow[e ^ 1] -= d;
            return d;
        }
    }
    return 0;
}

int dinic() {
    int res = 0;
    while (bfs(src, des)) {
        int d;
        memcpy(work, head, sizeof(head));
        while (true) {
            d = dfs(src, INF);
            if (d == 0) break;
            res += d;
        }
    }
    return res;
}
