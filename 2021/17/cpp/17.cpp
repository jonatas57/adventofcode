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

ll task1(int xl, int xr, int yl, int yr) {
  ll y = yl < 0 ? abs(yl) - 1 : yr;
  return y * (y + 1) / 2;
}

ll task2(int xl, int xr, int yl, int yr) {
  ll ans = 0;
  for (int i = 0;i <= xr;i++) {
    for (int j = yl;j <= abs(yl);j++) {
      if (!i and !j) continue;
      int x = 0, y = 0;
      int a = i, b = j;
      while (x <= xr and y >= yl) {
        x += a;
        y += b;
        a = max(0, a - 1);
        b--;
        if (xl <= x and x <= xr and yl <= y and y <= yr) {
          ans++;
          break;
        }
      }
    }
  }
  return ans;
}

int main() {
  regex r("target area: x=([-|0-9]*)..([-|0-9]*), y=([-|0-9]*)..([-|0-9]*)");
  string s;
  getline(cin, s);
  smatch mr;
  regex_search(s, mr, r);
  cout << "Task 1: " << task1(stoi(mr[1]), stoi(mr[2]), stoi(mr[3]), stoi(mr[4])) << endl;
  cout << "Task 2: " << task2(stoi(mr[1]), stoi(mr[2]), stoi(mr[3]), stoi(mr[4])) << endl;
  return 0;
}

