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

bool inside(ii a, ii b) {
  auto [l, r] = a;
  auto [x, y] = b;
  return l <= x and y <= r or x <= l and r <= y;
}

int task1(vector<pair<ii, ii>>& input) {
  int ans = 0;
  for (auto& [a, b] : input) {
    if (inside(a, b) or inside(b, a)) ans++;
  }
  return ans;
}

int task2(vector<pair<ii, ii>>& input) {
  int ans = 0;
  for (auto& [a, b] : input) {
    if (a > b) swap(a, b);
    if (a.second >= b.first) ans++;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vector<pair<ii, ii>> input;
  string s;
  int a, b, c, d;
  char t;
  while (cin >> a >> t >> b >> t >> c >> t >> d) {
    input.emplace_back(make_pair(a, b), make_pair(c, d));
  }
  cout << "Task 1: " << task1(input) << endl;
  cout << "Task 2: " << task2(input) << endl;
  return 0;
}

