#include <iostream>
#include<vector>
#include <climits>
#include <algorithm>

using namespace std;
/*
Holmes tries to minimize the number of steps from the current position
to the goal state for the red mapple, while Moriarty tries to maximize it.
The vice versa stands for the black mapple
*/
int n, m;
vector<int> memoMin;
vector<int> memoMax;
vector<vector<int>> graph;

int minSteps(int position);

int maxSteps(int position) {
  if (position == n) return 0;

  if (memoMax[position] != -1) return memoMax[position];

  int maxValue = 0;
  for (auto transition : graph[position]) {
    maxValue = max(1 + minSteps(transition), maxValue);
  }

  memoMax[position] = maxValue;

  return maxValue;

}

int minSteps(int position) {
  if (position == n) return 0;

  if (memoMin[position] != -1) return memoMin[position];

  int minValue = INT_MAX;
  for (auto transition : graph[position]) {
    minValue = min(1 + maxSteps(transition), minValue);
  }

  memoMin[position] = minValue;

  return minValue;

}

void test_case() {
  cin >> n >> m;
  int r, b;
  cin >> r >> b;
  graph = vector<vector<int>>(n);
  memoMin = vector<int>(n, -1);
  memoMax = vector<int>(n, -1);
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    graph[x].push_back(y);
  }

  int holmesSteps = minSteps(r); // holmes minimizes the steps to get R to goal state
  int moriartySteps = minSteps(b);

  if (holmesSteps < moriartySteps) cout << 0 << "\n";
  else if (moriartySteps < holmesSteps) cout << 1 << "\n";
  else if (holmesSteps % 2 == 1) cout << 0 << "\n";
  else cout << 1 << "\n";

}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;

  for (int i = 0; i < t; ++i) {
    test_case();
  }

  return 0;

}
