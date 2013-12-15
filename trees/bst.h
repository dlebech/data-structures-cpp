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

#ifndef _BST_H_
#define _BST_H_

#include "tree.h"

/**
 * Implementation of an unbalanced binary search tree
 */
template<class TKey, class TValue>
class BST: public Tree<TKey, TValue> {
    private:
        // typedef the TreeNode so it is available in methods.
        typedef typename Tree<TKey,TValue>::TreeNode TreeNode;

    public:
        // Puts a new node into the BST with the given key and value,
        // maintaining the binary search tree property If the height of the
        // tree is h, this operation is O(h).
        // Adapted from Cormen et. al., section 12.3
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
            if (!y)
                this->root = z;
            else if (z->key < y->key)
                y->left = z;
            else
                y->right = z;
        };
};

#endif
