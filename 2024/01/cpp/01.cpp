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

int task1(vi a, vi b) {
  sort(iter(a));
  sort(iter(b));
  ll ans = 0;
  int n = a.size();
  loop(n) ans += abs(a[i] - b[i]);
  return ans;
}

int task2(vi a, vi b) {
  map<int, int> cnt;
  each(x, b) cnt[x]++;
  int ans = 0;
  each(x, a) ans += x * cnt[x];
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vi a, b;
  string s;
  while (getline(cin, s)) {
    stringstream ss;
    ss << s;
    int x, y;
    ss >> x >> y;
    a.push_back(x);
    b.push_back(y);
  }
  cout << "Task 1: " << task1(a, b) << endl;
  cout << "Task 2: " << task2(a, b) << endl;
  return 0;
}

