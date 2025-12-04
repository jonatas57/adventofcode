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
  each(s, input) {
    int l = s[0] - '0';
    int m = 0;
    for (int i = 1;s[i];i++) {
      int x = s[i] - '0';
      m = max(m, 10 * l + x);
      l = max(l, x);
    }
    ans += m;
  }
  return ans;
}

ll task2(vector<string>& input) {
  ll ans = 0;
  each(s, input) {
    int n = s.length();
    vector<vector<ll>> dp(13, vector<ll>(n + 1));
    for (int pos = 1;pos <= 12;pos++) {
      for (int i = 1;i <= n;i++) {
        if (pos <= i) dp[pos][i] = max(dp[pos][i - 1], dp[pos - 1][i - 1] * 10 + (s[i - 1] - '0'));
      }
    }
    ans += dp[12][n];
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

