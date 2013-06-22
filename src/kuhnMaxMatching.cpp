// need: graph( head, to, nxt ), used, mate
bool kuhn(int v) {
    if (used[v]) return false;
    used[v] = true;
    for(int e = head[v]; e != -1; e = nxt[e]) {
        if (mate[to[e]] == -1) {
            mate[to[e]] = v;
            return true;
        }
    }
    for(int e = head[v]; e != -1; e = nxt[e]) {
        if (kuhn(mate[to[e]])) {
            mate[to[e]] = v;
            return true;
        }
    }
    return false;
}

int max_matching() {
    int res = 0;
    REP(i, 0, n) {
        _(used, false);
        if (kuhn(i)) res++;
    }
    return res;
}
