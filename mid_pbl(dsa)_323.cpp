#include<iostream>
using namespace std;
struct node{
	int isbn;
	string name;
	node* next;
};
node* newnode;
node* head=0;
node* temp=0;

void insertion(){
	int number;
	string st;
	int choice;
	do{
		cout<<"Do you want a new book insertion: ";cin>>choice;
		if(choice==1){
			node* newnode=new node();
			cout<<"Enter the ISBN NO for this Book: ";cin>>number;
			cin.ignore();
			getline(cin,st);
			cout<<"Enter the NAME of this book: ";cin>>st;
			
			newnode->isbn=number;
			newnode->name=st;
			newnode->next=0;
			
			if(head==0){
				head=temp=newnode;
			}else{
				temp->next=newnode;
				temp=newnode;
			}
		}
	}while(choice==1);
}

void searching(){
	int number;
	bool found=false;  //flag var.
	cout<<"Enter the ISBN NO of the required book: ";cin>>number;
	node* a=head;
	while(a!=0){
		if(a->isbn==number){
			cout<<"YOUR BOOK IS FOUND SUCCESSFULLY,CONGRATS!!!\n The details of the book are:\n-----------------------\n";
			cout<<"ISBN ["<<a->isbn<<"] , Title ["<<a->name<<"]\n";
			found=true;
		}
		a=a->next;
	}
	if(!found){
		cout<<"ALAS! your book isn't found.\n\tNEVER MIND...\n";
	}
}

void deletion(){
	
	int number;
	cout<<"Enter the ISBN No you want to DELETE: ";cin>>number;
	if(head==0){
		cout<<"No book is present there to be deleted!\n\tLibrary is empty BUDDY!\n";
		return; //to return from this function.
	}
	if(head->isbn==number){
		node* temp=head;
		head =head->next;
		delete temp;
		cout<<"Book DELETED successfully!\n";
		return;
	}
	node* previous=head;
	node* current=head->next;
	while(current!=0 && current->isbn!=number){
		previous=current;
		current=current->next;
	}
	if(current==0){
		cout<<"Book Not found!\n";
	}else{
		previous->next=current->next;
		delete current;
		cout<<"Book deleted successfully!";
	}
}

void display(){
	temp=head;
	cout<<"BOOKS PRESENT :\n------------------\n";
	while(temp!=0){
		cout<<"ISBN ["<<temp->isbn<<"] \n TITLE ["<<temp->name<<"]\n";
		temp=temp->next;
	}
}

void sorting() {
    // for ascending order
    node *i;
    node *j;
    for (i = head; i != NULL; i= i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->isbn > j->isbn) {
                swap(i->isbn, j->isbn);
                swap(i->name, j->name); 
            }
        }
    }
    temp = head;
    cout<<"Books in ASCENDING order:\n";
    while (temp != 0) {
        cout << "ISBN [" << temp->isbn << "], NAME [" << temp->name <<"]\n";
        temp = temp->next;
    }

    // for descending order
    for (i = head; i != NULL; i = i->next) {
        for (j= i->next; j != NULL; j= j->next) {
            if (i->isbn < j->isbn) {
                swap(i->isbn, j->isbn);
                swap(i->name, j->name);
            }
        }
    }

    temp = head;
    cout<<"Books in DESCENDING order:" << endl;
    while (temp != 0) {
        cout << "ISBN [" << temp->isbn << "], NAME [" << temp->name <<"]\n";
        temp = temp->next;
    }
}

void count() {
	int count=0;
    temp = head;
    while (temp != 0) {
    	count++;
        temp = temp->next;
    }
    cout<<"the BOOK COUNT in the library is: "<<count<<endl;
}

 void maximini(){
    if (head == 0) {
        cout << "Library is empty!\n";
        return;
    }

    node* max = head;
    node* min = head;
    node* temp = head->next;

    while (temp != 0) {
        if (temp->isbn > max->isbn) {
            max = temp;
        }
        if (temp->isbn < min->isbn) {
            min = temp;
        }
        temp=temp->next;
    }

    cout << "Book with MAXIMUM ISBN:\n" ;
    cout << "ISBN[" << max->isbn << "] ,TITLE [ " << max->name <<"].";

    cout << "Book with MINIMUM ISBN:" << endl;
    cout << "ISBN [" << min->isbn << "] , TITLE [" << min->name <<"].";
}

int main(){
	int choice;

    cout << "---------------------------------------------------------------------------\n" ;
    cout << "                  _LIBRARY MANAGEMENT SYSTEM_\n" ;
    cout << "---------------------------------------------------------------------------\n" ;

    do {
        cout << "\n\n\t\t\t\t MENU :  \n_______________________________________________________________________\n";
        cout << " \t\tEnter 1 to Insert Books\n" ;
        cout << " \t\tEnter 2 to Search for a Book\n";
        cout << " \t\tEnter 3 to Delete a Book\n";
        cout << " \t\tEnter 4 to Display Books (Ascending & Descending)\n";
        cout << " \t\tEnter 5 to Count Total Number of Books\n";
        cout << " \t\tEnter 6 to Find Book with Largest and Smallest ISBN\n";
        cout << "  \t\t(0 -> Exit)\n";
        cout << " _______________________________________________________________________\n\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                insertion();
                break;

            case 2:
                searching();
                break;

            case 3:
                deletion();
                break;

            case 4:
                sorting();
                break;

            case 5:
                count();
                break;

            case 6:
                maximini();
                break;

            case 0:
                cout << "EXIT(0)... \n\tBABYE!\n" ;
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 0);

return 0;

}
