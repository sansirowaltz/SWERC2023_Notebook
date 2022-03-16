/**
 * Author: RR
 * Date: 2022-03-15
 * Source: https://github.com/icpcvn/icpcvn.github.io/blob/master/2016/regional/solutions/F/RR.cpp
 * Description: Min-cost max-flow, assumes no negative cycles.
 * Status: Tested on kattis:mincostmaxflow, stress-tested against another implementation
 * Time: Ignoring SPFA, $O(FM\log M)$ if caps are integers and $F$ is max flow.
 */
#pragma once

struct MCMF {
  using F = ll; using C = ll;
  const F INF_FLOW = numeric_limits<F>::max();
  const C INF_COST = numeric_limits<C>::max();
  struct Edge {
    int to; F cap; C cost; int next;
    Edge(int to, F cap, C cost, int next) : to(to), cap(cap), cost(cost), next(next) {}
  };
  int n, t, S, T; F totalFlow; C totalCost;
  vi last, vis; vector<C> dis; vector<Edge> edges;
  MCMF(int n) : n(n), t(0), totalFlow(0), totalCost(0), last(n, -1), vis(n, 0), dis(n, 0) {}
  int addEdge(int from, int to, F cap, C cost) {
    edges.push_back(Edge(to, cap, cost, last[from]));
    last[from] = t++;
    edges.push_back(Edge(from, 0, -cost, last[to]));
    last[to] = t++;
    return t - 2;
  }
  pair<F, C> maxflow(int _S, int _T) {
    S = _S; T = _T; SPFA();
    while (1) { while (1) {
        rep(i,0,n) vis[i] = 0;
        if (!findFlow(S, INF_FLOW)) break;
      }
      if (!modifyLabel()) break;
    }
    return {totalFlow, totalCost};
  }
private:
  void SPFA() {
    rep(i,0,n) dis[i] = INF_COST;
    min_heap<pair<C, int>> Q;
    Q.emplace(dis[S] = 0, S);
    while (!Q.empty()) {
      C d = Q.top().first;
      int x = Q.top().second;
      Q.pop();
      // For double: dis[x] > d + EPS
      if (dis[x] != d) continue;
      for (int it = last[x]; it >= 0; it = edges[it].next)
        if (edges[it].cap > 0 && dis[edges[it].to] > d + edges[it].cost)
          Q.emplace(dis[edges[it].to] = d + edges[it].cost, edges[it].to);
    }
    C disT = dis[T];
    rep(i, 0, n) dis[i] = disT - dis[i];
  }
  F findFlow(int x, F flow) {
    if (x == T) {
      totalCost += dis[S] * flow; totalFlow += flow;
      return flow;
    }
    vis[x] = 1; F now = flow;
    for (int it = last[x]; it >= 0; it = edges[it].next)
      // For double: abs(dis[edges[it].to]+edges[it].cost-dis[x])<EPS
      if (edges[it].cap && !vis[edges[it].to] &&
          dis[edges[it].to] + edges[it].cost == dis[x]) {
        F tmp = findFlow(edges[it].to,min(now,edges[it].cap));
        edges[it].cap-=tmp;edges[it^1].cap+=tmp;now-=tmp;
        if (!now) break;
      }
    return flow - now;
  }
  bool modifyLabel() {
    C d = INF_COST;
    rep(i,0,n) if (vis[i])
      for (int it = last[i]; it >= 0; it = edges[it].next)
        if (edges[it].cap && !vis[edges[it].to])
          d = min(d,dis[edges[it].to]+edges[it].cost-dis[i]);
    // For double: if (d > INF_COST / 10)     INF_COST = 1e20
    if (d == INF_COST) return false;
    rep(i,0,n) if (vis[i]) dis[i] += d;
    return true;
  }
};
