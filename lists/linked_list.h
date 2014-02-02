/**
 * Copyright (c) 2014 David Volquartz Lebech
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

#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <string>
#include <sstream>
#include "../util.h"

// A double-link linked-list implementation.
template<class TValue>
class LinkedList {
    protected:
        struct LLNode {
            TValue value;
            LLNode * prev;
            LLNode * next;

            LLNode(TValue value) {
                prev = NULL;
                next = NULL;
                this->value = value;
            };
        };

        LLNode * head = NULL;
        LLNode * tail = NULL;

        // Linear search that returns the first node that matches the given
        // value.
        LLNode * search(TValue value) {
            if (this->head) {
                LLNode * curNode = this->head;
                do {
                    if (curNode->value == value)
                        return curNode;
                    curNode = curNode->next;
                }
                while (curNode != this->head);
            }
            return NULL;
        };

    public:
        // Inserts the given value to the end of the list.
        // Constant time insertion, O(1). 
        void insert(TValue value) {
            LLNode * node = new LLNode(value);

            // If there is no head, set the node to be both head and tail and
            // next node. Otherwise append to the end of the list.
        	if (!this->head) {
        		this->head = node;
        		this->tail = node;
        		node->next = node;
        		node->prev = node;
        	}
        	else {
                node->prev = this->tail;
        		node->next = this->head;
        		this->tail->next = node;
                this->head->prev = node;
        		this->tail = node;
        	}
        };

        // Removes the first node that matches the given value.
        // Linear time O(n).
        void remove(TValue value) {
            LLNode * node = this->search(value);
            if (node) {
                node->prev->next = node->next;
                delete node;
            }
        };

        // Returns a string representing all nodes in this linked list.
        std::string printList() {
            std::ostringstream os;
            // Make sure there is at least one node before starting.
            if (this->head) {
                LLNode * curNode = this->head;
                do {
                    os << to_string(curNode->value) << std::endl;
                    curNode = curNode->next;
                }
                while (curNode != this->head);
            }
            return os.str();
        };
};

#endif
