struct Node {
	Point p, v;
	Node *left, *right;
};

// sX -- points sorted by cmpX, sY -- points sorted by cmpY
Node* construct(int N, Point *sX, Point *sY, int depth) {
	Node * root = allocateNode();
	if(N == 1) {
		root->p = sX[0];	
	} else {

		Point * sx = (depth & 1) ? sX : sY;
		Point * sy = (depth & 1) ? sY : sX;

		bool (*cmp)(const Point &, const Point &);
		cmp = (depth & 1) ? cmpX : cmpY; 

		root->v = sx[N / 2];

		int K = 0;
		REP(i, 0, N) {
			if(!cmp(sy[i], root->v)) {
				tmp[K++] = sy[i];
			} else {
				sy[i - K] = sy[i];
			}
		}
		REP(i, 0, K) sy[N - K + i] = tmp[i];

		root->left = construct(N / 2, sX, sY, depth + 1);
		root->right = construct(K, sX + N/2, sY + N/2, depth + 1);

	}
	return root;
}

void findClosest(Node * root, const Point & p, ll & minDist, int depth) {

	if(root->left == NULL) {
		if(! (root->p == p) ) {
			minDist = min(minDist, (p - root->p).len());
		}
		return;
	}

	bool (*cmp)(const Point &, const Point &);
	cmp = (depth & 1) ? cmpX : cmpY;
	ll d = (depth & 1) ? (root->v.x - p.x) : (root->v.y - p.y);

	if(cmp(p, root->v)) {
		findClosest(root->left, p, minDist, depth + 1);
	} else {
		findClosest(root->right, p, minDist, depth + 1);
	}

	if(sqr(d) < minDist) {
		if(cmp(p, root->v)) {
			findClosest(root->right, p, minDist, depth + 1);
		} else {
			findClosest(root->left, p, minDist, depth + 1);
		}
	}
}
