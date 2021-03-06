#include <iostream>
#include <math.h>
#include <algorithm>
#include <string>
#include <list>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <limits>
#include <thread>
#include <mutex>
#include <fstream>
#include <memory>
using namespace std;

class Solution {
private:
	// pair<edge, len>
	pair<int, int> bfs(const unordered_map<int, vector<int> > &info, int start) {
		unordered_set<int> accessed;
		
		int longestLength(0);
		int longestVertex(start);
		
		queue< pair<int, int> > q;
		q.push( {start,0} );
		accessed.insert(start);
		
		while(!q.empty()) {
			auto [currVertex, currLength] = q.front(); q.pop();
			if (currLength > longestLength) {
				longestLength = currLength;
				longestVertex = currVertex;
			}
			
			for (int edge : info.at(currVertex)) {
				if (accessed.find(edge) == accessed.end()) {
					q.push( {edge,currLength+1} );
					accessed.insert(edge);
				}
			}
		}
		
		return make_pair(longestVertex, longestLength);
	}
	
public:
	int treeDiameter(vector<vector<int>>& edges) {
		if (edges.size() <= 1) return 0;
		
		unordered_map<int, vector<int> > info;
		for (auto &v : edges) {
			info[v[0]].push_back(v[1]);
			info[v[1]].push_back(v[0]);
		}
		
		int firstEdge = bfs(info, edges[0][0]).first;
		return bfs(info, firstEdge).second;
	}
};

int main(int argc, char *argv[]) {
	Solution s;
	vector< vector<int> > edges
	{
		{0,1},
		{1,2},
		{2,3},
		{1,4},
		{4,5}
	};
	assert(s.treeDiameter(edges) == 4);
	
}