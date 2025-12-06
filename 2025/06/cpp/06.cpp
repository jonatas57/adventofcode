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

ll task1(vector<string> ss, vector<function<ll(ll, ll)>> fs) {
  vector<vector<ll>> vs;
  each(s, ss) {
    stringstream sin;
    sin << s;
    ll x;
    vs.emplace_back();
    while (sin >> x) vs.back().push_back(x);
  }

  int n = fs.size();
  int m = vs.size();
  ll ans = 0;
  loop(n) {
    ll acc = vs[0][i];
    for (int j = 1;j < m;j++) {
      acc = fs[i](acc, vs[j][i]);
    }
    ans += acc;
  }
  return ans;
}

ll task2(vector<string> ss, vector<function<ll(ll, ll)>> fs) {
  vector<vector<ll>> vs;
  each(s, ss) s += ' ';
  vector<ll> v;
  for (int i = 0;ss[0][i];i++) {
    bool ok = false;
    for (int j = 0;j < ss.size();j++) ok |= isdigit(ss[j][i]);
    if (ok) {
      ll x = 0;
      for (int j = 0;j < ss.size();j++) {
        if (isdigit(ss[j][i])) {
          x *= 10;
          x += ss[j][i] - '0';
        }
      }
      v.push_back(x);
    }
    else {
      vs.push_back(v);
      v.clear();
    }
  }

  int n = fs.size();
  ll ans = 0;
  loop(n) {
    ll acc = vs[i][0];
    for (int j = 1;j < vs[i].size();j++) {
      acc = fs[i](acc, vs[i][j]);
    }
    ans += acc;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
  
  vector<string> vs;
  vector<function<ll(ll, ll)>> fs;
  string s;
  while (getline(cin, s)) {
    if (isdigit(s[s.find_first_not_of(' ')])) {
      vs.push_back(s);
    }
    else {
      string t;
      stringstream ss;
      ss << s;
      while (ss >> t) {
        if (t == "+") fs.push_back([] (ll a, ll b) { return a + b; });
        else fs.push_back([] (ll a, ll b) { return a * b; });
      }
    }
  }
  cout << "Task 1: " << task1(vs, fs) << endl;
  cout << "Task 2: " << task2(vs, fs) << endl;
  return 0;
}

