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

ll task1(vector<string>& ss) {
  ll a = 0, b = 0;
  int n = ss.size();
  int l = ss[0].length();
  for (int i = 0;ss[0][i];i++) {
    int cnt = 0;
    each(s, ss) {
      cnt += s[i] - '0';
    }
    if (cnt > n / 2) a |= 1 << (l - i - 1);
    else b |= 1 << (l - i - 1);
  }
  return a * b;
}


ll task2(vector<string>& ss) {
  int n = ss.size();
  vb ok;
  auto run = [&] (bool x) {
    ok.assign(n, true);
    int m = n;
    for (int i = 0;m > 1;i++) {
      int cnt = 0;
      vloop(j, n) {
        if (!ok[j]) continue;
        cnt += ss[j][i] - '0';
      }
      char bit;
      if ((2 * cnt >= m) ^ x) bit = '1';
      else bit = '0';
      vloop(j, n) {
        if (!ok[j]) continue;
        if (ss[j][i] != bit) {
          m--;
          ok[j] = false;
        }
      }
    }
    int ans = 0;
    loop(n) {
      if (ok[i]) {
        int l = ss[i].length();
        vloop(j, l) {
          if (ss[i][j] == '1') ans |= 1 << (l - j - 1);
        }
        break;
      }
    }
    return ans;
  };
  return run(true) * run(false);
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  string s;
  vector<string> a;
  while (cin >> s) {
    a.push_back(s);
  }
  cout << "Task 1: " << task1(a) << endl;
  cout << "Task 2: " << task2(a) << endl;
  return 0;
}

