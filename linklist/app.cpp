#include	<iostream>
#include    <iomanip>
#include	<fstream>
#include	"List.h"
#include	"Student.h"
#include    "Exam.h"
#include    "Subject.h"
#include    "Node.h"
#include    <string>
#include   <cctype>


using namespace std;

bool CreateStuList(const char *, List *);
bool DeleteStudent(List *, char *);
bool DisplayStudent(List, int);
bool AddExamResult(const char *, List *);
bool FilterStudent(List, List *, char *, int, int);
bool recalculateResult(List, char *);
bool checkEligibleFYP(List, char *);
int menu();
bool Redundant(List , Student );
double GradePoint();
const char *getGrade();
double GetGradePoint(double );
const char *GetGrade(double );
void print(Node*cur);
void printStudent(Node*cur);


using namespace std;


int main(){
    
	List *list1 = new List; // create two dynamic list pointer 
	List *list2 = new List;
	// below is use to gap input
	int input;
	int input2;
	char b[100];
	char id[12];
	char course[3];
	int year;
	int totalcredit;		
	int select;
	 do
	 {
	 	select = menu();
	 	switch(select)
		{
			case 1: 
			
				CreateStuList("student.txt",list1);
				break;
		

			case 2:
				
				cout << "Enter the id to delete " << endl;
				cin >> id;
				DeleteStudent(list1,id);
				break;
		

			case 3:
				cout << "Display in terminal input(1), Dispaly in textfile input (2)" << endl;
				cin >> input;
				cout << "Display list1, input (1), Display list 2,input(2)" << endl;
				cin >> input2;
				if(input2 == 1)
				{
					DisplayStudent(*list1,input);
				}
				else if(input2 == 2)
				{
					DisplayStudent(*list2,input);
				}
				break;
		
			case 4:
				
				
				if (AddExamResult("exam.txt", list1))
				{
					cout << "Insert Successfully" << endl;
				}
				else
				{
					cout << "Unable to insert" << endl;
				}
				
				break;
		
			case 5:
			
				cout <<"Enter the student id to recalculate result based on revised grading: " << endl;
				cin >> id;
				recalculateResult(*list1,id);
				break;
		
			case 6:
				cout << "Enter the Course which itend to filter" << endl;
				cin >> course;
				cout << "Enter the year which itend to filter" << endl;
				cin >> year;
		
				cout << "Enter the totalcredit which itend to filter" << endl;
				cin >> totalcredit;
				if(list2->count >= 0) // to clear the list for new filter
				{   
					free (list2);
					list2 = new List;
				}
				FilterStudent(*list1,list2,course,year,totalcredit);
				if(list2->count >=1) //display list2
				{
					DisplayStudent(*list2,1);
				}
				else
				{
					cout << "There are not student under those criteria. " << endl;
				}
				break;
		
			case 7:
				
				cout << "Enter the student id to check if eligible to take FYP: " << endl;
				cin >> id;
				checkEligibleFYP(*list1,id);
				break;
		
		}	
	 }while(select!= 8);

	return 0;
}






bool CreateStuList(const char * textfile, List * a)
{

   ifstream in;
    bool A; 
   	Student b; // use to save input student information temporaly
   	char s[200]; // grab the blank
   	in.open(textfile);
	
   if(in)
   { 
	 while(!in.eof()) // each loop mean one student
	 {  
		// grab by the student file format and insert to b 
	 	for(int i = 0; i < 3; i++)
		 {
			in >> s;
	 	}
		 in >> b.id;
	 	for(int i = 0; i < 2; i++)
	 	{
			in >> s;
	 	}
	 	in.ignore();
		in.getline(b.name, 30);
	 	for(int i = 0; i < 2; i++)
	 	{
			in >> s;
	 	}
	 	in >> b.course;
	 	for(int i = 0; i < 3; i++)
	 	{
			in >> s;
	 	}
		in >> b.phone_no;
	 	in.ignore();
		
	 	in.getline(s, 30);
		A = Redundant(*a,b);
        if(!A)       // insert if not redundant
		{
			a -> insert(b);
		}
		
		
	 }
	 cout << "Insert Successfully" << endl;
	 cout << endl;
	 return true;
   }    
   else
   {
	  cout << "Unable to open the " << textfile << endl;
	  cout << endl;
	  return false;
   }
   in.close();
  
}

