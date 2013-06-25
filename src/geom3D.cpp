pt operator*(const pt & p) const {
	return pt( y * p.z - z * p.y,
			   z * p.x - x * p.z,
			   x * p.y - y * p.x  );
}

// Projection on line (A, B)
pt getH(const pt & A, const pt & B) const {
	pt C = *this;
	pt v = B - A;
	pt u = C - A;
	double k = v ^ u / v.length();
	v = v.norm(k);
	pt H = A + v;
	return H;
}
 
// Rotation
pt rotate(pt normal) const { return *this * normal; }
 
pt rotate(double alpha, const pt & normal) const {
	return rotate(cos(alpha), sin(alpha), normal );
}
 
pt rotate(double cosa, double sina, const pt & normal) const {
	pt v = *this;
	pt u = v.rotate(normal);
	pt w = v * cosa + u * sina;
	return w;
}
 
// Undirected angle
double getAngle(pt u) const {
	pt v = *this;
	return atan2((v * u).length() , v ^ u);
}

bool isOnPlane(const pt & A, const pt & B, const pt & C) const {
	return doubleEqual( (A - *this) * (B - *this) ^ (C - *this), 0);
}
 
// Intersection of lines (A, B) & (C, D) 
int getIntersection(const pt & A, const pt & B, const pt & C, const pt & D, pt & O) {
	if( !doubleEqual( (B - A) * (C - A) ^ (D - A), 0)  ) {
		throw "It's not plane";
	}
	if( doubleEqual( ( (A - B) * (C - D) ).length(), 0)) {
		if(A.isOnLine(C, D) ) return 2;
		return 0;
	}
	pt normal = ( (A - B) * (C - B) ).norm();
	pt v = B - A;
	double s1 = (C - A) * (D - A) ^ normal;
	double s2 = (D - B) * (C - B) ^ normal;
	double s = s1 + s2; 
	v = v / s;
	v = v * s1; 
	O = A + v; 
	return 1; 
}
 
// Intersection of line (A, B) & plane (C, D, E) 
int getIntersection(const pt & A, const pt & B, const pt & C, const pt & D, const pt & E, pt & O) {
	pt v = B - A; 
	double V1 = (C - A) * (D - A) ^ (E - A); // thetrahedra (A, C, D, E) volume
	double V2 = (D - B) * (C - B) ^ (E - B);
	double V = V1 + V2;
	v = v / V;
	if(doubleEqual(V, 0) ) {
		if(A.isOnPlane(C, D, E) ) return 2;
		return 0;
	}
	v = v * V1;
	O = A + v;
	return 1;
}
 
// Intersection of planes (A, nA) & (B, nB) 
bool getIntersection(const pt & A, const pt & nA, const pt & B, const pt & nB, pt & P, pt & Q) {
	pt n = nA * nB;
	if(n.isZero() ) return false;
	pt v = n * nA;
	double k = (B - A) ^ nB / (v ^ nB);

	v = v * k;
	P = A + v;
	Q = P + n;
	return true;
}

//Nearest_neighbour_search_random_line
	srand(time(NULL));
	double A=rand(),B=rand(),C=rand(),g=sqrt(0.+A*A+B*B+C*C);
	A/=g; B/=g; C/=g;
	for(int i=0;i<n;++i)
		v.push_back(make_pair(A*x[i]+B*y[i]+C*z[i],i));
	sort(v.begin(),v.end());
	for(int i=0;i<n;++i) {
		long long ans=0; int ind;
		if (i) ans=dist(v[i].second,v[i-1].second),ind=i-1;
		else ans=dist(v[i].second,v[i+1].second),ind=i+1;
		int l=i-1,r=i+1;
		while(true) {
			bool ok=0;
			if (l>=0&&(v[i].first-v[l].first)*(v[i].first-v[l].first)<ans) {
				long long cur=dist(v[i].second,v[l].second);
				if (cur<ans) ans=cur,ind=l;
				--l; ok=1;
			}
			if (r<n&&(v[r].first-v[i].first)*(v[r].first-v[i].first)<ans) {
				long long cur=dist(v[i].second,v[r].second);
				if (cur<ans) ans=cur,ind=r;
				++r; ok=1;
			}
			if (!ok) break;
		}
		ansp[v[i].second]=v[ind].second;
	}
	for(int i=0;i<n;++i) {
		if (i) printf(" ");
		printf("%d",ansp[i]+1);
	}