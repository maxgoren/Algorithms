#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void tsp(const vector<vector<int>>& graph, vector<bool>& seen, vector<int>& path, int curr, int n, int count, int cost, int & ans)
{
	if (count == n && graph[curr][0]) {
		ans = min(ans, cost + graph[curr][0]);
		for (auto n : path) {
			cout<<n<<"-> ";
		}
		cout<<0<<", cost: "<<ans<<endl;
		return;
	}
	for (int i = 0; i < n; i++) {
		if (!seen[i] && graph[curr][i]) {
			seen[i] = true;
			path.push_back(i);
			tsp(graph, seen, path, i, n, count + 1, cost + graph[curr][i], ans);
			seen[i] = false;
			path.pop_back();
		}
	}
}

int main()
{
	int n = 4;
	vector<vector<int>> graph = { {0,10, 15, 20},
				      {10, 0, 35, 25},
				      {15, 35, 0, 30},
				      {20, 25, 30, 0} };
	vector<bool> seen(n, false);
	vector<int> path;
	path.push_back(0);
	seen[0] = true;
	int ans = INT_MAX;
	tsp(graph, seen, path, 0, n, 1, 0, ans);
	return 0;
}
