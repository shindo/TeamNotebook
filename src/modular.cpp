// All algorithms described here work on nonnegative integers.

// return a % b (positive value)
int mod(int a, int b) {
  return ((a%b)+b)%b;
}

// computes gcd(a,b)
int gcd(int a, int b) {
  int tmp;
  while(b){a%=b; tmp=a; a=b; b=tmp;}
  return a;
}

// computes lcm(a,b)
int lcm(int a, int b) {
  return a/gcd(a,b)*b;
}

// returns d = gcd(a,b); finds x,y such that d = ax + by
int extended_euclid(int a, int b, int &x, int &y) {  
  int xx = y = 0;
  int yy = x = 1;
  while (b) {
    int q = a/b;
    int t = b; b = a%b; a = t;
    t = xx; xx = x-q*xx; x = t;
    t = yy; yy = y-q*yy; y = t;
  }
  return a;
}

// finds all solutions to ax = b (mod n)
ve<int> modular_linear_equation_solver(int a, int b, int n) {
  int x, y;
  ve<int> solutions;
  int d = extended_euclid(a, n, x, y);
  if (!(b%d)) {
    x = mod (x*(b/d), n);
    for (int i = 0; i < d; i++)
      solutions.push_back(mod(x + i*(n/d), n));
  }
  return solutions;
}

// computes b such that ab = 1 (mod n), returns -1 on failure
int mod_inverse(int a, int n) {
  int x, y;
  int d = extended_euclid(a, n, x, y);
  if (d > 1) return -1;
  return mod(x,n);
}

// find z such that z % x = a, z % y = b.  Here, z is unique modulo M = lcm(x,y).
// Return (z,M).  On failure, M = -1.
pii chinese_remainder_theorem(int x, int a, int y, int b) {
  int s, t;
  int d = extended_euclid(x, y, s, t);
  if (a%d != b%d) return make_pair(0, -1);
  return make_pair(mod(s*b*x+t*a*y,x*y)/d, x*y/d);
}

// Chinese remainder theorem: find z such that
// z % x[i] = a[i] for all i.  Note that the solution is
// unique modulo M = lcm_i (x[i]). Return (z,M). On failure, M = -1.
pii chinese_remainder_theorem(const ve<int> &x, const ve<int> &a) {
  pii ret = make_pair(a[0], x[0]);
  for (int i = 1; i < x.size(); i++) {
    ret = chinese_remainder_theorem(ret.second, ret.first, x[i], a[i]);
    if (ret.second == -1) break;
  }
  return ret;
}

// computes x and y such that ax + by = c; on failure, x = y =-1
void linear_diophantine(int a, int b, int c, int &x, int &y) {
  int d = gcd(a,b);
  if (c%d) {
    x = y = -1;
  } else {
    x = c/d * mod_inverse(a/d, b/d);
    y = (c-a*x)/b;
  }
}

//from e-maxx
void shift_solution (int & x, int & y, int a, int b, int cnt) {
	x += cnt * b;
	y -= cnt * a;
}
int find_all_solutions (int a, int b, int c, int minx, int maxx, int miny, int maxy) {
	int x, y, g;
	if (! find_any_solution (a, b, c, x, y, g))
		return 0;
	a /= g;  b /= g;
	int sign_a = a>0 ? +1 : -1;
	int sign_b = b>0 ? +1 : -1;
	shift_solution (x, y, a, b, (minx - x) / b);
	if (x < minx)
		shift_solution (x, y, a, b, sign_b);
	if (x > maxx)
		return 0;
	int lx1 = x;
	shift_solution (x, y, a, b, (maxx - x) / b);
	if (x > maxx)
		shift_solution (x, y, a, b, -sign_b);
	int rx1 = x;
	shift_solution (x, y, a, b, - (miny - y) / a);
	if (y < miny)
		shift_solution (x, y, a, b, -sign_a);
	if (y > maxy)
		return 0;
	int lx2 = x;
	shift_solution (x, y, a, b, - (maxy - y) / a);
	if (y > maxy)
		shift_solution (x, y, a, b, sign_a);
	int rx2 = x;
	if (lx2 > rx2)
		swap (lx2, rx2);
	int lx = max (lx1, lx2);
	int rx = min (rx1, rx2);
	if(lx > rx) return 0;
	return (rx - lx) / abs(b) + 1;
}

//x^k=a mod n
//finds x, from e-maxx
	int n, k, a;
	if (a == 0) {
		puts ("1\n0");
		return;
	}
	int g = generator (n);
	int sq = (int) sqrt (n + .0) + 1;
	vector < pair<int,int> > dec (sq);
	for (int i=1; i<=sq; ++i)
		dec[i-1] = make_pair (powmod (g, int (i * sq * 1ll * k % (n - 1)), n), i);
	sort (dec.begin(), dec.end());
	int any_ans = -1;
	for (int i=0; i<sq; ++i) {
		int my = int (powmod (g, int (i * 1ll * k % (n - 1)), n) * 1ll * a % n);
		vector < pair<int,int> >::iterator it =
			lower_bound (dec.begin(), dec.end(), make_pair (my, 0));
		if (it != dec.end() && it->first == my) {
			any_ans = it->second * sq - i;
			break;
		}
	}
	if (any_ans == -1) {
		puts ("0");
		return;
	}
	int delta = (n-1) / gcd (k, n-1);
	vector<int> ans;
	for (int cur=any_ans%delta; cur<n-1; cur+=delta)
		ans.push_back (powmod (g, cur, n));
	sort (ans.begin(), ans.end());
	printf ("%d\n", ans.size());
	for (size_t i=0; i<ans.size(); ++i)
		printf ("%d ", ans[i]);

//square roots, tested on timus
bool is_sq_root(int a,int mod){
	return powmod(a,(mod-1)/2,mod)==1;
}
int generator(int p){
	while(true){
		int v = 1+rand()%(p-1);
		if (!is_sq_root(v,p))
			return v;
	}
}
int find_root(int a,int p){
	if (p%4==3) return powmod(a,(p+1)/4,p);
	int g = generator(p);
	int q = p-1, s = 0; while(q%2==0){ q/=2; s++; }
	int c = powmod(g,q,p);
	int r = powmod(a,(q+1)/2,p);
	int t = powmod(a,q,p);
	int m = s;
	while(t!=1){
		int i = 0, t2 = t; while(t2!=1) t2=t2*t2%p,i++;
		int b = powmod(c,1<<(m-i-1),p);
		r = r*b%p;
		t = t*b%p*b%p;
		c = b*b%p;
		m = i;
	}
	return r;
}
//using:
	a%=p;
	if (p==2){
		if (a==1) puts("1"); else puts("No root");
	}else if (!is_sq_root(a,p)) puts("No root");
	else{
		int r1 = find_root(a,p);
		int r2 = p-r1;
		if (r1 > r2) swap(r1,r2);
		printf("%d %d\n",r1,r2);
	}