bool Redundant(List list, Student target) {


	for (int i = 1; i <= list.count; i++) {
		Student p;
		list.get(i, p);
		if (p.compareID(target)) {
			
			return true;
		}
	}

	return false;
}
bool DeleteStudent(List *list, char * a)
{
   if(list ->count <= 0)
   {
	 cout << "The list a is empty" << endl;
	 return false;
   }
   for (int i = 1; i <= list -> count; i++) // traverse the list to compare
    {
		Student p;
		list -> get(i, p);
		if (strcmp(a, p.id) == 0)
		{
			list -> remove(i);
			return true;
		}

		
	}
	cout << "Student with id " << a << " is not inside the list" << endl;
	return false;
	

}


bool AddExamResult(const char* filename, List* a) {
	char id[12];
	
	ifstream in;
	char s[1000]; // grab the blank
	Exam b;     // use to save input exam information temporaly in order to insert in  exam array
	Subject c;  // use to save input subject information temporaly in order to insert in  subject array
	if(a->count <= 0)
	{
		cout << "The list is empty" << endl;
		return false;
	}
	in.open(filename);
	if (in) 
	{       Node * cur = a -> head;
		    for(int i = 1; i <= a->count; i++) // to make sure not have the duplicate insert in exam after few time of call in menu
			{
				cur ->item.exam_cnt = 0;
				cur = cur -> next;
			}
		    while(!in.eof()) // one loop mean a student each exam
			{
			Node *cur = a -> head; //because every time need to traverse from first node because  one student can have many exam
            in >> id; // use to compare with student id to insert
			// insert value in exam b
            in >> b.trimester;
            in >> b.year;
            in >> b.numOfSubjects;
			
            for (int i = 1; i <= a -> count; i++) // travese the list
            {
                
                if(strcmp((cur->item.id),id)==0) // check is that student?
                {   
					
                    cur ->item.exam[(cur->item.exam_cnt)] = b; // insert in that student which we intend to found
                    for(int a = 0; a < b.numOfSubjects ; a++) // travese to get input of subject from exam.txt and input in subject array 
                    {
                        // insert value in subject c
                        in >> c.subject_code;
                        in >> c.subject_name;
                        in >> c.credit_hours;
                        in >> c.marks;
						
						
						cur ->item.exam[(cur->item.exam_cnt)].sub[a] = c; //insert subject in exam
						
						
						

                    }
					cur ->item.exam[(cur->item.exam_cnt)].calculateGPA(); // calculate gpa
					cur->item.exam_cnt++;
					cur->item.calculateCurrentCGPA(); //calculate cgpa
					
					
					break;
                    
                }
				
				cur = cur -> next;
        
            }
            if(cur == NULL) //grab the rest input if the student is not in the list and not inset 
            {
                for(int i = 0; i < b.numOfSubjects ; i++)
                {
                        
                    in >> c.subject_code;
                    in >> c.subject_name;
                    in >> c.credit_hours;
                    in >> c.marks;

                        

                 }
            }
			in.getline(s,30);
                                        
                    
			  	
			}
			return true;		
	}
	else 
	{
		cout << "Unable to open  a" << filename << endl;
		return false;
		
	}
	
	
}

