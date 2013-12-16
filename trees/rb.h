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

#ifndef _RB_H_
#define _RB_H_

#include "tree.h"

/**
 * Implementation of a red-black tree
 */
template<class TKey, class TValue>
class RB: public Tree<TKey, TValue> {
    public:
        // Red-black insertion function.
        // Adapted from Cormen, section 13.3
        void insert(TKey key, TValue value) {
            TreeNode * z = new TreeNode(key, value);
            TreeNode * y, * x;
            y = NULL;
            x = this->root;
            while (x) {
                y = x;
                if (z->key < x->key)
                    x = x->left;
                else
                    x = x->right;
            }
            z->parent = y;
            if (!y) {
                this->root = z;
            }
            else if (z->key < y->key)
                y->left = z;
            else
                y->right = z;
            z->color = RED;
            insert_fixup(z);
        }

    private:
        // typedef the TreeNode so it is available in methods.
        typedef typename Tree<TKey,TValue>::TreeNode TreeNode;

        // Red-black insertion fixup.
        // Maintains the red-black tree property.
        // Adapted from Cormen, section 13.3
        void insert_fixup(TreeNode * z) {
            TreeNode * y;
            while (z && z->parent && z->parent->color == RED) {
                if (z->parent == z->parent->parent->left) {
                    y = z->parent->parent->right;
                    if (y && y->color == RED) {
                        z->parent->color = BLACK;
                        y->color = BLACK;
                        z->parent->parent->color = RED;
                        z = z->parent->parent;
                    }
                    else {
                        if (z == z->parent->right) {
                            z = z->parent;
                            rotate_left(z);
                        }
                        z->parent->color = BLACK;
                        z->parent->parent->color = RED;
                        rotate_right(z->parent->parent);
                    }
                }
                else { 
                    y = z->parent->parent->left;
                    if (y && y->color == RED) {
                        z->parent->color = BLACK;
                        y->color = BLACK;
                        z->parent->parent->color = RED;
                        z = z->parent->parent;
                    }
                    else {
                        if (z == z->parent->left) {
                            z = z->parent;
                            rotate_right(z);
                        }
                        z->parent->color = BLACK;
                        z->parent->parent->color = RED;
                        rotate_left(z->parent->parent);
                    }
                }		
            }
            this->root->color = BLACK;
        };

        // Left-rotates the subtree rooted at x.
        // Adapted from Cormen, section 13.2
        void rotate_left(TreeNode * x) {
            TreeNode * y;
            y = x->right;
            x->right = y->left;
            if (y->left)
                y->left->parent = x;
            y->parent = x->parent;
            if (!(x->parent))
                this->root = y;
            else if (x == x->parent->left)
                x->parent->left = y;
            else
                x->parent->right = y;
            y->left = x;
            x->parent = y;		
        };

        // Right-rotates the subtree rooted at y.
        // Adapted from Cormen, secion 13.2.
        // The reason for using "y" now is because
        // it was easier to read from the figure in the book.
        void rotate_right(TreeNode * y) {
            TreeNode * x;
            x = y->left;
            y->left = x->right;
            if (x->right)
                x->right->parent = y;
            x->parent = y->parent;
            if (!(y->parent))
                this->root = x;
            else if (y == y->parent->left)
                y->parent->left = x;
            else
                y->parent->right = x;
            x->right = y;
            y->parent = x;
        };
};

#endif
