#include<bits/stdc++.h>
using namespace std;

template<typename T>
class TreeNode {
public:
	T val;
	TreeNode *left;
	TreeNode *right;

	TreeNode(T x) {
		val = x;
		left = nullptr;
		right = nullptr;
	}
};

TreeNode<int>* BuildTree() {
	int x;
	cin >> x;
	if (x == -1) return NULL;
	TreeNode<int>* n = new TreeNode<int>(x);
	n->left = BuildTree();
	n->right = BuildTree();
	return n;
}


//Level Order Traversal To Print the Entire Tree for reverence :
void BFS(TreeNode<int>*root) {

	queue<TreeNode<int>*>q;
	q.push(root);
	q.push(NULL);

	while (!q.empty()) {

		TreeNode<int>*f = q.front();
		q.pop();

		if (f == NULL) {

			if (!q.empty()) {
				q.push(NULL);
			}

			cout << endl;

		} else {

			cout << f->val << " ";

			if (f->left != NULL) {
				q.push(f->left);
			}

			if (f->right != NULL) {
				q.push(f->right);
			}

		}

	}
	cout << "----------------------------" << endl;
}


//LeftView of the Tree :
void LeftView(TreeNode<int>*root, int Level, int &PrintedLevel) {

	if (root == NULL) {
		return;
	}

	if (PrintedLevel < Level) {
		cout << root->val << " ";
		PrintedLevel = Level;
	}

	LeftView(root->left, Level + 1, PrintedLevel);
	LeftView(root->right, Level + 1, PrintedLevel);
}

//RightView of the Tree :
void Rightview(TreeNode<int>*root, int Level, int &PrintedLevel) {

	if (root == NULL) {
		return;
	}

	if (PrintedLevel < Level) {
		cout << root->val << " ";
		PrintedLevel = Level;
	}

	Rightview(root->right, Level + 1, PrintedLevel);
	Rightview(root->left, Level + 1, PrintedLevel);
}


//TopView of the Tree Using Multimap : Column and Level Wise Sorted.
void dfs(TreeNode<int>* root, int column, int level, multimap<pair<int, int>, int>& mmap) {
	if (root == NULL) {
		return;
	}

	mmap.insert({{column, level}, root->val});

	dfs(root->left, column - 1, level + 1, mmap);
	dfs(root->right, column + 1, level + 1, mmap);
}

vector<int> TopViewColumnAndLevelWiseSortedUsingMultimap(TreeNode<int>* root) {
	vector<int> ans;
	if (root == NULL) return ans;

	multimap<pair<int, int>, int> mmap;
	dfs(root, 0, 0, mmap);

	int current_column = -1e9;

	for (auto it = mmap.begin(); it != mmap.end(); it++) {
		int col = it->first.first;
		int val = it->second;
		if (col != current_column) {
			ans.push_back(val);
			current_column = col;
		}
	}

	return ans;
}


void dfs2(TreeNode<int>* root, int column, int level, map<pair<int, int>, vector<int>>& mp) {
	if (root == NULL) return;
	mp[ {column, level}].push_back(root->val);

	dfs2(root->left, column - 1, level + 1, mp);
	dfs2(root->right, column + 1, level + 1, mp);
}

vector<int> TopViewColumnAndLevelWiseSortedUsingMap(TreeNode<int>* root) {
	vector<int> ans;
	if (root == NULL) return ans;

	map<pair<int, int>, vector<int>> mp;
	dfs2(root, 0, 0, mp);

	int current_column = -1e9;

	for (auto it : mp) {
		int col = it.first.first;
		if (col != current_column) {
			ans.push_back(it.second[0]);
			current_column = col;
		}
	}
	return ans;
}


vector<int> TopViewIterative(TreeNode<int>* root) {
	vector<int> ans;
	if (root == NULL) {
		return ans;
	}

	/*
		Map to store the Top View: map<column, node->val>
		It automatically sorts the columns from left to right.
	*/

	map<int, int> topNodeMap;

	// queue for BFS: queue< pair<node, column> >
	queue<pair<TreeNode<int>*, int>> q;

	// Push the root node at column 0
	q.push({root, 0});

	while (!q.empty()) {
		auto it = q.front();
		q.pop();

		TreeNode<int>* node = it.first;
		int col = it.second;

		// If this is the FIRST time seeing this column, add it to the map.
		// Because BFS goes level-by-level, this first node is guaranteed to be the top!
		if (topNodeMap.find(col) == topNodeMap.end()) {
			topNodeMap[col] = node->val;
		}

		// Push left child (column - 1)
		if (node->left != NULL) {
			q.push({node->left, col - 1});
		}

		// Push right child (column + 1)
		if (node->right != NULL) {
			q.push({node->right, col + 1});
		}
	}

	// Extract values from the map (which are already sorted by column)
	for (auto it : topNodeMap) {
		ans.push_back(it.second);
	}

	return ans;
}

