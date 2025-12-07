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

int task1(vector<string> ss) {
  int ans = 0;
  each(c, ss[0]) if (c == 'S') c = '|';
  for (int i = 1;i < ss.size();i++) {
    for (int j = 0;ss[i][j];j++) {
      if (ss[i - 1][j] != '|') continue;
      if (ss[i][j] == '^') {
        ans++;
        ss[i][j - 1] = ss[i][j + 1] = '|';
      }
      else if (ss[i][j] == '.') ss[i][j] = '|';
    }
  }
  return ans;
}

ll task2(vector<string> ss) {
  vector<vector<ll>> cnt(ss.size(), vector<ll>(ss[0].size()));
  loop(ss[0].size()) {
    if (ss[0][i] == 'S') {
      ss[0][i] = '|';
      cnt[0][i]++;
    }
  }
  for (int i = 1;i < ss.size();i++) {
    for (int j = 0;ss[i][j];j++) {
      if (ss[i - 1][j] != '|') continue;
      if (ss[i][j] == '^') {
        ss[i][j - 1] = ss[i][j + 1] = '|';
        cnt[i][j - 1] += cnt[i - 1][j];
        cnt[i][j + 1] += cnt[i - 1][j];
      }
      else if (ss[i][j] == '.' or ss[i][j] == '|') {
        ss[i][j] = '|';
        cnt[i][j] += cnt[i - 1][j];
      }
    }
  }
  ll ans = 0;
  each(x, cnt.back()) ans += x;
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
  
  vector<string> ss;
  string s;
  while (cin >> s) ss.push_back(s);
  cout << "Task 1: " << task1(ss) << endl;
  cout << "Task 2: " << task2(ss) << endl;
  return 0;
}

