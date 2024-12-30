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
  int x, y;
  loop(n) vloop(j, m) {
    if (input[i][j] == '^') {
      x = i;
      y = j;
      i = j = INF;
    }
  }
  vector<ii> pos;
  int dir = 0;
  while (true) {
    pos.emplace_back(x, y);
    int nx = x + (dir == 2) - (dir == 0);
    int ny = y + (dir == 1) - (dir == 3);
    if (nx < 0 or nx >= n or ny < 0 or ny >= m) break;
    if (input[nx][ny] == '#') {
      dir = (dir + 1) % 4;
    }
    else {
      x = nx;
      y = ny;
    }
  }
  sort(iter(pos));
  return unique(iter(pos)) - pos.begin();
}

int task2(vector<string> input) {
  int n = input.size();
  int m = input[0].size();
  int x, y;
  loop(n) vloop(j, m) {
    if (input[i][j] == '^') {
      x = i;
      y = j;
      i = j = INF;
    }
  }
  auto check = [&] (int x, int y) {
    vector<vi> vis(n, vi(m));
    int dir = 0;
    while (true) {
      if (vis[x][y] & (1 << dir)) return true;
      vis[x][y] |= 1 << dir;
      int nx = x + (dir == 2) - (dir == 0);
      int ny = y + (dir == 1) - (dir == 3);
      if (nx < 0 or nx >= n or ny < 0 or ny >= m) return false;
      if (input[nx][ny] == '#') dir = (dir + 1) % 4;
      else {
        x = nx;
        y = ny;
      }
    }
    return true;
  };
  int ans = 0;
  loop(n) vloop(j, n) {
    if (input[i][j] == '#') continue;
    input[i][j] = '#';
    ans += check(x, y);
    input[i][j] = '.';
  }
  return ans;
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

