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

struct bits {
  static const vector<ll> neutrals;
  static const vector<function<ll(ll, ll)>> fs;
  struct packet {
    int version;
    int id;
    ll value;
    vector<packet> subp;

    ll eval() {
      if (id < 4) {
        ll n = neutrals[id];
        each(sp, subp) n = fs[id](n, sp.eval());
        return n;
      }
      if (id == 4) return value;
      return fs[id - 1](subp[0].eval(), subp[1].eval());
    }
  } p;

  bits(string& s) {
    s = hex2bin(s);
    int pos = 0;
    s.resize(s.find_last_of('1') + 1);/*@*/
    cerr << s << endl;/*@*/
    p = readPacket(s, pos);
  }

  packet readPacket(string& s, int& pos) {
    packet p;
    p.version = readSubstr(s, pos, 3);/*@*/
    cerr << "version = " << p.version << endl;/*@*/
    p.id = readSubstr(s, pos, 3);/*@*/
    cerr << "id = " << p.id << endl;/*@*/
    if (p.id == 4) {
      bool run = true;
      p.value = 0;/*@*/
      cerr << "read val" << endl;/*@*/
      while (run) {
        int x = readSubstr(s, pos, 5);
        if (x & 16) x -= 16;
        else run = false;/*@*/
        cerr << x << endl;/*@*/
        p.value <<= 4;
        p.value += x;
      }
    }
    else {
      int l = readSubstr(s, pos, 1);/*@*/
      cerr << "mode = " << l << endl;/*@*/
      if (l) {
        int q = readSubstr(s, pos, 11);/*@*/
        cerr << "has " << q << " subpackets" << endl;/*@*/
        loop(q) p.subp.push_back(readPacket(s, pos));
      }
      else {
        int x = readSubstr(s, pos, 15);/*@*/
        cerr << "subpackets in " << x << " bits" << endl;/*@*/
        x += pos;
        while (pos < x) p.subp.push_back(readPacket(s, pos));
      }
    }/*@*/
    cerr << "end packet" << endl;/*@*/
    return p;
  }

  int readSubstr(string& s, int& pos, int l) {
    int x = 0;
    loop(l) {
      x <<= 1;
      x |= (s[pos++] == '1');
    }
    return x;
  }

  string hex2bin(string& h) {
    string b = "";
    each(c, h) {
      int x = isdigit(c) ? c - '0' : c - 'A' + 10;
      b += bitset<4>(x).to_string();
    }
    return b;
  }
};

const vector<ll> bits::neutrals = {0, 1, INFLL, -INFLL};
const vector<function<ll(ll, ll)>> bits::fs = {
  [] (ll a, ll b) { return a + b; },
  [] (ll a, ll b) { return a * b; },
  [] (ll a, ll b) { return min(a, b); },
  [] (ll a, ll b) { return max(a, b); },
  [] (ll a, ll b) { return a > b; },
  [] (ll a, ll b) { return a < b; },
  [] (ll a, ll b) { return a == b; }
};
/*@*/

void print(bits::packet& p, string tab = "") {
  cerr << tab << "{" << endl;
  cerr << tab << "  version = " << p.version << "," << endl;
  cerr << tab << "  id = " << p.id << "," << endl;
  if (p.subp.empty()) cerr << tab << "  value = " << p.value << endl;
  else {
    cerr << tab << "  subpackets = [" << endl;
    each(sp, p.subp) print(sp, tab + "    "), cerr << "," << endl;
    cerr << tab << "  ]," << endl;
  }
  cerr << tab << "  eval = " << p.eval() << endl;
  cerr << tab << "}";
}/*@*/

int task1(bits& b) {
  function<int(bits::packet& p)> sum = [&] (bits::packet& p) {
    int x = p.version;
    each(sp, p.subp) x += sum(sp);
    return x;
  };
  return sum(b.p);
}/*@*/

void printEval(bits::packet& p) {
  switch (p.id) {
    case 0:
    cerr << "(";
    printEval(p.subp[0]);
    for (int i = 1;i < p.subp.size();i++) {
      cerr << " + ";
      printEval(p.subp[i]);
    }
    cerr << ")";
    break;
    case 1:
    cerr << "(";
    printEval(p.subp[0]);
    for (int i = 1;i < p.subp.size();i++) {
      cerr << " * ";
      printEval(p.subp[i]);
    }
    cerr << ")";
    break;
    case 2:
    cerr << "min(";
    printEval(p.subp[0]);
    for (int i = 1;i < p.subp.size();i++) {
      cerr << ", ";
      printEval(p.subp[i]);
    }
    cerr << ")";
    break;
    case 3:
    cerr << "max(";
    printEval(p.subp[0]);
    for (int i = 1;i < p.subp.size();i++) {
      cerr << ", ";
      printEval(p.subp[i]);
    }
    cerr << ")";
    break;
    case 4:
    cerr << p.value;
    break;
    case 5:
    cerr << "(";
    printEval(p.subp[0]);
    cerr << " > ";
    printEval(p.subp[1]);
    cerr << ")";
    break;
    case 6:
    cerr << "(";
    printEval(p.subp[0]);
    cerr << " < ";
    printEval(p.subp[1]);
    cerr << ")";
    break;
    case 7:
    cerr << "(";
    printEval(p.subp[0]);
    cerr << " == ";
    printEval(p.subp[1]);
    cerr << ")";
    break;
    default:
    break;
  }
}/*@*/

ll task2(bits& b) {/*@*/
cerr << endl << "eval = ";
  printEval(b.p);
  cerr << endl;
  return b.p.eval();
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  string s;
  cin >> s;
  bits b(s);/*@*/
  print(b.p);
  cerr << endl;/*@*/
  cout << "Task 1: " << task1(b) << endl;
  cout << "Task 2: " << task2(b) << endl;
  return 0;
}

