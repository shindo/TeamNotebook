// Lyndon decomposition
for(int i = 0; i < n;) {
	int j=i+1, k=i;
	while (j < n && s[k] <= s[j]) {
		if (s[k] < s[j])
			k = i;
		else
			++k;
		++j;
	}
	while (i <= k) {
		cout << s.substr (i, j-k) << ' ';
		i += j - k;
	}
}

string min_cyclic_shift (string s) {
	s += s;
	int n = (int) s.length();
	int i=0, ans=0;
	while (i < n/2) {
		ans = i;
		int j=i+1, k=i;
		while (j < n && s[k] <= s[j]) {
			if (s[k] < s[j])
				k = i;
			else
				++k;
			++j;
		}
		while (i <= k)  i += j - k;
	}
	return s.substr (ans, n/2);
}
