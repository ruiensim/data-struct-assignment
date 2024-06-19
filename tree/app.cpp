#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	"BST.h"
#include    "Student.h"

using namespace std;

bool readFile(const char *, BST *);
int menu();


int main() {
    
	BST* tree1 = new BST;
	BST* tree2 = new BST;
	
	Student a;
	int order;
	int location;
	int value;
	int select;
	do
	{
		select = menu();
		switch (select)
		{
		case 1:
			readFile("student.txt", tree1);
			break;


		case 2:

			if (tree1->deepestNodes())
			{
				cout << endl;
			}
			else
			{
				cout << "The tree is empty. " << endl;
			}
			break;


		case 3:
			cout << "Print in ascending order press 1, print in descending order press 2." << endl;
			cin >> order;
			cout << "Print in terminal press 1, print in student-info.txt press 2." << endl;
			cin >> location;
			if (tree1->display(order, location))
			{

			}
			else
			{
				cout << "The tree is empty." << endl;
			}
			break;
			
		case 4:
			cout << "Insert the student id  which intend to clone." << endl;
			cin >> value;
			a.id = value;
			tree2 = new BST;
			if (tree2->CloneSubtree(*tree1, a))
			{
				cout << "Tree 1" << endl;
				tree1->preOrderPrint();
				cout << endl;
				cout << "Tree 2" << endl;
				tree2->preOrderPrint();
				cout << endl;
			}
			else
			{
				cout << "Cannot clone subtree." << endl;
			}
			break;
			

		case 5:

			if (tree1->printLevelNodes())
			{
				cout << endl;
			}
			else
			{
				cout << "The tree is empty." << endl;
			}
			break;

		case 6:
			if (tree1->printPath())
			{
				cout << endl;
			}
			else
			{
				cout << "The tree is empty." << endl;
			}
			break;
			

		

		}
	} while (select != 7);
	system("pause");
	return 0;
}

bool readFile(const char* filename, BST* t1)
{
	ifstream inFile(filename);
	Student newStu;//store student information to be inserted into BST
	string bin;//store unwanted string
	int count=0;//count the records inserted into BST from file
	if (!inFile) return false;//file not found
	while (!inFile.eof())
	{
		for (int n = 0; n < 3; n++)inFile >> bin;
		inFile >> newStu.id;
		count++;
		for (int n = 0; n < 2; n++)inFile >> bin;
		inFile.ignore();
		inFile.getline(newStu.name, 30);
		for (int n = 0; n < 2; n++)inFile >> bin;
		inFile.ignore();
		inFile.getline(newStu.address, 100);
		for (int n = 0; n < 2; n++)inFile >> bin;
		inFile >> newStu.DOB;
		for (int n = 0; n < 3; n++)inFile >> bin;
		inFile >> newStu.phone_no;
		for (int n = 0; n < 2; n++)inFile >> bin;
		inFile >> newStu.course;
		for (int n = 0; n < 2; n++)inFile >> bin;
		inFile >> newStu.cgpa;
		t1->insert(newStu);
	}
			
	
	inFile.close();
	cout << endl << count << " student record(s) successfully read from " << filename << endl;
	return true;
}
int menu()
{
	int insert;
	cout << "==============================================================\n" << "\t\t\tMenu\n" << "==============================================================";
	cout << endl;
	cout << endl;

	cout << "(1) Read data to BST" << endl;
	cout << "(2) Print deepest nodes" << endl;
	cout << "(3) Display student " << endl;
	cout << "(4) Clone Subtree" << endl;
	cout << "(5) Print Level Nodes" << endl;
	cout << "(6) Print Path" << endl;
	cout << "(7) Exit" << endl<<endl;
	cout << "Enter your choice:" << endl;
	cin >> insert;
	return insert;

}