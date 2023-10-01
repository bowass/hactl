#include "../utilities/template.h"
#include <bits/extc++.h>
#include "../../content/graph/MinCostMaxFlow.h"
#include "MinCostMaxFlowOld.h"

#include <cassert>

void testPerf() {
  srand(2);
  int N = 500, E = 10000, CAPS = 100, COSTS = 100000;
  MinCostMaxFlow mcmf(N);
  int s = 0, t = 1;
  rep(i, 0, E) {
    int a = rand() % N;
    int b = rand() % N;
    int cap = rand() % CAPS;
    int cost = rand() % COSTS;
    if (a == b)
      continue;
    mcmf.addEdge(a, b, cap, cost);
  }
  auto pa = mcmf.mcmf(s, t);
  cout << pa.first << ' ' << pa.second << endl;
}

void testWithCosts(int n, int m, const vector<vi> &costs) {
  int s = n + m, t = s + 1;

  MCMF old(n + m + 2);
  MinCostMaxFlow nf(n + m + 2);
  rep(i, 0, n) old.addEdge(s, i, 1, 0), nf.addEdge(s, i, 1, 0);
  rep(i, 0, m) old.addEdge(n + i, t, 1, 0), nf.addEdge(n + i, t, 1, 0);
  rep(i, 0, n) rep(j, 0, m) old.addEdge(i, n + j, 1, costs[i][j]),
      nf.addEdge(i, n + j, 1, costs[i][j]);

  old.setpi(s), nf.setpi(s);
  auto resold = old.maxflow(s, t), res = nf.mcmf(s, t);
  assert(res == resold);
}

void testPositive() {
  rep(_, 0, 10000) {
    int n = rand() % 10, m = rand() % 10;
    vector<vi> costs(n, vi(m));
    rep(i, 0, n) rep(j, 0, m) costs[i][j] = rand() % 20;
    testWithCosts(n, m, costs);
  }
}

void testNegative() {
  rep(_, 0, 10000) {
    int n = rand() % 10, m = rand() % 10;
    vector<vi> costs(n, vi(m));
    rep(i, 0, n) rep(j, 0, m) costs[i][j] = (rand() % 20) - 10;
    testWithCosts(n, m, costs);
  }
}

void testDoubleEdges() {
  MinCostMaxFlow nf(3);
  nf.addEdge(0, 1, 4, 3);
  nf.addEdge(0, 1, 1, 1);
  nf.addEdge(1, 2, 2, 1);
  nf.addEdge(1, 2, 1, 3);
  assert((nf.mcmf(0, 2) == pair<ll, ll>{3, 12}));
}

int main() {
  testPerf();
  testPositive();
  testNegative();
  testDoubleEdges();

  cout << "Tests passed!" << endl;
}
