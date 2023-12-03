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

struct game {
  int id;
  vector<tuple<int, int, int>> ds;
};

vector<game> parse(vector<string> input) {
  vector<game> gs;
  each(s, input) {
    string t;
    stringstream ss;
    game g;
    ss << s;
    ss >> t >> g.id >> t;
    int q;
    string color;
    vi ms(3, 0);
    while (ss >> q >> color) {
      ms[color[0] == 'r' ? 0 : color[0] == 'g' ? 1 : 2] += q;
      if (color.back() != ',') {
        g.ds.emplace_back(ms[0], ms[1], ms[2]);
        ms.assign(3, 0);
      }
    }
    gs.push_back(g);
  }
  return gs;
}

int task1(vector<string> input) {
  int ans = 0;
  vector<game> gs = parse(input);
  each(g, gs) {
    vi ms(3, 0);
    for (auto& [r, g, b] : g.ds) {
      ms[0] = max(ms[0], r);
      ms[1] = max(ms[1], g);
      ms[2] = max(ms[2], b);
    }
    bool ok = true;
    loop(3) ok &= ms[i] <= 12 + i;
    if (ok) ans += g.id;
  }
  return ans;
}

int task2(vector<string> input) {
  int ans = 0;
  vector<game> gs = parse(input);
  each(g, gs) {
    vi ms(3, 0);
    for (auto& [r, g, b] : g.ds) {
      ms[0] = max(ms[0], r);
      ms[1] = max(ms[1], g);
      ms[2] = max(ms[2], b);
    }
    ans += accumulate(iter(ms), 1, [] (int a, int b) { return a * b; });
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vector<string> input;
  string s;
  while (getline(cin, s)) {
    if (!s.empty()) input.push_back(s);
  }

  cout << "Task 1: " << task1(input) << endl;
  cout << "Task 2: " << task2(input) << endl;
  return 0;
}

