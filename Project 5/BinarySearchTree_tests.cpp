// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
#include <sstream>
using namespace std;

TEST(copy_nodes_impl_w_copy_ctr_nonempty_tree) {
	BinarySearchTree<int> tree;
	tree.insert(9);
	tree.insert(7);
	tree.insert(5);
	tree.insert(3);
	tree.insert(12);
	tree.insert(15);

	BinarySearchTree<int> tree2(tree);
	ASSERT_TRUE(tree.size() == tree2.size());
	ASSERT_TRUE(tree.height() == tree2.height());
	ASSERT_FALSE(tree2.empty());
}

TEST(empty_impl_w_empty_empty_tree) {
	BinarySearchTree<int> tree;
	ASSERT_TRUE(tree.empty());
}

TEST(empty_impl_w_empty_nonempty_tree) {
	BinarySearchTree<int> tree;
	tree.insert(9);
	tree.insert(7);
	tree.insert(5);
	tree.insert(3);
	tree.insert(12);
	tree.insert(15);

	ASSERT_FALSE(tree.empty());
}

TEST(height_impl_w_height_empty_tree) {
	BinarySearchTree<int> tree;
	ASSERT_TRUE(tree.height() == 0);
}

TEST(height_impl_w_height_lopsided_nonempty_tree) {
	BinarySearchTree<int> tree;
	tree.insert(9);
	tree.insert(7);
	tree.insert(5);
	tree.insert(3);
	tree.insert(12);
	tree.insert(15);

	ASSERT_TRUE(tree.height() == 4);

}

TEST(size_impl_w_size_empty_tree) {
	BinarySearchTree<int> tree;
	ASSERT_TRUE(tree.size() == 0);
}

TEST(size_impl_w_size_nonempty_tree) {
	BinarySearchTree<int> tree;
	tree.insert(9);
	tree.insert(7);
	tree.insert(5);
	tree.insert(3);
	tree.insert(12);
	tree.insert(15);

	ASSERT_TRUE(tree.size() == 6);

}

//Optional
TEST(size_impl_w_size_lopsided_tree) {
	BinarySearchTree<int> tree;
	tree.insert(9);
	tree.insert(7);
	tree.insert(5);
	tree.insert(3);

	ASSERT_TRUE(tree.size() == 4);
}


TEST(max_element_of_regular_tree) {
	BinarySearchTree<int> tree;
	tree.insert(9);
	tree.insert(7);
	tree.insert(5);
	tree.insert(3);
	tree.insert(12);
	tree.insert(15);
	ASSERT_TRUE(*tree.max_element() == 15);
}

TEST(max_element_of_lopsided_tree) {
	BinarySearchTree<int> tree;
	tree.insert(9);
	tree.insert(7);
	tree.insert(5);
	tree.insert(3);
	ASSERT_TRUE(*tree.max_element() == 9);
}
TEST(max_element_empty) {
	BinarySearchTree<int> tree;
	BinarySearchTree<int>::Iterator end_it = tree.end();

	ASSERT_EQUAL(tree.max_element(), end_it);
}

TEST(min_element_empty) {
	BinarySearchTree<int> tree;
	BinarySearchTree<int>::Iterator end_it = tree.end();

	ASSERT_EQUAL(tree.min_element(), end_it);
}
TEST(min_element_of_lopsided_tree) {
	BinarySearchTree<int> tree;
	tree.insert(9);
	tree.insert(7);
	tree.insert(5);
	tree.insert(3);
	ASSERT_TRUE(*tree.min_element() == 3);
}

TEST(min_element_of_regular_tree) {
	BinarySearchTree<int> tree;
	tree.insert(9);
	tree.insert(7);
	tree.insert(5);
	tree.insert(3);
	tree.insert(12);
	tree.insert(15);
	ASSERT_TRUE(*tree.min_element() == 3);
}

TEST(find_empty) {
	BinarySearchTree<int> tree;
	BinarySearchTree<int>::Iterator end_it = tree.end();

	ASSERT_EQUAL(tree.find(4), end_it);
}

TEST(traverse_preorder_impl_w_nonempty_tree) {
	BinarySearchTree<int> tree;

	tree.insert(9);
	tree.insert(7);
	tree.insert(5);
	tree.insert(3);
	tree.insert(12);
	tree.insert(15);

	ostringstream oss_preorder;
	tree.traverse_preorder(oss_preorder);

	ASSERT_TRUE(oss_preorder.str() == "9 7 5 3 12 15 ");
}

