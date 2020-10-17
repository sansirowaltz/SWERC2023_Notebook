/**
 * Author: hieplpvip
 * Date: 2020-10-17
 * License: CC0
 * Source: own work
 * Description: Minkowski sum of two polygons.
 * Time: O(M + N)
 * Status: untested
 */
#pragma once

using ll = long long;
using ii = pair<ll, ll>;

inline ii operator +(const ii &a, const ii &b) {
  return {a.X + b.X, a.Y + b.Y};
}

inline ii operator -(const ii &a, const ii &b) {
  return {a.X - b.X, a.Y - b.Y};
}

inline ll cross(const ii &a, const ii &b) {
  return a.X * b.Y - b.X * a.Y;
}

void minkowski(const vector<ii> &A, const vector<ii> &B, vector<ii> &C) {
  int i = 0, j = 0, m = A.size(), n = B.size();
  C.push_back(A[0] + B[0]);
  while (i < m || j < n) {
    ii last = C.back();
    ii v1 = A[(i + 1) % m] - A[i];
    ii v2 = B[(j + 1) % n] - B[j];
    if (j == n || (i < m && cross(v1, v2) >= 0)) {
      C.push_back(last + v1); ++i;
    } else {
      C.push_back(last + v2); ++j;
    }
  }
  C.pop_back();
}
