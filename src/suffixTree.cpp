struct Seg {
	int lb, rb, lcp;
	vector<Seg*> childList;
	void init(int l, int i, int j) {
		lb = i; rb = j; lcp = l;
	}
	void add(Seg * son) {
		childList.pb(son);
	}
};
typedef Seg* pSeg;

struct Stack {
	pSeg segs[MAXN << 1];
	int size;
	void push(pSeg seg) {
		segs[size++] = seg;
	}
	pSeg pop() {
		return segs[--size];
	}
	pSeg top() {
		return segs[size - 1];
	}
} stack;

pSeg top() { return stack.top(); }
void push(pSeg seg) { stack.push(seg); }
pSeg pop() { return stack.pop(); }

pSeg init(int lcp, int lb, int rb) {
	pSeg ret = new Seg;
	ret->init(lcp, lb, rb);
	return ret; 
}

pSeg makeTree() {
	stack.size = 0;
	pSeg lastInterval = NULL;
	int lastSingleton = 0;
	stack.push(init(0, 0, -1));
	REP(i, 1, N) {
		int lb = i - 1;
		pSeg singleton = init(N - suftab[i - 1] - 1, i - 1, i - 1);
		//process(singleton);

		while(lcptab[i] < top()->lcp) {
			if(singleton != NULL) {
				top()->add(singleton);
				singleton = NULL;
			}
			top()->rb = i - 1;
			lastInterval = pop();
			//process(lastInterval);
			lb = lastInterval->lb;
			if(lcptab[i] <= top()->lcp) {
				top()->add(lastInterval);
				lastInterval = NULL;
			}
		}
		if(lcptab[i] > top()->lcp) {
			if(lastInterval != NULL) {
				pSeg seg = init(lcptab[i], lb, -1);
				seg->add(lastInterval);
				push(seg);
				lastInterval = NULL;
			} else push(init(lcptab[i], lb, -1));
		}
		if(singleton != NULL) {
			top()->add(singleton);
		}
	}
	assert(stack.size == 1);
	//process(top());
	return top();
}
