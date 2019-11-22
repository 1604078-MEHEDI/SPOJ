///https://www.spoj.com/problems/GONE/
///https://www.youtube.com/watch?v=sCwokuCoQB8&t=538s
////https://github.com/anmolvarshney05/SPOJ-Solutions/blob/master/SPOJ%20GONE.cpp
#include <bits/stdc++.h>
using namespace std;
#define INF 1<<30
#define endl '\n'
#define maxn 100005
#define tc printf("Case %d: ", cs)
#define tcn printf("Case %d:\n", cs);
#define FASTIO ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
typedef long long ll;
const double PI = acos(-1.0);

#define dbg1(x) cerr << #x << " = " << x << endl;
#define dbg2(x, y) cerr << #x << " = " << x << ", " << #y << " = " << y << endl;
#define dbg3(x, y, z) cerr << #x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << endl;
#define dbg4(w,x, y, z) cerr << #w << " = " << w << ", " <<#x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << endl;

template < typename F, typename S >
ostream& operator << ( ostream& os, const pair< F, S > & p ) {
	return os << "(" << p.first << ", " << p.second << ")";
}

template < typename T >
ostream &operator << ( ostream & os, const vector< T > &v ) {
	os << "{";
	for (auto it = v.begin(); it != v.end(); ++it) {
		if ( it != v.begin() ) os << ", ";
		os << *it;
	}
	return os << "}";
}

template < typename T >
ostream &operator << ( ostream & os, const set< T > &v ) {
	os << "[";
	for (auto it = v.begin(); it != v.end(); ++it) {
		if ( it != v.begin()) os << ", ";
		os << *it;
	}
	return os << "]";
}

template < typename F, typename S >
ostream &operator << ( ostream & os, const map< F, S > &v ) {
	os << "[";
	for (auto it = v.begin(); it != v.end(); ++it) {
		if ( it != v.begin() ) os << ", ";
		os << it -> first << " = " << it -> second ;
	}
	return os << "]";
}

#define dbg(args...) do {cerr << #args << " : "; faltu(args); } while(0)

clock_t tStart = clock();
#define timeStamp dbg("Execution Time: ", (double)(clock() - tStart)/CLOCKS_PER_SEC)

void faltu () { cerr << endl; }

template <typename T>
void faltu( T a[], int n ) {
	for (int i = 0; i < n; ++i) cerr << a[i] << ' ';
	cerr << endl;
}

template <typename T, typename ... hello>
void faltu( T arg, const hello &... rest) { cerr << arg << ' '; faltu(rest...); }
// Program showing a policy-based data structure.
#include <ext/pb_ds/assoc_container.hpp> // Common file 
#include <ext/pb_ds/tree_policy.hpp>
#include <functional> // for less 
#include <iostream>
using namespace __gnu_pbds;
using namespace std;
// GNU link : https://goo.gl/WVDL6g
typedef tree<int, null_type, less_equal<int>, rb_tree_tag,
        tree_order_statistics_node_update>
        new_data_set;

/**___________________________________________________**/
ll dp[10][2][70];
int n;
string x;

string STR(ll N)
{
	stringstream ss;
	ss << N;
	return ss.str();
}

set<int> s;
int mark[101];

void Prime()
{
	for (int i = 2; i * i <= 100; i++)
	{
		if (mark[i] == 0)
		{
			for (int j = i * 2; j <= 100; j += i)
				mark[j] = 1;
		}
	}
	for (int i = 2; i <= 100; i++)
		if (mark[i] == 0)
			s.insert(i);
}

ll digit_dp(int pos, bool isSmall, int sm)
{
	if (pos == n)
		return (s.find(sm) != s.end());

	ll &ret = dp[pos][isSmall][sm];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = 0; i < 10; i++) {
		if (isSmall || (i <= (int)(x[pos] - '0'))) {
			ret += digit_dp(pos + 1, (isSmall || (i < (int)(x[pos] - '0'))), sm + i);
		}
	}
	return ret;
}


int main()
{
	FASTIO
	///*
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	freopen("error.txt", "w", stderr);
#endif
//*/
	int T;
	//scanf("%d", &T);
	T = 1;
	cin >> T;
	Prime();
	for (int cs = 1; cs <= T; cs++) {
		ll ans = 0;
		ll a, b;
		cin >> a >> b;
		a--;
		x = STR(b);
		n = x.size();
		memset(dp, -1, sizeof dp);
		ans = digit_dp(0, false, 0);
		x = STR(a);
		n = x.size();
		memset(dp, -1, sizeof dp);
		ans -= digit_dp(0, false, 0);
		cout << ans << endl;
	}
	return 0;
}
