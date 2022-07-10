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

int bfs(vector<string>& a) {
  int n = a.size(), m = a[0].size();
  priority_queue<tuple<int, int, int>> q;
  q.emplace(0, 0, 0);
  vector<vi> dist(n, vi(m, -1));
  while (!q.empty()) {
    auto [d, x, y] = q.top();
    q.pop();
    if (dist[x][y] != -1) continue;
    dist[x][y] = -d;
    vloop(dir, 4) {
      int nx = x + (dir == 0) - (dir == 1);
      int ny = y + (dir == 2) - (dir == 3);
      if (nx < 0 or nx >= n or ny < 0 or ny >= m or dist[nx][ny] != -1) continue;
      q.emplace(d - a[nx][ny] + '0', nx, ny);
    }
  }
  return dist[n - 1][m - 1];
}

int task1(vector<string>& a) {
  return bfs(a);
}

int task2(vector<string> a) {
  int n = a.size(), m = a[0].size();
  loop(n) {
    vloop(j, 4 * m) {
      a[i] += a[i][j] != '9' ? a[i][j] + 1 : '1';
    }
  }
  loop(4 * n) {
    a.emplace_back();
    transform(iter(a[i]), back_inserter(a.back()), [] (char c) {
      return c != '9' ? c + 1 : '1';
    });
  }
  return bfs(a);
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vector<string> ss;
  string s;
  while (cin >> s) ss.push_back(s);
  cout << "Task 1: " << task1(ss) << endl;
  cout << "Task 2: " << task2(ss) << endl;
  return 0;
}

