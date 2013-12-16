/**
 * Copyright (c) 2013 David Volquartz Lebech
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef _TREE_H_
#define _TREE_H_

#include <string>
#include <sstream>
#include <algorithm>

const bool RED = true;
const bool BLACK = false;

template<typename T>
std::string to_string(T value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

// An abstract tree implementation.
template<class TKey, class TValue>
class Tree {
    protected:
        // A node in the tree.
        struct TreeNode {
            TKey key;
            TValue value;
            bool color;
            TreeNode * left;
            TreeNode * right;
            TreeNode * parent;
            TreeNode() {
                left = NULL;
                right = NULL;
                parent = NULL;
                color = BLACK;
            };
            TreeNode(TKey key, TValue value) {
                left = NULL;
                right = NULL;
                parent = NULL;
                color = BLACK;
                this->key = key;
                this->value = value;
            };
            TreeNode(TKey key, TValue value, bool color) {
                left = NULL;
                right = NULL;
                parent = NULL;
                this->color = color;
                this->key = key;
                this->value = value;
            }
        };

        TreeNode * root = NULL;

    public:
        virtual void insert(TKey key, TValue value) = 0;

        // Prints all nodes in tree.
        // Linear time, O(n).
        std::string inorder_tree_walk() {
            return inorder_tree_walk(this->root);
        };

        // Prints all nodes in the subtree of x in order.
        // Linear time, O(n).
        std::string inorder_tree_walk(TreeNode * x) {
            std::ostringstream os;
            if (x) {
                os << inorder_tree_walk(x->left);
                os << to_string(x->key) + ": " + to_string(x->value) << std::endl;
                os << inorder_tree_walk(x->right);
            }
            return os.str();
        };

        // Searches (recursively) for a specific key in the subtree of x.
        // If the height of the tree is h, this operation is O(h).
        // Adapated from Cormen et. al., section 12.2
        TValue recursive_tree_search(TKey k) {
            return recursive_tree_search(this->root, k);
        };

        TValue recursive_tree_search(TreeNode * x, TKey k) {
            if (x && x->key == k)
                return x->value;

            if (k < x->key)
                return recursive_tree_search(x->left, k);
            else
                return recursive_tree_search(x->right, k);
        }

        // Searches (iteratively) for a specific key in the subtree of x.
        // If the height of the tree is h, this operation is O(h). 
        // Adapted from Cormen et. al., section 12.2
        TValue iterative_tree_search(TKey k) {
            TreeNode * x = this->root;
            while (x && x->key != k) {
                if (k < x->key)
                    x = x->left;
                else
                    x = x->right;
            }
            if (x)
                return x->value;
        };

        // Searches for a specific node in the subtree of x and returns the
        // number of steps it takes to get there.
        int count_steps(TKey k) {
            TreeNode * x = this->root;
            int result = 0;
            while (x && x->key != k) {
                result++;
                if (k < x->key)
                    x = x->left;
                else
                    x = x->right;
            }
            if (x && x->key == k)
                return result+1;
            return -1;
        };

        // Find the minimum key in the tree
        // Adapted from Cormen, section 12.2
        TKey tree_minimum() {
            TreeNode * x = this->root;
            while (x->left != NULL)
                x = x->left;
            return x->key;
        }

        // Find the maximum key in the tree
        // Adapted from Cormen, section 12.2
        TKey tree_maximum() {
            TreeNode * x = this->root;
            while (x->right != NULL)
                x = x->right;
            return x->key;
        }

        // Finds the height of the tree.
        // This operation is O(n). A better way is to store the height.
        // Something for the future :-)
        int height() {
            return height(this->root);
        }

        int height(TreeNode * x) {
            if (!x)
                return -1;
            else
                return std::max(height(x->left), height(x->right)) + 1;
        }
};

#endif
