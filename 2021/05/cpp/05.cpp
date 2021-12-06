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

int task1(vector<pair<ii, ii>>& ls) {
  vector<vi> cnt(1000, vi(1000, 0));
  int ans = 0;
  for (auto& [p, q] : ls) {
    if (p > q) swap(p, q);
    auto [x, y] = p;
    auto [a, b] = q;
    if (x == a) for (int i = y;i <= b;i++) if (cnt[x][i]++ == 1) ans++;
    if (y == b) for (int i = x;i <= a;i++) if (cnt[i][y]++ == 1) ans++;
  }
  return ans;
}

int sign(int x) {
  return x ? x / abs(x) : 0;
}

int task2(vector<pair<ii, ii>>& ls) {
  vector<vi> cnt(1000, vi(1000, 0));
  int ans = 0;
  for (auto& [p, q] : ls) {
    if (p > q) swap(p, q);
    auto [x, y] = p;
    auto [a, b] = q;
    int dx = sign(a - x);
    int dy = sign(b - y);
    for (int i = x, j = y;;i += dx, j += dy) {
      if (cnt[i][j]++ == 1) ans++;
      if (i == a and j == b) break;
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  string s;
  vector<pair<ii, ii>> ls;
  while (getline(cin, s)) {
    vi a(4, 0);
    int p = 0;
    for (int i = 0;;i++) {
      if (isdigit(s[i])) {
        a[p] *= 10;
        a[p] += s[i] - '0';
      }
      else if (s[i] == ',' or s[i] == '-') p++;
      else if (!s[i]) break;
    }
    ls.emplace_back(ii(a[0], a[1]), ii(a[2], a[3]));
  }
  cout << "Task 1: " << task1(ls) << endl;
  cout << "Task 2: " << task2(ls) << endl;
  return 0;
}

