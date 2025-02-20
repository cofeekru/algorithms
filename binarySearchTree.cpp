#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

struct Tree {
	int value;
  int depth;
	Tree* left = nullptr;
	Tree* right = nullptr;
	Tree(int inputValue): value(inputValue) {};
  Tree(int inputValue, int inputDepth): value(inputValue), depth(inputDepth) {};
  Tree() {};
};
void addNode(int value, Tree** root) {
    if (*root == nullptr) {
        *root = new Tree(value);
    } else if (value == (*root)->value) {
        return;
    } else if (value < (*root)->value) {
        addNode(value, &(*root)->left);
    } else {
        addNode(value, &(*root)->right);
    }
}
void addNode(int value, Tree** root, int depth) {
    if (*root == nullptr) {
        *root = new Tree(value, depth);
		    std::cout << (*root)->depth << " ";
    } else if (value == (*root)->value) {
        return;
    } else if (value < (*root)->value) {
        addNode(value, &(*root)->left, depth+1);
    } else {
        addNode(value, &(*root)->right, depth+1);
    }
}
void inorderTraversal(Tree* root) {
  if (root != nullptr) {
    inorderTraversal(root->left);
    std::cout << root->value << " ";
    inorderTraversal(root->right);
  } 
}
void inorderTraversal(Tree* root, std::vector <int>& sortedTree) {
  if (root != nullptr) {
    inorderTraversal(root->left, sortedTree);
    sortedTree.push_back(root->value);
    inorderTraversal(root->right, sortedTree);
  } 
}
void testInorderTraversal() {
  int start = 1;
  int end = 15000000;
  int x;
  std::vector <int> sortedValues;
  Tree* bst = nullptr;
  int n = rand() % (end - start + 1) + start;
  for (size_t i = 0; i < n; i++) {
    x = rand() % (end - start + 1) + start;
    addNode(x, &bst);
  }
  inorderTraversal(bst, sortedValues);
  for (size_t j = 0; j < n - 1; j++) {
    if (sortedValues[j] > sortedValues[j+1]) {
      std::cout << "Error" << "\n";
      for (int& v : sortedValues) {
        std::cout << v << " ";
      }
      
    }
  }
  //std::cout << "Success" << std::endl;
  
}

void outputLeaves(Tree* root) {
  if (root != nullptr && root->right == nullptr && root->left == nullptr) {
    std::cout << root->value << std::endl;
  } else {
    if (root->left) {
      outputLeaves(root->left);
    }
    if (root->right) {
      outputLeaves(root->right);
    } 
  }
}

int searchMaxOfSubtree(Tree* root) {
  while (root->right != nullptr) {
    root = root->right;
  }
  return root->value;
}
int searchSecondMax(int maxValue, Tree* root) {
  int secondMax;
  if (root->value == maxValue) {
    secondMax = searchMaxOfSubtree(root->left);
  } else {
    while (root->right != nullptr && root->right->value != maxValue) {
      root = root->right;
    }
      secondMax = root->value;
    if (root->right->left != nullptr) {
      secondMax = searchMaxOfSubtree(root->right->left);
    }
  }
  
  return secondMax;
}

int depthTree(Tree* root) {
    if (root == nullptr) {
        return 0;
    } else {
        return std::max(depthTree(root->right) + 1, depthTree(root->left) + 1);
    }
};
bool AVLTest(Tree* root) {
	if (root == nullptr) {
		return true;
	}
  int d1 = depthTree(root->right);
  int d2 = depthTree(root->left);
	if (abs(d1 - d2) <= 1) {
		return AVLTest(root->right) && AVLTest(root->left);
	} else {
		return false;
	}
}

int main() 
{
    int value;
    Tree* bst = nullptr;
    std::cin >> value;
    while (value != 0) {
      addNode(value, &bst);
      std::cin >> value;
    }
    if (AVLTest(bst)) {
      std::cout << "YES" << "\n";
    } else {
      std::cout << "NO" << "\n";
    }
	return 0;
}