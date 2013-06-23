for(i = 0; i < n; i++){
	if(i > r) k = 1;
	else k = min(d1[l + r - i], r - i);

	while(0 <= i-k && i+k < n && s[i - k] == s[i + k]) k++;
	d1[i] = k;
	if(i + k - 1 > r)
		r = i + k - 1, l = i - k + 1;
}

for(i = 0; i < n; i++){
	if(i > r) k = 0;
	else k = min(d2[l + r - i + 1], r - i + 1);

	while(i + k < n && i - k - 1 >= 0 && s[i+k] == s[i - k - 1]) k++;
	d2[i] = k;

	if(i + k - 1 > r)
		l = i - k, r = i + k - 1;
}
