#include <bits/stdc++.h>

using namespace std;

typedef long long          ll;
typedef vector<int>        vi;
typedef vector<bool>       vb;
typedef pair<int, int>     ii;

const int INF = 0x3f3f3f3f;
const ll  INFLL = 0x3f3f3f3f3f3f3f3fll;

#define each(x, s)  for(auto& x : s)
#define loop(x)     for(int i = 0;i < x;i++)
#define vloop(v, x) for(int v = 0;v < x;v++)
#define iter(a)     a.begin(), a.end()
#define riter(a)    a.rbegin(), a.rend()
#define endl        "\n"
#define avg(l, r)   (l + r) / 2

struct almanac {
  vector<ll> seeds;
  vector<vector<tuple<ll, ll, ll>>> maps;

  almanac(vector<string> input) {
    parseSeeds(input[0]);
    parseMaps(input);
  }

  void parseSeeds(string& s) {
    stringstream ss;
    ss << s;
    string t;
    ss >> t;
    ll x;
    while (ss >> x) seeds.push_back(x);
  }

  void parseMaps(vector<string>& ls) {
    vector<tuple<ll, ll, ll>> m;
    for (int i = 2;i < (int)ls.size();i++) {
      if (!ls[i].size()) {
        if (!m.empty()) {
          sort(iter(m));
          maps.push_back(m);
          m.clear();
        }
      }
      else if (isdigit(ls[i][0])) {
        int p = ls[i].find(' ');
        int q = ls[i].find(' ', p + 1);
        ll a = stoll(ls[i].substr(0, p));
        ll b = stoll(ls[i].substr(p + 1, q - p - 1));
        ll c = stoll(ls[i].substr(q + 1));
        m.emplace_back(b, a, c);
      }
    }
    sort(iter(m));
    maps.push_back(m);
  }
};

ll task1(almanac& a) {
  ll ans = INFLL;
  each(seed, a.seeds) {
    ll loc = seed;
    each(m, a.maps) {
      for (auto& [a, b, c] : m) {
        if (a <= loc and loc < a + c) {
          loc -= a;
          loc += b;
          break;
        }
      }
    }
    ans = min(ans, loc);
  }
  return ans;
}

bool valid(pair<ll, ll>& a) {
  return a.first <= a.second;
}

ll task2(almanac& a) {
  vector<pair<ll, ll>> ps, aux;
  for (int i = 0;i < (int)a.seeds.size();i += 2) {
    ps.emplace_back(a.seeds[i], a.seeds[i] + a.seeds[i + 1] - 1);
  }
  sort(iter(ps));
  for (auto& mp : a.maps) {
    int n = ps.size();
    int m = mp.size();
    for (int i = 0, j = 0;i < n;) {
      if (j == m) {
        aux.push_back(ps[i++]);
        continue;
      }
      auto& [l, r] = ps[i];
      auto& [a, b, c] = mp[j];
      ll del = b - a;
      pair<ll, ll> p1(l, min(r, a - 1));
      pair<ll, ll> p2(max(l, a), min(r, a + c - 1));
      pair<ll, ll> p3(max(l, a + c), r);
      if (valid(p1)) aux.push_back(p1);
      if (valid(p2)) {
        aux.emplace_back(p2.first + del, p2.second + del);
      }
      if (valid(p3)) {
        l = p3.first;
        j++;
      }
      else i++;
    }
    ps.clear();
    ps.swap(aux);
    sort(iter(ps));
  }
  return ps[0].first;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vector<string> input;
  string s;
  while (getline(cin, s)) input.push_back(s);
  almanac a(input);
  cout << "Task 1: " << task1(a) << endl;
  cout << "Task 2: " << task2(a) << endl;
  return 0;
}

