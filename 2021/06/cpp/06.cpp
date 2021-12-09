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

vi parse(string& s) {
  vi a;
  int x = 0;
  for (int i = 0;;i++) {
    if (isdigit(s[i])) {
      x *= 10;
      x += s[i] - '0';
    }
    else {
      a.push_back(x);
      x = 0;
      if (!s[i]) break;
    }
  }
  return a;
}

vector<vector<ll>> operator*(vector<vector<ll>>& a, vector<vector<ll>>& b) {
  int n = a.size();
  vector<vector<ll>> c(n, vector<ll>(n));
  loop(n) {
    vloop(j, n) {
      vloop(k, n) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return c;
}

vector<vector<ll>> xp(vector<vector<ll>>& b, ll e) {
  if (e == 1) return b;
  auto c = xp(b, e >> 1);
  c = c * c;
  if (e & 1) c = c * b;
  return c;
}

vector<vector<ll>> m = {
  {0,1,0,0,0,0,0,0,0},
  {0,0,1,0,0,0,0,0,0},
  {0,0,0,1,0,0,0,0,0},
  {0,0,0,0,1,0,0,0,0},
  {0,0,0,0,0,1,0,0,0},
  {0,0,0,0,0,0,1,0,0},
  {1,0,0,0,0,0,0,1,0},
  {0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0}
};

ll task1(vi& a) {
  vector<ll> cnt(9, 0);
  each(x, a) cnt[x]++;
  auto p = xp(m, 80);
  ll ans = 0;
  loop(9) {
    vloop(j, 9) {
      ans += p[i][j] * cnt[j];
    }
  }
  return ans;
}

ll task2(vi& a) {
  vector<ll> cnt(9, 0);
  each(x, a) cnt[x]++;
  auto p = xp(m, 256);
  ll ans = 0;
  loop(9) {
    vloop(j, 9) {
      ans += p[i][j] * cnt[j];
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  string s;
  cin >> s;
  vi a = parse(s);
  cout << "Task 1: " << task1(a) << endl;
  cout << "Task 2: " << task2(a) << endl;
  return 0;
}