bool DisplayStudent(List a, int b)
{
   if(a.count == 0)
   {    
		cout << "The list is empty" << endl;
		return false;
   }
  if(b == 1)//input in terminal
  {
	Node *cur = a.head;
	for(int i = 1; i <= a.count; i++) //traverse the list to cout all the student in list
	{
		cout<< "******************************************************STUDENT"<< i << "******************************************************" << endl;
		cout << endl;
		cout << endl;
		cur ->item.print(cout); // cout the student information such as name ,id
		cout << endl;
		cout << endl;
		cout << "--------------------------------------------------PAST EXAM RESULT:--------------------------------------------------" << endl;
		cout << endl;
		if(cur->item.exam_cnt == 0)
		{
			cout << "“THIS STUDENT HAVEN’T TAKEN ANY EXAM YET”" << endl;
		}
		else
		{
			for(int a = 0; a < cur -> item.exam_cnt; a++)
			{
				cur ->item.exam[a].print(cout); // cout the exam, subject and grade
			}
		}
		cout<< "******************************************************STUDENT"<< i << "******************************************************" << endl;
		cout << endl;
		cout << endl;
		cur = cur -> next;
   }
   return true;

  }
  else if(b == 2) // input in textfile
  {
	ofstream out;
	out.open("student_result.txt");
	if(out)
	{
		Node *cur = a.head;
		for(int i = 1; i <= a.count; i++)
		{
			out<< "******************************************************STUDENT"<< i << "******************************************************" << endl;
			out << endl;
			out << endl;
			cur ->item.print(out);
			out << endl;
			out << endl;
			out << "--------------------------------------------------PAST EXAM RESULT:--------------------------------------------------" << endl;
			out << endl;
			if(cur->item.exam_cnt == 0)
			{
				out << "“THIS STUDENT HAVEN’T TAKEN ANY EXAM YET”" << endl;
			}
			else{
				for(int a = 0; a < cur -> item.exam_cnt; a++)
					{
						cur ->item.exam[a].print(out);
					}
				}
			out<< "******************************************************STUDENT"<< i << "******************************************************" << endl;
			out << endl;
			out << endl;
			cur = cur -> next;
   		}
		out.close();
		return true;
	}
	else
	{
		cout << "Unable to open student_result.txt" << endl;
		return false;
	}
	
  }
  return false; // if not insert 1 or 2
} 
bool recalculateResult(List a, char *b)
{   if(a.count <= 0)
	{
		cout << "The list is empty" << endl;
		return false;
	}
	Node* cur = a.head;
    for (int i = 1; i <=  a.count; i++) // traverse the list to check every student
	{
		if(strcmp(cur->item.id, b) == 0) // check the student id of every student with fucntion id
		{
			if(cur->item.exam_cnt == 0) // if the student not have any exam
			{
				cout << "This student have not taken any exam yet and cannot recalculate result" <<endl;
				return false;
			}
			
			cout << "RESULT OUTPUT BASED ON ORIGINAL GRADING:" << endl; // same as display fucntion
            cout << "_________________________________________"<<endl;
			cout << endl;
			cur ->item.print(cout);
			cout << endl;
			cout << "-----------------------------------------------ORIGINAL GRADING EXAM RESULT:-------------------------------------------------" << endl;
			cout << endl;
			for(int a = 0; a < cur -> item.exam_cnt; a++)
			{
				cur ->item.exam[a].print(cout);
			}
			cout << "-----------------------------------------------ORIGINAL GRADING EXAM RESULT:-------------------------------------------------" << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout <<"RESULT OUTPUT BASED ON REVISED GRADING:" << endl;
			cout << endl;
			cout << "_______________________________________" << endl;
			cout << endl;
			printStudent(cur); // cout the student info after revised
			cout << "-----------------------------------------------REVISED GRADING EXAM RESULT:-------------------------------------------------" << endl;
			cout << endl;
			print(cur); // cout the student exam info after revised
			
			cout << "-----------------------------------------------REVISED GRADING EXAM RESULT:-------------------------------------------------" << endl;
			
			
			


			
			return true;
		}
		cur = cur -> next;




	}
	
	cout << "There is no student with id " << b << " in the list." << endl;
	return false;	
}

double GetGradePoint(double marks) //same concept in subject function
{
	if(marks >= 0 && marks < 36)
		return 0.00;
	else if(marks >= 36 && marks < 41)
		return 1.00;
	else if(marks >= 41 && marks < 46)
		return 1.33;
	else if(marks >= 46 && marks < 56)
		return 1.67;
	else if(marks >= 56 && marks < 61)
		return 2.00;
	else if(marks >= 61 && marks < 66)
		return 2.30;
	else if(marks >= 66 && marks < 71)
		return 2.7;
	else if(marks >= 71 && marks <76) 
		return 3.00;
	else if(marks >= 76 && marks < 81) 
		return 3.30;
	else if(marks >= 81 && marks < 86) 
		return 3.70;
	else if(marks >= 86 && marks <= 100) 
		return 4.00;
	else 
		return -1.0;
}
const char *GetGrade(double marks) // same concept in subject function

