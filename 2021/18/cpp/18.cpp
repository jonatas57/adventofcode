#include <bits/stdc++.h>

using namespace std;

typedef long long          ll;
typedef unsigned long long ull;
typedef vector<int>        vi;
typedef vector<bool>       vb;
typedef map<int, int>      mii;
typedef pair<int, int>     ii;

#define INF                0x3f3f3f3f
#define INFLL              0x3f3f3f3f3f3f3f3fll
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

struct number {
  bool isVal;
  int val;
  int dep;
  int mx;
  shared_ptr<number> left, right;

  number(int x = 0) : isVal(true), val(x), dep(0), mx(x), left(nullptr), right(nullptr) {}
};

bool readNumber(shared_ptr<number> x) {
  while (cin and isspace(cin.peek())) cin.get();
  if (!cin) return false;
  if (cin.peek() == '[') {
    x->isVal = false;
    cin.get();
    x->left = make_shared<number>();
    x->right = make_shared<number>();
    readNumber(x->left);
    assert(cin.get() == ',');
    readNumber(x->right);
    x->dep = max(x->left->dep, x->right->dep) + 1;
    x->mx = max(x->left->mx, x->right->mx);
    assert(cin.get() == ']');
  }
  else {
    x->isVal = true;
    cin >> x->val;
  }
  return true;
}

void update(shared_ptr<number> a, int x, bool goright) {
  if (a->isVal) {
    a->val += x;
    a->mx = a->val;
  }
  else {
    if (goright) update(a->right, x, goright);
    else update(a->left, x, goright);
    a->dep = max(a->left->dep, a->right->dep) + 1;
    a->mx = max(a->left->mx, a->right->mx);
  }
}

ii explode(shared_ptr<number> a) {
  ii ret;
  if (a->dep == 1) {
    ret = {a->left->val, a->right->val};
    a->isVal = true;
    a->val = 0;
    a->dep = 0;
    a->mx = 0;
    a->left = nullptr;
    a->right = nullptr;
  }
  else {
    if (a->left->dep == a->dep - 1) {
      auto [l, r] = explode(a->left);
      ret.first = l;
      update(a->right, r, false);
    }
    if (a->right->dep == a->dep - 1) {
      auto [l, r] = explode(a->right);
      ret.second = r;
      update(a->left, l, true);
    }
    a->dep = max(a->left->dep, a->right->dep) + 1;
    a->mx = max(a->left->mx, a->right->mx);
  }
  return ret;
}

void split(shared_ptr<number> a) {
  if (a->isVal) {
    a->isVal = false;
    a->left = make_shared<number>(a->val / 2);
    a->right = make_shared<number>(a->val - a->val / 2);
    a->dep = 1;
    a->mx = a->val - a->val / 2;
  }
  else {
    if (a->left->mx > 9) split(a->left);
    else split(a->right);
    a->dep = max(a->left->dep, a->right->dep) + 1;
    a->mx = max(a->left->mx, a->right->mx);
  }
}

shared_ptr<number> operator+(shared_ptr<number> a, shared_ptr<number> b) {
  shared_ptr<number> c = make_shared<number>();
  c->left = a;
  c->right = b;
  c->isVal = false;
  c->dep = max(a->dep, b->dep) + 1;
  while (c->dep > 4 or c->mx > 9) {
    if (c->dep > 4) explode(c);
    else split(c);
  }
  return c;
}

int getSum(shared_ptr<number> a) {
  return a->isVal ? a->val : 3 * getSum(a->left) + 2 * getSum(a->right);
}

int task1(vector<shared_ptr<number>> a) {
  int n = a.size();
  shared_ptr<number> x = a[0];
  for (int i = 1;i < n;i++) {
    x = x + a[i];
  }
  return getSum(x);
}

shared_ptr<number> deepcopy(shared_ptr<number> a) {
  if (!a) return nullptr;
  shared_ptr b = make_shared<number>();
  b->isVal = a->isVal;
  b->val = a->val;
  b->dep = a->dep;
  b->mx = a->mx;
  b->left = deepcopy(a->left);
  b->right = deepcopy(a->right);
  return b;
}

int task2(vector<shared_ptr<number>> a) {
  int n = a.size();
  int ans = 0;
  loop(n) vloop(j, n) {
    if (i == j) continue;
    ans = max(ans, getSum(deepcopy(a[i]) + deepcopy(a[j])));
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vector<shared_ptr<number>> a, b;
  shared_ptr<number> x = make_shared<number>();
  while (readNumber(x)) {
    if (x->isVal) break;
    a.push_back(x);
    b.push_back(deepcopy(x));
    x = make_shared<number>(); 
  }
  a.pop_back();
  cout << "Task 1: " << task1(a) << endl;
  cout << "Task 2: " << task2(b) << endl;
  return 0;
}

