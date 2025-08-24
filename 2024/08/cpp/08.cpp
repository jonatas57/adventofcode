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

int task1(vector<string> input) {
  int n = input.size();
  int m = input[0].size();
  map<char, vector<ii>> as;
  loop(n) vloop(j, n) {
    if (input[i][j] == '.') continue;
    as[input[i][j]].emplace_back(i, j);
  }
  auto check = [&] (int x, int y) { return 0 <= x and x < n and 0 <= y and y < m; };
  set<ii> s;
  for (auto& [c, v] : as) {
    for (auto& [a, b] : v) for (auto& [c, d] : v) {
      if (a == c and b == d) break;
      int dx = c - a, dy = d - b;
      if (check(a - dx, b - dy)) s.emplace(a - dx, b - dy);
      if (check(c + dx, d + dy)) s.emplace(c + dx, d + dy);
    }
  }
  return s.size();
}

int task2(vector<string> input) {
  int n = input.size();
  int m = input[0].size();
  map<char, vector<ii>> as;
  loop(n) vloop(j, n) {
    if (input[i][j] == '.') continue;
    as[input[i][j]].emplace_back(i, j);
  }
  auto check = [&] (int x, int y) { return 0 <= x and x < n and 0 <= y and y < m; };
  set<ii> s;
  for (auto& [c, v] : as) {
    for (auto& [a, b] : v) {
      s.emplace(a, b);
      for (auto& [c, d] : v) {
        if (a == c and b == d) break;
        int dx = c - a, dy = d - b;
        for (int i = 1;;i++) {
          if (check(a - i * dx, b - i * dy)) s.emplace(a - i * dx, b - i * dy);
          else break;
        }
        for (int i = 1;;i++) {
          if (check(c + i * dx, d + i * dy)) s.emplace(c + i * dx, d + i * dy);
          else break;
        }
      }
    }
  }
  return s.size();
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
  
  string s;
  vector<string> input;
  while (getline(cin, s)) input.push_back(s);
  cout << "Task 1: " << task1(input) << endl;
  cout << "Task 2: " << task2(input) << endl;
  return 0;
}

