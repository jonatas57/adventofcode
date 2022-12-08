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

int find(string& s, int cnt) {
  vi last(26, -1);
  int start = 0;
  for (int i = 0;s[i];i++) {
    int c = s[i] - 'a';
    start = max(start, last[c] + 1);
    if (i - start == cnt - 1) return i + 1;
    last[c] = i;
  }
  return 0;
}

int task1(string& s) {
  return find(s, 4);
}

int task2(string& s) {
  return find(s, 14);
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  string s;
  cin >> s;
  cout << "Task 1: " << task1(s) << endl;
  cout << "Task 2: " << task2(s) << endl;
  return 0;
}

