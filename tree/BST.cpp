#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}

bool BST::deepestNodes() {
	int maxlevel = 0, level = 0;
	if (root == NULL)return false; //special case: tree is empty
	else {
		deepestNodes2(root, level, maxlevel); //normal case: to get the deepest level of node
		cout << "The id of student(s)  at the deepest level is" << endl;
		PrintDeep(maxlevel, root); //print out the id when it's in the deepest level
		
	}
	return true;
}

void BST::deepestNodes2(BTNode* cur, int level, int& maxlevel) {
	if (cur != NULL) {
		deepestNodes2(cur->left, level + 1, maxlevel);     //count the height so level + 1
		deepestNodes2(cur->right, level + 1, maxlevel);
		if (level > maxlevel) {                      // compare height in post order
			maxlevel = level;
		}
	}
}

void BST::PrintDeep(int num,BTNode * cur) {
	if (cur == NULL) return;
	PrintDeep(num - 1,cur->left);       //find the deepset node by decrease the deepest height
	PrintDeep(num - 1,cur->right);
	if (num == 0)                        //if it is the deepst height
	{
		cout << cur->item.id << " ";
	}
	
}

bool BST::display(int order, int source) {
	ofstream out;
	
	if (root == NULL) return false;//special case: tree is empty
	else {
		if (order == 1) {

			if (source == 1) inOrderPrint(); //print out the student information in ascending order at terminal

			else if (source == 2) {
				out.open("student-info.txt");
				ASCprintfile(root, out); //print in the student information into "student-info.txt" in ascending order
				out.close();
			}
		}
		else if (order == 2) {
			if (source == 1) DESdisplay(root);//print out the student information in descending order at terminal

			else if (source == 2) {
				out.open("student-info.txt");
				DESprintfile(root,out);//print in the student information into "student-info.txt" in descending order
				out.close();
			}
		
		}
	}
	
	return true;
}
void BST::ASCprintfile(BTNode* cur,ofstream &out) {
	if (cur != NULL) {
		ASCprintfile(cur->left, out);
		cur->item.print(out);
		ASCprintfile(cur->right, out);
	}
}

void BST::DESdisplay(BTNode* cur) {
	if (cur != NULL) {
		DESdisplay(cur->right);
		cur->item.print(cout);
		DESdisplay(cur->left);
	}
}

void BST::DESprintfile(BTNode* cur,ofstream &out) {
	if (cur != NULL) {
		DESprintfile(cur->right,out);
		cur->item.print(out);
		DESprintfile(cur->left,out);
	}
}

bool BST::CloneSubtree(BST t1, type item)
{
	if (t1.root == NULL) //special case: t1 tree is empty
		return false;
	else {
		root = CloneSubtree2(t1.root, item);      //tree2 root point to the bstnode if have found
		if (root != NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

BTNode* BST::CloneSubtree2(BTNode* cur, type item)
{
	BTNode* temp;
	if (cur == NULL) return NULL; //special case: current node is empty
	if (cur->item.id == item.id) // if current node has same id as item.id
	{
		temp = cur; //save the all the information of a student from the current node and return it to last function
		return temp;
	}
	if (item.id < cur->item.id) { //if current id is greater than the type in id

		
		return CloneSubtree2(cur->left, item);   //bst traverse

	}
	else //if current id is less than the type in id
	{
		return CloneSubtree2(cur->right, item);
	}
}

bool BST::printLevelNodes()
{
	Student null;                           //create a student null with -100 id which is imposible occur in student id
	null.id = -100;
	BTNode* temp = new BTNode(null);              //create  an temp btnode to become a flag in later function
	BTNode* cur;
	Queue		    q;
	int i = 1;



	if (empty()) return false; 	// special case
	q.enqueue(root);	//since tree first level only one node so need to insert a flag after insert the first level node
	q.enqueue(temp);    // insert the flag
	cout << "Level " << i << " nodes: ";
	while (true) { 	
		q.dequeue(cur);     //get the node from the tree
		if (cur->item.id != -100) {      // if the node not equal the flag

			cout << cur->item.id << " "; //dislpay the level node
			if (cur->left != NULL)      //insert the level under the node
			{
				q.enqueue(cur->left);            //left node if exist

			}
			if (cur->right != NULL)
			{
				q.enqueue(cur->right);           //right node if exist
			}
		}
		else {                                 // if the node equal the flag
			cout << endl;
			if (q.empty()) break;    
			i++;
			cout << "Level " << i << " nodes: ";   //change the level 
			q.enqueue(temp);                   // if the queue not empty insert new flag 
		}

	}
	return true;
}

bool BST::printPath()
{   

	
	int a[1000];
	int index = 0;
	if (root == NULL) return false; //special case: tree is empty
	
	else {
		cout << "Below are all the external paths for the tree:" << endl;
		cout << endl;
		printexternalpath(root, a, index);
		return true;
	}
}

void BST::printexternalpath(BTNode* cur, int a[], int index)
{
	if (cur == NULL) return; //special case: current node is empty
	a[index] = cur->item.id; //save current node's id into array
	if (cur->left == NULL && cur->right == NULL) //if the node is the last node of the branch
	{
		printArray(a, index);
	}
	printexternalpath(cur -> left, a, index + 1);
	printexternalpath(cur-> right, a, index + 1);

}


void BST::printArray(int a[], int index)
{
	
	for (int i = 0; i <= index; i++)   //print until current branch
	{
		
		cout << a[i] << " ";
	}
	cout << endl;

}

