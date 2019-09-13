//https://www.spoj.com/problems/DISUBSTR/
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

const int nx = 1010;
int SA[nx], tempSA[nx];
int RA[nx], tempRA[nx];
int cnt[nx];
int lcp[nx], Plcp[nx], phi[nx];

char str[nx];
int n;

void counting_sort(int k)
{
    int mx = max(300, n);
    memset(cnt, 0, sizeof cnt);

    for (int i = 0; i < n; i++) {
        int a = i + k < n ? RA[i + k] : 0;
        cnt[a]++;
    }
    for (int i = 0, sum = 0; i < mx; i++) {
        int x = cnt[i];
        cnt[i] = sum;
        sum += x;
    }

    for (int i = 0; i < n; i++) {
        int a = SA[i] + k < n ? RA[SA[i] + k] : 0;
        int b = cnt[a];
        cnt[a]++;
        tempSA[b] = SA[i];
    }

    for (int i = 0; i < n; i++) {
        SA[i] = tempSA[i];
    }
}

void build_suffix_array()
{
    for (int i = 0; i < n; i++) {
        RA[i] = str[i];
        SA[i] = i;
    }

    for (int j = 1; j < n; j *= 2) {
        counting_sort(j);
        counting_sort(0);
        int r = 0;
        tempRA[SA[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + j] == RA[SA[i - 1] + j])
                tempRA[SA[i]] = r;
            else
                tempRA[SA[i]] = ++r;
        }

        for (int i = 0; i < n; i++) {
            RA[i] = tempRA[i];
        }
        if (RA[SA[n - 1]] == n - 1) break;
    }
}

void build_lcp()
{
    phi[SA[0]] = -1;
    for (int i = 1; i < n; i++) {
        phi[SA[i]] = SA[i - 1];
    }

    for (int i = 0, l = 0; i < n; i++) {
        if (phi[i] == -1) {
            Plcp[i] = 0;
            continue;
        }
        while (str[i + l] == str[phi[i] + l]) l++;
        Plcp[i] = l;
        l = max(l - 1, 0);
    }
    for (int i = 0; i < n; i++)
        lcp[i] = Plcp[SA[i]];
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
    scanf("%d", &T);
    for (int cs = 1; cs <= T; cs++) {
        scanf("%s", str);
        strcat(str, "$"); // add extra invalid character
        n = strlen(str);
        build_suffix_array();
        build_lcp();

        /*for(int i = 0; i <n; i++)
            cerr << SA[i] << " ";
        cerr << endl;
        for(int i = 0; i < n; i++){
            cerr << lcp[i] << " ";
        }
            cerr << endl;*/

        int ans = 0;
        int len = n - 1;
        for (int i = 1;  i < n; i++) {
            ans += (len - SA[i] - lcp[i]);
        }
        printf("%d\n", ans);
      //  cerr <<"------------\n";
    }

//double end_time = clock();
//printf( "Time = %lf ms\n", ( (end_time - start_time) / CLOCKS_PER_SEC)*1000);
    return 0;
}
