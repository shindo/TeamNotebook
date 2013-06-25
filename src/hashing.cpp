//fast! 2d int hashing
//returning the success of inserting into ht
struct HT{
	const static int MaxN = 1509, MaxC = 0x3F3F3F3F, Prime1 = 262139, Prime2 = 40999999;
	const static int NA = -1, MaxD = 4, MaxL = 1 << 23, AndL = MaxL - 1;
	pair <int, int> ZERO;
	HT(){ ZERO = make_pair (0, 0); }

	pair <int, int> h [MaxL];
	bool insert (int x, int y)
	{
		pair <int, int> p = make_pair (x, y);
		int q = (x * Prime1 + y * Prime2) & AndL;
		while (h[q] != ZERO && h[q] != p)
			q = (q + 1) & AndL;
		if (h[q] == p)
			return false;
		h[q] = p;
		return true;
	}
};

//string hashing
const int base = 13331, Q1 = 1000000007, Q2 = 1000000009;
int hash1[1000001], hash2[1000001], power1[1000001], power2[1000001];
char str[1000001];
bool check(int a, int b, int l) {
	int t1 = ((hash1[a+l] - (ll)hash1[a] * power1[l]) % Q1 + Q1) % Q1;
	int t2 = ((hash1[b+l] - (ll)hash1[b] * power1[l]) % Q1 + Q1) % Q1;
	if (t1 != t2) return false;
	int t3 = ((hash2[a+l] - (ll)hash2[a] * power2[l]) % Q2 + Q2) % Q2;
	int t4 = ((hash2[b+l] - (ll)hash2[b] * power2[l]) % Q2 + Q2) % Q2;
	if (t3 != t4) return false;
	return true;
}
//init:
	scanf("%d%s", &n, str);
	hash1[0] = hash2[0] = 0;
	for (int i = 0; i < n; i ++) {
			hash1[i+1] = ((ll)hash1[i] * base + str[i]) % Q1;
			hash2[i+1] = ((ll)hash2[i] * base + str[i]) % Q2;
	}
	power1[0] = power2[0] = 1;
	for (int i = 1; i <= n; i ++) {
			power1[i] = (ll)power1[i-1] * base % Q1;
			power2[i] = (ll)power2[i-1] * base % Q2;
	}