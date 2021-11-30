/**
 * Author: hieplpvip
 * Date: 2020-10-17
 * License: CC0
 * Source: own work
 * Description: Container where you can add segment of the form kx+m, and query maximum/minimum values at points x.
 *  Useful for dynamic programming (``convex hull trick'').
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once

template<typename T, T minX, T maxX, T defVal, bool maximum>
struct DynamicLiChaoTree {
private:
  struct Line {
    T a, b;
    inline T calc(T x) const { return a * x + b; }
  };
  struct Node {
    Line line = {0, maximum ? defVal : -defVal};
    Node *lt = nullptr, *rt = nullptr;
  } *root;
  void update(Node* cur, T l, T r, T u, T v, Line nw) {
    #define newNode(x) if (!x) x = new Node()
    if (v < l || r < u) return;
    T mid = (l + r) >> 1;
    if (u <= l && r <= v) {
      if (cur->line.calc(l) >= nw.calc(l)) swap(cur->line, nw);
      if (cur->line.calc(r) <= nw.calc(r)) {
        cur->line = nw; return;
      }
      if (nw.calc(mid) >= cur->line.calc(mid)) {
        newNode(cur->rt);
        update(cur->rt, mid + 1, r, u, v, cur->line);
        cur->line = nw;
      } else {
        newNode(cur->lt);
        update(cur->lt, l, mid, u, v, nw);
      }
    } else {
      newNode(cur->lt); newNode(cur->rt);
      update(cur->lt, l, mid, u, v, nw);
      update(cur->rt, mid + 1, r, u, v, nw);
    }
    #undef newNode
  }
public:
  DynamicLiChaoTree() { root = new Node(); }
  void add(T a, T b, T l = minX, T r = maxX) {
    if (!maximum) a = -a, b = -b;
    update(root, minX, maxX, l, r, {a, b});
  }
  T query(T x) {
    Node* cur = root;
    T res = cur->line.calc(x), l = minX, r = maxX, mid;
    while (cur) {
      res = max(res, cur->line.calc(x));
      mid = (l + r) >> 1;
      if (x <= mid) cur = cur->lt, r = mid;
      else cur = cur->rt, l = mid + 1;
    }
    return maximum ? res : -res;
  }
};
