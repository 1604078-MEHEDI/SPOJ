#include <bits/stdc++.h>
using namespace std;
#define INF 1<<30
#define endl '\n'
#define maxn 7809
#define tc printf("Case %d: ", cs)
#define tcn printf("Case %d:\n", cs);
#define FASTIO ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
typedef long long ll;
const double PI = acos(-1.0);
#define dbg(x) cerr << #x << " = " << x << endl;
#define dbg2(x, y) cerr << #x << " = " << x << ", " << #y << " = " << y << endl;
#define dbg3(x, y, z) cerr << #x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << endl;
#define dbg4(w,x, y, z) cerr << #w << " = " << w << ", " <<#x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << endl;


#define MAX 100009

typedef long long ll;

vector<int>primes;


void seive()
{
	bool flag[MAX + 1];

	for (int i = 0; i <= MAX; i++)
		flag[i] = true;
	primes.push_back(2);

	flag[0] = flag[1] = false;

	for (int i = 4; i <= MAX; i += 2) flag[i] = false;

	for (int i = 3; i <= MAX; i += 2) {

		if (flag[i] == true) { // i is prime
			primes.push_back(i);
			for (int j = i + i; j <= MAX; j = j + i) {
				flag[j] = false; // j is not prime
			}
		}
	}
}

void segmentedSeive(ll L, ll R)
{
	bool isPrime[R - L + 1];
	for (int i = 0; i <= (R - L + 1); i++)
		isPrime[i] = true;

	if (L == 1)isPrime[0] = false;

	for (int i = 0; primes[i]*primes[i] <= R; i++) {
		ll curPrime = primes[i];
		ll base = curPrime * curPrime;
		if (base < L) {
			base = ( (L + curPrime - 1) / curPrime) * curPrime;
		}

		for (ll j = base; j <= R; j += curPrime)
			isPrime[j - L] = false;
	}
	//int cnt = 0;
	for (int i = 0; i <= R - L; i++) {
		if (isPrime[i] == true) //cnt++;
			printf("%lld\n", L + i);
	}
	//cout << cnt << endl;
}

int main()
{
	//FASTIO
	///*
	//double start_time = clock();
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	freopen("error.txt", "w", stderr);
#endif
//*/
	int T;
	seive();
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		ll l, r;
		scanf("%lld %lld", &l, &r);
		//printf("Case %d: ", cs);
		segmentedSeive(l, r);
		printf("\n");
	}

	//double end_time = clock();
	//printf( "Time = %lf ms\n", ( (end_time - start_time) / CLOCKS_PER_SEC)*1000);
	return 0;
}
