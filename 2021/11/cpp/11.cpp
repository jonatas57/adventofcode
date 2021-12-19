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

int task1(vector<vi> a) {
  int ans = 0;
  function<void(int, int)> flash;
  auto inc = [&] (int x, int y) {
    if (a[x][y] == 10) return;
    a[x][y]++;
    if (a[x][y] == 10) flash(x, y);
  };
  flash = [&] (int x, int y) {
    ans++;
    for (int i = x - 1;i <= x + 1;i++) {
      for (int j = y - 1;j <= y + 1;j++) {
        if (x == i and y == j) continue;
        if (i < 0 or i >= 10 or j < 0 or j >= 10) continue;
        inc(i, j);
      }
    }
  };
  loop(100) {
    vloop(x, 10) vloop(y, 10) {
      inc(x, y);
    }
    vloop(x, 10) {
      vloop(y, 10) {
        if (a[x][y] == 10) a[x][y] = 0;
      }
    }
  }
  return ans;
}

int task2(vector<vi> a) {
  int sum = 0;
  each(v, a) each(x, v) sum += x;
  function<void(int, int)> flash;
  auto inc = [&] (int x, int y) {
    if (a[x][y] == 10) return;
    a[x][y]++;
    sum++;
    if (a[x][y] == 10) flash(x, y);
  };
  flash = [&] (int x, int y) {
    for (int i = x - 1;i <= x + 1;i++) {
      for (int j = y - 1;j <= y + 1;j++) {
        if (x == i and y == j) continue;
        if (i < 0 or i >= 10 or j < 0 or j >= 10) continue;
        inc(i, j);
      }
    }
  };
  for (int turn = 1;;turn++) {
    vloop(x, 10) vloop(y, 10) {
      inc(x, y);
    }
    vloop(x, 10) {
      vloop(y, 10) {
        if (a[x][y] == 10) a[x][y] = 0, sum -= 10;
      }
    }
    if (!sum) {
      return turn;
    }
  }
  return -1;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vector<vi> a;
  string s;
  while (cin >> s) {
    a.emplace_back();
    each(c, s) a.back().emplace_back(c - '0');
  }
  cout << "Task 1: " << task1(a) << endl;
  cout << "Task 2: " << task2(a) << endl;
  return 0;
}

