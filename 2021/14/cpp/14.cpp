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

using namespace std::literals;

string apply(string s, map<char, map<char, char>>& a) {
  string ans = s.substr(0, 1);
  for (int i = 1;s[i];i++) {
    ans += a[ans.back()][s[i]];
    ans += s[i];
  }
  return ans;
}

int task1(string s, map<char, map<char, char>>& a) {
  loop(10) s = apply(s, a);
  vi cnt(26, 0);
  each(c, s) cnt[c - 'A']++;
  int l = INF, h = 0;
  each(x, cnt) {
    if (!x) continue;
    h = max(h, x);
    l = min(l, x);
  }
  return h - l;
}

void apply2(map<string, ll>& ps, map<string, pair<string, string>>& ts) {
  map<string, ll> ps2;
  for (auto& [s, q] : ps) {
    auto& [t, u] = ts[s];
    ps2[t] += q;
    ps2[u] += q;
  }
  ps.swap(ps2);
}

ll task2(string s, map<char, map<char, char>>& a) {
  map<string, ll> ps;
  map<string, pair<string, string>> ts;
  for (auto& [c, m] : a) {
    for (auto& [d, e] : m) {
      ts[""s + c + d] = make_pair(""s + c + e, ""s + e + d);
    }
  }
  for (int i = 1;s[i];i++) {
    ps[""s + s[i - 1] + s[i]]++;
  }
  loop(40) apply2(ps, ts);
  vector<ll> cnt(26, 0);
  cnt[s[0] - 'A'] = cnt[s.back() - 'A'] = 1;
  for (auto& [t, q] : ps) {
    cnt[t[0] - 'A'] += q;
    cnt[t[1] - 'A'] += q;
  }
  ll l = INFLL, h = 0;
  each(x, cnt) {
    if (!x) continue;
    h = max(h, x);
    l = min(l, x);
  }
  return (h - l) >> 1;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  string s, t;
  getline(cin, s);
  getline(cin, t);
  map<char, map<char, char>> a;
  while (getline(cin, t)) {
    stringstream ss;
    ss << t;
    string lhs, rhs;
    ss >> lhs >> rhs >> rhs;
    a[lhs[0]][lhs[1]] = rhs[0];
  }
  cout << "Task 1: " << task1(s, a) << endl;
  cout << "Task 2: " << task2(s, a) << endl;
  return 0;
}

