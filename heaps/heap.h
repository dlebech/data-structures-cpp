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

#ifndef _HEAP_H_
#define _HEAP_H_

#include <string>
#include <sstream>
#include "../util.h"

// Implementation of a fixed array-based heap.
// Based on implementation in Cormen, et. al.
template<class TValue>
class Heap {
    protected:
        long heapSize;
        long length;
        TValue * heap;

        // Returns the index of the left child of i.
        // From CLRS, chapter 6
        long left(long i) {
        	return 2*i+1;
        };

        // Returns the index of the right child of i.
        // From CLRS, chapter 6
        long right(long i) {
        	return 2*i+2;
        };

        // Returns the index of the parent of i.
        // Note: In C++, integer division automatically rounds down.
        // From CLRS, chapter 6
        long parent(long i) {
        	return (i-1)/2;
        };

        // Maintains the max-heap property for the node at index i
        // From CLRS, chapter 6
        void maxHeapify(long i) {
        	long l = this->left(i);
        	long r = this->right(i);
        	long largest = 0;
        	if (l <= this->heapSize-1 && this->heap[l] > this->heap[i])
        		largest = l;
        	else
        		largest = i;
        	if (r <= this->heapSize-1 && this->heap[r] > this->heap[largest])
        		largest = r;
        	if (largest != i) {
        		TValue temp = this->heap[i];
        		this->heap[i] = this->heap[largest];
        		this->heap[largest] = temp;
        		this->maxHeapify(largest);
        	}
        };

        // Builds a max-heap for A.
        // From CLRS, chapter 6
        void buildMaxHeap() {
        	this->heapSize = this->length;
        	for (long i = this->length/2-1; i >= 0; i--) {
        		this->maxHeapify(i);
        	}
        };

    public:
        // Constructor.
        // All values of the heap currently have to be given here.
        Heap(TValue heap[], long length, long heapSize) {
            this->heap = heap;
            this->length = length;
            this->heapSize = heapSize;
        };

        // Implentation of heapsort
        // From CLRS, chapter 6
        void heapSort() {
        	this->buildMaxHeap();
        	for (long i = this->length-1; i >= 1; i--) {
        		TValue temp = this->heap[i];
        		this->heap[i] = this->heap[0];
        		this->heap[0] = temp;
        		this->heapSize--;
        		this->maxHeapify(0);
        	}
        };

        // Returns a string representing all value in this heap.
        std::string printHeap() {
            std::ostringstream os;
            // Make sure there is at least one node before starting.
            if (this->heap) {
                for (long i = 0; i < this->length; i++) {
                    os << to_string(this->heap[i]) << std::endl;
                }
            }
            return os.str();
        };
};

#endif