void dfs3(TreeNode<int>* root, int column, int level, multimap<pair<int, int>, int>& mmap) {
	if (root == NULL) return;

	mmap.insert({{column, level}, root->val});

	dfs3(root->left, column - 1, level + 1, mmap);
	dfs3(root->right, column + 1, level + 1, mmap);
}

vector<int> BottomViewColumnAndLevelWiseSortedUsingMultimap(TreeNode<int>* root) {
	vector<int> ans;
	if (root == NULL) return ans;

	multimap<pair<int, int>, int> mmap;
	dfs3(root, 0, 0, mmap);

	// Map to store the final deepest node for each column
	map<int, int> bottomNodes;

	for (auto it = mmap.begin(); it != mmap.end(); it++) {
		int col = it->first.first;
		int val = it->second;

		// We constantly overwrite.
		// Because 'it' is sorted by level, deeper nodes will overwrite shallower ones.
		bottomNodes[col] = val;
	}

	for (auto it : bottomNodes) {
		ans.push_back(it.second);
	}
	return ans;
}


void dfs4(TreeNode<int>* root, int column, int level, map<pair<int, int>, vector<int>>& mp) {
	if (root == NULL) return;

	mp[ {column, level}].push_back(root->val);

	dfs4(root->left, column - 1, level + 1, mp);
	dfs4(root->right, column + 1, level + 1, mp);
}

vector<int> BottomViewColumnAndLevelWiseSortedUsingMap(TreeNode<int>* root) {
	vector<int> ans;
	if (root == NULL) return ans;

	map<pair<int, int>, vector<int>> mp;
	dfs4(root, 0, 0, mp);

	map<int, int> bottomNodes;

	for (auto it : mp) {
		int col = it.first.first;

		// it.second is the vector of nodes at this specific (column, level)
		// .back() safely grabs the last (rightmost) element.
		// As the loop progresses through deeper levels, it overwrites shallower ones.
		bottomNodes[col] = it.second.back();
	}

	for (auto it : bottomNodes) {
		ans.push_back(it.second);
	}
	return ans;
}


vector<int> BottomViewIterative(TreeNode<int>* root) {
	vector<int> ans;
	if (root == NULL) return ans;

	map<int, int> bottomNodeMap;
	queue<pair<TreeNode<int>*, int>> q;

	q.push({root, 0});

	while (!q.empty()) {
		auto it = q.front();
		q.pop();

		TreeNode<int>* node = it.first;
		int col = it.second;

		// MAGIC HAPPENS HERE:
		// We ALWAYS overwrite the value at this column.
		// Because BFS goes top-to-bottom, the last value written will be the deepest node.
		// If two nodes are at the same depth, the right one is processed later, overwriting the left.
		bottomNodeMap[col] = node->val;

		if (node->left != NULL) {
			q.push({node->left, col - 1});
		}

		if (node->right != NULL) {
			q.push({node->right, col + 1});
		}
	}

	for (auto it : bottomNodeMap) {
		ans.push_back(it.second);
	}

	return ans;
}

void dfs5(TreeNode<int>* root, int col, int level, multimap<pair<int, int>, int>& mmap) {
	if (root == NULL) return;

	// Insert the node. The multimap handles all the sorting!
	mmap.insert({{col, level}, root->val});

	dfs5(root->left, col - 1, level + 1, mmap);
	dfs5(root->right, col + 1, level + 1, mmap);
}

vector<int> VerticalViewColumnAndLevelSortedUsingMultimap(TreeNode<int>* root) {
	vector<int> ans;
	if (root == NULL) return ans;

	// multimap< pair<column, level>, node_value >
	multimap<pair<int, int>, int> mmap;

	dfs5(root, 0, 0, mmap);

	// Because the multimap perfectly sorts by column first, then level second,
	// we just iterate from beginning to end and grab the values!
	for (auto it : mmap) {
		ans.push_back(it.second);
	}

	return ans;
}

void dfs6(TreeNode<int>* root, int col, int level, map<pair<int, int>, vector<int>>& mp) {
	if (root == NULL) return;

	// Append the node to the vector at this specific {column, level} coordinate
	mp[ {col, level}].push_back(root->val);

	// Traverse left and right
	dfs6(root->left, col - 1, level + 1, mp);
	dfs6(root->right, col + 1, level + 1, mp);
}

