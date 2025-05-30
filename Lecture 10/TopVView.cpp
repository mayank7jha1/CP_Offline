#include<iostream>
#include<queue>
#include<unordered_map>
#include<map>
using namespace std;
const int N = 0;

class TreeNode {
public:

	int val;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int inputvalue) {
		val = inputvalue;
		left = NULL;
		right = NULL;
	}
};

TreeNode*Buildtree() {

	int x;
	cin >> x;

	if (x == -1) {
		return NULL;

	} else {

		//Node with the help of constructer
		TreeNode *r = new TreeNode(x);
		r->left = Buildtree();
		r->right = Buildtree();
		return r;
	}
}


void bfs2(TreeNode*root) {

	queue<TreeNode*>q;
	q.push(root);
	q.push(NULL);

	while (!q.empty()) {

		TreeNode* f = q.front();

		if (f == NULL) {
			cout << endl;
			q.pop();

			if (!q.empty()) {
				q.push(NULL);
			}
		} else {
			cout << f->val << " ";
			q.pop();

			if (f->left != NULL) {
				q.push(f->left);
			}

			if (f->right != NULL) {
				q.push(f->right);
			}
		}

	}
}


void Solve(TreeNode* root, unordered_map<int, int>&ump, int column) {

	if (root == NULL) {
		return;
	}

	if (ump.count(column) == 0) {
		ump[column] = root->val;
	}


	Solve(root->left, ump, column - 1);
	Solve(root->right, ump, column + 1);
}

void Solve2(TreeNode* root, map<int, int>&ump, int column) {

	if (root == NULL) {
		return;
	}

	if (ump.count(column) == 0) {
		ump[column] = root->val;
	}


	Solve2(root->left, ump, column - 1);
	Solve2(root->right, ump, column + 1);
}

vector<int>TopView(TreeNode* root) {

	vector<int>ans;

	if (root == NULL) {
		return ans;
	}

	//unordered_map<int, int>ump;
	map<int, int>ump;//Sort Karta hain on the basis of Column.

	Solve2(root, ump, 0);

	for (auto x : ump) {
		ans.push_back(x.second);
	}
	return ans;
}

int main() {
	TreeNode*root = Buildtree();
	bfs2(root);

	cout << "Top View of the Tree :" << endl;
	vector<int>a = TopView(root);
	for (auto x : a) {
		cout << x << " ";
	}

}