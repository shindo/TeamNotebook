// maximize c^T x
// Ax <= b
// x >= 0

struct LPSolver {
	int m, n;
	ve<int> B, N;
	ve< ve<double> > D;

	LPSolver(const ve< ve<double> > &A, const ve<double> &b, const ve<double> &c) :
		m(b.size()), n(c.size()), N(n+1), B(m), D(m+2, ve<double>(n+2)) {
			REP(i, 0, m) REP(j, 0, n) D[i][j] = A[i][j];
			REP(i, 0, m) { B[i] = n+i; D[i][n] = -1; D[i][n+1] = b[i]; }
			REP(j, 0, n) { N[j] = j; D[m][j] = -c[j]; }
			N[n] = -1; D[m+1][n] = 1;
		}

	void Pivot(int r, int s) {
		REP(i, 0, m + 2) if (i != r)
			REP(j, 0, n + 2) if (j != s)
				D[i][j] -= D[r][j] * D[i][s] / D[r][s];
		REP(j, 0, n + 2) if (j != s) D[r][j] /= D[r][s];
		REP(i, 0, n + 2) if (i != r) D[i][s] /= -D[r][s];
		D[r][s] = 1.0 / D[r][s];
		swap(B[r], N[s]);
	}

	bool Simplex(int phase) {
		int x = phase == 1 ? m+1 : m;
		while (true) {
			int s = -1;
			REP(j, 0, n + 1) {
				if (phase == 2 && N[j] == -1) continue;
				if (s == -1 || D[x][j] < D[x][s] || D[x][j] == D[x][s] && N[j] < N[s]) s = j;
			}
			if (D[x][s] >= -EPS) return true;
			int r = -1;
			REP(i, 0, m) {
				if (D[i][s] <= 0) continue;
				if (r == -1 || D[i][n+1] / D[i][s] < D[r][n+1] / D[r][s] ||
						D[i][n+1] / D[i][s] == D[r][n+1] / D[r][s] && B[i] < B[r]) r = i;
			}
			if (r == -1) return false;
			Pivot(r, s);
		}
	}

	double Solve(ve<double> &x) {
		int r = 0;
		REP(i, 1, m) if (D[i][n+1] < D[r][n+1]) r = i;
		if (D[r][n+1] <= -EPS) {
			Pivot(r, n);
			if (!Simplex(1) || D[m+1][n+1] < -EPS) return -numeric_limits<double>::infinity();
			REP(i, 0, m) if (B[i] == -1) {
				int s = -1;
				REP(j, 0, n + 1)
					if (s == -1 || D[i][j] < D[i][s] || D[i][j] == D[i][s] && N[j] < N[s]) s = j;
				Pivot(i, s);
			}
		}
		if (!Simplex(2)) return numeric_limits<double>::infinity();
		x = ve<double>(n);
		REP(i, 0, m) if (B[i] < n) x[B[i]] = D[i][n+1];
		return D[m][n+1];
	}
};