vector<int> VerticalViewColumnAndLevelSortedUsingMap(TreeNode<int>* root) {
	vector<int> ans;
	if (root == NULL) return ans;

	// map< {column, level}, list_of_nodes >
	map<pair<int, int>, vector<int>> mp;

	dfs6(root, 0, 0, mp);

	// Iterate through the perfectly sorted map
	for (auto it : mp) {

		// Optional LeetCode 987 Fix:
		// If your platform requires overlapping nodes to be sorted by their VALUE,
		// you can simply sort the vector right here before adding it to the answer!
		// sort(it.second.begin(), it.second.end());

		// Extract all nodes at this coordinate
		for (int val : it.second) {
			ans.push_back(val);
		}
	}

	return ans;
}


vector<int> VerticalOrderIterativeNoValueSort(TreeNode<int>* root) {
	vector<int> ans;
	if (root == NULL) return ans;

	// map<column, list_of_nodes>
	// The map automatically sorts by column (left to right).
	map<int, vector<int>> colMap;

	// queue<pair<Node, column>>
	// We no longer need to track the level in the queue!
	queue<pair<TreeNode<int>*, int>> q;

	q.push({root, 0});

	while (!q.empty()) {
		auto current = q.front();
		q.pop();

		TreeNode<int>* node = current.first;
		int col = current.second;

		// Push the value into the vector for this column.
		// Because BFS processes top-to-bottom, shallower levels are naturally pushed first!
		colMap[col].push_back(node->val);

		if (node->left != NULL) {
			q.push({node->left, col - 1});
		}

		if (node->right != NULL) {
			q.push({node->right, col + 1});
		}
	}

	// Extract the nodes
	// The map is sorted by column. The vectors are naturally sorted by level.
	for (auto it : colMap) {
		for (int val : it.second) {
			ans.push_back(val);
		}
	}

	return ans;
}

void dfs7(TreeNode<int>* root, int col, int level, vector<pair<pair<int, int>, int>>& all_nodes) {
	if (root == NULL) return;

	// Store coordinates and value: {{col, level}, value}
	all_nodes.push_back({{col, level}, root->val});

	dfs7(root->left, col - 1, level + 1, all_nodes);
	dfs7(root->right, col + 1, level + 1, all_nodes);
}

vector<int> VerticalViewColumnAndLevelAndValueSortedUsingSort(TreeNode<int>* root) {
	vector<int> ans;
	if (root == NULL) return ans;

	vector<pair<pair<int, int>, int>> all_nodes;
	dfs7(root, 0, 0, all_nodes);

	// std::sort automatically sorts by column first.
	// If columns tie, it sorts by level second.
	// If levels tie, it sorts by value third.
	sort(all_nodes.begin(), all_nodes.end());

	// Extract everything into the final answer
	for (auto node : all_nodes) {
		ans.push_back(node.second);
	}

	return ans;
}

void dfs8(TreeNode<int>* root, int col, int level, map<int, map<int, multiset<int>>>& nodes) {
	if (root == NULL) return;

	// Insert the node's value into the exact {column, level} bucket.
	// The map -> map -> multiset structure handles ALL the sorting automatically!
	nodes[col][level].insert(root->val);

	// Traverse left (col-1, level+1) and right (col+1, level+1)
	dfs8(root->left, col - 1, level + 1, nodes);
	dfs8(root->right, col + 1, level + 1, nodes);
}

vector<int> VerticalViewColumnAndLevelAndValueSortedUsingMap(TreeNode<int>* root) {
	vector<int> ans;
	if (root == NULL) return ans;

	// The ultimate triple-sorting data structure
	map<int, map<int, multiset<int>>> nodes;

	dfs8(root, 0, 0, nodes);

	// Extract the perfectly sorted nodes
	// 1. Iterate through the columns (left to right)
	for (auto col_it : nodes) {

		// 2. Iterate through the levels for this column (top to bottom)
		for (auto level_it : col_it.second) {

			// 3. Iterate through the values at this exact coordinate (smallest to largest)
			for (int val : level_it.second) {
				ans.push_back(val);
			}
		}
	}

	return ans;
}

void dfs9(TreeNode<int>* root, int col, int level, multiset<pair<pair<int, int>, int>>& all_nodes) {
	if (root == NULL) return;

	// Insert the entire coordinate and value as one single item.
	// C++ compares the first element (col), then the second (level), then the third (value)!
	all_nodes.insert({{col, level}, root->val});

	dfs9(root->left, col - 1, level + 1, all_nodes);
	dfs9(root->right, col + 1, level + 1, all_nodes);
}

