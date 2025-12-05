#include <bits/stdc++.h>

using namespace std;

typedef long long      ll;
typedef vector<int>    vi;
typedef vector<bool>   vb;
typedef pair<int, int> ii;

const int INF = 0x3f3f3f3f;
const ll  INFLL = 0x3f3f3f3f3f3f3f3fll;

#define each(x, s)  for (auto& x : s)
#define loop(x)     for (int i = 0;i < x;i++)
#define vloop(v, x) for (int v = 0;v < x;v++)
#define iter(a)     a.begin(), a.end()
#define riter(a)    a.rbegin(), a.rend()
#define endl        "\n"

int task1(vector<pair<ll, ll>> rs, vector<ll> is) {
  vector<pair<ll, ll>> sl;
  for (auto& [l, r] : rs) {
    sl.emplace_back(l, -1);
    sl.emplace_back(r, 1);
  }
  each(x, is) sl.emplace_back(x, 0);
  int cnt = 0;
  int ans = 0;
  sort(iter(sl));
  for (auto& [x, t] : sl) {
    if (!t) ans += !!cnt;
    else cnt -= t;
  }
  return ans;
}

ll task2(vector<pair<ll, ll>> rs) {
  sort(iter(rs));
  ll last = -INF;
  ll ans = 0;
  for (auto& [l, r] : rs) {
    if (r <= last) continue;
    if (l <= last + 1) {
      ans += r - last;
    }
    else {
      ans += r - l + 1;
    }
    last = r;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
  
  string s;
  vector<pair<ll, ll>> rs;
  vector<ll> is;
  while (getline(cin, s) and !s.empty()) {
    stringstream ss;
    ss << s;
    ll l, r;
    char c;
    ss >> l >> c >> r;
    rs.emplace_back(l, r);
  }
  ll x;
  while (cin >> x) is.push_back(x);
  cout << "Task 1: " << task1(rs, is) << endl;
  cout << "Task 2: " << task2(rs) << endl;
  return 0;
}

