//https://www.spoj.com/problems/QTREE/
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

const int nx = 15;
const int root = 0;
vector<int> graph[maxn], cost[maxn], idx[maxn];
int baseArray[maxn], ptr;
int ChainNo, ChainIdx[maxn], ChainHead[maxn], posInBase[maxn];
int depth[maxn], parent[nx][maxn], otherEnd[maxn], subSize[maxn];
int st[maxn * 6], qt[maxn * 6];


void make_tree(int cur, int l, int r)
{
    if (l == r - 1) {
        st[cur] = baseArray[l];
        return;
    }

    int lft = (cur << 1);
    int rgt = lft | 1;
    int m = (l + r) >> 1;
    make_tree(lft, l, m);
    make_tree(rgt, m, r);
    st[cur] = st[lft] > st[rgt] ? st[lft] : st[rgt];
}

void update_tree(int cur, int l, int r, int x, int val)
{
    if (l > x || r <= x) return;

    if (l == x && l == r - 1) {
        st[cur] = val;
        return;
    }
    int lft = (cur << 1);
    int rgt = lft | 1;
    int m = (l + r) >> 1;
    update_tree(lft, l, m, x, val);
    update_tree(rgt, m, r, x, val);
    st[cur] = st[lft] > st[rgt] ? st[lft] : st[rgt];
}

void change(int i, int val)
{
    int u = otherEnd[i];
    update_tree(1, 0, ptr, posInBase[u], val);
}

void HLD(int curNode, int Cost, int prev)
{
    if (ChainHead[ChainNo] == -1) {
        ChainHead[ChainNo] = curNode; // assign chain head
    }

    ChainIdx[curNode] = ChainNo;
    posInBase[curNode] = ptr; // // Position of this node in baseArray which we will use in Segtree
    baseArray[ptr++] = Cost;

    int sc = -1, ncost;
    // loop for find special child
    for (int i = 0; i < (int)graph[curNode].size(); i++) {
        int v = graph[curNode][i];
        if (v != prev)
        {
            if (sc == -1 || subSize[sc] < subSize[v]) {
                sc = v;
                ncost = cost[curNode][i];
            }
        }
    }

    // expand the chain
    if (sc != -1) HLD(sc, ncost, curNode);

    for (int i = 0; i < (int)graph[curNode].size(); i++) {
        int v = graph[curNode][i];
        if (v != prev) {
            if (sc != v) {
                ChainNo++;
                HLD(v, cost[curNode][i], curNode);
            }
        }
    }

}

///dfs used to set parent of a node, depth of a node, subtree size of a node
void dfs(int cur, int prev, int _depth = 0) {
    parent[0][cur] = prev;
    depth[cur] = _depth;
    subSize[cur] = 1;
    for (int i = 0; i < (int)graph[cur].size(); i++) {
        int v = graph[cur][i];
        if (v != prev) {
            otherEnd[idx[cur][i]] = v;
            dfs(v, cur, _depth + 1);
            subSize[cur] += subSize[v];
        }
    }
}


//Given S and E, it will return the maximum value in the range [S,E)
void query_tree(int cur, int l, int r, int S, int E)
{
    if (l >= E || r <= S) {
        qt[cur] = -1;
        return;
    }

    if (l >= S && r <= E) {
        qt[cur] = st[cur];
        return;
    }
    int lft = (cur << 1);
    int rgt = lft | 1;
    int m = (l + r) >> 1;
    query_tree(lft, l, m, S, E);
    query_tree(rgt, m, r, S, E);
    qt[cur] = qt[lft] > qt[rgt] ? qt[lft] : qt[rgt];
}

int query_up(int u, int v)
{
    if (u == v) return 0;

    //uchain and vchain are chain numbers of u and v
    int uChain;
    int vChain = ChainIdx[v];
    int ans = -1;

    while (1) {
        uChain = ChainIdx[u];
        if (uChain == vChain) { // same chain
            if (u == v) break;
            query_tree(1, 0, ptr, posInBase[v] + 1, posInBase[u] + 1);
            if (qt[1] > ans) ans = qt[1]; // upadte ans
            break;
        }
        query_tree(1, 0, ptr, posInBase[ChainHead[uChain]], posInBase[u] + 1);
        if (qt[1] > ans) ans = qt[1];
        u = ChainHead[uChain];
        u = parent[0][u]; // chains change
    }
    return ans;
}

int LCA(int u, int v)
{
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];

    for (int i = 0; i < nx; i++) {
        if ((diff >> i) & 1) u = parent[i][u];
    }
    if (u == v) return u;

    for (int i = nx - 1; i >= 0; i--) {
        if (parent[i][u] != parent[i][v]) {
            u = parent[i][u];
            v = parent[i][v];
        }
    }
    return parent[0][u];
}

void query(int u, int v)
{
    int lca = LCA(u, v);
    //dbg(lca);
    int ans = query_up(u, lca);
    //dbg(ans);
    int tt = query_up(v, lca);
    //dbg(ans);
    if (tt > ans) ans = tt;
    //dbg(ans);
    printf("%d\n", ans);
}
int main()
{
    // FASTIO
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
    //dbg(T);
    for (int cs = 1; cs <= T; cs++) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            graph[i].clear();
            cost[i].clear();
            idx[i].clear();
            ChainHead[i] = -1;
            for (int j = 0; j < nx; j++) parent[j][i] = -1;
        }

        for (int i = 1; i < n; i++) {
            int u, v, c;
            scanf("%d %d %d", &u, &v, &c);
            --u;
            --v;
            graph[u].push_back(v);
            cost[u].push_back(c);
            idx[u].push_back(i - 1);
            graph[v].push_back(u);
            cost[v].push_back(c);
            idx[v].push_back(i - 1);
        }

        ChainNo = 0;
        dfs(root, -1); // We set up subsize, depth and parent for each node
        HLD(root, -1, -1); //  We decomposed the tree and created baseArray
        make_tree(1, 0, ptr); // We use baseArray and construct the needed segment tree

        for (int i = 1; i < nx; i++) {
            for (int j = 0; j < n; j++) {
                if (parent[i - 1][j] != -1)
                    parent[i][j] = parent[i - 1][parent[i - 1][j]];
            }
        }

        while (1) {
            char ch[100];
            scanf("%s", ch);
            //dbg(ch);
            if (ch[0] == 'D') break;
            int u, v;
            scanf("%d %d", &u, &v);
            //dbg2(u,v);
            if (ch[0] == 'Q') query(u - 1, v - 1);
            else change(u - 1, v);
        }
    }

    //double end_time = clock();
    //printf( "Time = %lf ms\n", ( (end_time - start_time) / CLOCKS_PER_SEC)*1000);
    return 0;
}
