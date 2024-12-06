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

struct node {
  map<char, int> next;

  int& operator[](char c) { return next[c]; }
};

// 0 -m> 1 -u> 2 -l> 3 -(> 4 -,> 5 -)> 6
int task1(vector<string>& input) {
  vector<node> g(7);
  each(u, g) u['m'] = 1;
  g[1]['u'] = 2;
  g[2]['l'] = 3;
  g[3]['('] = 4;
  g[4][','] = 5;
  g[5][')'] = 6;
  loop(10) {
    g[4]['0' + i] = 4;
    g[5]['0' + i] = 5;
  }

  int a = 0, b = 0, ans = 0;
  each(s, input) {
    int at = 0;
    each(c, s) {
      int at2 = g[at][c];
      if (at == 4 and at2 == 4) a *= 10, a += c - '0';
      else if (at == 5 and at2 == 5) b *= 10, b += c - '0';
      at = at2;
      if (at == 6) {
        ans += a * b;
      } else if (at == 1) {
        a = b = 0;
      }
    }
  }
  return ans;
}

int task2(vector<string>& input) {
  vector<node> g(16);
  each(u, g) {
    u['m'] = 1;
    u['d'] = 7;
  }
  g[1]['u'] = 2;
  g[2]['l'] = 3;
  g[3]['('] = 4;
  g[4][','] = 5;
  g[5][')'] = 6;
  loop(10) {
    g[4]['0' + i] = 4;
    g[5]['0' + i] = 5;
  }
  g[7]['o'] = 8;
  g[8]['('] = 9;
  g[9][')'] = 10;
  g[8]['n'] = 11;
  g[11]['\''] = 12;
  g[12]['t'] = 13;
  g[13]['('] = 14;
  g[14][')'] = 15;

  int a = 0, b = 0, ans = 0;
  bool ok = true;
  each(s, input) {
    int at = 0;
    each(c, s) {
      int at2 = g[at][c];
      if (at == 4 and at2 == 4) a *= 10, a += c - '0';
      else if (at == 5 and at2 == 5) b *= 10, b += c - '0';
      at = at2;
      if (at == 6) {
        if (ok) ans += a * b;
      }
      else if (at == 1) a = b = 0;
      else if (at == 10) ok = true;
      else if (at == 15) ok = false;
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
  
  vector<string> input;
  string s;
  while (getline(cin, s)) {
    input.push_back(s);
  }
  cout << "Task 1: " << task1(input) << endl;
  cout << "Task 2: " << task2(input) << endl;
  return 0;
}

