// stack[i].second = min { stack[j].first }, j <= i

// add val
int minima = st.empty() ? val : min (val, st.top().second);
st.push ( mp(val, minima) );

// pop
int res = st.top().first;
st.pop();

// get minimum
int minima = st.top().second;
