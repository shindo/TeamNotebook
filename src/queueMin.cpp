deque<int> q;

// get minimum
current_minimum = q.front();

// add val
while (!q.empty() && q.back() > val)
	q.pop_back();
q.push_back (val);

// pop val
if (!q.empty() && q.front() == val)
	q.pop_front();
