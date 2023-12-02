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

const char first = 'a';
const char last = 'z';
const int K = last - first + 1;

struct aho {
  struct vertex {
    int par;
    int link;
    int value;
    bool leaf;
    char pch;
    vi next;
    vertex(int p = -1, char c = '\0') : par(p), link(-1), value(0), leaf(false), pch(c), next(K, -1) {}

    int& operator[](char c) {
      return next[c - first];
    }
  };

  int size;
  vector<vertex> t;
  aho() : size(1), t(1) {}

  int addString(string s, int val) {
    int v = 0;
    each(c, s) {
      if (t[v][c] == -1) {
        t.emplace_back(v, c);
        t[v][c] = size++;
      }
      v = t[v][c];
    }
    t[v].value = val;
    t[v].leaf = true;
    return v;
  }

  int go(int v, char c) {
    if (t[v][c] == -1) t[v][c] = v == 0 ? 0 : go(getLink(v), c);
    return t[v][c];
  }

  int getLink(int v) {
    if (t[v].link == -1) t[v].link = v == 0 or t[v].par == 0 ? 0 : go(getLink(t[v].par), t[v].pch);
    return t[v].link;
  }

  vertex& operator[](int i) {
    return t[i];
  }
};

int task1(vector<string> ss) {
  int ans = 0;
  each(s, ss) {
    vi d;
    each(c, s) {
      if (isdigit(c)) {
        d.push_back(c - '0');
      }
    }
    if (d.empty()) continue;
    ans += d[0] * 10 + d.back();
  }
  return ans;
}

int task2(vector<string> ss) {
  vector<string> ds = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
  aho a;
  loop(9) a.addString(ds[i], i + 1);
  int ans = 0;
  each(s, ss) {
    vi d;
    int at = 0;
    each(c, s) {
      if (isdigit(c)) {
        at = 0;
        d.push_back(c - '0');
      }
      else {
        at = a.go(at, c);
        if (a[at].leaf) {
          d.push_back(a[at].value);
        }
      }
    }
    if (d.empty()) continue;
    ans += d[0] * 10 + d.back();
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vector<string> ss;
  string s;
  while (cin >> s) {
    ss.push_back(s);
  }
  cout << "Task 1: " << task1(ss) << endl;
  cout << "Task 2: " << task2(ss) << endl;
  return 0;
}