{   
	if(marks >= 0 && marks < 36)
		return "F";
	else if(marks >= 36 && marks < 41)
		return "E";
	else if(marks >= 41 && marks < 46)
		return "D-";
	else if(marks >= 46 && marks < 56)
		return "D";
	else if(marks >= 56 && marks < 61)
		return "C";
	else if(marks >= 61 && marks < 66)
		return "C+";
	else if(marks >= 66 && marks < 71)
		return "B-";
	else if(marks >= 71 && marks <76) 
		return "B";
	else if(marks >= 76 && marks < 81) 
		return "B+";
	else if(marks >= 81 && marks < 86) 
		return "A-";
	else if(marks >= 86 && marks <= 100) 
		return "A";
	else 
		return "N/A";
	
}
void print(Node*cur)
{
  for(int a = 0; a < cur -> item.exam_cnt; a++) // travese the exam array
  {   
				
				double gpa = 0; //use this to calculate gpa
				double sum = 0; //use this to calculate gpa
				int total_credit_hours = 0; // use this to calculate gpa
				// below is same concept of exam print in exam fucntion 
				cout << "\n\n" << cur->item.exam[a].printTrimester() << " " << cur->item.exam[a].year << " Exam Results: " << endl;
				cout << "\n" << cur->item.exam[a].numOfSubjects << " subjects taken.";
				cout << "\n___________________________________________________________________________________________________________________________";
				cout << "\nSubject Code\t" << setw(70) <<  left << "Subject Name" << "Credit Hours" << "\tGrade " << "\tGrade Point"; 
				cout << "\n___________________________________________________________________________________________________________________________";
				// below same concept to the print subject in subject function only create new getgrade and getgrade point to change the algorithm
				for (int i = 0; i < cur->item.exam[a].numOfSubjects; i++) // traverse the subject array 
				{
					cout << "\n";
					cout << cur->item.exam[a].sub[i].subject_code << "\t" << setw(70) << left << cur->item.exam[a].sub[i].subject_name << setw(7) << right << cur->item.exam[a].sub[i].credit_hours << 
					"\t" << setw(10) << left << " " << GetGrade(cur->item.exam[a].sub[i].marks)<< "\t  " << setprecision(5) << fixed << showpoint <<
					GetGradePoint(cur->item.exam[a].sub[i].marks);
					sum = sum + GetGradePoint(cur->item.exam[a].sub[i].marks) * cur->item.exam[a].sub[i].credit_hours;
					total_credit_hours = total_credit_hours + cur->item.exam[a].sub[i].credit_hours;
					
				}
				gpa = sum/(double)total_credit_hours; // calculate gpa
				cout << "\nGPA: " << gpa;
				

				cout << "\n\n";
  }
			


}

void printStudent(Node*cur) //need this function because the print function is call below the print student
{
   Student A = cur ->item; //student A store all the information with original result expect the cgpa is not same
  for(int a = 0; a < cur -> item.exam_cnt; a++)
  {   
				//use this to calculate gpa and in order to calculate cgpa
				double gpa = 0;
				double sum = 0;
				int total_credit_hours = 0;
				for (int i = 0; i < cur->item.exam[a].numOfSubjects; i++)
				{
					
					sum = sum + GetGradePoint(cur->item.exam[a].sub[i].marks) * cur->item.exam[a].sub[i].credit_hours;
					total_credit_hours = total_credit_hours + cur->item.exam[a].sub[i].credit_hours;
					
				}
				gpa = sum/(double)total_credit_hours;
				A.exam[a].gpa = gpa;  // insert each exam gpa

	
  }
  A.calculateCurrentCGPA(); //recalculate cgpa
  A.print(cout);



}

