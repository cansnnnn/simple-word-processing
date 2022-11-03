#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct node
{ 
	char ch; 
	node * next; 
	node()
	{ 
	}
	node(char letter, node * p)
		: ch(letter), next(p)
	{};
};

string word(node *head)
{//gets the word from linked list
	node* q;
	q=head;
	string word="";
	while (q != NULL) 
	{
		word=word+q->ch;
		q = q->next;
	}
	return word;
}

void fileOpen(ifstream & input, string & fileName, const int & number)
{//open the file if the given name is correct
	do
	{
		cout<<"Please enter the file "<<number<<" name: ";
		cin>>fileName;
		//file ismi büyük küçük fark eder mi??
		input.open(fileName.c_str());
	}while(input.fail());
}

void fileRead(ifstream & input, node *head)
{//reads from file and assihn chars to linked list and closes the file
	char letter;
	node* temp = head;
	int count=0;
	while(input>>letter)
	{
		if (count==0) // for head
		{head->ch=letter; head->next=NULL; count++; }
		else //for the rest
		{
			node* q;
			q=new node(letter,NULL);
			temp->next=q;
			temp=q;
		}
	}
	input.close();
}

int sim(node* head1, node* head2)
{//looks both linked lists
//returns # of similarities
	int count=0;
	while( head1 != nullptr && head2 != nullptr)
	{
		if(head1->ch == head2->ch)
		{count++;}
		head1=head1->next;
		head2=head2->next;
	}
	return count;
}

bool charCheck(const char & letter)
{//checks the entered char
	if(letter<='z' && letter>='a')
	{return true;}
	else
	{return false;}
}

void del(node* & head, const int & num )
{//deletes all accurences of given char
	bool control=false; // to control the cout part
	char delChar;
	cin>>delChar;
	node* ptr= head;
	node* pre=ptr;

	if (charCheck(delChar) && head!=NULL) //list is not empty and delChar is in correct format
	{
		//deletion in the middle
		while(ptr->next != NULL)
		{
			
			if(ptr!=head && ptr->ch==delChar)
			{
				node* toDelete= ptr;
				pre->next=toDelete->next;
				ptr=ptr->next;
				delete toDelete;
				control=true;

			}
			else
			{ pre=ptr;   ptr=ptr->next; }
		}

		//deletion at the end
		if(ptr->next==NULL && ptr->ch==delChar && ptr!= head)
		{
			pre->next=NULL;
			delete ptr;
			control=true;
		}

		//delettion of head
		if(head->ch==delChar)
		{
			if(head->next==NULL)
			{ head=NULL; control= true; }
			else
			{
				control= true;
				node*headCop=head;
				head=head->next;			
				delete headCop;
			}
		}

		if(control==false) //no deletion made
		{cout<<"No deletion as the value "<<delChar<<" was not found in the list"<<endl;}
		else
		{
			cout<<"Deleting all occurrences of "<<delChar<<" in List"<<num<<"."<<endl;
			cout<<"The current content of List"<<num<<" is: "<<word(head)<<endl;
		}
	}
	else if(head ==NULL) // if list is empty
	{cout<<"No deletion as the value "<<delChar<<" was not found in the list"<<endl;}
	else {cout<<"Invalid arguments."<<endl;}
	//_CrtDumpMemoryLeaks();
}

node* insert(node* head, const int & num)
//Inserts nodes to the list
{
	char insert;
	char after;
	cin>>insert>>after;

	if(head==NULL) //add to emty list
	{
		node* newhead= new node(insert,NULL);
		head=newhead;
		cout<<"The node with "<<after<<" value does not exist. Therefore, Inserting "<<insert<<" at the beginning of the list."<<endl;
		return head;	
	}


	if(charCheck(insert) && charCheck(after)) //inputs are between 'a' and 'z'
	{

		cout<<"Inserting "<<insert<<" after "<<after<<" in List"<<num<<"."<<endl;
		node* ptr; ptr=head; 
		node* node2add; // the node that will be added

		//adding to the middle of the word
		while (ptr->next != NULL)
		{
			if(ptr->ch==after)
			{
				node2add=new node(insert,ptr->next);
				ptr->next=node2add;
				cout<<"The node with "<<insert<<" has been inserted after the first occurrence of a node with "<<after<<" value."<<endl;
				
				return head;
			}
			ptr=ptr->next;
		}

		//adding after the last letter
		if(ptr->next==NULL && ptr->ch==after)
		{	node2add= new node (insert, NULL);
			ptr->next=node2add;
			cout<<"The node with "<<insert<<" has been inserted after the first occurrence of a node with "<<after<<" value."<<endl;
			return head;	
		}

		//adding to the beginning
		node* newHead= new node(insert,head);
		cout<<"The node with "<<after<<" value does not exist. Therefore, Inserting "<<insert<<" at the beginning of the list."<<endl;
		head=newHead;
		return head;
	}

	else {cout<<"Invalid arguments."<<endl;}
}

void arguments(const string& argument, node* & head1, node* & head2)
{//assigns to the correct function by checking the argument string
	if(argument=="sim")
	{
		cout<<"Displaying the contents of the two lists:"<<endl;
		cout<<"List1: "<<word(head1)<<endl<<"List2: "<<word(head2)<<endl;
		cout<<"There is/are "<<sim(head1,head2)<<" letter(s) matched in the same positions in both lists."<<endl;
	}

	else if(argument=="insert1")
	{
		head1=insert(head1, 1);
		cout<<"The current content of List1 is: "<<word(head1)<<endl;
	}
	else if(argument=="insert2")
	{
		head2=insert(head2, 2);
		cout<<"The current content of List2 is: "<<word(head2)<<endl;
	}

	else if(argument=="del1")
	{	del(head1, 1);	}
	else if(argument=="del2")
	{	del(head2, 2);	}

	else if(argument!="exit") //not exit but invalid argument
	{
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cout<<"Invalid command."<<endl;
	}

}

/* Begin: code taken from 2.2-pointers-linkedlists.ptt  */
void DeleteList (node * & head)
{		
	node *temp = NULL;				
    while (head != NULL) {				
      temp = head->next;			
      delete head;
      head = temp;
  }
  delete temp;
}
/* End: code taken from 2.2-pointers-linkedlists.ptt  */


int main()
{
	ifstream input1; ifstream input2;
	string fileName1; string fileName2;
	node* head1; node* head2;
	head1= new node; head2=new node;

	fileOpen(input1, fileName1,1);
	fileOpen(input2, fileName2,2);

	fileRead(input1, head1);
	fileRead(input2, head2);

	cout<<"List1: "<<word(head1)<<endl;
	cout<<"List2: "<<word(head2)<<endl<<endl;

	string argument;
	do //keeps getting argument until it is equal to "exit"
	{
		cout<<"Enter a command and its corresponding argument(s), if any: ";
		cin>>argument;

		arguments(argument,head1,head2);
		cout<<endl;
	}while(argument!="exit");

	cout<<"Clearing the two lists and saying Goodbye!"<<endl;
	DeleteList(head1); DeleteList(head2);
	
	return 0;
}
