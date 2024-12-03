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

int task1(vector<vi>& a) {
  int ans = 0;
  each(v, a) {
    int mt = 0;
    bool del = true;
    for (int i = 1;i < (int)v.size();i++) {
      mt += v[i] < v[i - 1];
      int x = abs(v[i] - v[i - 1]);
      del &= x >= 1 and x <= 3;
    }
    if ((!mt or mt == v.size() - 1) and del) ans++;
  }
  return ans;
}

int task2(vector<vi> a) {
  int ans = 0;
  each(b, a) {
    int n = b.size();
    vector<vi> a2(n);
    loop(n) {
      vloop(j, n) {
        if (j == i) continue;
        a2[i].push_back(b[j]);
      }
    }
    bool safe = false;
    a2.push_back(b);
    each(v, a2) {
      if (safe) break;
      int mt = 0;
      bool del = true;
      for (int i = 1;i < (int)v.size();i++) {
        mt += v[i] < v[i - 1];
        int x = abs(v[i] - v[i - 1]);
        del &= x >= 1 and x <= 3;
      }
      if ((!mt or mt == v.size() - 1) and del) safe = true;
    }
    if (safe) ans++;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
  
  vector<vi> input;
  string s;
  while (getline(cin, s)) {
    stringstream ss;
    ss << s;
    int x;
    vi a;
    while (ss >> x) {
      a.push_back(x);
    }
    input.push_back(a);
  }
  cout << "Task 1: " << task1(input) << endl;
  cout << "Task 2: " << task2(input) << endl;
  return 0;
}

