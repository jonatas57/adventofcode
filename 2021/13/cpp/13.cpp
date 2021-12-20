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

ii apply(ii p, ii f) {
  if (f.first != -1) p.first = p.first > f.first ? f.first - (p.first - f.first) : p.first;
  else p.second = p.second > f.second ? f.second - (p.second - f.second) : p.second;
  return p;
}

int task1(vector<ii> ps, vector<ii>& fs) {
  transform(iter(ps), ps.begin(), [&] (ii p) { return apply(p, fs[0]); });
  sort(iter(ps));
  ps.resize(unique(iter(ps)) - ps.begin());
  return ps.size();
}

string task2(vector<ii> ps, vector<ii>& fs) {
  each(f, fs) {
    transform(iter(ps), ps.begin(), [&] (ii p) { return apply(p, f); });
  }
  sort(iter(ps), [] (ii a, ii b) { return a.second == b.second ? a.first < b.first : a.second < b.second; });
  ps.resize(unique(iter(ps)) - ps.begin());
  int mx = 0, my = 0;
  for (auto& [x, y] : ps) mx = max(mx, x), my = max(my, y);
  string ans = "", s(mx + 1, '.');
  for (int i = 0, y = 0;i < ps.size();) {
    if (ps[i].second > y) {
      ans += "\n";
      ans += s;
      s = string(mx + 1, '.');
      y++;
    }
    else {
      s[ps[i].first] = '#';
      i++;
    }
  }
  ans += "\n" + s;
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vector<ii> ps, fs;
  string s;
  while (getline(cin, s) and !s.empty()) {
    int p = s.find(',');
    ps.emplace_back(stoi(s.substr(0, p)), stoi(s.substr(p + 1)));
  }
  while (getline(cin, s)) {
    int x = -1, y = -1, v = stoi(s.substr(13));
    if (s[11] == 'x') x = v;
    else y = v;
    fs.emplace_back(x, y);
  }
  cout << "Task 2: " << task2(ps, fs) << endl;
  return 0;
}

