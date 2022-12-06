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

typedef tuple<int, int, int> op;

void move(int x, stack<char>& a, stack<char>& b) {
  loop(x) {
    char c = a.top();
    a.pop();
    b.push(c);
  }
}

string task1(vector<stack<char>> sts, vector<op>& ops) {
  for (auto& [qtd, from, to] : ops) {
    move(qtd, sts[from], sts[to]);
  }
  string ans;
  each(s, sts) ans += s.top();
  return ans;
}

string task2(vector<stack<char>> sts, vector<op>& ops) {
  stack<char> aux;
  for (auto& [qtd, from, to] : ops) {
    move(qtd, sts[from], aux);
    move(qtd, aux, sts[to]);
  }
  string ans;
  each(s, sts) ans += s.top();
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vector<string> input;
  string s;
  int eol = -1;
  for (int i = 0;getline(cin, s);i++) {
    input.push_back(s);
    if (s.empty()) eol = i;
  }
  vector<stack<char>> sts;
  vector<op> ops;
  for (int j = 0;input[eol - 1][j];j++) {
    if (isdigit(input[eol - 1][j])) {
      sts.emplace_back();
      for (int i = eol - 2;i >= 0 and input[i][j] != ' ';i--) {
        sts[input[eol - 1][j] - '1'].push(input[i][j]);
      }
    }
  }
  for (int i = eol + 1;i < input.size();i++) {
    int a, b, c;
    stringstream ss;
    ss << input[i];
    ss >> s >> a >> s >> b >> s >> c;
    ops.emplace_back(a, b - 1, c - 1);
  }
  cout << "Task 1: " << task1(sts, ops) << endl;
  cout << "Task 2: " << task2(sts, ops) << endl;
  return 0;
}

