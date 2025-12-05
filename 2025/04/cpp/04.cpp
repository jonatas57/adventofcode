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

int task1(vector<string>& input) {
  int ans = 0;
  int n = input.size();
  int m = input[0].size();
  loop(n) vloop(j, m) {
    if (input[i][j] != '@') continue;
    int cnt = -1;
    for (int a = i - 1;a <= i + 1;a++) for (int b = j -  1;b <= j + 1;b++) {
      if (a < 0 or b < 0 or a >= n or b >= m) continue;
      cnt += input[a][b] == '@';
    }
    ans += cnt < 4;
  }
  return ans;
}

int task2(vector<string> input) {
  int ans = 0;
  int n = input.size();
  int m = input[0].size();
  while (true) {
    vector<ii> rem;
    loop(n) vloop(j, m) {
      if (input[i][j] != '@') continue;
      int cnt = -1;
      for (int a = i - 1;a <= i + 1;a++) for (int b = j -  1;b <= j + 1;b++) {
        if (a < 0 or b < 0 or a >= n or b >= m) continue;
        cnt += input[a][b] == '@';
      }
      if (cnt < 4) rem.emplace_back(i, j);
    }
    if (rem.empty()) break;
    ans += rem.size();
    for (auto& [x, y] : rem) input[x][y] = '.';
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
  
  string s;
  vector<string> input;
  while (cin >> s) input.push_back(s);
  cout << "Task 1: " << task1(input) << endl;
  cout << "Task 2: " << task2(input) << endl;
  return 0;
}

