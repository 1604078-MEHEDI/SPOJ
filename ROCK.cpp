///https://www.spoj.com/problems/ROCK/
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
    #define dbg(x) cerr << #x << " = " << x << endl;
    #define dbg2(x, y) cerr << #x << " = " << x << ", " << #y << " = " << y << endl;
    #define dbg3(x, y, z) cerr << #x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << endl;
    #define dbg4(w,x, y, z) cerr << #w << " = " << w << ", " <<#x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << endl;
     
    ll n;
    string s;
    ll dp[202][202][202];
     
    ll solve(ll pos, ll one, ll zero)
    {
    	if (pos == n)
    		return (zero < one ? zero + one : 0);
    	if (s[pos] == '1')one++;
    	else zero++;
     
    	//ll &ret = dp[pos][one][zero];
    	if (dp[pos][one][zero] != -1) return dp[pos][one][zero];
    	if (one > zero) {
    		ll x = one + zero + solve(pos + 1, 0, 0); // partion
    		ll y = solve(pos + 1, one, zero); // don't partition
    		return dp[pos][one][zero] = max(x, y);
    	}
    	else {
    		ll x = solve(pos + 1, 0, 0); //  leave previous segment
    		ll y = solve(pos + 1, one, zero);
    		return dp[pos][one][zero] = max(x, y);
    	}
    }
     
    int main()
    {
    	FASTIO
    	///*
    	//double start_time = clock();
    #ifndef ONLINE_JUDGE
    	freopen("in.txt", "r", stdin);
    	freopen("out.txt", "w", stdout);
    	freopen("error.txt", "w", stderr);
    #endif
    //*/
    	int T;
    	cin >> T;
    	//T = 1;
    	for (int cs = 1; cs <= T; cs++) {
    		cin >> n >> s;
    		for (int i = 0; i <= n; i++)
    			for (int j = 0; j <= n; j++)
    				for (int k = 0; k <= n; k++)
    					dp[i][j][k] = -1;
     
    		cout << solve(0, 0, 0) << endl;
    	}
     
    	//double end_time = clock();
    	//printf( "Time = %lf ms\n", ( (end_time - start_time) / CLOCKS_PER_SEC)*1000);
    	return 0;
    } 
