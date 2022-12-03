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

int task1(vector<vi>& input) {
  int ans = 0;
  each(v, input) {
    ans = max(ans, accumulate(iter(v), 0));
  }
  return ans;
}

int task2(vector<vi>& input) {
  vi sums;
  transform(iter(input), back_inserter(sums), [](vi& v) {
    return accumulate(iter(v), 0);
  });
  sort(riter(sums));
  return sums[0] + sums[1] + sums[2];
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vector<vi> input(1);
  string s;
  while (getline(cin, s)) {
    if (s.empty()) input.emplace_back();
    else input.back().push_back(stoi(s));
  }
  cout << "Task 1: " << task1(input) << endl;
  cout << "Task 2: " << task2(input) << endl;
  return 0;
}