TEST(traverse_preorder_impl_w_1_node_tree) {
	BinarySearchTree<int> tree;

	tree.insert(37);

	ostringstream oss_preorder;
	tree.traverse_preorder(oss_preorder);
	cout << "preorder" << endl;
	cout << oss_preorder.str() << endl << endl;
	ASSERT_TRUE(oss_preorder.str() == "37 ");
}

TEST(traverse_preorder_impl_w_empty_node_tree) {
	BinarySearchTree<int> tree;

	ostringstream oss_preorder;
	tree.traverse_preorder(oss_preorder);
	cout << "preorder" << endl;
	cout << oss_preorder.str() << endl << endl;
	ASSERT_TRUE(oss_preorder.str() == "");
}

TEST(traverse_inorder_impl_w_nonempty_tree) {
	BinarySearchTree<int> tree;

	tree.insert(9);
	tree.insert(7);
	tree.insert(5);
	tree.insert(3);
	tree.insert(12);
	tree.insert(15);

	ostringstream oss_inorder;
	tree.traverse_inorder(oss_inorder);
	cout << oss_inorder.str() << endl << endl;

	ASSERT_TRUE(oss_inorder.str() == "3 5 7 9 12 15 ");
}

TEST(traverse_inorder_impl_w_1_node_tree) {
	BinarySearchTree<int> tree;

	tree.insert(10);

	ostringstream oss_inorder;
	tree.traverse_preorder(oss_inorder);

	cout << oss_inorder.str() << endl << endl;
	ASSERT_TRUE(oss_inorder.str() == "10 ");
}

TEST(traverse_inorder_impl_w_empty_tree) {
	BinarySearchTree<int> tree;


	ostringstream oss_inorder;
	tree.traverse_preorder(oss_inorder);

	cout << oss_inorder.str() << endl << endl;
	ASSERT_TRUE(oss_inorder.str() == "");
}


