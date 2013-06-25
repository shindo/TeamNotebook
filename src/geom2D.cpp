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
	N = A + v.rotate(-alpha);
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

//принадлежность точки невыпуклому многоугольнику
//0 - на границе, 1 - вне, -1 - внутри
//F(y)=f(x1,x2,y)·f(x2,x3,y)···f(xn-1,xn,y)·f(xn,x1,y)
//f: пересекает ли луч выпущенный из точки middle вдоль оси x в направлении увеличения x отрезок (a,b) с учетом всех крайних случаев
public static int checkPolygon(Point2D a, Point2D b, Point2D middle)
{
    long ax = a.x - middle.x;
    long ay = a.y - middle.y;
    long bx = b.x - middle.x;
    long by = b.y - middle.y;
    if (ay * by > 0)
        return 1;
    int s = Long.signum(ax * by - ay * bx);
    if (s == 0)
    {
        if (ax * bx <= 0)
            return 0;
        return 1;
    }
    if (ay < 0)
        return -s;
    if (by < 0)
        return s;
    return 1;
}

//теорема Пика,решетчатый многоугольник
//S-площадь
//точек с целочисленными координатами:
//I - строго внутри, B - на границе
//S=I+B/2-1

//delaunayTriangulation
typedef double T;
struct triple {
    int i, j, k;
    triple() {}
    triple(int i, int j, int k) : i(i), j(j), k(k) {}
};
vector<triple> delaunayTriangulation(vector<T>& x, vector<T>& y) {
	int n = x.size();
	vector<T> z(n);
	vector<triple> ret;
	for (int i = 0; i < n; i++)
	    z[i] = x[i] * x[i] + y[i] * y[i];
	for (int i = 0; i < n-2; i++) {
	    for (int j = i+1; j < n; j++) {
		for (int k = i+1; k < n; k++) {
		    if (j == k) continue;
		    double xn = (y[j]-y[i])*(z[k]-z[i]) - (y[k]-y[i])*(z[j]-z[i]);
		    double yn = (x[k]-x[i])*(z[j]-z[i]) - (x[j]-x[i])*(z[k]-z[i]);
		    double zn = (x[j]-x[i])*(y[k]-y[i]) - (x[k]-x[i])*(y[j]-y[i]);
		    bool flag = zn < 0;
		    for (int m = 0; flag && m < n; m++)
			flag = flag && ((x[m]-x[i])*xn + 
					(y[m]-y[i])*yn + 
					(z[m]-z[i])*zn <= 0);
		    if (flag) ret.push_back(triple(i, j, k));
		}
	    }
	}
	return ret;
}
