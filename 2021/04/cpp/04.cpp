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

vi parse(string& s) {
  vi a;
  int x = 0;
  for (int i = 0;;i++) {
    if (isdigit(s[i])) {
      x *= 10;
      x += s[i] - '0';
    }
    else {
      a.push_back(x);
      x = 0;
      if (!s[i]) break;
    }
  }
  return a;
}

struct bingo {
  vector<vi> a;
  map<int, ii> pos;
  vi row, col;
  int sum = 0;
  bingo() : a(5, vi(5)), row(5), col(5) {}
  bool tryMark(int x) {
    if (!pos.count(x)) return false;
    auto [r, c] = pos[x];
    sum -= x;
    return ++row[r] == 5 or ++col[c] == 5;
  }
  friend istream& operator>>(istream& is, bingo& b) {
    b = bingo();
    loop(5) {
      vloop(j, 5) {
        is >> b.a[i][j];
        b.sum += b.a[i][j];
        b.pos[b.a[i][j]] = {i, j};
      }
    }
    return is;
  }
  friend ostream& operator<<(ostream& os, bingo& b) {
    each(v, b.a) {
      each(x, v) os << x << " ";
      os << endl;
    }
    return os;
  }
};

int task1(vi& input, vector<bingo> bs) {
  each(x, input) {
    each(b, bs) {
      if (b.tryMark(x)) {
        return b.sum * x;
      }
    }
  }
  return -1;
}

int task2(vi& input, vector<bingo> bs) {
  int n = bs.size();
  int ok = n;
  vb win(n, false);
  each(x, input) {
    loop(n) {
      if (win[i]) continue;
      if (bs[i].tryMark(x)) {
        ok--;
        win[i] = true;
      }
      if (!ok) {
        return bs[i].sum * x;
      }
    }
  }
  return -1;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  string input;
  cin >> input;
  vi in = parse(input);
  bingo b;
  vector<bingo> bs;
  while (cin >> b) {
    bs.push_back(b);
  }
  cout << "Task 1: " << task1(in, bs) << endl;
  cout << "Task 2: " << task2(in, bs) << endl;
  return 0;
}

