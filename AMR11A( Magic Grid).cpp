https://www.spoj.com/problems/AMR11A/
#include <bits/stdc++.h>
using namespace std;
#define INF 1<<30
#define endl '\n'
#define maxn 1005
#define tc printf("Case %d: ", cs)
#define tcn printf("Case %d:\n", cs);
#define FASTIO ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
typedef long long ll;
const double PI = acos(-1.0);
#define dbg(x) cerr << #x << " = " << x << endl;
#define dbg2(x, y) cerr << #x << " = " << x << ", " << #y << " = " << y << endl;
#define dbg3(x, y, z) cerr << #x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << endl;
#define dbg4(w,x, y, z) cerr << #w << " = " << w << ", " <<#x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << endl;

ll n, m;
ll grid[maxn][maxn];

void solve()
{
	grid[n][m] = 1;
	for (int i = m - 1; i >= 1; i--) {
		//dbg3(grid[1][i], grid[1][i - 1], i);
		grid[n][i] = grid[n][i + 1] - grid[n][i];
		if (grid[n][i] <= 0) grid[n][i] = 1;
		//dbg2(grid[1][i], grid[1][i - 1]);
	}
	for (int i = n - 1; i >=  1; i--) {
		grid[i][m] = grid[i + 1][m] - grid[i][m];
		if (grid[i][m] <= 0) grid[i][m] = 1;
		//dbg2(grid[i - 1][1], grid[i][1]);
	}
	//dbg(grid[1][3]);
	for (int i = n - 1; i >= 1; i--) {
		for (int j = m - 1; j >= 1; j--) {
			grid[i][j] = min(grid[i + 1][j], grid[i][j + 1]) - grid[i][j];
			if (grid[i][j] <= 0) grid[i][j] = 1;
			//dbg3(grid[i][j], i, j);
		}
	}
	//for (int i = 1; i <= n; i++)
	//{
	//	for (int j = 1; j <= m; j++)
		//	cerr << grid[i][j] << " ";
	//	cerr << endl;
	//}
	cout << grid[1][1] << endl;
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
		cin >> n >> m;
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= m; j++) grid[i][j] = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				cin >> grid[i][j];
		solve();
	}

	//double end_time = clock();
	//printf( "Time = %lf ms\n", ( (end_time - start_time) / CLOCKS_PER_SEC)*1000);
	return 0;
}
