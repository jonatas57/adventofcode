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

struct point {
  ll x, y;
  point(ll x = 0, ll y = 0) : x(x), y(y) {}
  point operator-(point p) {
    return point(x - p.x, y - p.y);
  }
  point operator+(point p) {
    return point(x + p.x, y + p.y);
  }
  bool operator<(const point& p) const {
    return x == p.x ? y < p.y : x < p.x;
  }
  ll operator^(point p) {
    return x * p.y - y * p.x;
  }
};

const int ZERA = 1;
const int SOMA = 2;
const int SOM0 = 3;
struct segtree {
  int size;
  vector<ll> st;
  vector<pair<int, ll>> lazy;

  segtree(int n) : size(n), st(4 * n + 10), lazy(4 * n + 10) {}

  ll join(ll a, ll b) {
    return min(a, b);
  }

  void prop(int id, int l, int r) {
    if (!lazy[id].first) return;
    switch (lazy[id].first) {
      case ZERA:
      st[id] = 0;
      break;
      case SOMA:
      st[id] = st[id] ? st[id] + lazy[id].second : st[id];
      break;
      case SOM0:
      st[id] = max(st[id], lazy[id].second);
      break;
    }
    if (l < r) {
      auto& left = lazy[id << 1];
      auto& right = lazy[id << 1 | 1];
      int mid = (l + r) >> 1;
      if (left.first and left.first != lazy[id].first) prop(id << 1, l, mid);
      if (right.first and right.first != lazy[id].first) prop(id << 1 | 1, mid + 1, r);
      left.first = lazy[id].first;
      left.second = lazy[id].first == SOM0 ? lazy[id].second : lazy[id].second + left.second;
      right.first = lazy[id].first;
      right.second = lazy[id].first == SOM0 ? lazy[id].second : lazy[id].second + right.second;
    }
    lazy[id].first = lazy[id].second = 0;
  }

  void update(int id, int l, int r, int a, int b, int op, int val) {
    prop(id, l, r);
    if (r < a or b < l) return;
    if (a <= l and r <= b) {
      lazy[id].first = op;
      lazy[id].second += val;
      prop(id, l, r);
    }
    else {
      int mid = (l + r) >> 1;
      update(id << 1, l, mid, a, b, op, val);
      update(id << 1 | 1, mid + 1, r, a, b, op, val);
      st[id] = join(st[id << 1], st[id << 1 | 1]);
    }
  }

  ll query(int id, int l, int r, int a, int b) {
    prop(id, l, r);
    if (r < a or b < l) return INFLL;
    if (a <= l and r <= b) return st[id];
    int mid = (l + r) >> 1;
    return join(query(id << 1, l, mid, a, b), query(id << 1 | 1, mid + 1, r, a, b));
  }

  void updateZeros(int l, int r) {
    update(1, 0, size - 1, l, r, SOM0, 1);
  }

  void updateNonZero(int val) {
    update(1, 0, size - 1, 0, size - 1, SOMA, val);
  }

  void updateZera(int l, int r) {
    update(1, 0, size - 1, l, r, ZERA, 0);
  }

  ll query(int l, int r) {
    ll ans = query(1, 0, size - 1, l, r);
    return ans == INFLL ? 0 : ans;
  }
};

ll task1(vector<point> ps) {
  ll ans = 0;
  sort(iter(ps));
  int n = ps.size();
  loop(n) vloop(j, i) {
    point del = ps[i] - ps[j] + point(1, 1);
    ans = max(ans, abs(del.x * del.y));
  }
  return ans;
}

ostream& operator<<(ostream& os, point& p) {
  os << p.x << "," << p.y;
  return os;
}

ll task1Alt(vector<point> ps) {
  int n = ps.size();
  int pos = min_element(iter(ps)) - ps.begin();
  vector<point> hull;
  hull.push_back(ps[pos]);
  hull.push_back(ps[(pos + 1) % n]);
  for (int i = 2, j = (pos + 2) % n;i < n;i++, j = (j + 1) % n) {
    point u = hull.back() - hull[hull.size() - 2];
    point v = ps[j] - hull.back();
    while (hull.size() >= 2 and (u ^ v) < 0) {
      hull.pop_back();
      u = hull.back() - hull[hull.size() - 2];
      v = ps[j] - hull.back();
    }
    hull.push_back(ps[j]);
  }
  n = hull.size();
  hull.insert(hull.end(), hull.begin(), hull.begin() + n);

  point base = hull[1] - hull[0];
  ll ans = 0;
  auto calc = [] (point p, point q) { 
    point del = p - q + point(1, 1);
    return abs(del.x * del.y);
  };
  for (int i = 0, j = 1;i < n;) {
    point caliper = hull[j + 1] - hull[j];
    ll cr = base ^ caliper;
    if (cr <= 0) {
      ans = max({ans, calc(hull[j], hull[i]), calc(hull[j], hull[i + 1])});
      if (!cr) ans = max({ans, calc(hull[j + 1], hull[i]), calc(hull[j + 1], hull[i + 1])});
      i++;
      base = hull[i + 1] - hull[i];
    }
    else {
      j++;
    }
  }
  return ans;
}

ll task2(vector<point> ps) {
  ll yl = INFLL, yr = -INFLL;
  map<ll, set<ll>> ps2;
  each(p, ps) {
    yl = min(yl, p.y);
    yr = max(yr, p.y);
    ps2[p.x].insert(p.y);
  }
  int n = ps.size();
  int m = yr - yl + 1;
  segtree st(m);
  map<ll, vector<pair<ll, ll>>> sl;
  ps.push_back(ps[0]);
  loop(n) {
    if (ps[i].x != ps[i + 1].x) continue;
    ll l = ps[i].y, r = ps[i + 1].y;
    if (l > r) swap(l, r);
    sl[ps[i].x].emplace_back(l - yl, r - yl);
  }
  int lastx = 0;
  set<ll> validY;
  ll ans = 0;
  for (auto& [x, rs] : sl) {
    st.updateNonZero(x - lastx);
    vector<pair<ll, ll>> zeros;
    vector<ll> ys;
    for (auto& [l, r] : rs) {
      ll mn = st.query(l, r);
      if (mn) zeros.emplace_back(l, r);
      else st.updateZeros(l, r);
      ys.push_back(l);
      ys.push_back(r);
    }
    each(y, ys) {
      each(y2, validY) {
        ll h = st.query(min(y, y2), max(y, y2));
        auto [it1, it2] = ps2[x - h + 1].equal_range(y2 + yl);
        if (it1 == it2) continue;
        ans = max(ans, h * (abs(y - y2) + 1));
      }
      validY.insert(y);
    }
    for (auto& [l, r] : zeros) {
      int l2 = l + 1, r2 = r - 1;
      if (!st.query(l - 1, l - 1)) l2--;
      if (!st.query(r + 1, r + 1)) r2++;
      st.updateZera(l2, r2);
    }
    lastx = x;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
  
  string s;
  vector<point> ps;
  while (cin >> s) {
    int p = s.find(',');
    ps.emplace_back(stoi(s.substr(0, p)), stoi(s.substr(p + 1)));
  }
  cout << "Task 1: " << task1(ps) << endl;
  cout << "Task 1: " << task1Alt(ps) << endl;
  cout << "Task 2: " << task2(ps) << endl;
  return 0;
}

