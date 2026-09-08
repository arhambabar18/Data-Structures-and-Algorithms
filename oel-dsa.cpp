#include <iostream>
using namespace std;

struct Node {
	int roll;
	string name;
	string department;
	int semester;
	float cgpa;
	Node* prev;
	Node* next;
};

class DoubleLL {
	private:
		Node* head;

	public:
		DoubleLL() {
			head = NULL;
		}

		bool isDuplicate(int r) {
			Node* temp = head;
			while (temp != NULL) {
				if (temp->roll == r)
					return true;
				temp = temp->next;
			}
			return false;
		}

		void insertAtPosition() {
			int roll, semester, pos;
			string name, dept;
			float cgpa;
			cout << "Enter Roll No: ";
			cin >> roll;

			if (isDuplicate(roll)) {
				cout << "Duplicate Roll No not allowed!\n";
				return;
			}

			cout << "Enter Name: ";
			cin >> name;
			cout << "Enter Department: ";
			cin >> dept;
			cout << "Enter Semester: ";
			cin >> semester;
			cout << "Enter CGPA: ";
			cin >> cgpa;

			cout << "Enter position: ";
			cin >> pos;

			Node* newNode = new Node{roll, name, dept, semester, cgpa, NULL, NULL};

			if (pos <= 1 || head == NULL) {
				newNode->next = head;
				if (head != NULL)
					head->prev = newNode;
				head = newNode;
				return;
			}

			Node* temp = head;
			for (int i = 1; i < pos - 1 && temp->next != NULL; i++) {
				temp = temp->next;
			}

			newNode->next = temp->next;
			newNode->prev = temp;

			if (temp->next != NULL)
				temp->next->prev = newNode;

			temp->next = newNode;
		}

		void deleteByRoll() {
			int roll;
			cout << "Enter Roll No to delete: ";
			cin >> roll;

			Node* temp = head;

			while (temp != NULL && temp->roll != roll)
				temp = temp->next;

			if (temp == NULL) {
				cout << "Student not found!\n";
				return;
			}

			if (temp->prev != NULL)
				temp->prev->next = temp->next;
			else
				head = temp->next;

			if (temp->next != NULL)
				temp->next->prev = temp->prev;

			delete temp;
			cout << "Record deleted successfully!\n";
		}

		void updateRecord() {
			int roll;
			cout << "Enter Roll No to update: ";
			cin >> roll;

			Node* temp = head;
			while (temp != NULL) {
				if (temp->roll == roll) {
					cout << "Enter new Semester: ";
					cin >> temp->semester;
					cout << "Enter new CGPA: ";
					cin >> temp->cgpa;
					cout << "Record updated!\n";
					return;
				}
				temp = temp->next;
			}
			cout << "Student not found!\n";
		}

		void display() {
			if (head == NULL) {
				cout << "List is empty!\n";
				return;
			}

			Node* temp = head;
			while (temp != NULL) {
				cout << "\nRoll No: " << temp->roll;
				cout << "\nName: " << temp->name;
				cout << "\nDepartment: " << temp->department;
				cout << "\nSemester: " << temp->semester;
				cout << "\nCGPA: " << temp->cgpa << endl;
				temp = temp->next;
			}
		}

		void topCGPA() {
			if (head == NULL) return;

			Node* temp = head;
			float maxCGPA = head->cgpa;

			while (temp != NULL) {
				if (temp->cgpa > maxCGPA)
					maxCGPA = temp->cgpa;
				temp = temp->next;
			}

			temp = head;
			cout << "\nTop Performer(s):\n";
			while (temp != NULL) {
				if (temp->cgpa == maxCGPA) {
					cout << "Roll: " << temp->roll
					     << " Name: " << temp->name
					     << " CGPA: " << temp->cgpa << endl;
				}
				temp = temp->next;
			}
		}

		void countRecords() {
			int count = 0;
			Node* temp = head;
			while (temp != NULL) {
				count++;
				temp = temp->next;
			}
			cout << "Total Students: " << count << endl;
		}
};

int main() {
	DoubleLL list;
	int choice;

	do {
		cout << "\n--- Student Record Management ---\n";
		cout << "1. Insert Student\n";
		cout << "2. Delete Student\n";
		cout << "3. Update Student\n";
		cout << "4. Display All Students\n";
		cout << "5. Top CGPA Student\n";
		cout << "6. Total Record Count\n";
		cout << "0. Exit\n";
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {
			case 1:
				list.insertAtPosition();
				break;
			case 2:
				list.deleteByRoll();
				break;
			case 3:
				list.updateRecord();
				break;
			case 4:
				list.display();
				break;
			case 5:
				list.topCGPA();
				break;
			case 6:
				list.countRecords();
				break;
			case 0:
				cout << "Program Ended\n";
				break;
			default:
				cout << "Invalid choice!\n";
		}
	} while (choice != 0);

	return 0;
}