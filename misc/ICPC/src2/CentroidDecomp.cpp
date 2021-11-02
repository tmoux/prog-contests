struct CentroidDecomposition {
	vector<set<int>> tree; // it's not vector<vector<int>>!
	vector<int> dad;
	vector<int> sub;
    vector<int> dep;
 
	CentroidDecomposition(vector<set<int>> &tree) : tree(tree) {
		int n = tree.size();
		dad.resize(n);
		sub.resize(n);
        dep.resize(n);
		build(0, -1);
	}
 
	void build(int u, int p) {
		int n = dfs(u, p); // find the size of each subtree
		int centroid = dfs(u, p, n); // find the centroid
        if (p == -1) {
            dep[centroid] = 0;
        } else {
            dep[centroid] = dep[p] + 1;
        }
		if (p == -1) p = centroid; // dad of root is the root itself
		dad[centroid] = p;
		// for each tree resulting from the removal of the centroid
        while (!tree[centroid].empty()) {
            int v = *(tree[centroid].begin());
			tree[centroid].erase(v); // remove the edge to disconnect
			tree[v].erase(centroid); // the component from the tree
			build(v, centroid);
        }
 
	}
 
	int dfs(int u, int p) {
		sub[u] = 1;
 
		for (auto v : tree[u])
			if (v != p) sub[u] += dfs(v, u);
 
		return sub[u];
	}
 
	int dfs(int u, int p, int n) {
		for (auto v : tree[u])
			if (v != p and sub[v] > n/2) return dfs(v, u, n);
 
		return u;
	}
 
	int operator[](int i) {
		return dad[i];
	}
};
