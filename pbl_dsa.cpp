#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Patient {
	int id;
	string name;
	int age;
	string disease;
	Patient* next;
};

struct Doctor {
	int id;
	string name;
	string specialization;
	Doctor* next;
};

struct Appointment {
	int patientId;
	Appointment* next;
};

// ================= GLOBAL POINTERS =================

Patient* head = NULL;
Doctor* docHead = NULL;
Appointment* front = NULL;
Appointment* rear = NULL;

void login();
void adminMenu();
void receptionistMenu();

void addPatient();
void viewPatients();
void deletePatient();

void addDoctor();
void viewDoctors();
void deleteDoctor();

void bookAppointment();
void servePatient();

void saveToFile();
void loadFromFile();

// ================= MAIN FUNCTION =================

int main() {
	loadFromFile();
	login();
	saveToFile();
	return 0;
}

// ================= LOGIN SYSTEM =================

void login() {
	string user, pass;
	cout << "Login as (admin/reception): ";
	cin >> user;
	cout << "Password: ";
	cin >> pass;

	if (user == "admin" && pass == "admin123")
		adminMenu();
	else if (user == "reception" && pass == "123")
		receptionistMenu();
	else {
		cout << "Invalid Login!\n";
		login();
	}
}

// ================= ADMIN MENU =================

void adminMenu() {
	int choice;
	do {
		cout << "\n--- ADMIN MENU ---\n";
		cout << "1. View Patients\n";
		cout << "2. Delete Patient\n";
		cout << "3. Add Doctor\n";
		cout << "4. View Doctors\n";
		cout << "5. Delete Doctor\n";
		cout << "6. Exit\n";
		cout << "Choice: ";
		cin >> choice;

		switch (choice) {
			case 1:
				viewPatients();
				break;
			case 2:
				deletePatient();
				break;
			case 3:
				addDoctor();
				break;
			case 4:
				viewDoctors();
				break;
			case 5:
				deleteDoctor();
				break;
		}
	} while (choice != 6);
}

// ================= RECEPTION MENU =================

void receptionistMenu() {
	int choice;
	do {
		cout << "\n--- RECEPTION MENU ---\n";
		cout << "1. Add Patient\n";
		cout << "2. Book Appointment\n";
		cout << "3. Serve Patient\n";
		cout << "4. View Patients\n";
		cout << "5. Exit\n";
		cout << "Choice: ";
		cin >> choice;

		switch (choice) {
			case 1:
				addPatient();
				break;
			case 2:
				bookAppointment();
				break;
			case 3:
				servePatient();
				break;
			case 4:
				viewPatients();
				break;
		}
	} while (choice != 5);
}

// ================= PATIENT FUNCTIONS =================

void addPatient() {
	Patient* newNode = new Patient();

	cout << "Enter Patient ID: ";
	cin >> newNode->id;
	cout << "Enter Name: ";
	cin.ignore();
	getline(cin, newNode->name);
	cout << "Enter Age: ";
	cin >> newNode->age;
	cout << "Enter Disease: ";
	cin.ignore();
	getline(cin, newNode->disease);

	newNode->next = NULL;

	if (head == NULL)
		head = newNode;
	else {
		Patient* temp = head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newNode;
	}

	cout << "Patient Added Successfully!\n";
}

void viewPatients() {
	if (head == NULL) {
		cout << "No patients found!\n";
		return;
	}

	Patient* temp = head;
	while (temp != NULL) {
		cout << "\nID: " << temp->id;
		cout << "\nName: " << temp->name;
		cout << "\nAge: " << temp->age;
		cout << "\nDisease: " << temp->disease << "\n";
		cout << "----------------------\n";
		temp = temp->next;
	}
}

void deletePatient() {
	int id;
	cout << "Enter Patient ID to delete: ";
	cin >> id;

	Patient* temp = head;
	Patient* prev = NULL;

	while (temp != NULL && temp->id != id) {
		prev = temp;
		temp = temp->next;
	}

	if (temp == NULL) {
		cout << "Patient not found!\n";
		return;
	}

	if (prev == NULL)
		head = temp->next;
	else
		prev->next = temp->next;

	delete temp;
	cout << "Patient Deleted Successfully!\n";
}

// ================= DOCTOR FUNCTIONS =================

void addDoctor() {
	Doctor* newDoc = new Doctor();

	cout << "Enter Doctor ID: ";
	cin >> newDoc->id;
	cout << "Enter Doctor Name: ";
	cin.ignore();
	getline(cin, newDoc->name);
	cout << "Enter Specialization: ";
	getline(cin, newDoc->specialization);

	newDoc->next = NULL;

	if (docHead == NULL)
		docHead = newDoc;
	else {
		Doctor* temp = docHead;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newDoc;
	}

	cout << "Doctor Added Successfully!\n";
}

void viewDoctors() {
	if (docHead == NULL) {
		cout << "No doctors available!\n";
		return;
	}

	Doctor* temp = docHead;
	while (temp != NULL) {
		cout << "\nDoctor ID: " << temp->id;
		cout << "\nName: " << temp->name;
		cout << "\nSpecialization: " << temp->specialization << endl;
		cout << "------------------------\n";
		temp = temp->next;
	}
}

void deleteDoctor() {
	int id;
	cout << "Enter Doctor ID to delete: ";
	cin >> id;

	Doctor* temp = docHead;
	Doctor* prev = NULL;

	while (temp != NULL && temp->id != id) {
		prev = temp;
		temp = temp->next;
	}

	if (temp == NULL) {
		cout << "Doctor not found!\n";
		return;
	}

	if (prev == NULL)
		docHead = temp->next;
	else
		prev->next = temp->next;

	delete temp;
	cout << "Doctor deleted successfully!\n";
}

// ================= APPOINTMENT QUEUE =================

void bookAppointment() {
	int id;
	cout << "Enter Patient ID for appointment: ";
	cin >> id;

	Appointment* newNode = new Appointment();
	newNode->patientId = id;
	newNode->next = NULL;

	if (rear == NULL) {
		front = rear = newNode;
	} else {
		rear->next = newNode;
		rear = newNode;
	}

	cout << "Appointment Booked Successfully!\n";
}

void servePatient() {
	if (front == NULL) {
		cout << "No appointments pending!\n";
		return;
	}

	cout << "Serving Patient ID: " << front->patientId << endl;
	Appointment* temp = front;
	front = front->next;

	if (front == NULL)
		rear = NULL;

	delete temp;
}

// ================= FILE HANDLING =================

void saveToFile() {
	ofstream file("patients.txt");
	Patient* temp = head;

	while (temp != NULL) {
		file << temp->id << endl;
		file << temp->name << endl;
		file << temp->age << endl;
		file << temp->disease << endl;
		temp = temp->next;
	}
	file.close();
}

void loadFromFile() {
	ifstream file("patients.txt");
	if (!file) return;

	while (!file.eof()) {
		Patient* temp = new Patient();
		file >> temp->id;
		file.ignore();
		getline(file, temp->name);
		file >> temp->age;
		file.ignore();
		getline(file, temp->disease);

		temp->next = NULL;

		if (head == NULL)
			head = temp;
		else {
			Patient* t = head;
			while (t->next != NULL)
				t = t->next;
			t->next = temp;
		}
	}
	file.close();
}