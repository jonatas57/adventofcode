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

struct graph {
  vector<list<int>> adj;
  vb big;
  map<string, int> conv;
  int size;
  graph() : size(0) {}
  void addEdge(string s, string t) {
    int a = addNode(s);
    int b = addNode(t);
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  int addNode(string s) {
    if (!conv.count(s)) {
      conv[s] = size++;
      big.push_back(isupper(s[0]));
      adj.emplace_back();
    }
    return conv[s];
  }
};

int task1(graph& g) {
  int st = g.conv["start"];
  int en = g.conv["end"];
  g.big[en] = true;
  vb visit(g.size, false);
  int cnt = 0;
  function<void(int)> dfs = [&] (int u) {
    if (u == en) {
      cnt++;
      return;
    }
    if (!g.big[u]) visit[u] = true;
    each(v, g.adj[u]) {
      if (visit[v]) continue;
      dfs(v);
    }
    visit[u] = false;
  };
  dfs(st);
  return cnt;
}

int task2(graph& g) {
  int st = g.conv["start"];
  int en = g.conv["end"];
  g.big[en] = true;
  vb visit(g.size, false);
  int cnt = 0, twice = -1;
  function<void(int)> dfs = [&] (int u) {
    if (u == en) {
      cnt++;
      return;
    }
    if (visit[u]) {
      if (twice == -1 and u != st) twice = u;
      else return;
    }
    else if (!g.big[u]) visit[u] = true;
    each(v, g.adj[u]) {
      dfs(v);
    }
    if (twice == u) twice = -1;
    else visit[u] = false;
  };
  dfs(st);
  return cnt;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  graph g;
  string s;
  while (cin >> s) {
    int x = s.find('-');
    g.addEdge(s.substr(0, x), s.substr(x + 1));
  }
  cout << "Task 1: " << task1(g) << endl;
  cout << "Task 2: " << task2(g) << endl;
  return 0;
}

