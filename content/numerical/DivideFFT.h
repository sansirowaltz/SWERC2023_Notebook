/**
 * Author: chemthan
 * Date: 2022-10-11
 * Source: https://github.com/chemthan/chemthan/blob/master/DP%20Optimization/DivideFFT.cpp
 * Description: Solve dp formula: a[i] = a[i - 1] * b[0] + a[i - 2] * b[1] + ... + a[0] * b[i - 1]
 * Time: O(N \log^2 N)
 * Status: untested
 */
#pragma once

// conv(ll a[], ll b[], ll c[], int na, int nb)
// conv multiply a and b, store in c, na and nb are the size of a and b
ll a[N], b[N], c[N];
for (int i = 0; i < n; ++i) {
  for (int k = 1; (i + 1) % k == 0; k <<= 1) {
    conv(a + i - k + 1, b + k - 1, c, k, k);
    for (int j = i + 1; j < i + 2 * k; ++j) {
      (a[j] += c[j - i - 1]) %= MOD;
    }
  }
}
