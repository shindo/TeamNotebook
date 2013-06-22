pair<int, ve<int> > GetMinCut(ve< ve<int> > &weights) {
	int N = weights.size();
	ve<int> used(N), cut, best_cut;
	int best_weight = -1;

	REPD(phase, 0, N) {
		ve<int> w = weights[0];
		ve<int> added = used;
		int prev, last = 0;
		REP(i, 0, phase) {
			prev = last;
			last = -1;
			REP(j, 1, N)
				if (!added[j] && (last == -1 || w[j] > w[last])) last = j;
			if (i == phase-1) {
				REP(j, 0, N) weights[prev][j] += weights[last][j];
				REP(j, 0, N) weights[j][prev] = weights[prev][j];
				used[last] = true;
				cut.pb(last);
				if (best_weight == -1 || w[last] < best_weight) {
					best_cut = cut;
					best_weight = w[last];
				}
			} else {
				REP(j, 0, N)
					w[j] += weights[last][j];
				added[last] = true;
			}
		}
	}
	return mp(best_weight, best_cut);
}
