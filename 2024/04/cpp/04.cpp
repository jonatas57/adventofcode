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
  string xmas = "XMAS";
  vector<ii> dirs;
  loop(3) vloop(j, 3) if (i != 1 or j != 1) dirs.emplace_back(i - 1, j - 1);
  auto check = [&] (int x, int y, int dx, int dy) {
    loop(4) {
      int nx = x + i * dx;
      int ny = y + i * dy;
      if (nx < 0 or nx >= n or ny < 0 or ny >= m or input[nx][ny] != xmas[i]) return false;
    }
    return true;
  };
  int ans = 0;
  loop(n) vloop(j, m) {
    if (input[i][j] != 'X') continue;
    for (auto [dx, dy] : dirs) {
      if (check(i, j, dx, dy)) ans++;
    }
  }
  return ans;
}

int task2(vector<string> input) {
  int n = input.size();
  int m = input[0].size();
  auto check = [&] (int x, int y) {
    string d1, d2;
    d1 += input[x - 1][y - 1];
    d1 += input[x + 1][y + 1];
    d2 += input[x - 1][y + 1];
    d2 += input[x + 1][y - 1];
    sort(iter(d1));
    sort(iter(d2));
    if (d1 == "MS" and d2 == "MS") return true;
    return false;
  };
  int ans = 0;
  for (int i = 1;i < n -1;i++) for (int j = 1;j < m - 1;j++) {
    if (input[i][j] != 'A') continue;
    if (check(i, j)) ans++;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
  
  vector<string> input;
  string s;
  while (getline(cin, s)) input.push_back(s);
  cout << "Task 1: " << task1(input) << endl;
  cout << "Task 2: " << task2(input) << endl;
  return 0;
}

