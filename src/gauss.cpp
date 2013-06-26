// Ax = B. RETURN: determinant, A -> A^(-1), B -> solution
T GaussJordan(VVT &a, VT &b) {
	const int n = a.size();
	ve<int> irow(n), icol(n), ipiv(n);
	T det = 1;

	REP(i, 0, n) {
		int pj = -1, pk = -1;
		REP(j, 0, n) if (!ipiv[j])
			REP(k, 0, n) if (!ipiv[k])
				if (pj == -1 || fabs(a[j][k]) > fabs(a[pj][pk])) { pj = j; pk = k; }
		if (fabs(a[pj][pk]) < EPS) { cerr << "Matrix is singular." << endl; exit(0); }
		ipiv[pk]++;
		swap(a[pj], a[pk]);
		swap(b[pj], b[pk]);
		if (pj != pk) det *= -1;
		irow[i] = pj;
		icol[i] = pk;

		T c = 1.0 / a[pk][pk];
		det *= a[pk][pk];
		a[pk][pk] = 1.0;
		REP(p, 0, n) a[pk][p] *= c;
		b[pk] *= c;
		REP(p, 0, n) if (p != pk) {
			c = a[p][pk];
			a[p][pk] = 0;
			REP(q, 0, n) a[p][q] -= a[pk][q] * c;
			b[p] -= b[pk] * c;      
		}
	}

	REPD(p, 0, n) if (irow[p] != icol[p]) {
		REP(k, 0, n) swap(a[k][irow[p]], a[k][icol[p]]);
	}

	return det;
}