bool FilterStudent(List list1, List *list2, char *course, int year, int totalcredit)
{   
	if(list1.count <= 0)
	{   
		cout << "list1 is empty" << endl;
		return false;
	}
	if(list2 ->count != 0)
	{   
		cout << "list 2 is not empty" << endl;
		return false;
	}
	Node *cur = list1.head;
	for(int i = 1; i <= list1.count; i++)
	{   
		if((tolower(cur->item.course[0]) ==  tolower(course[0]) )&& (tolower(cur->item.course[1]) ==  tolower(course[1]))) // check course include no matter the case of student input
		{   
			string a;
			a =to_string(year); // change to string in order to compare string to string
			if(a[2]== cur->item.id[0]  && a[3] == cur->item.id[1]) //to check the last two integer is same with the first two integer in student id
			{
					if(cur -> item.totalCreditsEarned >= totalcredit) //check credit
					{
						Student copy = cur ->item; // use student copy tempo to save in order to insert
						list2 ->insert(copy);
						
					}
			
			}
			
		}
		cur = cur -> next;

	}
	return true;
}
bool checkEligibleFYP(List list, char *id)
{
	Node *cur = list.head;
	if(list.count == 0)
	{
		cout << "The list is empty" << endl;
		return false;
	}
	for(int i = 1; i <= list.count; i++)
	{   
		bool A = 0; //flag
		bool B = 0; // flag
		if(strcmp(cur->item.id,id)==0)
		{   
			char aa[5]; // to get the grade of uccd2502
			char bb[5]; // to get the grade of uccd 2513
			
			if(cur->item.totalCreditsEarned >= 30)
			{
			for(int a = 0; a < cur ->item.exam_cnt; a++) //check credit hour valid or not
			{
				for(int b = 0; b < cur->item.exam[a].numOfSubjects; b++)
				{
					if(strcmp(cur->item.exam[a].sub[b].subject_code,"UCCD2502") == 0 &&(cur->item.exam[a].sub[b].marks >= 50)) //check the course exist and pass
					{
						A = 1;
						//cout << "has the proposal writing" << endl;
						strcpy(aa, cur->item.exam[a].sub[b].getGrade()); //get the grade
					}
					else if(strcmp(cur->item.exam[a].sub[b].subject_code,"UCCD2513") == 0 &&(cur->item.exam[a].sub[b].marks >= 50)) //check the course exist and pass
					{
						B = 1;
						//cout << "has mini project" << endl;
						strcpy(bb, cur->item.exam[a].sub[b].getGrade()); // get the grade
					}
					
				}
				
			}
			}
			if(A && B) // check two condition exist
			{
				//output
				cout <<"This student is eligible to take FYP. Below are the details of the students:" << endl;  
				cout << endl;

                cout << "Name:" <<  cur->item.name << endl;
				cout <<"Id:"<< cur->item.id << endl;
				cout <<"Course:" << cur->item.course << endl;
				cout <<"Phone No:" << cur->item.phone_no << endl;
				cout <<"Current CGPA:" << cur ->item.current_cgpa << endl;
				cout <<"Total Credits Earned:" << cur->item.totalCreditsEarned << endl;

				cout <<"Grade obtained for UCCD2502 Introduction to Inventive Problem Solving is " << aa << endl;
                cout << "Grade obtained for UCCD2513 Mini Project "<< bb  <<endl;

				return true;
			}
			else
			{
				
				
				cout << "This student" << cur->item.name << "is not eligible to take FYP yet" << endl;
				
				
				return false;
			}

		}
		cur = cur -> next;
	}
	cout << "There is no student with id "<<id << " in the list" << endl;
	return false;








}

int menu()
{
int insert;
cout <<"Menu " << endl;
cout << endl;
cout << endl;

cout <<"1. Create student list" << endl;
cout << "2. Delete student" << endl;
cout <<"3. Display student list" << endl;
cout << "4. Add exam result" << endl;
cout << "5. Recalculate Result"<< endl;
cout << "6. Filter Student" << endl;
cout << "7. Check Eligible FYP Student" << endl;
cout << "8. Exit." << endl;
cout <<"Enter your choice:" << endl ;
cin >> insert;
return insert;

}







