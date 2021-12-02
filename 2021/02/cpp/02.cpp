#include <bits/stdc++.h>

using namespace std;

typedef long long          ll;
typedef unsigned long long ull;
typedef vector<int>         vi;
typedef vector<bool>       vb;
typedef map<int, int>      mii;
typedef pair<int, int>     ii;

#define INF                0x3f3f3f3f
#define INFLL              0x3f3f3f3f3f3f3f3f
#define each(x, s)         for(auto& x : s)
#define loop(x)            for(int i = 0;i < x;i++)
#define vloop(v, x)        for(int v = 0;v < x;v++)
#define avg(l, r)          (l + r) >> 1
#define iter(a)            a.begin(), a.end()
#define riter(a)           a.rbegin(), a.rend()
#define endl               "\n"

const ll mod = 1000000007;
const double EPS = 1e-7;
const double PI = acos(-1);

ll task1(vector<pair<string, int>>& a) {
  ll pos = 0;
  ll dep = 0;
  for (auto& [op, x] : a) {
    switch (op[0]) {
      case 'f':
      pos += x;
      break;
      case 'd':
      dep += x;
      break;
      case 'u':
      dep -= x;
      break;
    }
  }
  return pos * dep;
}

ll task2(vector<pair<string, int>>& a) {
  ll pos = 0;
  ll dep = 0;
  ll aim = 0;
  for (auto& [op, x] : a) {
    switch (op[0]) {
      case 'f':
      pos += x;
      dep += x * aim;
      break;
      case 'd':
      aim += x;
      break;
      case 'u':
      aim -= x;
      break;
    }
  }
  return pos * dep;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vector<pair<string, int>> a;
  string op;
  int x;
  while (cin >> op >> x) {
    a.emplace_back(op, x);
  }
  cout << "Task 1: " << task1(a) << endl;
  cout << "Task 2: " << task2(a) << endl;
  return 0;
}

