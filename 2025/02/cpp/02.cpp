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

pair<string, string> split(string s, int pos) {
  string l = s.substr(0, pos);
  string r = s.substr(pos);
  return make_pair(l, r);
}

ll task1(vector<pair<string, string>>& ss) {
  ll ans = 0;
  for (auto& [l, r] : ss) {
    auto [ll, lr] = split(l, l.size() / 2);
    auto [rl, rr] = split(r, r.size() / 2);
    if (l.size() & 1) ll = "1" + string(ll.size(), '0');
    if (r.size() & 1) rl = string(rl.size(), '9');
    int x = stoi(ll) + (lr > ll and ~l.size() & 1);
    int y = stoi(rl) - (rr < rl and ~r.size() & 1);
    for (int i = x;i <= y;i++) {
      string s = to_string(i);
      ans += stoll(s + s);
    }
  }
  return ans;
}

ll task2(vector<pair<string, string>>& ss) {
  vector<ll> l, r;
  for (auto& [sl, sr] : ss) {
    l.push_back(stoll(sl));
    r.push_back(stoll(sr));
  }
  sort(iter(l));
  sort(iter(r));
  int n = ss.size();
  bool ok = true;
  set<ll> vs;
  for (int i = 1;ok;i++) {
    string s = to_string(i);
    string t = s + s;
    for (int j = 0;;t += s, j++) {
      ll x = stoll(t);
      if (x > r.back() and !j) ok = false;
      int pos = upper_bound(iter(l), x) - l.begin();
      if (pos) {
        pos--;
        if (l[pos] <= x and x <= r[pos]) vs.insert(x);
        if (pos == n - 1) break;
      }
    }
  }
  ll ans = 0;
  each(x, vs) ans += x;
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
  
  string s;
  getline(cin, s);
  size_t p = 0;
  vector<pair<string, string>> ss;
  while (true) {
    size_t a = s.find('-', p);
    size_t b = s.find(',', a);
    ss.emplace_back(s.substr(p, a - p), s.substr(a + 1, b == string::npos ? b : b - a - 1));
    if (b == string::npos) break;
    p = b + 1;
  }
  cout << "Task 1: " << task1(ss) << endl;
  cout << "Task 2: " << task2(ss) << endl;
  return 0;
}

