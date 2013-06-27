long long mul( long long a, long long b, long long m ) {
	long long q = (long long)((long double)a * (long double)b / (long double)m);
	long long r = a * b - q * m;
	return (r + 5 * m) % m;
}
