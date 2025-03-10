#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

template <typename T>
class Graph {
public:
	virtual void addVertex(T v) = 0;
	virtual bool isAdjacent(T v1, T v2) = 0;
	virtual void addEdge(T v1, T v2) = 0;
	virtual vector<T> getNeighbors(T v) const = 0;
	virtual void printGraph() = 0;
};

template <typename T>
class EdgeList : public Graph<T> {
	vector<pair<T, T>> _edges;

public:
	EdgeList() {}
	EdgeList(vector<pair<T, T>> edges) : _edges(edges) {}

	void addVertex(T v) override {
		// Do nothing
	}

	bool isAdjacent(T v1, T v2) override {
		for (auto edge : _edges) {
			if (edge == pair<T, T>{v1, v2}) {
				return true;
			}
		}
		return false;
	}

	void addEdge(T v1, T v2) override {
		_edges.push_back(pair<T, T>{v1, v2});
	}

	vector<T> getNeighbors(T v) const override {
		vector<T> neighbors;
		for (auto edge : _edges) {
			if (edge.first == v) {
				neighbors.push_back(edge.second);
			}
		}
		return neighbors;
	}

	void printGraph() override {
		for (auto edge : _edges) {
			cout << edge.first << " -> " << edge.second << endl;
		}
	}
};

template <typename T>
class AdjacencyList : public Graph<T> {
	unordered_map<T, vector<T>> _adjacencyList;

public:

	AdjacencyList() {}

	void addVertex(T v) override {
		_adjacencyList.emplace(make_pair(v, vector<T>()));
	}

	void addEdge(T v1, T v2) override {
		this->addVertex(v1);
		this->addVertex(v2);
		_adjacencyList[v1].push_back(v2);
	}

	bool isAdjacent(T v1, T v2) override {
		return find(_adjacencyList[v1].begin(), _adjacencyList[v1].end(), v2) != _adjacencyList[v1].end();
	}

	vector<T> getNeighbors(T v) const override {
		return _adjacencyList.at(v);
	}

	void printGraph() override {
		for (auto& pair : _adjacencyList) {
			cout << pair.first << ": ";
			for (auto& neighbor : pair.second) {
				cout << neighbor << " ";
			}
			cout << endl;
		}
	}

	const vector<T>& getNeighborsRef(T v) {
		return _adjacencyList[v];
	}
};

template <typename T>
class AdjacencyMatrix : public Graph<T> {
	unordered_map<T, int> _vertexToIndex;
	unordered_map<int, T> _indexToVertex;
	vector<vector<bool>> _adjacencyMatrix;

public:
	AdjacencyMatrix() {}

	void addVertex(T v) override {
		if (_vertexToIndex.find(v) != _vertexToIndex.end()) {
			return;
		}

		_vertexToIndex[v] = _adjacencyMatrix.size();
		_indexToVertex[_vertexToIndex[v]] = v;

		// add new row and column for the new vertex
		for (auto& row : _adjacencyMatrix) {
			row.push_back(false);
		}
		_adjacencyMatrix.push_back(vector<bool>(_adjacencyMatrix.size() + 1, false));
	}

	void addEdge(T v1, T v2) override {
		this->addVertex(v1);
		this->addVertex(v2);

		int i = _vertexToIndex.at(v1);
		int j = _vertexToIndex.at(v2);

		_adjacencyMatrix[i][j] = true;
	}

	bool isAdjacent(T v1, T v2) override {
		int i = _vertexToIndex.at(v1);
		int j = _vertexToIndex.at(v2);

		return _adjacencyMatrix[i][j];
	}

	vector<T> getNeighbors(T v) const override {
		int i = _vertexToIndex.at(v);
		vector<T> neighbors;

		for (int j = 0; j < _adjacencyMatrix.size(); ++j) {
			if (_adjacencyMatrix[i][j]) {
				neighbors.push_back(_indexToVertex.at(j));
			}
		}

		return neighbors;
	}

	void printGraph() override {
		for (int i = 0; i < _adjacencyMatrix.size(); ++i) {
			cout << _indexToVertex[i] << ": ";
			for (int j = 0; j < _adjacencyMatrix.size(); ++j) {
				if (_adjacencyMatrix[i][j]) {
					cout << _indexToVertex[j] << " ";
				}
			}
			cout << endl;
		}
	}
};


template <typename T>
void _dfs(const Graph<T>& g, const T& source, unordered_set<T>& visitedVertices, vector<T>& results) {
	cout << "Current: " << source << endl;
	visitedVertices.insert(source);
	results.push_back(source);

	vector<T> neighbors = g.getNeighbors(source);
	for (T neighbor : neighbors) {
		if (visitedVertices.find(neighbor) == visitedVertices.end()) {
			_dfs(g, neighbor, visitedVertices, results);
		}
	}
}

template <typename T>
vector<T> dfs(const Graph<T>& g, T source) {
	unordered_set<T> visitedVertices;
	vector<T> results;
	_dfs(g, source, visitedVertices, results);
	return results;
}

template <typename T>
vector<T> bfs(const Graph<T>& g, T source) {
		unordered_set<T> visitedVertices;
		vector<T> results;
		queue<T> q;

		visitedVertices.insert(source);
		q.push(source);

		while (!q.empty()) {
			T current = q.front();
			q.pop();
			results.push_back(current);

			for (const T& neighbor : g.getNeighbors(current)) {
				if (visitedVertices.find(neighbor) == visitedVertices.end()) {
					visitedVertices.insert(neighbor);
					q.push(neighbor);
				}
			}
		}

		return results;
}

int main() {
	AdjacencyMatrix<char> adjMatrix;
	AdjacencyList<char> adjList;
	EdgeList<char> edgeList;

	// go crazy!

	return 0;
}
