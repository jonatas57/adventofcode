#include <bits/stdc++.h>

using namespace std;

typedef long long          ll;
typedef unsigned long long ull;
typedef vector<int>         vi;
typedef vector<bool>       vb;
typedef map<int, int>      mii;
typedef pair<int, int>     ii;

#define INF                0x3f3f3f3f
#define INFLL              0x3f3f3f3f3f3f3f3f
#define each(x, s)         for(auto& x : s)
#define loop(x)            for(int i = 0;i < x;i++)
#define vloop(v, x)        for(int v = 0;v < x;v++)
#define avg(l, r)          (l + r) >> 1
#define iter(a)            a.begin(), a.end()
#define riter(a)           a.rbegin(), a.rend()
#define endl               "\n"

const ll mod = 1000000007;
const double EPS = 1e-7;
const double PI = acos(-1);

int task1(vector<string>& a) {
  int ans = 0;
  int n = a.size(), m = a[0].length();
  loop(n) vloop(j, m) {
    bool low = true;
    vloop(dir, 4) {
      int nx = i + (dir == 0) - (dir == 1);
      int ny = j + (dir == 2) - (dir == 3);
      if (nx < 0 or nx >= n or ny < 0 or ny >= m) continue;
      if (a[nx][ny] <= a[i][j]) low = false;
    }
    if (low) ans += a[i][j] - '0' + 1;
  }
  return ans;
}

struct dsu {
  vi id, sz;

  dsu(int n) : id(n), sz(n, 1) {
    loop(n) id[i] = i;
  }

  int find(int x) {
    return x == id[x] ? x : id[x] = find(id[x]);
  }

  bool join(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    if (sz[a] > sz[b]) swap(a, b);
    id[a] = id[b];
    sz[b] += sz[a];
    return true;
  }
};

int task2(vector<string>& a) {
  int n = a.size(), m = a[0].length();
  dsu uf(n * m);
  loop(n) vloop(j, m) {
    if (a[i][j] == '9') continue;
    vloop(dir, 4) {
      int nx = i + (dir == 0) - (dir == 1);
      int ny = j + (dir == 2) - (dir == 3);
      if (nx < 0 or nx >= n or ny < 0 or ny >= m) continue;
      if (a[nx][ny] != '9') uf.join(i * m + j, nx * m + ny);
    }
  }
  set<ii> ss;
  loop(n * m) ss.emplace(uf.sz[uf.find(i)], uf.find(i));
  vector<ii> b(riter(ss));
  ll ans = 1;
  loop(3) ans *= b[i].first;
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vector<string> a;
  string s;
  while (cin >> s) a.push_back(s);
  cout << "Task 1: " << task1(a) << endl;
  cout << "Task 2: " << task2(a) << endl;
  return 0;
}

