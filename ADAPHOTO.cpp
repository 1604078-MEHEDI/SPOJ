///http://acm.timus.ru/problem.aspx?space=1&num=1517
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

typedef unsigned long long ull;
// Generate random base in (before, after) open interval:
int gen_base(const int before, const int after) {
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 mt_rand(seed);
    int base = std::uniform_int_distribution<int>(before + 1, after)(mt_rand);
    return base % 2 == 0 ? base - 1 : base;
}

struct Hash
{
    static const int mod = 2147483647;
    static vector<int> pw1; // powers of base modulo mod
    static vector<ull> pw2; // powers of base modulo 2^64
    static int base;

    static inline int diff(int a, int b)
    {
        return (a -= b) < 0 ? a + mod : a;
    }

    static inline int MOD(ull x) {
        x = (x >> 31) + (x & mod);
        return int ((x >> 31) + (x & mod));
    }

    vector<int> pref1; // powers of base modulo mod
    vector<ull> pref2; // powers of base modulo 2^64

    Hash(const vector<int>& s)
        : pref1(s.size() + 1u, 0)
        , pref2(s.size() + 1u, 0)
    {
        assert(base < mod);
        const int n = s.size(); // firstly calculated needed power of base
        while ((int)pw1.size() <= n) {
            pw1.push_back(MOD((ull)pw1.back() * base));
            pw2.push_back(pw2.back() * base);
        }
        for (int i = 0; i < n; i++) {
            assert(base > s[i]);
            pref1[i + 1] = MOD(pref1[i] + (ull) s[i] * pw1[i]);
            pref2[i + 1] = pref2[i] + s[i] * pw2[i];
        }
    }

    // Polynomial hash of subsequence [pos, pos+len)
    // If mxPow != 0, value automatically multiply on base in needed power. Finally base ^ mxPow
    inline pair<int, ull> operator()(const int pos, const int len, const int mxpow = 0)const {
        int hash1 = diff(pref1[pos + len], pref1[pos]);
        ull hash2 = pref2[pos + len] - pref2[pos];
        if (mxpow != 0) {
            hash1 = MOD((ull) hash1 * pw1[mxpow - (pos + len - 1)]);
            hash2 *= pw2[mxpow - (pos + len - 1)];
        }
        return {hash1, hash2};
    }
};


int Hash::base(1e9 + 7);
vector<int> Hash::pw1{1};
vector<ull> Hash:: pw2{1};

int code(char c) {
    if (c == 'v') return 0;
    if (c == '^') return 1;
    if (c == '~') return 2;
    assert(c == '-');
    return 3;
}

int solve(int lw, int hi, const vector<int>& a, const vector<int>& b)
{
    hi = min(hi, min((int)a.size() + 1, (int)b.size() + 1));
    const int mxpow = max(a.size(), b.size());

    Hash hash_a(a), hash_b(b);

    while (hi - lw > 1) {
        int mid = (lw + hi) / 2;
        vector<pair<int, ull>> hashes;
        for (int i = 0; i + mid - 1 < (int) a.size(); i++) {
            hashes.push_back(hash_a(i, mid, mxpow));
        }
        sort(hashes.begin(), hashes.end());
        bool  p = false;
        for (int i = 0; i + mid - 1 < (int) b.size(); i++) {
            if (binary_search(hashes.begin(), hashes.end(), hash_b(i, mid, mxpow))) {
                p = true;
                break;
            }
        }
        if (p) {
            lw = mid;
        }
        else {
            hi = mid;
        }
    }
    return lw;
}

int main()
{
    // FASTIO
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
    for (int cs = 1; cs <= T; cs++) {
        Hash::base = gen_base(1e6, Hash::mod);
        char ch[1000006];
        scanf("%s", ch);
        string a(ch);
        scanf("%s", ch);
        string b(ch);

        vector<int> s1(a.size()), t1(b.size());
        for (int i = 0; i < (int)s1.size(); i++) s1[i] = code(a[i]);
        for (int i = 0; i < (int)t1.size(); i++) t1[i] = code(b[i]);

        if (min(s1.size(), t1.size()) <= 2000u) {
            for (auto& it : s1) it++;
            for (auto& it : t1) it++;
            cout << solve(0, (int)min(s1.size(), t1.size()) + 1, s1, t1);
            return 0;
        }

        vector<int> s2(a.size() / 4, 1), t2(b.size() / 4, 1);
        for (int i = 0; i < (int)s1.size(); i++)
            s2[i / 4] += (s1[i] << 2 * (i % 4));
        for (int i = 0; i < (int)t1.size(); i++)
            t2[i / 4] += (t1[i] << 2 * (i % 4));

        int ans = solve(0, (int)min(s2.size(), t2.size()) + 1, s2, t2);
        for (auto& it : s1) it++;
        for (auto& it : t1) it++;
        cout << solve(4 * ans, 4 * ans + 8, s1, t1);
    }
    return 0;
}
