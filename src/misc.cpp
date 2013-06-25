//Grey code
int g (int n) {
	return n ^ (n >> 1);
}
int rev_g (int g) {
	int n = 0;
	for (; g; g>>=1)
		n ^= g;
	return n;
}

//long multiplication
long long mulmod(long long a, long long b, long long MOD)
{
	if (b == 0) return 0;
	long long res = mulmod(a, b >> 1, MOD);
	res += res;
	res %= MOD;
	return (b & 1)? (a + res) % MOD : res;
}
long long powmod(long long a, long long b, long long MOD)
{
	if (b == 0) return 1;
	long long res = powmod(a, b >> 1, MOD);
	res *= res;
	res %= MOD;
	return (b & 1)? (a * res) % MOD : res;
}
long long mul( long long a, long long b, long long m ) {
	long long q = (long long)((long double)a * (long double)b / (long double)m);
	long long r = a * b - q * m;
	return (r + 5 * m) % m;
}

//brackets next permutation
#define N 6
int counter;
char buffer[N+5];
char input[N+5] = "(())()";
void gen_permutation(int pos, int opened){
	if (pos == N){
		puts(buffer);
		return;
	}
	if (N - pos > opened){
		buffer[pos] = '(';
		gen_permutation(pos + 1, opened + 1);
	}
	if (opened > 0){
		buffer[pos] = ')';
		gen_permutation(pos + 1, opened - 1);
	}
}
void next_permutation(int pos, int opened){
	if (counter >= 2) return;
	if (pos == N){
		if (counter == 1){
			puts(buffer);
		}
		++counter;
		return;
	}
	if (counter > 0 || (counter == 0 && input[pos]=='(')){
		if (N - pos > opened){
			buffer[pos] = '(';
			next_permutation(pos + 1, opened + 1);
		}
	}
	if (counter > 0 || (counter == 0 && input[pos]==')')){
		if (opened > 0){
			buffer[pos] = ')';
			next_permutation(pos + 1, opened - 1);
		}
	}
}
//using:
	puts("=== Generate all length N permutation ===");
	gen_permutation(0,0);
	printf("Output the next permutation of %s\n", input);
	counter = 0;
	next_permutation(0,0);
