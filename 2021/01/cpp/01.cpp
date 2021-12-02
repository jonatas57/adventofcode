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

int task1(vi& a) {
  int n = a.size();
  int ans = 0;
  for (int i = 1;i < n;i++) ans += a[i] > a[i - 1];
  return ans;
}

int task2(vi& a) {
  int n = a.size();
  int ans = 0;
  for (int i = 3;i < n;i++) ans += a[i] > a[i - 3];
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vi a;
  int x;
  while (cin >> x) a.push_back(x);
  cout << "Task 1: " << task1(a) << endl;
  cout << "Task 2: " << task2(a) << endl;
  return 0;
}

