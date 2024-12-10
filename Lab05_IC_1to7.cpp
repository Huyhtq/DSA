#include <iostream>
#include <queue>
#include <cmath>

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

    TreeNode* deleteNode(TreeNode* node, int value) {
        if (!node) return node;
        if (value < node->value) {
            node->left = deleteNode(node->left, value);
        }
        else if (value > node->value) {
            node->right = deleteNode(node->right, value);
        }
        else {
            if (!node->left) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            TreeNode* temp = findMin(node->right);
            node->value = temp->value;
            node->right = deleteNode(node->right, temp->value);
        }
        return node;
    }

    TreeNode* findMin(TreeNode* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    void preOrder(TreeNode* node) {
        if (!node) return;
        cout << node->value << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    void inOrder(TreeNode* node) {
        if (!node) return;
        inOrder(node->left);
        cout << node->value << " ";
        inOrder(node->right);
    }

    void postOrder(TreeNode* node) {
        if (!node) return;
        postOrder(node->left);
        postOrder(node->right);
        cout << node->value << " ";
    }

    int calculateHeight(TreeNode* node) {
        if (!node) return 0;
        return 1 + max(calculateHeight(node->left), calculateHeight(node->right));
    }

    bool isBalanced(TreeNode* node) {
        if (!node) return true;
        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);
        return abs(leftHeight - rightHeight) <= 1 && isBalanced(node->left) && isBalanced(node->right);
    }

    int diameter(TreeNode* node, int& maxDiameter) {
        if (!node) return 0;
        int leftHeight = diameter(node->left, maxDiameter);
        int rightHeight = diameter(node->right, maxDiameter);
        maxDiameter = max(maxDiameter, leftHeight + rightHeight);
        return 1 + max(leftHeight, rightHeight);
    }

    TreeNode* lowestCommonAncestor(TreeNode* node, int p, int q) {
        if (!node || node->value == p || node->value == q) return node;
        TreeNode* left = lowestCommonAncestor(node->left, p, q);
        TreeNode* right = lowestCommonAncestor(node->right, p, q);
        if (left && right) return node;
        return left ? left : right;
    }

public:
    BinaryTree() : root(nullptr) {}

    void insert(int value) { root = insert(root, value); }
    void deleteValue(int value) { root = deleteNode(root, value); }
    bool search(int value) { return search(root, value) != nullptr; }
    void preOrderTraversal() { preOrder(root); }
    void inOrderTraversal() { inOrder(root); }
    void postOrderTraversal() { postOrder(root); }
    int height() { return calculateHeight(root); }
    bool balanced() { return isBalanced(root); }
    int findDiameter() {
        int maxDiameter = 0;
        diameter(root, maxDiameter);
        return maxDiameter;
    }
    TreeNode* findLCA(int p, int q) { return lowestCommonAncestor(root, p, q); }
};

// Functions to handle each menu option
void handleInsert(BinaryTree& tree) {
    int value;
    cout << "Enter the value to insert: ";
    cin >> value;
    tree.insert(value);
    cout << "Value inserted successfully!\n";
}

void handleDelete(BinaryTree& tree) {
    int value;
    cout << "Enter the value to delete: ";
    cin >> value;
    tree.deleteValue(value);
    cout << "Value deleted successfully!\n";
}

void handleSearch(BinaryTree& tree) {
    int value;
    cout << "Enter the value to search for: ";
    cin >> value;
    cout << (tree.search(value) ? "Value found in the tree!\n" : "Value not found!\n");
}

void handleTraversals(BinaryTree& tree) {
    cout << "1. Pre-order Traversal\n";
    cout << "2. In-order Traversal\n";
    cout << "3. Post-order Traversal\n";
    cout << "Choose a traversal method: ";
    int choice;
    cin >> choice;
    if (choice == 1) tree.preOrderTraversal();
    else if (choice == 2) tree.inOrderTraversal();
    else if (choice == 3) tree.postOrderTraversal();
    else cout << "Invalid choice!\n";
    cout << endl;
}

void handleHeight(BinaryTree& tree) {
    cout << "Height of the tree: " << tree.height() << endl;
}

void handleBalanced(BinaryTree& tree) {
    cout << (tree.balanced() ? "The tree is balanced.\n" : "The tree is not balanced.\n");
}

void handleLCA(BinaryTree& tree) {
    int p, q;
    cout << "Enter two values to find their Lowest Common Ancestor: ";
    cin >> p >> q;
    TreeNode* lca = tree.findLCA(p, q);
    if (lca) cout << "Lowest Common Ancestor: " << lca->value << endl;
    else cout << "No common ancestor found!\n";
}

// Display menu options
void displayMenu() {
    cout << "\n=== Menu ===\n";
    cout << "1. Insert a value\n";
    cout << "2. Delete a value\n";
    cout << "3. Search for a value\n";
    cout << "4. Traverse the tree\n";
    cout << "5. Calculate tree height\n";
    cout << "6. Check if tree is balanced\n";
    cout << "7. Find Lowest Common Ancestor\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";
}
/*
int main() {
    BinaryTree tree;
    int choice;

    do {
        displayMenu();
        cin >> choice;
        switch (choice) {
        case 1: handleInsert(tree); break;
        case 2: handleDelete(tree); break;
        case 3: handleSearch(tree); break;
        case 4: handleTraversals(tree); break;
        case 5: handleHeight(tree); break;
        case 6: handleBalanced(tree); break;
        case 7: handleLCA(tree); break;
        case 0: cout << "Exiting program. Goodbye!\n"; break;
        default: cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
*/