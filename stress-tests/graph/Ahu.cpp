#include "../utilities/template.h"

#include "../../content/graph/Ahu.h"

vector<pii> generateTree(int n) {
  vi p(n); rep(i, 1, n) p[i] = rand() % i;
  vi perm(n); iota(all(perm), 0); random_shuffle(all(perm));
  vector<pii> edges;
  rep(i, 1, n) {
    if (rand() % 2) {
      edges.emb(perm[i], perm[p[i]]);
    } else {
      edges.emb(perm[p[i]], perm[i]);
    }
  }
  random_shuffle(all(edges));
  return edges;
}

int main() {
  srand(8);
  rep(N,2,3000) {
    vi perm(N); iota(all(perm), 0); random_shuffle(all(perm));
    auto edges = generateTree(N);
    vector<vi> g[2];
    g[0].resize(N); g[1].resize(N);
    for (auto e: edges) {
      g[0][e.first].emb(e.second);
      g[0][e.second].emb(e.first);
      g[1][perm[e.first]].emb(perm[e.second]);
      g[1][perm[e.second]].emb(perm[e.first]);
    }
    assert(checkIsomorphic(g));
  }
  rep(N,100,3000) {
    vector<vi> g[2];
    g[0].resize(N); g[1].resize(N);
    auto edges = generateTree(N);
    for (auto e: edges) {
      g[0][e.first].emb(e.second);
      g[0][e.second].emb(e.first);
    }
    edges = generateTree(N);
    for (auto e: edges) {
      g[1][e.first].emb(e.second);
      g[1][e.second].emb(e.first);
    }
    assert(!checkIsomorphic(g));
  }
  cout << "Tests passed!" << endl;
}