TEST(check_sorting_invariant_impl_empty) {
	BinarySearchTree<int> tree;

	ASSERT_TRUE(tree.empty());
	ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(check_sorting_invariant_1_element){
	BinarySearchTree<int> tree;
	tree.insert(10);
	ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(check_sorting_invariant_impl_nonempty_tree) {
	BinarySearchTree<int> tree;

	tree.insert(3);

	ASSERT_TRUE(tree.size() == 1);
	ASSERT_TRUE(tree.height() == 1);

	ASSERT_TRUE(tree.find(3) != tree.end());

	tree.insert(7);
	tree.insert(8);

	ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(check_sorting_invariant_impl_1_node_tree) {
	BinarySearchTree<int> tree;

	tree.insert(10);

	ASSERT_TRUE(tree.size() == 1);
	ASSERT_TRUE(tree.height() == 1);

	ASSERT_TRUE(tree.find(10) != tree.end());

	ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(check_sorting_invariant_normal_tree) {
	BinarySearchTree<int> tree;
	tree.insert(5);
	tree.insert(1);
	tree.insert(9);
	tree.insert(3);
	tree.insert(2);
	tree.insert(11);
	tree.insert(6);
	ASSERT_TRUE(tree.check_sorting_invariant()); 
}

TEST(check_sorting_invariant_false) {
	BinarySearchTree<int> tree;
	tree.insert(20);
	tree.insert(9);
	tree.insert(14);
	tree.insert(7);
	tree.insert(8);
	tree.insert(37);
	tree.insert(3);
	tree.insert(1);

	BinarySearchTree<int>::Iterator val = tree.find(37);
	*val = 2;	
	ASSERT_FALSE(tree.check_sorting_invariant());
	*val = 21;
	// val = tree.find(20);
	// *val = 5;
	ASSERT_TRUE(tree.check_sorting_invariant()); 
}

TEST(check_sorting_invariant_false_2) {
	BinarySearchTree<int> treeuno;
	treeuno.insert(20);
	treeuno.insert(9);
	treeuno.insert(14);
	treeuno.insert(7);
	treeuno.insert(8);
	treeuno.insert(37);
	treeuno.insert(3);
	treeuno.insert(1);

	BinarySearchTree<int>::Iterator high = treeuno.max_element();
	*high = 2;
	ASSERT_FALSE(treeuno.check_sorting_invariant());
	
	BinarySearchTree<int> treedos;
	treedos.insert(20);
	treedos.insert(9);
	treedos.insert(14);
	treedos.insert(7);
	treedos.insert(8);
	treedos.insert(37);
	treedos.insert(3);
	treedos.insert(1);
	
	BinarySearchTree<int>::Iterator low = treedos.min_element();
	*low = 40;
	ASSERT_FALSE(treeuno.check_sorting_invariant()); 
}

TEST(min_greater_than_empty) {
	BinarySearchTree<int> tree;
	BinarySearchTree<int>::Iterator end_it = tree.end();

	ASSERT_EQUAL(tree.min_greater_than(1), end_it);
}
TEST(min_greater_than_impl_Iterator_prefix_increment) {
	BinarySearchTree<int> tree;

	tree.insert(9);

	ASSERT_TRUE(tree.size() == 1);
	ASSERT_TRUE(tree.height() == 1);

	ASSERT_TRUE(tree.find(9) != tree.end());

	tree.insert(11);
	tree.insert(5);
	ASSERT_TRUE(tree.check_sorting_invariant());
	ASSERT_TRUE(*tree.max_element() == 11);
	ASSERT_TRUE(*tree.min_element() == 5);
	ASSERT_TRUE(*tree.min_greater_than(9) == 11);

}

TEST(min_greater_than_impl_big_tree) {
	BinarySearchTree<int> tree;

	tree.insert(7);
	tree.insert(20);
	tree.insert(5);
	tree.insert(15);
	tree.insert(10);
	tree.insert(4);
	tree.insert(33);
	tree.insert(2);
	tree.insert(25);
	tree.insert(6);

	ASSERT_EQUAL(*tree.min_greater_than(6), 7);
}

TEST(prefix_2_element_test){
	BinarySearchTree<int> tree;
    
	tree.insert(19);
    tree.insert(37);
    
	BinarySearchTree<int>::Iterator prefix = tree.begin();
    ++prefix; 
    ASSERT_TRUE(*prefix == 37); 
}

TEST(prefix_regular_element_test){
    BinarySearchTree<int> tree;
    tree.insert(20);
    tree.insert(10);
    tree.insert(19);
    tree.insert(9);
    tree.insert(15);
    tree.insert(16);
    tree.insert(12);
    tree.insert(13);
   
    BinarySearchTree<int>::Iterator prefix = tree.begin();
    ++prefix; 
    ASSERT_TRUE(*prefix == 10); 
    ++prefix; 
    ++++prefix;
    cout << *prefix << endl; 
    ASSERT_TRUE(*prefix == 15);
}

TEST(bst_every_function_test) {
	BinarySearchTree<int> tree;

	tree.insert(5);

	ASSERT_TRUE(tree.size() == 1);
	ASSERT_TRUE(tree.height() == 1);

	ASSERT_TRUE(tree.find(5) != tree.end());

	tree.insert(7);
	tree.insert(3);

	ASSERT_TRUE(tree.check_sorting_invariant());
	ASSERT_TRUE(*tree.max_element() == 7);
	ASSERT_TRUE(*tree.min_element() == 3);
	ASSERT_TRUE(*tree.min_greater_than(5) == 7);

	ostringstream oss_preorder;
	tree.traverse_preorder(oss_preorder);

	ASSERT_TRUE(oss_preorder.str() == "5 3 7 ");

	ostringstream oss_inorder;
	tree.traverse_inorder(oss_inorder);

	ASSERT_TRUE(oss_inorder.str() == "3 5 7 ");
}

TEST(Bst_compile_check) {
	BinarySearchTree<int> tree;
	const BinarySearchTree<int>& const_tree = tree;

	BinarySearchTree<int> bst_tree;
	const BinarySearchTree<int>& const_bst_tree = bst_tree;

	tree.insert(100);
	tree.insert(1000);
	tree.insert(10000);
	bst_tree.insert((100));
	bst_tree.insert((1000));
	bst_tree.insert((10000));

	bool b;
	size_t i;
	size_t st;
	string s;

	BinarySearchTree<int>::Iterator it;
	BinarySearchTree<int>::Iterator bst_it;

	BinarySearchTree<int> tree_copy(const_tree);
	BinarySearchTree<int> bst_tree_copy(const_bst_tree);

	tree_copy = const_tree;
	bst_tree_copy = const_bst_tree;

	b = const_tree.empty();
	b = const_bst_tree.empty();
	ASSERT_EQUAL(b, 0);

	i = const_tree.height();
	i = const_bst_tree.height();
	ASSERT_EQUAL(i, 3);

	st = const_tree.size();
	st = const_bst_tree.size();
	ASSERT_EQUAL(st, 3);

	ostringstream tree_tree_inorder;
	ostringstream bst_tree_inorder;
	const_tree.traverse_inorder(tree_tree_inorder);
	const_bst_tree.traverse_inorder(bst_tree_inorder);
	//ASSERT_EQUAL(tree, bst_tree);
	ASSERT_TRUE(tree_tree_inorder.str() == "100 1000 10000 ");
	ASSERT_TRUE(bst_tree_inorder.str() == "100 1000 10000 ");


	ostringstream tree_tree_preorder;
	ostringstream bst_tree_preorder;
	const_tree.traverse_preorder(tree_tree_preorder);
	const_bst_tree.traverse_preorder(bst_tree_preorder);
	//ASSERT_EQUAL(tree, bst_tree);
	//ASSERT_EQUAL(tree, bst_tree);
	ASSERT_TRUE(tree_tree_preorder.str() == "100 1000 10000 ");
	ASSERT_TRUE(bst_tree_preorder.str() == "100 1000 10000 ");

	b = const_tree.check_sorting_invariant();
	b = const_bst_tree.check_sorting_invariant();
	ASSERT_TRUE(const_tree.check_sorting_invariant());
	ASSERT_TRUE(const_bst_tree.check_sorting_invariant());


	it = const_tree.begin();
	bst_it = const_bst_tree.begin();
	//ASSERT_EQUAL(tree, bst_tree);
	ASSERT_TRUE(const_tree.begin() == it);
	ASSERT_TRUE(const_bst_tree.begin() == bst_it);

	it = const_tree.end();
	bst_it = const_bst_tree.end();
	//ASSERT_EQUAL(tree, bst_tree);
	ASSERT_TRUE(const_tree.end() == it);
	ASSERT_TRUE(const_bst_tree.end() == bst_it);

	it = const_tree.min_element();
	bst_it = const_bst_tree.min_element();
	//ASSERT_EQUAL(tree, bst_tree);
	ASSERT_TRUE(const_tree.min_element() == it);
	ASSERT_TRUE(const_bst_tree.min_element() == bst_it);

	it = const_tree.max_element();
	bst_it = const_bst_tree.max_element();
	//ASSERT_EQUAL(tree, bst_tree);
	ASSERT_TRUE(const_tree.max_element() == it);
	ASSERT_TRUE(const_bst_tree.max_element() == bst_it);

	it = const_tree.find(0);
	bst_it = const_bst_tree.find((0));
	//ASSERT_EQUAL(tree, bst_tree);
	ASSERT_TRUE(const_tree.find(0) == it);
	ASSERT_TRUE(const_bst_tree.find(0) == bst_it);

	s = const_tree.to_string();
	s = const_bst_tree.to_string();
	//ASSERT_EQUAL(tree, bst_tree);
	ASSERT_TRUE(const_tree.to_string() == s);
	ASSERT_TRUE(const_bst_tree.to_string() == s);

	it = const_tree.min_greater_than(0);
	bst_it = const_bst_tree.min_greater_than((0));
	//ASSERT_EQUAL(tree, bst_tree);
	ASSERT_TRUE(const_tree.min_greater_than(0) == it);
	ASSERT_TRUE(const_bst_tree.min_greater_than(0) == bst_it);

	it = tree.insert(0);
	bst_it = bst_tree.insert((0));
	//ASSERT_EQUAL(tree, bst_tree);

	it = tree.begin();
	bst_it = bst_tree.begin();
	//ASSERT_EQUAL(tree, bst_tree);

	*it = 50;
	*bst_it = (50);

	++++it;
	++++bst_it;

	it = it++;
	bst_it = bst_it++;

	b = tree.end() == tree.end();
	b = bst_tree.end() == bst_tree.end();
	cout << b << endl;

	b = tree.end() != tree.end();
	b = bst_tree.end() != bst_tree.end();
	cout << b << endl;
}

TEST_MAIN()

