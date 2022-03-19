/**
 * Author: Maksim1744
 * Date: 2022-03-19
 * Source: https://codeforces.com/blog/entry/91632
 * Description: Count number of primes from $1$ to $n$.
 * Status: Tested
 */
#pragma once

ll count_primes(ll n) {
  vector<ll> v, dp;
  for (ll k = 1; k * k <= n; ++k) {
    v.emb(n / k); v.emb(k);
  }
  sort(all(v)); uniq(v);

  // return i such that v[i] = x, since v[i] = i + 1 for i <= sqrt(n)
  // and v[v.size() - i] = n / i for i <= sqrt(n),
  // we can calculate index in O(1)
  ll sq = (ll)sqrt(n);
  auto geti = [&](ll x) {
    return (x <= sq) ? ((int)x - 1) : (int)(v.size() - (n / x));
  };

  dp.resize(sz(v));
  rep(i,0,sz(v)) dp[i] = v[i]; // S(n, 0) = n
  int a = 0;
  for (ll p = 2; p * p <= n; ++p) {
    // this condition is true for primes
    if (dp[geti(p)] != dp[geti(p - 1)]) {
      ++a;
      for (int i = (int)v.size() - 1; i >= 0; --i) {
        if (v[i] < p * p) break;
        dp[i] -= dp[geti(v[i] / p)] - a;
      }
    }
  }
  return dp[geti(n)] - 1;
}
