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

struct graph {
  int size;
  map<int, vi> adj;
  map<string, int> ns;
  graph() : size(0) {}
  void addEdge(int a, int b) {
    adj[a].push_back(b);
  }
};

int task1(graph& g, vector<vi>& input) {
  int ans = 0;
  each(a, input) {
    map<int, int> deg;
    each(u, a) {
      each(v, g.adj[u]) {
        deg[v]++;
      }
    }
    bool ok = true;
    each(u, a) {
      if (deg[u]) {
        ok = false;
        break;
      }
      each(v, g.adj[u]) {
        deg[v]--;
      }
    }
    if (ok) ans += a[a.size() / 2];
  }
  return ans;
}

int task2(graph& g, vector<vi>& input) {
  int ans = 0;
  each(a, input) {
    map<int, int> deg;
    map<int, bool> used, canUse;
    each(u, a) {
      canUse[u] = true;
      each(v, g.adj[u]) {
        deg[v]++;
      }
    }
    bool ok = false;
    queue<int> q;
    each(u, a) if (!deg[u]) q.push(u);
    vi ord;
    each(u2, a) {
      int u = u2;
      if (ok or deg[u2]) {
        ok = true;
        while (used[q.front()] or !canUse[q.front()]) q.pop();
        u = q.front();
        q.pop();
      }
      used[u] = true;
      ord.push_back(u);
      each(v, g.adj[u]) {
        deg[v]--;
        if (!deg[v]) q.push(v);
      }
    }
    if (ok) ans += ord[ord.size() / 2];
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
  
  string s;
  graph g;
  while (getline(cin, s) and s.length()) {
    stringstream ss;
    ss << s;
    int a, b;
    ss >> a;
    ss.get();
    ss >> b;
    g.addEdge(a, b);
  }
  vector<vi> input;
  while (getline(cin, s)) {
    vi a;
    int pos = 0;
    while (true) {
      int p = s.find(',', pos);
      if (p == string::npos) break;
      a.push_back(stoi(s.substr(pos, p - pos)));
      pos = p + 1;
    }
    a.push_back(stoi(s.substr(pos)));
    input.push_back(a);
  }
  cout << "Task 1: " << task1(g, input) << endl;
  cout << "Task 2: " << task2(g, input) << endl;
  return 0;
}

