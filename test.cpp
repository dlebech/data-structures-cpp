// Test all the tree implementations.

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <cassert>

#include "trees/bst.h"
#include "trees/rb.h"
#include "trees/llrb.h"

using namespace std;

int main() {
    // Create expected output for out mini-tree.
    ostringstream os;
    os << "1: first" << endl;
    os << "2: second" << endl;
    os << "3: third" << endl;
    os << "4: fourth" << endl;
    os << "5: fifth" << endl;
    string expected = os.str();

    // Test BST.
    // Insert ordered. This gives the worst case (maximum height).
    cout << "Testing BST" << endl;
    BST<int,string> my_tree;
    my_tree.insert(1,"first");
    assert (my_tree.height() == 0);
    my_tree.insert(2,"second");
    assert (my_tree.height() == 1);
    my_tree.insert(3,"third");
    assert (my_tree.height() == 2);
    my_tree.insert(4,"fourth");
    assert (my_tree.height() == 3);
    my_tree.insert(5,"fifth");
    assert (my_tree.height() == 4);
    
    // Test the tree order
    string actual = my_tree.inorder_tree_walk();
    assert (actual == expected);

    // Insert backwards ordered. This also gives worst case (maximum height).
    my_tree = * new BST<int,string>;
    my_tree.insert(5,"fifth");
    assert (my_tree.height() == 0);
    my_tree.insert(4,"fourth");
    assert (my_tree.height() == 1);
    my_tree.insert(3,"third");
    assert (my_tree.height() == 2);
    my_tree.insert(2,"second");
    assert (my_tree.height() == 3);
    my_tree.insert(1,"first");
    assert (my_tree.height() == 4);

    // Test the tree order
    actual = my_tree.inorder_tree_walk();
    assert (actual == expected);

    // Insert "randomly". This gives a better height.
    my_tree = * new BST<int,string>;
    my_tree.insert(3,"third");
    assert (my_tree.height() == 0);
    my_tree.insert(1,"first");
    assert (my_tree.height() == 1);
    my_tree.insert(5,"fifth");
    assert (my_tree.height() == 1);
    my_tree.insert(2,"second");
    assert (my_tree.height() == 2);
    my_tree.insert(4,"fourth");
    assert (my_tree.height() == 2);

    // Test the tree order
    actual = my_tree.inorder_tree_walk();
    assert (actual == expected);

    cout << "BST OK" << endl;

    // Test RB.
    // Insert ordered
    cout << "Testing RB" << endl;
    RB<int,string> my_rb_tree;
    my_rb_tree.insert(1,"first");
    my_rb_tree.insert(2,"second");
    my_rb_tree.insert(3,"third");
    my_rb_tree.insert(4,"fourth");
    my_rb_tree.insert(5,"fifth");
    actual = my_rb_tree.inorder_tree_walk();
    assert (actual == expected);

    // Insert backwards ordered
    my_rb_tree = * new RB<int,string>;
    my_rb_tree.insert(5,"fifth");
    my_rb_tree.insert(4,"fourth");
    my_rb_tree.insert(3,"third");
    my_rb_tree.insert(2,"second");
    my_rb_tree.insert(1,"first");
    actual = my_rb_tree.inorder_tree_walk();
    assert (actual == expected);

    // Insert "randomly"
    my_rb_tree = * new RB<int,string>;
    my_rb_tree.insert(3,"third");
    my_rb_tree.insert(1,"first");
    my_rb_tree.insert(5,"fifth");
    my_rb_tree.insert(2,"second");
    my_rb_tree.insert(4,"fourth");
    actual = my_rb_tree.inorder_tree_walk();
    assert (actual == expected);

    // Insert a lot of elements to see if the height property holds.
    int array_size = 100000;
    double max_height = 2*log2((double)(array_size+1));
    cout << "With " << array_size << " elements, max height should be: " << max_height << endl;

    my_rb_tree = * new RB<int,string>;
    int keys [array_size];
    for (int i = 0; i < array_size; i++) {
        my_rb_tree.insert(i, "");
        keys[i] = i;
    }

    assert (my_rb_tree.tree_minimum() == 0);
    assert (my_rb_tree.tree_maximum() == (array_size-1));

    double height = (double)my_rb_tree.height();
    cout << "Tree height (sorted keys): " << height << endl;
    assert (height <= max_height);

    // Try and shuffle the elements and make another big tree.
    random_shuffle(&keys[0], &keys[array_size-1]);
    my_rb_tree = * new RB<int,string>;
    for (int i = 0; i < array_size; i++) {
        my_rb_tree.insert(keys[i], "");
    }

    assert (my_rb_tree.tree_minimum() == 0);
    assert (my_rb_tree.tree_maximum() == (array_size-1));

    height = (double)my_rb_tree.height();
    cout << "Tree height (shuffled keys): " << height << endl;
    assert (height <= max_height);

    cout << "RB OK" << endl;

    // Test LLRB.
    // Insert ordered
    cout << "Testing LLRB" << endl;
    LLRB<int,string> my_llrb_tree;
    my_llrb_tree.insert(1,"first");
    my_llrb_tree.insert(2,"second");
    my_llrb_tree.insert(3,"third");
    my_llrb_tree.insert(4,"fourth");
    my_llrb_tree.insert(5,"fifth");
    actual = my_llrb_tree.inorder_tree_walk();
    assert (actual == expected);

    // Insert backwards ordered
    my_llrb_tree = * new LLRB<int,string>;
    my_llrb_tree.insert(5,"fifth");
    my_llrb_tree.insert(4,"fourth");
    my_llrb_tree.insert(3,"third");
    my_llrb_tree.insert(2,"second");
    my_llrb_tree.insert(1,"first");
    actual = my_llrb_tree.inorder_tree_walk();
    assert (actual == expected);

    // Insert "randomly"
    my_llrb_tree = * new LLRB<int,string>;
    my_llrb_tree.insert(3,"third");
    my_llrb_tree.insert(1,"first");
    my_llrb_tree.insert(5,"fifth");
    my_llrb_tree.insert(2,"second");
    my_llrb_tree.insert(4,"fourth");
    actual = my_llrb_tree.inorder_tree_walk();
    assert (actual == expected);

    // Insert a lot to see if the height property holds.
    cout << "With " << array_size << " elements, max height should be: " << max_height << endl;

    my_llrb_tree = * new LLRB<int,string>;
    for (int i = 0; i < array_size; i++) {
        my_llrb_tree.insert(i, "");
        keys[i] = i;
    }

    assert (my_llrb_tree.tree_minimum() == 0);
    assert (my_llrb_tree.tree_maximum() == (array_size-1));

    height = (double)my_llrb_tree.height();
    cout << "Tree height (sorted keys): " << height << endl;
    assert (height <= max_height);

    // Try and shuffle the elements and make another big tree.
    random_shuffle(&keys[0], &keys[array_size-1]);
    my_llrb_tree = * new LLRB<int,string>;
    for (int i = 0; i < array_size; i++) {
        my_llrb_tree.insert(keys[i], "");
    }

    assert (my_llrb_tree.tree_minimum() == 0);
    assert (my_llrb_tree.tree_maximum() == (array_size-1));

    height = (double)my_llrb_tree.height();
    cout << "Tree height (shuffled keys): " << height << endl;
    assert (height <= max_height);

    cout << "LLRB OK" << endl;
}
