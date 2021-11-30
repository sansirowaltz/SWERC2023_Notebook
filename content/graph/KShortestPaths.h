/**
 * Author: Yaowei Lyu
 * Date: 2021-10-28
 * Source: https://judge.yosupo.jp/submission/60375
 * Description: Finds the k shortest paths (not required to be simple) from S to T in a digraph.
 * Time: O(M + N \log N + K)
 * Status: Tested on yosupo:k_shortest_walk
 */
#pragma once

struct Edge { int u, v, w; };
struct Node {
  int v, h; ll w;
  Node *ls, *rs;
  Node(int v, ll w) : v(v), h(1), w(w), ls(0), rs(0) {}
};
Node* merge(Node* u, Node* v) {
  if (!u) return v;
  if (!v) return u;
  if (u->w > v->w) swap(u, v);
  Node* p = new Node(*u);
  p->rs = merge(u->rs, v);
  if (p->rs && (!p->ls || p->ls->h < p->rs->h)) swap(p->ls, p->rs);
  p->h = (p->rs ? p->rs->h : 0) + 1;
  return p;
}
vector<ll> k_shortest_paths(int N, const vector<Edge>& edges, int S, int T, int K) {
  vector<vi> G(N);
  rep(i,0,sz(edges)) G[edges[i].v].emb(i);
  min_heap<pair<ll, int>> pq;
  vector<ll> d(N, -1); vi done(N), par(N, -1), p;
  pq.emplace(d[T] = 0, T);
  while (!pq.empty()) {
    int u = pq.top().second; pq.pop();
    if (done[u]) continue;
    p.emb(u); done[u] = 1;
    for (int i : G[u]) {
      auto [v, _, w] = edges[i];
      if (d[v] == -1 || d[v] > d[u] + w) {
        par[v] = i;
        pq.emplace(d[v] = d[u] + w, v);
      }
    }
  }
  if (d[S] == -1) return vector<ll>(K, -1);
  vector<Node*> heap(N);
  rep(i,0,sz(edges)) {
    auto [u, v, w] = edges[i];
    if (~d[u] && ~d[v] && par[u] != i)
      heap[u] = merge(heap[u], new Node(v, d[v] + w - d[u]));
  }
  for (int u : p) if (u != T)
    heap[u] = merge(heap[u], heap[edges[par[u]].v]);
  min_heap<pair<ll, Node*>> q;
  if (heap[S]) q.emplace(d[S] + heap[S]->w, heap[S]);
  vector<ll> res = {d[S]};
  for (int i = 1; i < K && !q.empty(); ++i) {
    auto [w, node] = q.top(); q.pop(); res.emb(w);
    if (heap[node->v])
      q.emplace(w + heap[node->v]->w, heap[node->v]);
    for (auto s : {node->ls, node->rs})
      if (s) q.emplace(w + s->w - node->w, s);
  }
  res.resize(K, -1);
  return res;
}
