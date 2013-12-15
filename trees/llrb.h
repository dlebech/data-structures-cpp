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

#ifndef _LLRB_H_
#define _LLRB_H_

#include "tree.h"

/**
 * Implementation of a balanced left-leaning red-black tree.
 */
template<class TKey, class TValue>
class LLRB: public Tree<TKey, TValue> {
    public:
        void insert(TKey key, TValue value) {
            // If the root does not exist, create it.
            // Otherwise insert recursively at the root.
            TreeNode * x = new TreeNode(key, value);
            if (!(this->root))
                this->root = x;
        	else
        		this->root = insert(this->root, key, value);
        }

    private:
        // typedef the TreeNode so it is available in methods.
        typedef typename Tree<TKey,TValue>::TreeNode TreeNode;
        
        TreeNode * insert(TreeNode * h, TKey key, TValue value) {
            // Bottom of the recursion -- return a new node.
        	if (!h) {
        		TreeNode * x = new TreeNode(key, value, RED);
        		return x;
            }
        
            // If both left and right child color is RED then perform a color
            // flip.
        	if (h->left && h->left->color == RED && 
                h->right && h->right->color == RED)
        		color_flip(h);
        
            // Go down the left subtree.
        	if (key < h->key)
        		h->left = insert(h->left, key, value);
        	else
        		h->right = insert(h->right, key, value);
        
        	if (h->right && h->right->color == RED)
        		h = rotate_left(h);
        
        	if (h->left->color == RED && 
                h->left->left && h->left->left->color == RED)
        		h = rotate_right(h);
        
        	return h;
        };
        
        // Left rotates the subtree rooted at h
        TreeNode * rotate_left(TreeNode * h) {
        	TreeNode * x;
        	x = h->right;
        	h->right = x->left;
        	x->left = h;
        	x->color = x->left->color;
        	x->left->color = RED;
        	return x;
        };
        
        // Right rotates the subtree rooted at h
        TreeNode * rotate_right(TreeNode * h) {
        	TreeNode * x;
        	x = h->left;
        	h->left = x->right;
        	x->right = h;
        	x->color = x->right->color;
        	x->right->color = RED;
        	return x;
        };
        
        // Swaps the colors of the node x and its children
        TreeNode* color_flip(TreeNode* x) {
        	x->color = !x->color;
        	x->left->color = !x->left->color;
        	x->right->color = !x->right->color;
        	return x;
        };
};

#endif