vector<int> VerticalViewColumnAndLevelAndValueSortedUsingMultiset(TreeNode<int>* root) {
	vector<int> ans;
	if (root == NULL) return ans;

	// multiset< {{column, level}, value} >
	multiset<pair<pair<int, int>, int>> all_nodes;

	dfs9(root, 0, 0, all_nodes);

	// Because everything was part of the element being sorted,
	// the multiset is already perfectly ordered col -> level -> value.
	for (auto node : all_nodes) {
		ans.push_back(node.second); // Just extract the value!
	}

	return ans;
}

vector<int> VerticalViewTripleSortIterative(TreeNode<int>* root) {
	vector<int> ans;
	if (root == NULL) return ans;

	// The triple-sorting structure: map<column, map<level, multiset<values>>>
	map<int, map<int, multiset<int>>> nodes;

	// The queue tracks the node AND its 2D coordinates: queue<pair<Node, {col, level}>>
	queue<pair<TreeNode<int>*, pair<int, int>>> q;

	// Start with the root at column 0, level 0
	q.push({root, {0, 0}});

	while (!q.empty()) {
		auto current = q.front();
		q.pop();

		TreeNode<int>* node = current.first;
		int col = current.second.first;
		int level = current.second.second;

		// Insert into the nested maps
		// 1. col sorts left-to-right
		// 2. level sorts top-to-bottom
		// 3. multiset sorts overlapping values small-to-large
		nodes[col][level].insert(node->val);

		// Traverse left (col - 1, level + 1)
		if (node->left != NULL) {
			q.push({node->left, {col - 1, level + 1}});
		}

		// Traverse right (col + 1, level + 1)
		if (node->right != NULL) {
			q.push({node->right, {col + 1, level + 1}});
		}
	}

	// Extract everything exactly in order
	for (auto col_it : nodes) {
		for (auto level_it : col_it.second) {
			for (int val : level_it.second) {
				ans.push_back(val);
			}
		}
	}

	return ans;
}





int main() {

	TreeNode<int>*root = BuildTree();
	BFS(root);
	int PrintedLevel = -1;
	LeftView(root, 0, PrintedLevel);
	cout << endl << "-------------------------" << endl;
	PrintedLevel = -1;
	Rightview(root, 0, PrintedLevel);
	cout << endl << "-------------------------" << endl;
	vector<int>ans = TopViewColumnAndLevelWiseSortedUsingMultimap(root);
	for (auto x : ans) {
		cout << x << " ";
	}
	cout << endl << "-------------------------" << endl;
	vector<int>ans2 = TopViewColumnAndLevelWiseSortedUsingMap(root);
	for (auto x : ans2) {
		cout << x << " ";
	}
	cout << endl << "-------------------------" << endl;
	vector<int>ans3 = TopViewIterative(root);
	for (auto x : ans3) {
		cout << x << " ";
	}
	cout << endl << "-------------------------" << endl;
	vector<int>ans4 = BottomViewColumnAndLevelWiseSortedUsingMultimap(root);
	for (auto x : ans4) {
		cout << x << " ";
	}
	cout << endl << "-------------------------" << endl;
	vector<int>ans5 = BottomViewColumnAndLevelWiseSortedUsingMap(root);
	for (auto x : ans5) {
		cout << x << " ";
	}
	cout << endl << "-------------------------" << endl;
	vector<int>ans6 = BottomViewIterative(root);
	for (auto x : ans6) {
		cout << x << " ";
	}
	cout << endl << "-------------------------" << endl;
	vector<int>ans7 = VerticalViewColumnAndLevelSortedUsingMultimap(root);
	for (auto x : ans7) {
		cout << x << " ";
	}
	cout << endl << "-------------------------" << endl;
	vector<int>ans8 = VerticalViewColumnAndLevelSortedUsingMap(root);
	for (auto x : ans8) {
		cout << x << " ";
	}
	cout << endl << "-------------------------" << endl;

	vector<int>ans9 = VerticalOrderIterativeNoValueSort(root);
	for (auto x : ans9) {
		cout << x << " ";
	}
	cout << endl << "-------------------------" << endl;
	vector<int>ans10 = VerticalViewColumnAndLevelAndValueSortedUsingSort(root);
	for (auto x : ans10) {
		cout << x << " ";
	}
	cout << endl << "-------------------------" << endl;
	vector<int>ans11 = VerticalViewColumnAndLevelAndValueSortedUsingMap(root);
	for (auto x : ans11) {
		cout << x << " ";
	}
	cout << endl << "-------------------------" << endl;
	vector<int>ans12 = VerticalViewColumnAndLevelAndValueSortedUsingMultiset(root);
	for (auto x : ans12) {
		cout << x << " ";
	}
	cout << endl << "-------------------------" << endl;
	vector<int>ans13 = VerticalViewTripleSortIterative(root);
	for (auto x : ans13) {
		cout << x << " ";
	}
	cout << endl << "-------------------------" << endl;
}
