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

ll task1(vector<pair<ll, vector<ll>>> input) {
  ll ans = 0;
  for (auto& [k, v] : input) {
    int l = v.size();
    loop((1 << l)) {
      ll x = 0;
      for (int j = 0, m = 1;j < l;m <<= 1, j++) {
        if (i & m) x *= v[j];
        else x += v[j];
      }
      if (x == k) {
        ans += x;
        break;
      }
    }
  }
  return ans;
}

ll xp(ll b, ll e) {
  if (e == 0) return 1;
  ll c = xp(b, e >> 1);
  c = c * c;
  if (e & 1) c = c * b;
  return c;
}

ll concat(ll x, ll y) {
  if (!y) {
    x *= 10;
  }
  else {
    for (ll i = y;i;i /= 10) x *= 10;
    x += y;
  }
  return x;
}

ll task2(vector<pair<ll, vector<ll>>> input) {
  ll ans = 0;
  for (auto& [k, v] : input) {
    int l = v.size();
    loop(xp(3, l)) {
      ll x = 0;
      for (int j = 0, m = i;j < l;m /= 3, j++) {
        switch (m % 3) {
          case 0:
          x += v[j];
          break;
          case 1:
          x *= v[j];
          break;
          case 2:
          x = concat(x, v[j]);
          break;
        }
      }
      if (x == k) {
        ans += x;
        break;
      }
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
  
  vector<pair<ll, vector<ll>>> input;
  string s;
  while (getline(cin, s)) {
    stringstream ss;
    ss << s;
    ll x;
    ss >> x;
    ss.get();
    vector<ll> a;
    ll y;
    while (ss >> y) a.push_back(y);
    input.emplace_back(x, a);
  }
  cout << "Task 1: " << task1(input) << endl;
  cout << "Task 2: " << task2(input) << endl;
  return 0;
}

