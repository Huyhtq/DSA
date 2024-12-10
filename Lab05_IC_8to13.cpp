#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// Definition of TreeNode class
class TreeNode {
public:
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Definition of BinaryTree class
class BinaryTree {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, int value) {
        if (!node) return new TreeNode(value);
        if (value < node->value)
            node->left = insert(node->left, value);
        else
            node->right = insert(node->right, value);
        return node;
    }

    TreeNode* search(TreeNode* node, int value) {
        if (!node || node->value == value) return node;
        if (value < node->value)
            return search(node->left, value);
        return search(node->right, value);
    }

    int maxPathSumHelper(TreeNode* node, int& globalMax) {
        if (!node) return 0;
        int left = max(0, maxPathSumHelper(node->left, globalMax));
        int right = max(0, maxPathSumHelper(node->right, globalMax));
        globalMax = max(globalMax, left + right + node->value);
        return node->value + max(left, right);
    }

    void verticalOrderHelper(TreeNode* node, int hd, map<int, vector<int>>& result) {
        if (!node) return;
        result[hd].push_back(node->value);
        verticalOrderHelper(node->left, hd - 1, result);
        verticalOrderHelper(node->right, hd + 1, result);
    }

    TreeNode* buildTreeHelper(vector<int>& inorder, vector<int>& postorder, int& postIndex, int inStart, int inEnd) {
        if (inStart > inEnd) return nullptr;
        TreeNode* root = new TreeNode(postorder[postIndex--]);
        int inIndex = find(inorder.begin(), inorder.end(), root->value) - inorder.begin();
        root->right = buildTreeHelper(inorder, postorder, postIndex, inIndex + 1, inEnd);
        root->left = buildTreeHelper(inorder, postorder, postIndex, inStart, inIndex - 1);
        return root;
    }

    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (!t1) return t2;
        if (!t2) return t1;
        t1->value += t2->value;
        t1->left = mergeTrees(t1->left, t2->left);
        t1->right = mergeTrees(t1->right, t2->right);
        return t1;
    }

public:
    BinaryTree() : root(nullptr) {}

    void insert(int value) { root = insert(root, value); }
    bool search(int value) { return search(root, value) != nullptr; }

    vector<vector<int>> levelOrderTraversal() {
        vector<vector<int>> result;
        if (!root) return result;

        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            vector<int> level;
            for (int i = 0; i < size; ++i) {
                TreeNode* current = q.front();
                q.pop();
                level.push_back(current->value);
                if (current->left) q.push(current->left);
                if (current->right) q.push(current->right);
            }
            result.push_back(level);
        }
        return result;
    }

    int maxPathSum() {
        int globalMax = INT_MIN;
        maxPathSumHelper(root, globalMax);
        return globalMax;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int postIndex = postorder.size() - 1;
        return buildTreeHelper(inorder, postorder, postIndex, 0, inorder.size() - 1);
    }

    map<int, vector<int>> verticalOrderTraversal() {
        map<int, vector<int>> result;
        verticalOrderHelper(root, 0, result);
        return result;
    }

    void merge(BinaryTree& other) {
        root = mergeTrees(root, other.root);
    }

    TreeNode* findLCA(TreeNode* node, int p, int q) {
        if (!node || node->value == p || node->value == q) return node;
        TreeNode* left = findLCA(node->left, p, q);
        TreeNode* right = findLCA(node->right, p, q);
        if (left && right) return node;
        return left ? left : right;
    }
};

// Functions for handling new menu options
void handleLevelOrder(BinaryTree& tree) {
    auto result = tree.levelOrderTraversal();
    cout << "Level-order traversal:\n";
    for (const auto& level : result) {
        for (int val : level) cout << val << " ";
        cout << endl;
    }
}

void handleMaxPathSum(BinaryTree& tree) {
    cout << "Maximum path sum: " << tree.maxPathSum() << endl;
}

void handleReconstructTree(BinaryTree& tree) {
    vector<int> inorder, postorder;
    int n;
    cout << "Enter the number of nodes: ";
    cin >> n;
    cout << "Enter the inorder traversal: ";
    inorder.resize(n);
    for (int& val : inorder) cin >> val;
    cout << "Enter the postorder traversal: ";
    postorder.resize(n);
    for (int& val : postorder) cin >> val;

    tree = BinaryTree();
    tree.insert(tree.buildTree(inorder, postorder)->value);
    cout << "Tree reconstructed successfully.\n";
}

void handleVerticalOrder(BinaryTree& tree) {
    auto result = tree.verticalOrderTraversal();
    cout << "Vertical order traversal:\n";
    for (const auto& pair : result) {
        int key = pair.first;
        const vector<int>& values = pair.second;

        cout << "Column " << key << ": ";
        for (int val : values) cout << val << " ";
        cout << endl;
    }
}

void handleMerge(BinaryTree& tree1, BinaryTree& tree2) {
    tree1.merge(tree2);
    cout << "Trees merged successfully.\n";
}

// Display menu options
void displayMenu() {
    cout << "\n=== Menu ===\n";
    cout << "1. Insert a value\n";
    cout << "2. Search for a value\n";
    cout << "3. Level-order traversal\n";
    cout << "4. Maximum path sum\n";
    cout << "5. Reconstruct tree from inorder and postorder\n";
    cout << "6. Vertical order traversal\n";
    cout << "7. Merge two trees\n";
    cout << "8. Find Lowest Common Ancestor\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    BinaryTree tree1, tree2;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            int value;
            cout << "Enter value to insert: ";
            cin >> value;
            tree1.insert(value);
            break;
        }
        case 2: {
            int value;
            cout << "Enter value to search for: ";
            cin >> value;
            cout << (tree1.search(value) ? "Value found!\n" : "Value not found!\n");
            break;
        }
        case 3: handleLevelOrder(tree1); break;
        case 4: handleMaxPathSum(tree1); break;
        case 5: handleReconstructTree(tree1); break;
        case 6: handleVerticalOrder(tree1); break;
        case 7: handleMerge(tree1, tree2); break;
        case 8: {
            int p, q;
            cout << "Enter two values to find their LCA: ";
            cin >> p >> q;
            auto lca = tree1.findLCA(tree1.findLCA(tree1.findLCA(nullptr, p, q), p, q),p,q);
            cout << (lca ? "LCA: " + /*to_string*/(lca->value) : "No LCA found") << endl;
            break;
        }
        case 0: cout << "Exiting program. Goodbye!\n"; break;
        default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
