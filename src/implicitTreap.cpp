int cnt (pitem t) { return t ? t->cnt : 0; }

void upd_cnt (pitem t) {
	if (t) t->cnt = 1 + cnt(t->l) + cnt (t->r);
}

void merge (pitem & t, pitem l, pitem r) {
	if (!l || !r)
		t = l ? l : r;
	else if (l->prior > r->prior)
		merge (l->r, l->r, r),  t = l;
	else
		merge (r->l, l, r->l),  t = r;
	upd_cnt (t);
}
// key(l) < key, key(r) > key
void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
	if (!t)
		return void( l = r = 0 );
	int cur_key = add + cnt(t->l);
	if (key <= cur_key)
		split (t->l, l, t->l, key, add),  r = t;
	else
		split (t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
	upd_cnt (t);
}

pitem build(int *a, int cnt) {
	if (cnt <= 0) return NULL;
	int p = cnt/2;
	pitem root = &buf[buf_sz++];
	root->val = a[p]; // root->prior ???
	root->l = build(a, p);
	root->r = build(a + p + 1, cnt - p - 1);
	upd_cnt(root);
	return root;
}
