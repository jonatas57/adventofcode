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

int task1(vi& a) {
  sort(iter(a));
  int n = a.size();
  int x = a[n / 2];
  int ans = 0;
  each(y, a) {
    ans += abs(x - y);
  }
  return ans;
}

ll task2(vi& a) {
  sort(iter(a));
  int l = a[0], r = a.back();
  auto f = [&] (int x) {
    ll s = 0;
    each(y, a) {
      ll z = abs(y - x);
      s += (z * (z + 1)) / 2;
    }
    return s;
  };
  while (r - l >= 3) {
    int del = (r - l) / 3;
    int x = l + del, y = r - del;
    int f1 = f(x);
    int f2 = f(y);
    if (f1 <= f2) r = y;
    if (f1 >= f2) l = x;
  }
  ll ans = INFLL;
  for (int i = l;i <= r;i++) ans = min(ans, f(i));
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

