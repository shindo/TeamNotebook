// point projection on line (A, B)
pt getH(const pt & A, const pt & B) const {
	pt C = *this;
	pt v = B - A;
	pt u = C - A;
	double k = v ^ u / v.len();
	v = v.norm(k);
	pt H = A + v;
	return H;
}

// Intersection of lines (A, B) & (C, D)
int getIntersection(const pt & A, const pt & B, const pt & C, const pt & D,	pt & O) {
	pt v = B - A;
	double s1 = (C - A) * (D - A);
	double s2 = (D - B) * (C - B);
	double s = s1 + s2;
	if(doubleEqual(s, 0) ) {
		if(!A.isOnLine(C, D) ) {
			return 0;
		}
		return 2;
	}
	v = v / s; 
	v = v * s1;
	O = A + v;
	return 1;
}

// Intersection of circles (A, rA) & (B, rB)
int getIntersection(const pt & A, double rA, const pt & B, double rB, pt & M, pt & N) {
	double d = A.distTo(B);
	if(doubleLess(rA + rB, d) || doubleLess(d, fabs(rA - rB)) )	{
		return 0;
	}
	double a = (sqr(rA) - sqr(rB) + sqr(d) ) / 2 / d;
	double h = mySqrt(sqr(rA) - sqr(a));
	pt v = B - A;
	pt u = v.rotate();
	v = v.norm(a); 
	u = u.norm(h);
	pt H = A + v; 
	M = H + u;
	N = H - u;
	if(u.isZero()) return 1;
	return 2;
}

// Intersection of line (A, B) & circle (O, r)
int getIntersection(const pt & A, const pt & B,	const pt & O, double r,	pt & M,	pt & N) {
	double h = O.distTo(A, B); 
	if(doubleLess(r, h) ) {
		return 0;
	}
	pt H = O.getH(A, B);
	pt v = B - A;
	double k = mySqrt(sqr(r) - sqr(h) );
	v = v.norm(k);
	M = H + v;
	N = H - v;
	if(v.isZero() ) return 1;
	return 2;
}

// Tangent lines through point A to circle (O, r)
int getTangent(const pt & A, const pt & O, double r, pt & M, pt & N) {
	pt v = O - A; 
	double d = v.len();
	if(doubleLess(d, r) ) return 0;
	double alpha = asin(r / d);
	double L = mySqrt(sqr(d) - sqr(r));
	v = v.norm(L);
	M = A + v.rotate(alpha);  
	N = A - v.rotate(alpha);
	if(doubleEqual(r, d)) return 1;
	return 2;
}

// Outer tangent lines between circles (A, rA) & (B, rB)
void getOutTangent(pt A, double rA, pt B, double rB, pair<pt, pt> & P, pair<pt, pt> & Q) {
	if(rA > rB)	{
		swap(rA, rB);
		swap(A, B);
	}
	pt u = (A - B).rotate(asin(r / d)).rotate().norm(rA);
	P.first = A + u;
	Q.first = A - u;
	pt T1, T2;
	getTangent(A, B, rB - rA, T1, T2);
	P.second = T1 + u;
	Q.second = T2 - u;
}

// Inner tangent lines between circles (A, rA) & (B, rB)
void getInTangent(pt A, double rA, pt B, double rB, pair<pt, pt> & P, pair<pt, pt> & Q) {
	pt I = (A * rB / (rA + rB)) + (B * rA / (rA + rB));
	pt M1, N1, M2, N2;
	getTangent(I, A, rA, M1, N1);
	getTangent(I, B, rB, M2, N2);
	if(I.isOnLine(M1, M2)) P = mp(M1, M2), Q = mp(N1, N2);
	else P = mp(M1, N2), Q = mp(N1, M2);
}
