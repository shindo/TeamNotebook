struct entry {
	int nr[2], p;
} L[MAXN], tmp[MAXN];
#define eq(a, b) ((a).nr[0] == (b).nr[0] && (a).nr[1] == (b).nr[1])
int cnt[MAXN], p[2][MAXN];

void radixPass(entry * a, int N, int pass, int K, entry * b) {
	memset(cnt, 0, (K + 1) * sizeof(int));
	REP(i, 0, N) cnt[a[i].nr[pass]]++;
	int sum = 0;
	REP(i, 0, K + 1) {
		sum += cnt[i];
		cnt[i] = sum - cnt[i];
	}
	REP(i, 0, N) b[cnt[a[i].nr[pass]]++] = a[i];
}

void makeSA(int * s, int N, int * suftab, int * isuftab) {
	REP(i, 0, N) p[0][i] = s[i];
	int k = 200;
	for(int step = 1, len = 1; ; step ^= 1, len <<= 1) {
		for(int i = 0, j = len; i < N; i++, j++) {
			L[i].nr[0] = p[step ^ 1][i];
			L[i].nr[1] = j < N ? p[step ^ 1][j] : 0;
			L[i].p = i;
		}
		radixPass(L, N, 1, k, tmp);
		radixPass(tmp, N, 0, k, L);
		k = 1;
		REP(i, 0, N) {
			p[step][L[i].p] = i > 0 && eq(L[i], L[i - 1]) ?
				p[step][L[i - 1].p] : k++;
		}
		if(k > N) break;
	}
	REP(i, 0, N) suftab[i] = L[i].p;
	REP(i, 0, N) isuftab[suftab[i]] = i;
}

void makeLCP(int * s, int * suftab, int * isuftab, int N, int * lcptab) {
	int cur = 0;
	REP(i, 0, N) {
		if(isuftab[i] == 0) continue;
		int ii = i + cur, jj = suftab[isuftab[i] - 1] + cur;
		while(ii < N && jj < N && s[ii] == s[jj]) ii++, jj++, cur++;
		lcptab[isuftab[i]] = cur--;
		if(cur < 0) cur = 0;
	}
}
