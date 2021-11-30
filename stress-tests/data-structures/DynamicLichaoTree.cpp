#include "../utilities/template.h"

#include "../../content/data-structures/DynamicLichaoTree.h"
#include "../../content/data-structures/LineContainer.h"

const int MIN_X = 1e9, MAX_X = 1e9;
const ll oo = 1e18;

mt19937 rng(1337);

template<typename T>
T rand(T low, T high) {
  return uniform_int_distribution<T>(low, high)(rng);
}

void test_max() {
  DynamicLiChaoTree<ll, MIN_X, MAX_X, -oo, true> lichao;
  vector<tuple<ll, ll, int, int>> segments;
  for (int i = 0; i < 50000; ++i) {
    ll a = rand(MIN_X, MAX_X);
    ll b = rand(MIN_X, MAX_X);
    int l = 0, r = -1;
    while (l > r) {
      l = rand(MIN_X, MAX_X);
      r = rand(MIN_X, MAX_X);
    }
    lichao.add(a, b, l, r);
    segments.emplace_back(a, b, l, r);
  }
  for (int q = 0; q < 50000; ++q) {
    int x = rand(MIN_X, MAX_X);
    ll max_val = -oo;
    for (auto [a, b, l, r] : segments) {
      if (l <= x && x <= r) {
        max_val = max(max_val, a * x + b);
      }
    }
    assert(max_val == lichao.query(x));
  }
}

void test_min() {
  DynamicLiChaoTree<ll, MIN_X, MAX_X, oo, false> lichao;
  vector<tuple<ll, ll, int, int>> segments;
  for (int i = 0; i < 50000; ++i) {
    ll a = rand(MIN_X, MAX_X);
    ll b = rand(MIN_X, MAX_X);
    int l = 0, r = -1;
    while (l > r) {
      l = rand(MIN_X, MAX_X);
      r = rand(MIN_X, MAX_X);
    }
    lichao.add(a, b, l, r);
    segments.emplace_back(a, b, l, r);
  }
  for (int q = 0; q < 50000; ++q) {
    int x = rand(MIN_X, MAX_X);
    ll min_val = oo;
    for (auto [a, b, l, r] : segments) {
      if (l <= x && x <= r) {
        min_val = min(min_val, a * x + b);
      }
    }
    assert(min_val == lichao.query(x));
  }
}

void test_line() {
  DynamicLiChaoTree<ll, MIN_X, MAX_X, -oo, true> lichao;
  LineContainer mh;
  for (int i = 0; i < 100000; ++i) {
    ll a = rand(MIN_X, MAX_X);
    ll b = rand(MIN_X, MAX_X);
    lichao.add(a, b, MIN_X, MAX_X);
    mh.add(a, b);
  }
  for (int q = 0; q < 100000; ++q) {
    int x = rand(MIN_X, MAX_X);
    assert(lichao.query(x) == mh.query(x));
  }
}

int main() {
  test_max();
  test_min();
  test_line();
  cout << "Tests passed!" << endl;
}
