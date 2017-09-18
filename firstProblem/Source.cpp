#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <queue>

using namespace std;

struct edge {
	int x1;
	int y1;
	int x2;
	int y2;
	edge() {}
	edge(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
	const bool operator==(const edge &Y) const {
		return (x1 == Y.x1 && x2 == Y.x2 && y1 == Y.y1 && y2 == Y.y2);
	}
	const bool operator< (const edge& Y) const {
		if (x1 < Y.x1)
			return true;
		if (x1 == Y.x1 && y1 < Y.y1)
			return true;
		return false;
	}
};
bool isInside(edge &rect, int x1, int y1, int x2, int y2) {
	if (x1 >= rect.x1 && x2 <= rect.x2 &&
		y1 >= rect.y1 && y2 <= rect.y2)
		return true;
	return false;
}
set<int> setX, setY;
bool used[200][200];
edge med[200][200];
map<edge, vector<int> > map_color;
int n, m;
void bfs(int x, int y) {
	queue<pair<int, int>> que;
	que.push(make_pair(x, y));
	used[x][y] = true;
	while (!que.empty()) {
		pair<int, int> cur = que.front();
		que.pop();
		int X = cur.first;
		int Y = cur.second;
		if (X > 0 && !used[X - 1][Y] && map_color[med[X][Y]] == map_color[med[X - 1][Y]])
			que.push(make_pair(X - 1, Y)), used[X - 1][Y] = true;
		if (X + 1 < n && !used[X + 1][Y] && map_color[med[X][Y]] == map_color[med[X + 1][Y]])
			que.push(make_pair(X + 1, Y)), used[X + 1][Y] = true;
		if (Y > 0 && !used[X][Y - 1] && map_color[med[X][Y]] == map_color[med[X][Y - 1]])
			que.push(make_pair(X, Y - 1)), used[X][Y - 1] = true;
		if (Y < m && !used[X][Y + 1] && map_color[med[X][Y]] == map_color[med[X][Y + 1]])
			que.push(make_pair(X, Y + 1)), used[X][Y + 1] = true;
		
	}
}
int main() {
	int N;
	cin >> N;
	vector<edge> rects;
	rects.push_back(edge(-100000, -100000, 100000, 100000));
	setX.insert(-100000);
	setX.insert(100000);
	setY.insert(-100000);
	setY.insert(100000);
	for (int i = 0; i < N; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		if (x1 > x2)
			swap(x1, x2);
		if (y1 > y2)
			swap(y1, y2);
		rects.push_back(edge(x1, y1, x2, y2));
		setX.insert(x1);
		setX.insert(x2);
		setY.insert(y1);
		setY.insert(y2);
	}
	n = setX.size() - 1;
	m = setY.size() - 1;
	int indI = 0, indJ = 0;
	for (set<int>::iterator itX = setX.begin(); itX != setX.end(); itX++, indI++) {
		if (itX == --setX.end())
			continue;
		indJ = 0;
		for (set<int>::iterator itY = setY.begin(); itY != setY.end(); itY++, indJ++) {
			if (itY == --setY.end())
				continue;
			set<int>::iterator itx = itX;
			set<int>::iterator ity = itY;
			int x1 = *itx;
			int y1 = *ity;
			itx++;
			ity++;
			int x2 = *itx;
			int y2 = *ity;
			edge cur_edge(x1, y1, x2, y2);
			med[indI][indJ] = cur_edge;
			for (int i = 0; i < rects.size(); i++) {
				if (isInside(rects[i], x1, y1, x2, y2))
					map_color[cur_edge].push_back(i);
			}
		}
	}
	int k = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (!used[i][j]) {
				bfs(i, j);
				k++;
			}
		}
	}
	cout << k;
	system("pause");
	return 0;
}