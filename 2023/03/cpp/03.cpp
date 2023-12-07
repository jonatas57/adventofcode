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

int task1(vector<string> input) {
  int ans = 0;
  int h = input.size();
  int w = input[0].length();
  int val = 0;
  bool part = false;
  loop(h) vloop(j, w) {
    char c = input[i][j];
    if (!isdigit(c)) {
      if (part) ans += val;
      val = 0;
      part = false;
    }
    else {
      val *= 10;
      val += c - '0';
      for (int di = -1;di <= 1;di++) for (int dj = -1;dj <= 1;dj++) {
        if (!di and !dj) continue;
        int ni = i + di;
        int nj = j + dj;
        if (ni < 0 or ni >= h or nj < 0 or nj >= w) continue;
        char c2 = input[ni][nj];
        if (!isdigit(c2) and c2 != '.' and val) {
          part = true;
        }
      }
    }
  }
  return ans;
}

int task2(vector<string> input) {
  int ans = 0;
  int h = input.size();
  int w = input[0].length();
  vector<vi> ids(h, vi(w, -1));
  vi vals;
  int next = 0;
  int val = 0;
  loop(h) vloop(j, w) {
    char c = input[i][j];
    if (!isdigit(c)) {
      for (int k = j - 1;k >= 0 and isdigit(input[i][k]);k--) {
        ids[i][k] = next;
      }
      next++;
      vals.push_back(val);
      val = 0;
    }
    else {
      val *= 10;
      val += c - '0';
    }
  }
  loop(h) vloop(j, w) {
    if (input[i][j] != '*') continue;
    set<int> adj;
    for (int di = -1;di <= 1;di++) for (int dj = -1;dj <= 1;dj++) {
      if (!di and !dj) continue;
      int ni = i + di;
      int nj = j + dj;
      if (ni < 0 or ni >= h or nj < 0 or nj >= w) continue;
      int x = ids[ni][nj];
      if (x >= 0) adj.insert(x);
    }
    if (adj.size() == 2) {
      int p = 1;
      each(x, adj) p *= vals[x];
      ans += p;
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vector<string> input;
  string s;
  while (cin >> s) input.push_back(s + '.');
  cout << "Task 1: " << task1(input) << endl;
  cout << "Task 2: " << task2(input) << endl;
  return 0;
}

