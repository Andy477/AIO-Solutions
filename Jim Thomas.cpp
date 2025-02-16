#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <queue>
#include <climits>
#include <string>
#include <unordered_map>
#define speed()                  \
    ios::sync_with_stdio(false); \
    cin.tie(0)
#define file(name)                       \
    speed();                             \
    freopen(#name "in.txt", "r", stdin); \
    freopen(#name "out.txt", "w", stdout)
#define dbg(x) cout << '>' << #x << ':' << x << endl;
#define ll long long
//Sirhc47
using namespace std;
ll gcd(ll a, ll b)
{
    if (b > a)
    {
        return gcd(b, a);
    }
    if (b == 0){
        return a;
    }
    return gcd(b, a % b);
    // LCM = (a*b)/gcd(a,b)
}
class SegmentTree
{
private:
    vector<int> tree;
    vector<int> arr;
    int n;
 
    void build(int node, int start, int end)
    {
        if (start == end)
        {
            // Leaf node will have a single element
            tree[node] = arr[start];
        }
        else
        {
            int mid = (start + end) / 2;
            // Recursively build the segment tree
            build(2 * node, start, mid);
            build(2 * node + 1, mid + 1, end);
            // Internal node will have the sum of both of its children
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }
 
    void update(int node, int start, int end, int idx, int val)
    {
        if (start == end)
        {
            // Leaf node
            arr[idx] = val;
            tree[node] = val;
        }
        else
        {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid)
            {
                // If idx is in the left child, recurse on the left child
                update(2 * node, start, mid, idx, val);
            }
            else
            {
                // If idx is in the right child, recurse on the right child
                update(2 * node + 1, mid + 1, end, idx, val);
            }
            // Internal node will have the sum of both of its children
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }
 
    int query(int node, int start, int end, int l, int r)
    {
        if (r < start || end < l)
        {
            // range represented by a node is completely outside the given range
            return 0;
        }
        if (l <= start && end <= r)
        {
            // range represented by a node is completely inside the given range
            return tree[node];
        }
        // range represented by a node is partially inside and partially outside the given range
        int mid = (start + end) / 2;
        int p1 = query(2 * node, start, mid, l, r);
        int p2 = query(2 * node + 1, mid + 1, end, l, r);
        return p1 + p2;
    }
 
public:
    SegmentTree(const vector<int> &inputArr)
    {
        arr = inputArr;
        n = arr.size();
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }
 
    void update(int idx, int val)
    {
        update(1, 0, n - 1, idx, val);
    }
 
    int query(int l, int r)
    {
        return query(1, 0, n - 1, l, r);
    }
};
long long binpow(long long a, long long b, long long m)
{
    a %= m;
    long long res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
int countDigits(ll n)
{
    int digits = 0;
    while (n > 0)
    {
        n /= 10;
        digits++;
    }
    return digits;
}
vector<int> z_function(string s)
{
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++)
    {
        if (i < r)
        {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
        {
            z[i]++;
        }
        if (i + z[i] > r)
        {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}
void printv(const vector<int> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}
const int dx[5] {1, 0, -1, 0, 0}, dy[5]{0, 1, 0, -1, 0};
typedef pair<int,int> pii;
vector<vector<pii>> adj;
vector<int> depth;
int jump[(int)(1e5+5)][31];
ll cost[(int)(1e5+5)];
void dfs(int x, int last = -1, ll cst = 0){
    for (auto sigma : adj[x]){
        auto [i,j] = sigma;
        if (i == last){
            continue;
        }
        jump[i][0] =x;
        cost[i] = cst + j;
        for (int k = 1; k < 30; k++){
            jump[i][k] = jump[jump[i][k-1]][k-1];
        }
        depth[i] = depth[x]+1;
        dfs(i,x,cost[i]);
    }
}
 
int lca(int x, int y){
    for (int k = 29; k >= 0; k--){
        if (depth[jump[x][k]]>=depth[y]) x = jump[x][k];
        if (depth[jump[y][k]]>=depth[x]) y = jump[y][k];
    }
    for (int k = 29; k>=0; k--){
        if (jump[x][k] != jump[y][k]){
            x = jump[x][k];
            y = jump[y][k];
        }
    }
    return (x==y) ? x : jump[x][0];
}
 
int main()
{
    freopen("jim.in", "r", stdin);
    freopen("jim.out", "w", stdout);
    int n, q;
    cin >> n >> q;
    adj.resize(n);
    depth.resize(n);
    for (int i = 0; i < n-1; i++){
        int x,y;
        cin >> x >> y;
        x--;
        y--;
        int d;
        cin >> d;
        adj[x].push_back({y, d});
        adj[y].push_back({x,d});
    }
 
    depth[0] = 0;
    jump[0][0] = 0;
    cost[0] = 0;
    dfs(0);
 
 
 
 
    vector<ll> ans;
    while (q--){
        int x,y;
        cin >> x >> y;
        x--;
        y--;
        ans.push_back(cost[x]+cost[y]-2*cost[lca(x,y)]);
    }
    for (auto sus : ans){
        cout << sus << "\n";
    }
    return 0;
}
