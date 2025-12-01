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

int task1(vi rots) {
  int x = 50;
  int ans = 0;
  each(y, rots) {
    x += y;
    x %= 100;
    if (x < 0) x += 100;
    if (!x) ans++;
  }
  return ans;
}

int task2(vi rots) {
  int x = 50;
  int ans = 0;
  each(y, rots) {
    ans += abs(x + y) / 100;
    if (x and x <= -y) ans++;
    x += y;
    x %= 100;
    if (x < 0) x += 100;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
  
  vi input;
  string s;
  while (cin >> s) {
    int x = stoi(s.substr(1)) * (s[0] == 'L' ? -1 : 1);
    input.push_back(x);
  }
  cout << "Task 1: " << task1(input) << endl;
  cout << "Task 2: " << task2(input) << endl;
  return 0;
}

