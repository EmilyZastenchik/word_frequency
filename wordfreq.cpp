/*Emily Zastenchik
Programming Assignment 4


*/

#include<cstdlib>
#include<iostream>
#include<cmath> //for log function
#include "wordscollection.h"
#include "frequency.h"
#include "bintree.h"
using namespace FREQPROJ;
//Postcondition: inserts nodes into BST alphabetically
template <class String_thing>
void insert(binary_tree_node<frequency <String_thing>>*& root, frequency<String_thing>& item);
//Postcondition: inserts nodes into BST based on word count
template<class Token>
void insert(binary_tree_node<frequency<Token>>* root, binary_tree_node<frequency<Token>>* newnode);
//Postcondition: outputs BST nodes in a list form using inorder traversing
template<class T1>
void printTree(binary_tree_node<T1> *root);
//Postcondition: resets node data for word count ordered BST
template<class T1>
binary_tree_node<frequency<T1>>* orderTree(binary_tree_node<frequency<T1>>* root, binary_tree_node<frequency<T1>>* &other_root);
int main(int argc, char* argv[]) {

	for (int argi = 1; argi < argc; ++argi)
	{
		binary_tree_node <frequency<std::string>>* root = NULL;//root for alphabetical tree
		binary_tree_node <frequency<std::string>>* newroot = NULL;//root for word frequency tree
		wordscollection wc = wordscollection(argv[argi]); //puts tokens in words queue

		while (wc.hasTokens())	//words queue not empty
		{
			frequency<std::string> a = frequency<std::string>(wc.getNextToken());//makes a frequency object with text file tokens
			insert(root, a);//adds nodes to alphabetical BST

		}//end while

		std::cout << "WORD FREQUENCY - Alphabetical" << std::endl;
		printTree(root);	//prints BST in sequential list using inOrder traversal
		std::cout << std::endl << std::endl;
		std::cout << "WORD FREQUENCY - Highest to Lowest" << std::endl;
		//newroot = tree_copy(root);	//copies nodes from alphabetical tree to word frequency tree

		orderTree(root, newroot);//re-order nodes for word frequency tree
		printTree(newroot);//print tree
		tree_clear(root);	//clear tree for next txt file


	}//end for
	return 0;
}
template <class String_thing>//alphabetical bst insert
void insert(binary_tree_node<frequency<String_thing>>*& root, frequency<String_thing>& item)
{
	if (!root) //root == NULL//empty tree
	{
		root = new binary_tree_node<frequency <String_thing>>(item);//make new node
	}
	else
	{
		//item token == root node token
		if (item.data() == root->data().data())  //root->data().isData(item.data()) //repeated token, update frequency
		{
			++root->data();
		}
		else if (item.data() < root->data().data())	//make left node
		{
			if (!root->left())//if left is NULL, make newnode
			{
				root->set_left(new binary_tree_node <frequency<String_thing>>(item));
				return;
			}
			
			binary_tree_node <frequency<String_thing>>* pass = root->left(); //else 
			insert(pass, item);
		}
		else// if(item.data() > root->data().data()) //make right node
		{
			if (!root->right())
			{
				root->set_right(new binary_tree_node <frequency <String_thing>>(item));//if right is NULL make newnode
				return;
			}

			binary_tree_node<frequency<String_thing>>* current_ptr = root->right();
			insert(current_ptr, item);
		}
	}
}
template<class Token>//insert into bst based on token frequency
void insert(binary_tree_node<frequency<Token>>* root, binary_tree_node<frequency<Token>>* newroot)
{
	
	
	if (!root)//when the root pointer to the newnode of NULL, nothing needs to be inserted
	{
		return;
	}
	else if (root->data().isData(newroot->data().data()))//or if newnode points to root node   //item token == root node token
		return;
	else if ((!root->left()) && (!root->right()))//leaf node
	{
		if (newroot->data().count() >= root->data().count())//make right node
		{
			binary_tree_node<frequency<Token>>* newnode = new binary_tree_node <frequency<Token>>(root->right()->data());
			root->set_right(newnode);
			return;
		}
		else if (newroot->data().count() < root->data().count())//else make a left node
		{
			binary_tree_node<frequency<Token>>* newnode = new binary_tree_node <frequency<Token>>(root->left()->data());
			root->set_left(newnode);
			return;
		}
	}
	else if ((newroot->data().count() >= root->data().count()) && (!root->left()))
	{
		if (root->left()!= NULL)
			insert(newroot, root->left());
		else{
		binary_tree_node<frequency<Token>>* newnode = new binary_tree_node<frequency<Token>>(newroot->data());
		root->set_right(newroot);
		return;
		}
	}
	else if ((newroot->data().count() < root->data().count()) && (!root->right()))
	{
		if (root->right()!= NULL)
			insert(newroot, root->right());
		else {
		binary_tree_node<frequency<Token>>* newnode = new binary_tree_node<frequency<Token>>(newroot->data());
		root->set_left(newroot);
		return;
		}
	}
		
}
template<class T1>
binary_tree_node<frequency<T1>>* orderTree(binary_tree_node<frequency<T1>>* root, binary_tree_node<frequency<T1>>*& newroot)
{
	if (root!=NULL)
	{
		orderTree(root->left(), newroot);
		if (!newroot)
		{
			newroot = new binary_tree_node<frequency<T1>>(root->data());
		}
		insert(root, newroot);
		orderTree(root->right(), newroot);
	}

	return newroot;
}
template<class T1>
void printTree(binary_tree_node<T1> *root)
{
	if (root->left() != NULL)
	{
		printTree(root->left());
	}
	std::cout << root->data() << " ";
	if (root->right() != NULL)
	{
		printTree(root->right());
	}
	else return;
}
