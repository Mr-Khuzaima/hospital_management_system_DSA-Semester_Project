#include <string>
#include <queue>
#include <stack>
#include <list>
#include <Windows.h>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <random>
#include <cmath>
#include <vector>
#include <cctype>
#include <iostream>
using namespace std;


// THINGS TO DO:
// 1. LEAVE EMERGENCY IS NOT PICKING THE DATA OF SOTRED PATIENT
// 2. CHANGES IN DOCTOR CASE(EDIT SEARCH, MAKE A FUNCTION OF CHECK-UP, PATIENT'S FOLLOW UP OPTION TO UPDATE SO THAT AUTO SET THE PATIENT DATA,
//  PRIORITY WISE CHECK UP IN DOCTOR CASE, LIST THEM WITH HEIGHER PRIORITY)

// Forward declarations

// code of directory below

struct Doctor {
    string name;
    int id = 0; // Initialize id to 0
    string speciality;
    bool isSurgeon = false; // Initialize isSurgeon to false
    string cnic;
    string dob;
    string contactNumber;
    string homeAddress;
    string officeRoomNo;
    string buildingNo;

    Doctor* left = nullptr; // Initialize left to nullptr
    Doctor* right = nullptr; // Initialize right to nullptr
};

class HospitalDirectory {

public:
    Doctor* root;

    // Function to validate "yes" or "no"
    bool validateYesNo(const string& input) {
        return (input == "yes" || input == "no");
    }

    // Function to create a new doctor node
    Doctor* createDoctor() {
        Doctor* newDoctor = new Doctor;
        cout << "Enter Doctor Name: ";
        cin.ignore();
        getline(cin, newDoctor->name);

        cout << "Enter Doctor Id: ";
        cin >> newDoctor->id;
        cin.ignore(); // Clear the input buffer

        cout << "Enter Doctor Speciality: ";
        getline(cin, newDoctor->speciality);

        string isSurgeonInput;
        do {
            cout << "Is the doctor a Surgeon? (yes/no): ";
            getline(cin, isSurgeonInput);
            if (!validateYesNo(isSurgeonInput)) {
                cout << "Invalid input. Please enter 'yes' or 'no'." << endl;
            }
        } while (!validateYesNo(isSurgeonInput));
        newDoctor->isSurgeon = (isSurgeonInput == "yes");

        cout << "Is the doctor a Surgeon? (yes/no): ";
        
        getline(cin, isSurgeonInput);
        newDoctor->isSurgeon = (isSurgeonInput == "yes");

        cout << "Enter CNIC No (13 digits): ";
        getline(cin, newDoctor->cnic);
        while (newDoctor->cnic.length() != 13) {
            cout << "Invalid CNIC. Enter CNIC No again (13 digits): ";
            getline(cin, newDoctor->cnic);
        }

        bool validDOB = false;
        do {
            cout << "Enter Date of Birth (DD-MM-YY): ";
            getline(cin, newDoctor->dob);

            // Validate the format of the date of birth
            if (newDoctor->dob.length() == 8 &&
                isdigit(newDoctor->dob[0]) && isdigit(newDoctor->dob[1]) &&
                newDoctor->dob[2] == '-' &&
                isdigit(newDoctor->dob[3]) && isdigit(newDoctor->dob[4]) &&
                newDoctor->dob[5] == '-' &&
                isdigit(newDoctor->dob[6]) && isdigit(newDoctor->dob[7])) {
                validDOB = true;
            }
            else {
                cout << "Invalid Date of Birth format. Please enter again." << endl;
            }
        } while (!validDOB);


        cout << "Enter Contact Number: ";
        getline(cin, newDoctor->contactNumber);

        cout << "Enter Home Address: ";
        getline(cin, newDoctor->homeAddress);

        cout << "Enter Doctor Office Room No: ";
        getline(cin, newDoctor->officeRoomNo);

        cout << "Enter Building No: ";
        getline(cin, newDoctor->buildingNo);

        newDoctor->left = nullptr;
        newDoctor->right = nullptr;

        return newDoctor;
    }

    // Function to insert a doctor into the BST
    Doctor* insertRecord(Doctor* root, Doctor* newDoctor) {
        if (root == nullptr) {
            return newDoctor;
        }

        if (newDoctor->id < root->id) {
            root->left = insertRecord(root->left, newDoctor);
        }
        else if (newDoctor->id > root->id) {
            root->right = insertRecord(root->right, newDoctor);
        }

        return root;
    }

    // Function to delete a doctor from the BST
    Doctor* deleteRecord(Doctor* root, int id) {
        if (root == nullptr) {
            cout << "Doctor with ID " << id << " not found." << endl;
            return root;
        }

        if (id < root->id) {
            root->left = deleteRecord(root->left, id);
        }
        else if (id > root->id) {
            root->right = deleteRecord(root->right, id);
        }
        else {
            if (root->left == nullptr) {
                Doctor* temp = root->right;
                delete root;
                cout << "Record with ID " << id << " deleted successfully." << endl;
                return temp;
            }
            else if (root->right == nullptr) {
                Doctor* temp = root->left;
                delete root;
                cout << "Record with ID " << id << " deleted successfully." << endl;
                return temp;
            }

            Doctor* temp = root->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }

            root->id = temp->id;
            root->right = deleteRecord(root->right, temp->id);
            cout << "Record with ID " << id << " deleted successfully." << endl;
        }

        return root;
    }

    // Function to update a doctor's information
    void updateRecord(Doctor* root, int id) {
        if (root == nullptr) {
            cout << "Doctor with ID " << id << " not found." << endl;
            return;
        }

        int choice;
        do {
            // Doctor found, update information
            cout << "Which information would you like to update? Select a number:" << endl;
            cout << "1. Doctor Name" << endl;
            cout << "2. Doctor Speciality" << endl;
            cout << "3. Is the doctor a Surgeon? (yes/no)" << endl;
            cout << "4. CNIC No (13 digits)" << endl;
            cout << "5. Date of Birth (DD-MM-YY)" << endl;
            cout << "6. Contact Number" << endl;
            cout << "7. Home Address" << endl;
            cout << "8. Doctor Office Room No" << endl;
            cout << "9. Building No" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter the number corresponding to the field you want to update (0 to exit): ";

            cin >> choice;
            cin.ignore(); // Clear the input buffer

            switch (choice) {
            case 1: {
                cout << "Enter Updated Doctor Name: ";
                getline(cin, root->name);
                break;
            }
            case 2: {
                cout << "Enter Updated Doctor Speciality: ";
                getline(cin, root->speciality);
                break;
            }
            case 3: {
                cout << "Is the doctor a Surgeon? (yes/no): ";
                string isSurgeonInput;
                getline(cin, isSurgeonInput);
                root->isSurgeon = (isSurgeonInput == "yes");
                break;
            }
            case 4: {
                cout << "Enter Updated CNIC No (13 digits): ";
                getline(cin, root->cnic);
                while (root->cnic.length() != 13) {
                    cout << "Invalid CNIC. Enter CNIC No again (13 digits): ";
                    getline(cin, root->cnic);
                }
                break;
            }
            case 5: {
                cout << "Enter Updated Date of Birth (DD-MM-YY): ";
                getline(cin, root->dob);
                break;
            }
            case 6: {
                cout << "Enter Updated Contact Number: ";
                getline(cin, root->contactNumber);
                break;
            }
            case 7: {
                cout << "Enter Updated Home Address: ";
                getline(cin, root->homeAddress);
                break;
            }
            case 8: {
                cout << "Enter Updated Doctor Office Room No: ";
                getline(cin, root->officeRoomNo);
                break;
            }
            case 9: {
                cout << "Enter Updated Building No: ";
                getline(cin, root->buildingNo);
                break;
            }
            case 0: {
                cout << "Exiting update operation." << endl;
                break;
            }
            default:
                cout << "Invalid choice. No update performed." << endl;
                break;
            }

            if (choice != 0) {
                cout << "Record Updated Successfully." << endl;
            }

        } while (choice != 0);
    }



    // Function to search for a doctor by ID
    void searchRecord(Doctor* root, int id) {
        if (root == nullptr) {
            cout << "Doctor with ID " << id << " not found." << endl;
            return;
        }

        if (id < root->id) {
            searchRecord(root->left, id);
        }
        else if (id > root->id) {
            searchRecord(root->right, id);
        }
        else {
            // Doctor found, display information
            cout << "Doctor Found!" << endl;
            cout << "Name: " << root->name << endl;
            cout << "ID: " << root->id << endl;
            cout << "Speciality: " << root->speciality << endl;
            cout << "Is Surgeon: " << (root->isSurgeon ? "Yes" : "No") << endl;
            cout << "CNIC: " << root->cnic << endl;
            cout << "DOB: " << root->dob << endl;
            cout << "Contact Number: " << root->contactNumber << endl;
            cout << "Home Address: " << root->homeAddress << endl;
            cout << "Office Room No: " << root->officeRoomNo << endl;
            cout << "Building No: " << root->buildingNo << endl;
        }
    }

    // Function to display all records (in-order traversal of BST)
    void displayAllRecords(Doctor* root) {
        if (root != nullptr) {
            displayAllRecords(root->left);
            //cout << "Name: " << root->name << ", ID: " << root->id << ", Speciality: " << root->speciality << endl;
            cout << "Doctor Found!" << endl;
            cout << "Name: " << root->name << endl;
            cout << "ID: " << root->id << endl;
            cout << "Speciality: " << root->speciality << endl;
            cout << "Is Surgeon: " << (root->isSurgeon ? "Yes" : "No") << endl;
            cout << "CNIC: " << root->cnic << endl;
            cout << "DOB: " << root->dob << endl;
            cout << "Contact Number: " << root->contactNumber << endl;
            cout << "Home Address: " << root->homeAddress << endl;
            cout << "Office Room No: " << root->officeRoomNo << endl;
            cout << "Building No: " << root->buildingNo << endl;
            displayAllRecords(root->right);
        }
    }

    // Function to sort records alphabetically (in-order traversal of BST)
    void sortRecordsAlphabetical(Doctor* root) {
        if (root != nullptr) {
            sortRecordsAlphabetical(root->left);
            cout << "Name: " << root->name << ", ID: " << root->id << ", Speciality: " << root->speciality << endl;
            sortRecordsAlphabetical(root->right);
        }
    }

    // Function to save records to a file
    void saveRecords(const string& fileName = "hospital_records.txt") {
        ofstream file(fileName);

        if (!file.is_open()) {
            cout << "Error opening file for writing." << endl;
            return;
        }

        saveRecordsToFile(root, file);

        file.close();
        cout << "Records saved to file successfully." << endl;
    }

    // Helper function for saving records to a file (recursive)
    void saveRecordsToFile(Doctor* root, ofstream& file) {
        if (root != nullptr) {
            saveRecordsToFile(root->left, file);
            file << root->name << "," << root->id << "," << root->speciality << ","
                << (root->isSurgeon ? "1" : "0") << "," << root->cnic << "," << root->dob << ","
                << root->contactNumber << "," << root->homeAddress << "," << root->officeRoomNo << ","
                << root->buildingNo << "\n";
            saveRecordsToFile(root->right, file);
        }
    }

    // Function to load records from a file
    void loadRecords(const string& fileName) {
        ifstream file(fileName);

        if (!file.is_open()) {
            cout << "Error opening file for reading." << endl;
            return;
        }

        string line;

        while (getline(file, line)) {
            Doctor* newDoctor = parseRecord(line);
            root = insertRecord(root, newDoctor);
        }

        file.close();
        cout << "Records loaded from file successfully." << endl;
    }

    // Helper function for parsing a record from a line
    Doctor* parseRecord(const string& line) {
        Doctor* newDoctor = new Doctor;
        size_t pos = 0;

        // Create a non-const string to use erase
        string tempLine = line;

        // Split the line using ',' as a delimiter
        pos = tempLine.find(",");
        newDoctor->name = tempLine.substr(0, pos);
        tempLine.erase(0, pos + 1);

        pos = tempLine.find(",");
        newDoctor->id = stoi(tempLine.substr(0, pos));
        tempLine.erase(0, pos + 1);

        pos = tempLine.find(",");
        newDoctor->speciality = tempLine.substr(0, pos);
        tempLine.erase(0, pos + 1);

        pos = tempLine.find(",");
        newDoctor->isSurgeon = (stoi(tempLine.substr(0, pos)) == 1);
        tempLine.erase(0, pos + 1);

        pos = tempLine.find(",");
        newDoctor->cnic = tempLine.substr(0, pos);
        tempLine.erase(0, pos + 1);

        pos = tempLine.find(",");
        newDoctor->dob = tempLine.substr(0, pos);
        tempLine.erase(0, pos + 1);

        pos = tempLine.find(",");
        newDoctor->contactNumber = tempLine.substr(0, pos);
        tempLine.erase(0, pos + 1);

        pos = tempLine.find(",");
        newDoctor->homeAddress = tempLine.substr(0, pos);
        tempLine.erase(0, pos + 1);

        pos = tempLine.find(",");
        newDoctor->officeRoomNo = tempLine.substr(0, pos);
        tempLine.erase(0, pos + 1);

        newDoctor->buildingNo = tempLine;

        newDoctor->left = nullptr;
        newDoctor->right = nullptr;

        return newDoctor;
    }

    void insertRecord(Doctor* newDoctor) {
        root = insertRecord(root, newDoctor);
    }

    // Function to delete a doctor from the BST
    void deleteRecord(int idToDelete) {
        root = deleteRecord(root, idToDelete);
    }

    // Function to update a doctor's information
    void updateRecord(int idToUpdate) {
        updateRecord(root, idToUpdate);
    }

    // Function to search for a doctor by ID
    void searchRecord(int idToSearch) {
        searchRecord(root, idToSearch);
    }

    // Function to display all records (in-order traversal of BST)
    void displayAllRecords() {
        cout << "All Doctor Records:" << endl;
        displayAllRecords(root);
    }

    // Function to sort records alphabetically (in-order traversal of BST)
    void sortRecordsAlphabetical() {
        cout << "Sorted Records Alphabetically:" << endl;
        sortRecordsAlphabetical(root);
    }


public:
    // Constructor
    HospitalDirectory() : root(nullptr) {}

    // Destructor
    ~HospitalDirectory() {
        // Save records when the program exits
        saveRecords();
        // Free memory for the tree (you might want to traverse and delete nodes)
    }

};;
// code of directory above



// Game Functions Declaration From Here ********************************        ***********************
//function prototypes for Tic_Tac_Toe
void Initialize(char[3][3], char SetTo = '-');                 // sets dummy characters on board such as '-'
void DisplayBoard(char[3][3]);                               // Displays the board and it's elements
void SetPosition(char[3][3], char, char&, int);              // for setting tick or cross on board
void InputFromPlayers(int&, char[3][3], char, char&);        // takes input from the player
void InputValidation(char, char[3][3], char, int&);          // validates the input taken from player
char WhoWon(char);                                            // checks who won
char CheckWin(char[3][3]);                                   // checks if someone has won

//funtion protoypes for Rock_Paper_Scissor
void RockPaperScissorMenuDisplay();            			//To display basic selection menu for rock, paper and scissor
void WinCheck_R_P_S(char, char, char&);        			//To check if someone has won
void ComputerPick(char&);                      			//To enable the computer to make their choice
void WhoWon_R_P_S(char, char);                 			//To check who has won if there is a winner
void PlayAgain(char&);                         			//To enable to player to play again
void IsValidSelection(char&, char);             			//To check if the selection that player made is valid or not

//function protoypes made during compilation
void LoadingScreen();

// Gamw Functions Declaration From Here ********************************        ***********************



struct OldEmergencyPatient
{
    int patientID;
    string name;
    string contact;
    int age;
    string entryCondition;
    double totalBill;
    string leavingCondition;
    bool hasLeft;  // Added flag to track whether the patient has left

    // Constructor
    OldEmergencyPatient() : patientID(0), age(0), totalBill(0.0), leavingCondition(""), hasLeft(false) {}
};

class EmergencyManagement
{
private:
    stack<OldEmergencyPatient> EmergencyPatientsStack;
    stack<OldEmergencyPatient> oldEmergencyPatientsStack;

public:
    // Function to register an emergency patient
    void RegisterEmergencyPatient(int patientID)
    {
        // Check if the patient with the given ID already exists in the oldEmergencyPatientsStack
        stack<OldEmergencyPatient> tempStack = oldEmergencyPatientsStack;
        while (!tempStack.empty())
        {
            OldEmergencyPatient existingPatient = tempStack.top();
            tempStack.pop();

            if (existingPatient.patientID == patientID)
            {
                cout << "Patient with ID " << patientID << " is already registered in the system.\n";
                return;
            }
        }

        OldEmergencyPatient newEmergencyPatient;

        newEmergencyPatient.patientID = patientID;

        // Take input from the user
        cout << "Enter patient name: ";
        cin.ignore(); // Ignore the newline character in the buffer
        getline(cin, newEmergencyPatient.name);

        cout << "Enter patient contact: ";
        cin >> newEmergencyPatient.contact;

        cout << "Enter patient age: ";
        cin >> newEmergencyPatient.age;

        cout << "Enter entry condition: ";
        cin.ignore();
        getline(cin, newEmergencyPatient.entryCondition);

        // Add the emergency patient record to the EmergencyPatientsStack
        EmergencyPatientsStack.push(newEmergencyPatient);

        cout << "Emergency Patient with ID " << patientID << " registered successfully.\n";
    }

    // Function to display current emergency patients
    void DisplayEmergencyPatients()
    {
        if (EmergencyPatientsStack.empty())
        {
            cout << "No current emergency patients to display.\n";
            return;
        }

        // Create a temporary stack to preserve the original data
        stack<OldEmergencyPatient> tempStack = EmergencyPatientsStack;

        cout << "Current Emergency Patients:\n";
        while (!tempStack.empty())
        {
            OldEmergencyPatient emergencyPatient = tempStack.top();
            cout << "Patient ID: " << emergencyPatient.patientID << "\n";
            cout << "Patient Name: " << emergencyPatient.name << "\n";
            cout << "Contact: " << emergencyPatient.contact << "\n";
            cout << "Age: " << emergencyPatient.age << "\n";
            cout << "Entry Condition: " << emergencyPatient.entryCondition << "\n";
            cout << "------------------------\n";

            tempStack.pop();
        }
    }

    // Function to search for an emergency patient
    void SearchEmergencyPatient(int patientID)
    {
        // Search in the current emergency patients
        stack<OldEmergencyPatient> tempStack = EmergencyPatientsStack;
        while (!tempStack.empty())
        {
            OldEmergencyPatient emergencyPatient = tempStack.top();
            tempStack.pop();

            if (emergencyPatient.patientID == patientID)
            {
                cout << "Found in Current Emergency Patients:\n";
                cout << "Patient ID: " << emergencyPatient.patientID << "\n";
                cout << "Patient Name: " << emergencyPatient.name << "\n";
                cout << "Contact: " << emergencyPatient.contact << "\n";
                cout << "Age: " << emergencyPatient.age << "\n";
                cout << "Entry Condition: " << emergencyPatient.entryCondition << "\n";
                return;
            }
        }

        // Search in the old emergency patients
        tempStack = oldEmergencyPatientsStack;
        while (!tempStack.empty())
        {
            OldEmergencyPatient emergencyPatient = tempStack.top();
            tempStack.pop();

            if (emergencyPatient.patientID == patientID)
            {
                cout << "Found in Old Emergency Patients:\n";
                cout << "Patient ID: " << emergencyPatient.patientID << "\n";
                cout << "Patient Name: " << emergencyPatient.name << "\n";
                cout << "Contact: " << emergencyPatient.contact << "\n";
                cout << "Age: " << emergencyPatient.age << "\n";
                cout << "Entry Condition: " << emergencyPatient.entryCondition << "\n";
                return;
            }
        }

        cout << "Patient with ID " << patientID << " not found in the emergency records.\n";
    }

    // Function for a patient leaving emergency
    void LeaveEmergency(int patientID)
    {
        // Find the patient in the current emergency patients stack and update the record
        stack<OldEmergencyPatient> tempStack;
        OldEmergencyPatient patientToUpdate;

        while (!EmergencyPatientsStack.empty())
        {
            OldEmergencyPatient tempPatient = EmergencyPatientsStack.top();
            EmergencyPatientsStack.pop();

            if (tempPatient.patientID == patientID)
            {
                // Found the patient to update
                patientToUpdate = tempPatient;
                break;
            }

            tempStack.push(tempPatient);
        }

        if (patientToUpdate.patientID == 0)
        {
            cout << "Patient with ID " << patientID << " not found in the current emergency records.\n";
            return;
        }

        // Take input from the user
        cout << "Enter total bill: ";
        cin >> patientToUpdate.totalBill;

        cout << "Enter leaving health condition: ";
        cin.ignore();
        getline(cin, patientToUpdate.leavingCondition);

        // Set the flag to indicate that the patient has left
        patientToUpdate.hasLeft = true;

        // Push the patient to the old emergency patient records only if they have left
        if (patientToUpdate.hasLeft)
        {
            oldEmergencyPatientsStack.push(patientToUpdate);
        }

        // Restore the remaining patients back to the stack
        while (!tempStack.empty())
        {
            EmergencyPatientsStack.push(tempStack.top());
            tempStack.pop();
        }

        cout << "Emergency Patient with ID " << patientID << " left the emergency successfully.\n";
    }

    // Function to display old emergency patients
    void DisplayOldEmergencyPatients()
    {
        if (oldEmergencyPatientsStack.empty())
        {
            cout << "No old emergency patients to display.\n";
            return;
        }

        // Create a temporary stack to preserve the original data
        stack<OldEmergencyPatient> tempStack = oldEmergencyPatientsStack;

        cout << "Old Emergency Patients:\n";
        while (!tempStack.empty())
        {
            OldEmergencyPatient oldEmergencyPatient = tempStack.top();

            cout << "Patient ID: " << oldEmergencyPatient.patientID << "\n";
            cout << "Patient Name: " << oldEmergencyPatient.name << "\n";
            cout << "Contact: " << oldEmergencyPatient.contact << "\n";
            cout << "Age: " << oldEmergencyPatient.age << "\n";
            cout << "Entry Condition: " << oldEmergencyPatient.entryCondition << "\n";
            cout << "Total Bill: " << oldEmergencyPatient.totalBill << "\n";
            cout << "Leaving Condition: " << oldEmergencyPatient.leavingCondition << "\n";
            cout << "------------------------\n";

            tempStack.pop();
        }
    }
};                  //**************        **************  End of Emeregency Management Class **************       ***************

struct node
{
    int prior;
    int data; // Assuming data represents patient ID
    string name;
    string contact;
    string doctorName;
    string medicine;
    string tests;
    string diagnosis;
    bool admitted; // New field to track admission status
    int age; // New field for patient age
    string entryCondition; // New field for entry condition
    double totalBill; // New field for total bill
    string leavingCondition; // New field for leaving health condition
    string notesforpatient;
    struct node* link;

    // Constructor to initialize member variables
    node() : prior(0), data(0), medicine("--"), tests("--"), diagnosis("--"),
        admitted(false), age(0), totalBill(0.0), notesforpatient("-"), link(nullptr) {}
};

class Priority_Queue
{
private:
    node* front;
    stack<node*> oldPatientsStack;
    stack<OldEmergencyPatient> oldEmergencyPatientsStack; // Declare old emergency patients stack
    queue<string> complaintsQueue; // Queue to store complaints
    list<node*> admittedPatientsList; // List to store admitted patients
public:
    Priority_Queue()
    {
        front = nullptr;
    }

    void BookAppointments()
    {
        node* tmp, * q;
        tmp = new node;

        // Initialize member variables in the BookAppointments function
        tmp->data = 0;
        tmp->prior = 0;
        tmp->link = nullptr;

        // Take input from the user
        cout << "Enter patient ID: ";
        cin >> tmp->data;

        cout << "Enter patient name: ";
        cin.ignore(); // Ignore the newline character in the buffer
        getline(cin, tmp->name);

        cout << "Enter patient contact: ";
        cin >> tmp->contact;

        cout << "Enter doctor name: ";
        cin.ignore(); // Ignore the newline character in the buffer
        getline(cin, tmp->doctorName);

        // Ask user if patient needs priority
        cout << "Need to Set Priority? (1 for YES :: 0 for NO)\nEnter Here: ";
        int priorityChoice; cin >> priorityChoice;

        if (priorityChoice == 1)
        {
            
            // Set priority to a large value to push it to the front
            tmp->prior = INT_MAX;

            // Insert the new priority appointment at the top
            tmp->link = front;
            front = tmp;
        }
        else
        {
            // Set priority to 0 for non-priority patients
            tmp->prior = 0;

            // Insert the new appointment into the priority queue based on priority
            q = front;
            while (q->link != nullptr && q->link->prior <= tmp->prior)
                q = q->link;
            tmp->link = q->link;
            q->link = tmp;
        }

        cout << "Appointment booked successfully.\n";
    }

    void CancelAppointments(int patientID)
    {
        node* tmp, * prev;
        tmp = front;
        prev = nullptr;

        // Search for the appointment to cancel based on patient ID
        while (tmp != nullptr && tmp->data != patientID)
        {
            prev = tmp;
            tmp = tmp->link;
        }

        if (tmp == nullptr)
        {
            cout << "Appointment with Patient ID " << patientID << " not found.\n";
        }
        else
        {
            // Appointment found, perform deletion
            if (prev == nullptr)
            {
                // If the appointment to be canceled is the first in the queue
                front = front->link;
            }
            else
            {
                // If the appointment to be canceled is not the first in the queue
                prev->link = tmp->link;
            }

            cout << "Appointment with Patient ID " << patientID << " canceled successfully.\n";
            delete tmp;
        }
    }

    void SearchAppointments(int patientID)
    {
        node* tmp = front;

        // Search for the appointment based on patient ID
        while (tmp != nullptr && tmp->data != patientID)
        {
            tmp = tmp->link;
        }

        if (tmp == nullptr)
        {
            cout << "Appointment with Patient ID " << patientID << " not found.\n";
        }
        else
        {
            // Appointment found, display details
            cout << "Appointment details for Patient ID " << patientID << ":\n";
            cout << "Patient Name: " << tmp->name << "\n";
            cout << "Patient Contact: " << tmp->contact << "\n";
            cout << "Doctor Name: " << tmp->doctorName << "\n";
            cout << "Medicine: " << tmp->medicine << "\n";
            cout << "Tests: " << tmp->tests << "\n";
            cout << "Diagnosis: " << tmp->diagnosis << "\n";
            cout << "Priority: " << tmp->prior << "\n";
        }
    }


    void displayAllAppointments()
    {
        node* tmp = front;

        if (tmp == nullptr)
        {
            cout << "No appointments to display.\n";
            return;
        }

        cout << "All Appointments (sorted by priority):\n";
        while (tmp != nullptr)
        {
            cout << "\n========================\n";
            cout << "Patient ID: " << tmp->data << "\n";
            cout << "Patient Name: " << tmp->name << "\n";
            cout << "Doctor Name: " << tmp->doctorName << "\n";
            cout << "Medicine: " << tmp->medicine << "\n";
            cout << "Tests: " << tmp->tests << "\n";
            cout << "Diagnosis: " << tmp->diagnosis << "\n";
            cout << "Priority: " << tmp->prior << "\n";
            cout << "\n========================\n";

            tmp = tmp->link;
        }
    }


    void CheckUpAppointment()
    {
        if (front == nullptr)
        {
            cout << "No appointments to display.\n";
            return;
        }

        node* tmp = front;

        cout << "\nUpcoming Appointment (highest priority):\n";
        // Display details of the first patient (highest priority)
        cout << "\n========================\n";
        cout << "Patient ID: " << tmp->data << "\n";
        cout << "Patient Name: " << tmp->name << "\n";
        cout << "Patient Priority: " << tmp->prior << "\n";
        cout << "========================\n";

        // Ask for medicines
        cout << "Enter Medicine: ";

        // Vector to store medicines
        vector<string> medicines;

        // Loop to add multiple medicines
        do {
            string medicine;
            cin.ignore();
            getline(cin, medicine);
            medicines.push_back(medicine);

            cout << "Add another medicine? (1 for YES :: 0 for NO)\nEnter Here: ";
            int addAnotherMedicine;
            cin >> addAnotherMedicine;

            if (addAnotherMedicine != 1) {
                break;  // Exit the loop if the user enters other than 1
            }

            cin.ignore();
            cout << "Enter Medicine: ";
        } while (true);

        // Combine medicines into a single string
        string combinedMedicines;
        for (const string& medicine : medicines)
        {
            if (!combinedMedicines.empty())
            {
                combinedMedicines += ", ";
            }
            combinedMedicines += medicine;
        }

        // Update the existing appointment with the new medicine details
        tmp->medicine = combinedMedicines;

        // Ask for tests
        cout << "Enter Tests: ";
        cin.ignore();  // Ignore newline character in the buffer
        getline(cin, tmp->tests);

        // Ask for diagnosis
        cout << "Enter Diagnosis: ";
        getline(cin, tmp->diagnosis);

        // Option to change admission status
        cout << "Need To Admitted Patient? (1 for YES :: 0 for NO)\nEnter Here: ";
        cin >> tmp->admitted;

        // Push the old patient data to the stack
        oldPatientsStack.push(tmp);

        // Remove the checked-up patient from the priority queue
        front = front->link;

        // Add to admitted patients list if admitted
        if (tmp->admitted)
        {
            admittedPatientsList.push_back(tmp);
        }

        cout << "Appointment details updated successfully.\n";
    }



    // Function to admit a patient
    void AdmitPatient(int patientID)
    {
        node* tmp = front;

        // Search for the patient based on patient ID
        while (tmp != nullptr && tmp->data != patientID)
        {
            tmp = tmp->link;
        }

        if (tmp == nullptr)
        {
            cout << "Patient with ID " << patientID << " not found.\n";
        }
        else
        {
            // Update admission status
            tmp->admitted = true;

            // Move the patient to the admitted patients list
            admittedPatientsList.push_back(tmp);

            cout << "Patient with ID " << patientID << " admitted successfully.\n";
        }
    }

    void DisplayOldPatients()
    {
        if (oldPatientsStack.empty())
        {
            cout << "No old patient records available.\n";
            return;
        }

        // Create a temporary stack to preserve the original data
        stack<node*> tempStack = oldPatientsStack;

        cout << "Old Patient Records:\n";
        while (!tempStack.empty())
        {
            node* oldPatient = tempStack.top();
            cout << "Patient ID: " << oldPatient->data << "\n";
            cout << "Patient Name: " << oldPatient->name << "\n";
            cout << "Doctor Name: " << oldPatient->doctorName << "\n";
            cout << "Medicine: " << oldPatient->medicine << "\n";
            cout << "Tests: " << oldPatient->tests << "\n";
            cout << "Diagnosis: " << oldPatient->diagnosis << "\n";
            cout << "------------------------\n";

            tempStack.pop();
        }
    }

    void SearchOldPatient(int patientID)
    {
        if (oldPatientsStack.empty())
        {
            cout << "No old patient records available.\n";
            return;
        }

        // Create a temporary stack to preserve the original data
        stack<node*> tempStack = oldPatientsStack;
        bool found = false;

        while (!tempStack.empty())
        {
            node* oldPatient = tempStack.top();

            if (oldPatient->data == patientID)
            {
                found = true;
                cout << "\n========================\n";
                cout << "Old Patient found with ID " << patientID << ":\n";
                cout << "Patient Name: " << oldPatient->name << "\n";
                cout << "Doctor Name: " << oldPatient->doctorName << "\n";
                cout << "Medicine: " << oldPatient->medicine << "\n";
                cout << "Tests: " << oldPatient->tests << "\n";
                cout << "Diagnosis: " << oldPatient->diagnosis << "\n";
                cout << "Diagnosis: " << oldPatient->notesforpatient << "\n";
                cout << "\n========================\n";
                break;
            }

            tempStack.pop();
        }

        if (!found)
        {
            cout << "Old Patient with ID " << patientID << " not found.\n";
        }
    }


    void DisplayAdmittedPatients()
    {
        if (admittedPatientsList.empty())
        {
            cout << "No admitted patients to display.\n";
            return;
        }

        cout << "Admitted Patients:\n";
        for (const auto& patient : admittedPatientsList)
        {
            cout << "\n========================\n";
            cout << "Patient ID: " << patient->data << "\n";
            cout << "Patient Name: " << patient->name << "\n";
            cout << "Doctor Name: " << patient->doctorName << "\n";
            cout << "Medicine: " << patient->medicine << "\n";
            cout << "Tests: " << patient->tests << "\n";
            cout << "Diagnosis: " << patient->diagnosis << "\n";
            cout << "Diagnosis: " << patient->notesforpatient << "\n";
            cout << "\n========================\n";
        }
    }


    // Function to modify details of an admitted patient
    void ModifyAdmittedPatient(int patientID)
    {
        for (auto& patient : admittedPatientsList)
        {
            if (patient->data == patientID)
            {
                // Allow modification
                cout << "Modify details for Admitted Patient with ID " << patientID << ":\n";
                cout << "Patient Name: " << patient->name << endl;
                cout << "Patient Name: " << patient->doctorName << endl; 
                cout << "Diagnosis of the Patient: " << patient->diagnosis << endl;
                cout << "Doctor's Recommended Medicines: " << patient->medicine << endl;
                
                cout << "Press 1 IF Doses Given to Patient: ";

                cout << "Enter Notes Related to Health Condition of Patient: ";
                cin.ignore();
                getline(cin, patient->notesforpatient);

                cout << "Admitted Patient details updated successfully.\n";
                return;
            }
        }

        cout << "Admitted Patient with ID " << patientID << " not found.\n";
    }


    void SearchAdmittedPatient(int patientID) 
    {
        bool found = false;

        for (const auto& patient : admittedPatientsList) 
        {
            if (patient->data == patientID)
            {
                found = true;
                cout << "\n========================\n";
                cout << "Admitted Patient found with ID " << patientID << ":\n";
                cout << "Patient Name: " << patient->name << "\n";
                cout << "Doctor Name: " << patient->doctorName << "\n";
                cout << "Medicine: " << patient->medicine << "\n";
                cout << "Tests: " << patient->tests << "\n";
                cout << "Diagnosis: " << patient->diagnosis << "\n";
                cout << "Contact: " << patient->contact << "\n";
                cout << "Diagnosis: " << patient->notesforpatient << "\n";
                cout << "\n========================\n";
                break;
            }
        }

        if (!found)
        {
            cout << "Admitted Patient with ID " << patientID << " not found.\n";
        }
    }

    void RegisterComplaint(const string& complaint)
    {
        complaintsQueue.push(complaint);
        cout << "Complaint registered successfully.\n";
    }

    // Function to display complaints
    void DisplayComplaints()
    {
        if (complaintsQueue.empty())
        {
            cout << "No complaints registered.\n";
            return;
        }

        cout << "Registered Complaints:\n";
        int count = 1;
        while (!complaintsQueue.empty())
        {
            cout << count << ". " << complaintsQueue.front() << "\n";
            complaintsQueue.pop();
            count++;
        }
    }

    void LoadingFunction()
    {
        cout << "\nLoading";
        for (int i = 0; i < 5; i++)
        {
            cout << ". ";
            Sleep(500);
        }
        cout << endl;
    }
};    // Add other functions as needed

string generateRandomPassword()
{
    string newPassword;
    srand(time(0)); // Seed the random number generator with current time

    for (int i = 0; i < 7; ++i)
    {
        char randomChar = 'a' + (rand() % 26); // Generate a random lowercase character
        newPassword += randomChar;
    }

    return newPassword;
}

void changePassword(string& password)
{
    string newPassword;
    cin.ignore(); // Ignore the newline character
    cout << "Enter your new password: ";
    getline(cin, newPassword);
    password = newPassword;
    cout << "Password changed successfully!" << endl;
}

void setPassword(string& password)
{
    cin.ignore();
    cout << "Enter a new password: ";
    getline(cin, password);
    cout << "Password set successfully!" << endl;
}

// main Starts from here            --------            --------            --------        --------
int main()
{
    string password; // Declare an empty password
    bool loggedIn = false; //flag variable to track the login status

    Priority_Queue pqobj;
    HospitalDirectory hospital;
    EmergencyManagement emobj;

login:
    while (true)
    {
        system("cls");
        cout << "LOGIN" << endl;
        cout << "1) Login with existing password" << endl;
        cout << "2) Set password and login" << endl;
        cout << "3) Forgot password" << endl;
        int loginChoice;
        cin >> loginChoice;

        if (loginChoice == 1)
        {
            string enteredPassword;
            cin.ignore(); // Ignore the newline character
            cout << "Enter your password: ";
            getline(cin, enteredPassword);
            if (enteredPassword == password) {
                cout << "Login successful!" << endl;
                loggedIn = true;
                break; // Exit the login loop
            }
            else
            {
                cout << "Incorrect password. Please try again." << endl;
            }
        }
        else if (loginChoice == 2)
        {
            setPassword(password); // Call the setPassword function
        }
        else if (loginChoice == 3)
        {
            cout << "Forgot Password Options:" << endl;
            cout << "1) Generate a random password" << endl;
            cout << "2) Enter email for password recovery" << endl;
            int forgotChoice;
            cin >> forgotChoice;

            if (forgotChoice == 1)
            {
                string newPassword = generateRandomPassword();
                password = newPassword;
                cout << "A new password has been generated: " << newPassword << endl;
            }
            else if (forgotChoice == 2)
            {
                string recoveryEmail;
                cout << "Enter your recovery email: ";
                cin.ignore();
                getline(cin, recoveryEmail);
                // Implement recovery logic here
                cout << "Recovery email sent to " << recoveryEmail << endl;
            }
            else
            {
                cout << "Invalid choice. Returning to the main menu." << endl;
            }
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
        if (loggedIn)
        {
            while (true)
            {

                bool signaltoQuit = false;
                char GamesMenuSelection{ 0 };
                do {
                MainMenu:
                    cout << "Select Related Option from the List:-\n";
                    cout << "1: Doctor\n2: Nurse\n3: Patient\n4: Emergency\n5: Administrator\n6: Complaints\n7: Game\n8: Change Password\n9: Exit\n";
                    cout << "Enter Choice Here: ";
                    int category_type; cin >> category_type;
                    switch (category_type)
                    {
                    case 1:
                        //doctor case
                        cout << "Select Related Option:-\n1) View Appointments\n2) Search Appointments\n3) Check-up Patient \n4) Display Old Patients Data\nEnter Here: ";
                        int doctor_menu; cin >> doctor_menu;

                        if (doctor_menu == 1)
                        {
                            int modify_again;
                            do {
                                cout << "\nDisplaying Apointments. Loading";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << ". ";
                                    Sleep(500);
                                }
                                cout << endl;
                                pqobj.displayAllAppointments();
                                cout << "Do you want to Display Again?\nPress 1 for YES :: Press 0 for NO\nEnter Here: ";
                                cin >> modify_again;
                            } while (modify_again != 0);
                        }
                        else if (doctor_menu == 2)
                        {
                            int modify_again;
                            do
                            {
                                int patientIDToSearch;
                                cout << "Enter Patient ID to search appointment: ";
                                cin >> patientIDToSearch;
                                cout << "\nSearching Apointments. Loading";
                                for (int i = 0; i < 5; i++)
                                {
                                    cout << ". ";
                                    Sleep(500);
                                }
                                cout << endl;
                                pqobj.SearchAppointments(patientIDToSearch);

                                cout << "Do you want to Search Again?\nPress 1 for YES :: Press 0 for NO\nEnter Here: ";
                                cin >> modify_again;
                            } while (modify_again != 0);
                        }
                        else if (doctor_menu == 3)
                        {
                            int modify_again;
                            do
                            {
                                int patientIDToModify;
                                cout << "Enter Patient ID to modify appointment: ";
                                cin >> patientIDToModify;
                                cout << "\nSearching to Modify\n";
                                pqobj.LoadingFunction();
                                pqobj.CheckUpAppointment();

                                cout << "Do you want to Modify Again?\nPress 1 for YES :: Press 0 for NO\nEnter Here: ";
                                cin >> modify_again;
                            } while (modify_again != 0);
                        }
                        else if (doctor_menu == 4)
                        {
                            int modify_again;
                            do {
                                cout << "\nDisplaying Old Patient Record. Loading";
                                for (int i = 0; i < 5; i++)

                                {
                                    cout << ". ";
                                    Sleep(500);
                                }
                                cout << endl;
                                pqobj.DisplayOldPatients();
                                cout << "\nDo you want to Display Old Patient Record Again?\nPress 1 for YES :: Press 0 for NO\nEnter Here: ";
                                cin >> modify_again;
                            } while (modify_again != 0);
                        }
                        else
                            cout << "\nInvalid Input\n";

                        break;
                    case 2:
                        //nurse case
                        cout << "Select Related Option\n1. Display Admitted Patients\n2. Modify Admitted Patients\n3. Search Admitted Patient\nEnter Here: ";
                        int nurse_menu; cin >> nurse_menu;

                        if (nurse_menu == 1)
                        {
                            int nurse_again;
                            do {
                                pqobj.DisplayAdmittedPatients();
                                cout << "Do you want to display again?\nPress 1 for YES :: Press 0 for NO\nEnter Here: ";
                                cin >> nurse_again;
                            } while (nurse_again != 0);
                            //Display Admisted patients
                        }
                        else if (nurse_menu == 2)
                        {
                            int nurse_again;
                            // Modify Patients data
                            do {
                                cout << "Enter Patient ID to Modify: ";
                                int admittedpatientID; cin >> admittedpatientID;
                                pqobj.ModifyAdmittedPatient(admittedpatientID);

                                cout << "Do you want to display again?\nPress 1 for YES :: Press 0 for NO\nEnter Here: ";
                                cin >> nurse_again;
                            } while (nurse_again != 0);
                        }
                        else if (nurse_menu == 3)
                        {
                            //Search Admitted Patients
                            int nurse_again;
                            do {
                                cout << "Enter Patient ID to Search: ";
                                int admittedpatientID; cin >> admittedpatientID;
                                pqobj.SearchAdmittedPatient(admittedpatientID);

                                cout << "Do you want to display again?\nPress 1 for YES :: Press 0 for NO\nEnter Here: ";
                                cin >> nurse_again;
                            } while (nurse_again != 0);
                        }
                        else
                            cout << "Invalid Option Selected!\n";
                        break;
                    case 3:
                        // patient case
                        int patient_again;
                        do {
                            cout << "Select Related Option\n1: Book Appointments\n2: Cancel Appointment\n3: Search Appointments\nEnter Here: ";
                            int patient_menu; cin >> patient_menu;

                            if (patient_menu == 1)
                            {
                                cout << "\nBOOKING OPTION\n";
                                pqobj.BookAppointments();
                            }
                            else if (patient_menu == 2)
                            {
                                cout << "\nCANCEL APPOINTMENT OPTION\n";

                                int patientIDToCancel;
                                cout << "Enter Patient ID to cancel appointment: ";
                                cin >> patientIDToCancel;
                                pqobj.CancelAppointments(patientIDToCancel);
                            }
                            else if (patient_menu == 3)
                            {
                                cout << "\nSEARCH APPOINTMENT OPTION\n";
                                cout << "Enter Patient ID to search appointment: ";
                                int patientIDToSearch; cin >> patientIDToSearch;
                                pqobj.SearchAppointments(patientIDToSearch);
                            }
                            else
                                cout << "\nInvalid Option Selected\n";

                            cout << "\nDo You Want to Perform any Task Again?\n Press 1 for YES :: Press 0 for NO\nEnter Here: ";
                            cin >> patient_again;
                        } while (patient_again != 0);

                        // Search for an appointment based on patient ID
                        break;
                    case 4:
                        //emergency case 

                        int emergency_again;
                        do {
                            cout << "\nSelect Related Option:-\n1: Register New Emergency Patients\n2: DIsplay Emergency Patients\n3: Display Old Emergency Patients\n4: Leave Emergency after Recovery\nEnter Here: ";
                            int emergency_menu; cin >> emergency_menu;

                            if (emergency_menu == 1)
                            {

                                int registerEmergencyPatient;
                                cout << "Enter Emergency Patient ID: ";
                                cin >> registerEmergencyPatient;
                                emobj.RegisterEmergencyPatient(registerEmergencyPatient);
                            }
                            else if (emergency_menu == 2)
                            {
                                pqobj.LoadingFunction();
                                emobj.DisplayEmergencyPatients();
                            }
                            else if (emergency_menu == 3)
                            {
                                pqobj.LoadingFunction();
                                emobj.DisplayOldEmergencyPatients();
                            }
                            else if (emergency_menu == 4)
                            {
                                pqobj.LoadingFunction();

                                int leavepatientID;
                                cout << "Enter Patient ID: ";
                                cin >> leavepatientID;
                                emobj.LeaveEmergency(leavepatientID);
                            }
                            else
                                cout << "\nInvalid Input\n";

                            cout << "\nDo You Want to Perform any Task Again?\n Press 1 for YES :: Press 0 for NO\nEnter Here: ";
                            cin >> emergency_again;
                        } while (emergency_again != 0);

                        break;
                    case 5:
                        // Administrator case
                        cout << "ACCESS DIRECTORY OPTION\n";
                        pqobj.LoadingFunction();

                        int admin_again;
                        do {

                            cout << "\nSelect Related Option:-\n1: Access Directory\n2: View Admitted Patients\n3: Display Old Patients\n4: Search Admitted Patients\n5: Search Old Patients\n";
                            cout << "6: Display Emergency Patients\n7: Display Old Emergency Patients\n8: Search Emergency Patients\nEnter Here: ";
                            int admin_menu; cin >> admin_menu;
                            if (admin_menu == 1)
                            {
                                // Access Directory
                                pqobj.LoadingFunction();
                                hospital.loadRecords("hospital_records.txt");

                                int choice;
                                do {
                                    cout << "\nHospital Directory Menu:" << endl;
                                    cout << "1. Insert Record\n";
                                    cout << "2. Delete Record\n";
                                    cout << "3. Update Record\n";
                                    cout << "4. Search Record\n";
                                    cout << "5. Display All Records\n";
                                    cout << "6. Sort Records Alphabetically\n";
                                    cout << "7. Save Records\n";
                                    cout << "9. Exit\n";
                                    cout << "Enter your choice: ";
                                    cin >> choice;
                                    cin.ignore(); // Clear the input buffer

                                    switch (choice) {
                                    case 1: {
                                        int option;
                                        cout << "Enter your below option\n"
                                            << "1- Doctor\n"
                                            << "2- Nurse\n";
                                        cin >> option;

                                        if (option == 1)
                                        {
                                            Doctor* newDoctor = hospital.createDoctor();
                                            hospital.insertRecord(newDoctor);
                                            break;
                                        }
                                        else if (option == 2)
                                        {
                                            // Add Nurse functionality here if needed
                                        }
                                    }
                                    case 2: {
                                        int idToDelete;
                                        cout << "Enter Doctor ID to delete: ";
                                        cin >> idToDelete;
                                        cin.ignore(); // Clear the input buffer
                                        hospital.deleteRecord(idToDelete);
                                        break;
                                    }
                                    case 3: {
                                        int idToUpdate;
                                        cout << "Enter Doctor ID to update: ";
                                        cin >> idToUpdate;
                                        cin.ignore(); // Clear the input buffer
                                        hospital.updateRecord(idToUpdate);
                                        break;
                                    }
                                    case 4: {
                                        int idToSearch;
                                        cout << "Enter Doctor ID to search: ";
                                        cin >> idToSearch;
                                        cin.ignore(); // Clear the input buffer
                                        hospital.searchRecord(idToSearch);
                                        break;
                                    }
                                    case 5: {
                                        hospital.displayAllRecords();
                                        break;
                                    }
                                    case 6: {
                                        hospital.sortRecordsAlphabetical();
                                        break;
                                    }
                                    case 7: {
                                        // Save records automatically without asking for a file name
                                        hospital.saveRecords();
                                        cout << "Records saved successfully." << endl;
                                        break;
                                    }
                                    case 9: {
                                        cout << "Exiting program. Goodbye!" << endl;
                                        break;
                                    }
                                    default:
                                        cout << "Invalid choice. Please enter a valid option." << endl;
                                    }
                                } while (choice != 9);

                            }
                            else if (admin_menu == 2)
                            {
                                // View Admitted Patients
                                pqobj.LoadingFunction();
                                pqobj.DisplayAdmittedPatients();
                            }
                            else if (admin_menu == 3)
                            {
                                //Display Old Patients
                                pqobj.LoadingFunction();
                                pqobj.DisplayOldPatients();
                            }
                            else if (admin_menu == 4)
                            {
                                pqobj.LoadingFunction();

                                //Search Admitted Patients
                                int searchAdmitted_Patients;
                                cout << "Enter Patient ID to Search: ";
                                cin >> searchAdmitted_Patients;
                                pqobj.SearchAdmittedPatient(searchAdmitted_Patients);

                            }
                            else if (admin_menu == 5)
                            {
                                pqobj.LoadingFunction();
                                //Search Old Patients
                                int searchOld_Patients;
                                cout << "Enter Patient ID to Search: ";
                                cin >> searchOld_Patients;
                                pqobj.SearchOldPatient(searchOld_Patients);
                            }
                            else if (admin_menu == 6)
                            {
                                pqobj.LoadingFunction();
                                emobj.DisplayEmergencyPatients();
                            }
                            else if (admin_menu == 7)
                            {
                                pqobj.LoadingFunction();
                                emobj.DisplayOldEmergencyPatients();
                            }
                            else if (admin_menu == 8)
                            {
                                pqobj.LoadingFunction();
                                cout << "Enter Patient ID to Search Emergency Patients: ";
                                int emergencyPatient; cin >> emergencyPatient;
                                emobj.SearchEmergencyPatient(emergencyPatient);
                            }
                            else
                                cout << "Invalid Option Selected!\n";

                            cout << "\nDo You Want to Perform any Task Again?\n Press 1 for YES :: Press 0 for NO\nEnter Here: ";
                            cin >> admin_again;
                        } while (admin_again != 0);
                        break;

                    case 6:
                        // complaints case
                        cout << "\nLoading";
                        for (int i = 0; i < 5; i++)
                        {
                            cout << ". ";
                            Sleep(500);
                        }
                        cout << endl;

                        cout << "1. Register a Complaint\n2. Display Complaints\nEnter your choice: ";
                        int complaintOption;
                        cin >> complaintOption;
                        if (complaintOption == 1)
                        {
                            string complaintText;
                            cout << "Enter your complaint: ";
                            cin.ignore(); // Clear the buffer
                            getline(cin, complaintText);
                            pqobj.RegisterComplaint(complaintText);
                        }
                        else if (complaintOption == 2)
                        {
                            pqobj.DisplayComplaints();
                        }
                        else
                        {
                            cout << "Invalid option.\n";
                        }
                        break;

                        break;
                    case 7:
                        // Games
                        LoadingScreen();

                        do
                        {

                            cout << "(A) for Tic_Tac_Toe\n";
                            cout << "(B) for Rock_Paper_Scissor\n";
                            cin >> GamesMenuSelection;

                            GamesMenuSelection = toupper(GamesMenuSelection);

                            if (GamesMenuSelection != 'A' && GamesMenuSelection != 'B')
                            {
                                cout << "Invalid selection, Kindly choose from one of the options below:\n";
                            }

                        } while (!(GamesMenuSelection == 'A' || GamesMenuSelection == 'B'));

                        switch (GamesMenuSelection)
                        {
                        case 'A':
                        {
                            //variable declarations
                            int Round{ 1 };
                            char Board[3][3], Winner{ 'Z' }, WhoseTurn{ 'Z' }, BoxValidation{ 'Y' }, BeforeStartChoice{ 0 };
                            int Box{ 0 }, BoxesFilled{ 0 };

                            LoadingScreen();

                            Initialize(Board);                                        //Initializing array to our value, not passing second value so it will resort to default value set in funtion parameter

                            cout << "WELCOME TO TICK TAC TOE\n\n";
                            while (!(BeforeStartChoice == 'A' || BeforeStartChoice == 'B'))
                            {
                                cout << "Select one of the the options below\n";
                                cout << "(A) if you want to play the game\n";
                                cout << "(B) if you want to know on how to play the game\n";
                                cin >> BeforeStartChoice;

                                BeforeStartChoice = toupper(BeforeStartChoice);
                                if (BeforeStartChoice != 'A' && BeforeStartChoice != 'B')
                                {
                                    cout << "Invalid choice, Try again\n";
                                }
                            }
                            switch (BeforeStartChoice)
                            {
                            case 'A':
                            {
                            P:
                                while (!(Winner == 'F' || Winner == 'S'))
                                {
                                    cout << "\nROUND " << Round << "\n";

                                    //Player 1 section
                                    WhoseTurn = 'F';
                                    BoxesFilled++;

                                    InputFromPlayers(Box, Board, WhoseTurn, BoxValidation);

                                    DisplayBoard(Board);
                                    Winner = WhoWon(CheckWin(Board));

                                    if (Winner == 'F')
                                    {
                                        cout << "Player 1 wins\n";
                                        break;
                                    }

                                    if (BoxesFilled >= 9)                                   //Since there can't be more than 9 boxes and 9 turns
                                    {
                                        cout << "The game is a tie\n";
                                        break;
                                    }

                                    //Player 2 section
                                    WhoseTurn = 'S';
                                    BoxesFilled++;

                                    InputFromPlayers(Box, Board, WhoseTurn, BoxValidation);

                                    DisplayBoard(Board);
                                    Winner = WhoWon(CheckWin(Board));

                                    if (Winner == 'S')
                                    {
                                        cout << "Player 2 wins\n";
                                        break;
                                    }
                                    Round++;
                                }

                                break;
                            }
                            case 'B':
                            {
                                char PlayGame{ 0 };
                                cout << "In this game the boxes go from left to right and are labelled as follows:\n";
                                cout << "| 1 | 2 | 3 |\n\n";
                                cout << "| 4 | 5 | 6 |\n\n";
                                cout << "| 7 | 8 | 9 |\n\n";
                                cout << "The game finishes when anyone of the players sucessflly makes a line such as\n";
                                cout << "| T | - | - |\n\n";
                                cout << "| - | T | - |\n\n";
                                cout << "| - | - | T |\n\n";
                                cout << "In this case the game is won by the player with the 'TICK MARK'\n";

                                cout << "Would you like to play the game now?\n";
                                cout << "(Y) for yes\n";
                                cout << "(N) for no\n";
                                cin >> PlayGame;

                                PlayGame = toupper(PlayGame);

                                if (PlayGame == 'Y')
                                {
                                    goto P;
                                    system("CLS");
                                }

                                break;
                            }
                            default:
                            {
                                cout << "THIS SHOULD NEVER EXECUTE\n";
                                break;
                            }
                            }

                            break;
                        }
                        case 'B':
                        {
                            char Player1{ 0 }, Player2{ 0 }, Winner{ 0 }, UserChoice{ 0 }, ValidChoice{ 0 };

                            LoadingScreen();

                            cout << "Welcome to the game of Rock, Papers and scissor\n";

                            while (!(UserChoice == 'H' || UserChoice == 'C'))
                            {
                                cout << "To get started select one of the following options:\n";
                                cout << "(H) to play Human vs Human\n";
                                cout << "(C) to play Human vs Computer\n";
                                cin >> UserChoice;

                                UserChoice = toupper(UserChoice);

                                switch (UserChoice)
                                {
                                case 'H':
                                {
                                    LoadingScreen();
                                    system("CLS");

                                    //This loop validates the first players choice
                                    do
                                    {
                                        cout << "Player one select one of the following:\n";
                                        RockPaperScissorMenuDisplay();
                                        cin >> Player1;
                                        Player1 = toupper(Player1);

                                        IsValidSelection(ValidChoice, Player1);
                                    } while (ValidChoice != 'V');

                                    //This loop validates the second players choice
                                    do
                                    {
                                        cout << "Player two select one of the following:\n";
                                        RockPaperScissorMenuDisplay();
                                        cin >> Player2;
                                        Player2 = toupper(Player2);

                                        IsValidSelection(ValidChoice, Player2);
                                    } while (ValidChoice != 'V');

                                    WinCheck_R_P_S(Player1, Player2, Winner);

                                    WhoWon_R_P_S(Winner, UserChoice);

                                    PlayAgain(UserChoice);

                                    break;
                                }
                                case 'C':
                                {
                                    LoadingScreen();
                                    system("CLS");

                                    //This loop validates the first players choice
                                    do
                                    {
                                        cout << "Player select one of the following:\n";
                                        RockPaperScissorMenuDisplay();
                                        cin >> Player1;
                                        Player1 = toupper(Player1);

                                        IsValidSelection(ValidChoice, Player1);
                                    } while (ValidChoice != 'V');

                                    cout << "\n......Computer is picking......\n\n";
                                    Sleep(2000);
                                    ComputerPick(Player2);

                                    cout << "Computer picked " << Player2 << "\n";

                                    WinCheck_R_P_S(Player1, Player2, Winner);

                                    WhoWon_R_P_S(Winner, UserChoice);

                                    PlayAgain(UserChoice);

                                    break;
                                }
                                default:
                                {
                                    cout << "Invalid choice, Kindly select from one of the options above\n";
                                    Sleep(2000);
                                    system("CLS");
                                    break;
                                }
                                }
                            }

                            break;
                        }
                        default:
                        {
                            cout << "Should not execute\n";
                            break;
                        }
                        }
                        break;
                    case 8:
                        // Add your menu options here

                        int menuOption1;
                        cout << "Enter a menu option: ";
                        cin >> menuOption1;

                        if (menuOption1 == 9) //-------------Changing Password-------------
                        {
                            changePassword(password);
                        }
                        break;
                    case 9:
                        //Quiting program
                        cout << "\nQuiting Program.Loading";
                        for (int i = 0; i < 5; i++)
                        {
                            cout << ". ";
                            Sleep(500);
                        }
                        cout << endl;

                        exit(0);
                        break;
                    default:
                        cout << "Invalid Queue!\n";
                    }

                    cout << "\nDo you want to go to main Screen?\nPress 1 for Yes :: Press 0 for NO\nEnter Here: ";
                    int Again_mainMenu; cin >> Again_mainMenu;

                    if (Again_mainMenu == 0)
                    {
                        signaltoQuit = true;
                    }
                    else if (Again_mainMenu == 1)
                    {
                        goto MainMenu;
                    }
                    else
                        cout << "\nInvalid Input\n";
                } while (!signaltoQuit);

            }
        }
    }


    

    return 0;
}


// Function Prototypes of the Games
//function definitions for Tic_Tac_Toe
void Initialize(char BoardValueSet[3][3], char SetTo)
{
    for (int i{ 0 }; i < 3; i++)
    {
        for (int j{ 0 }; j < 3; j++)
        {
            BoardValueSet[i][j] = SetTo;
        }
    }
}

void DisplayBoard(char BoardReceive[3][3])
{
    for (int i{ 0 }; i < 3; i++)
    {
        cout << "\n | ";

        for (int j{ 0 }; j < 3; j++)
        {
            cout << BoardReceive[i][j] << " | ";
        }
        cout << endl;
    }
}

void InputFromPlayers(int& Box, char Board[3][3], char WhoseTurn, char& BoxValidation)
{
    if (WhoseTurn == 'F')
    {
        cout << "\nPlayer 1 enter the box where you want to place your marker: ";
    }
    else
    {
        cout << "\nPlayer 2 enter the box where you want to place your marker: ";
    }

    cin >> Box;

    while (cin.fail())
    {
        cout << "\nInvalid Input, Try again";
        cin.clear();                                                                     //clears the error flags with cin
        cin.ignore(1000, '\n');                                                         //ignore the next 1000 characters or upto \n
        cout << "\nEnter valid box no: ";
        cin >> Box;
    }

    SetPosition(Board, WhoseTurn, BoxValidation, Box);

    if (BoxValidation == 'I' || BoxValidation == 'O')
    {
        InputValidation(BoxValidation, Board, WhoseTurn, Box);
    }
}

void InputValidation(char BoxValidation, char Board[3][3], char WhoseTurn, int& Box)
{
    if (BoxValidation == 'I')
    {
        cout << "\nThe box you selected is already occupied please select again: ";
        cin >> Box;
        SetPosition(Board, WhoseTurn, BoxValidation, Box);
        InputValidation(BoxValidation, Board, WhoseTurn, Box);
    }
    if (BoxValidation == 'O')
    {
        cout << "\nThe box you selected doesn't exist please select again: ";
        cin >> Box;
        SetPosition(Board, WhoseTurn, BoxValidation, Box);
        InputValidation(BoxValidation, Board, WhoseTurn, Box);
    }
}

char CheckWin(char ReceiveBoard[3][3])
{
    char FirstValue{ 'X' };
    for (int i{ 0 }; i < 3; i++)
    {
        FirstValue = ReceiveBoard[i][0];
        if (FirstValue == ReceiveBoard[i][1] && FirstValue == ReceiveBoard[i][2])
        {
            return FirstValue;
        }

        FirstValue = ReceiveBoard[0][i];
        if (FirstValue == ReceiveBoard[1][i] && FirstValue == ReceiveBoard[2][i])
        {
            return FirstValue;
        }

        FirstValue = ReceiveBoard[1][1];
        if (FirstValue == ReceiveBoard[0][0] && FirstValue == ReceiveBoard[2][2])
        {
            return FirstValue;
        }
        if (FirstValue == ReceiveBoard[0][2] && FirstValue == ReceiveBoard[2][0])
        {
            return FirstValue;
        }
    }
    return 'N';
}

char WhoWon(char CheckWinner)
{
    if (CheckWinner == 'T')
    {
        return 'F';
    }

    if (CheckWinner == 'X')
    {
        return 'S';
    }

    return 'N';
}

void SetPosition(char ReceiveBoard[3][3], char WhoseTurn, char& ValidMove, int BoxNo)
{
    switch (BoxNo)
    {
    case 1:
    {
        if (ReceiveBoard[0][0] == '-' && WhoseTurn == 'F')
        {
            ReceiveBoard[0][0] = 'T';
            ValidMove = 'V';
        }
        else if (ReceiveBoard[0][0] == '-' && WhoseTurn == 'S')
        {
            ReceiveBoard[0][0] = 'X';
            ValidMove = 'V';
        }
        else
        {
            ValidMove = 'I';
        }
        break;
    }
    case 2:
    {
        if (ReceiveBoard[0][1] == '-' && WhoseTurn == 'F')
        {
            ReceiveBoard[0][1] = 'T';
            ValidMove = 'V';
        }
        else if (ReceiveBoard[0][1] == '-' && WhoseTurn == 'S')
        {
            ReceiveBoard[0][1] = 'X';
            ValidMove = 'V';
        }
        else
        {
            ValidMove = 'I';
        }
        break;
    }
    case 3:
    {
        if (ReceiveBoard[0][2] == '-' && WhoseTurn == 'F')
        {
            ReceiveBoard[0][2] = 'T';
            ValidMove = 'V';
        }
        else if (ReceiveBoard[0][2] == '-' && WhoseTurn == 'S')
        {
            ReceiveBoard[0][2] = 'X';
            ValidMove = 'V';
        }
        else
        {
            ValidMove = 'I';
        }
        break;
    }
    case 4:
    {
        if (ReceiveBoard[1][0] == '-' && WhoseTurn == 'F')
        {
            ReceiveBoard[1][0] = 'T';
            ValidMove = 'V';
        }
        else if (ReceiveBoard[1][0] == '-' && WhoseTurn == 'S')
        {
            ReceiveBoard[1][0] = 'X';
            ValidMove = 'V';
        }
        else
        {
            ValidMove = 'I';
        }
        break;
    }
    case 5:
    {
        if (ReceiveBoard[1][1] == '-' && WhoseTurn == 'F')
        {
            ReceiveBoard[1][1] = 'T';
            ValidMove = 'V';
        }
        else if (ReceiveBoard[1][1] == '-' && WhoseTurn == 'S')
        {
            ReceiveBoard[1][1] = 'X';
            ValidMove = 'V';
        }
        else
        {
            ValidMove = 'I';
        }
        break;
    }
    case 6:
    {
        if (ReceiveBoard[1][2] == '-' && WhoseTurn == 'F')
        {
            ReceiveBoard[1][2] = 'T';
            ValidMove = 'V';
        }
        else if (ReceiveBoard[1][2] == '-' && WhoseTurn == 'S')
        {
            ReceiveBoard[1][2] = 'X';
            ValidMove = 'V';
        }
        else
        {
            ValidMove = 'I';
        }
        break;
    }
    case 7:
    {
        if (ReceiveBoard[2][0] == '-' && WhoseTurn == 'F')
        {
            ReceiveBoard[2][0] = 'T';
            ValidMove = 'V';
        }
        else if (ReceiveBoard[2][0] == '-' && WhoseTurn == 'S')
        {
            ReceiveBoard[2][0] = 'X';
            ValidMove = 'V';
        }
        else
        {
            ValidMove = 'I';
        }
        break;
    }
    case 8:
    {
        if (ReceiveBoard[2][1] == '-' && WhoseTurn == 'F')
        {
            ReceiveBoard[2][1] = 'T';
            ValidMove = 'V';
        }
        else if (ReceiveBoard[2][1] == '-' && WhoseTurn == 'S')
        {
            ReceiveBoard[2][1] = 'X';
            ValidMove = 'V';
        }
        else
        {
            ValidMove = 'I';
        }
        break;
    }
    case 9:
    {
        if (ReceiveBoard[2][2] == '-' && WhoseTurn == 'F')
        {
            ReceiveBoard[2][2] = 'T';
            ValidMove = 'V';
        }
        else if (ReceiveBoard[2][2] == '-' && WhoseTurn == 'S')
        {
            ReceiveBoard[2][2] = 'X';
            ValidMove = 'V';
        }
        else
        {
            ValidMove = 'I';
        }
        break;
    }
    default:
    {
        ValidMove = 'O';
    }
    }
}

//function definitions for Rock_Paper_Scissor
void RockPaperScissorMenuDisplay()
{
    cout << "(R) for rock\n";
    cout << "(P) for paper\n";
    cout << "(S) for scissor\n";
}

void WinCheck_R_P_S(char PlayerOne, char PlayerTwo, char& Winner)
{
    if (PlayerOne == 'R' && PlayerTwo == 'P')
    {
        Winner = 'S';
    }
    if (PlayerOne == 'R' && PlayerTwo == 'S')
    {
        Winner = 'F';
    }
    if (PlayerOne == 'P' && PlayerTwo == 'R')
    {
        Winner = 'F';
    }
    if (PlayerOne == 'S' && PlayerTwo == 'R')
    {
        Winner = 'S';
    }
    if (PlayerOne == 'P' && PlayerTwo == 'S')
    {
        Winner = 'S';
    }
    if (PlayerOne == 'S' && PlayerTwo == 'P')
    {
        Winner = 'F';
    }
    if (PlayerOne == PlayerTwo)
    {
        Winner = 'T';
    }
}

void ComputerPick(char& CompSelect)
{
    int ComputerRandom{ 0 };

    srand(time(0));
    ComputerRandom = rand() % 3;

    if (ComputerRandom == 0)
    {
        CompSelect = 'R';
    }
    if (ComputerRandom == 1)
    {
        CompSelect = 'P';
    }
    if (ComputerRandom == 2)
    {
        CompSelect = 'S';
    }
}

void WhoWon_R_P_S(char Champ, char UserPicked)
{
    if (Champ == 'F')
    {
        if (UserPicked == 'C')
        {
            cout << "Player has won\n";
        }
        else
        {
            cout << "Player one has won\n";
        }
    }
    if (Champ == 'S')
    {
        if (UserPicked == 'C')
        {
            cout << "Computer has won\n";
        }
        else
        {
            cout << "Player two has won\n";
        }
    }
    if (Champ == 'T')
    {
        cout << "It's a tie\n";
    }
}

void PlayAgain(char& Selection)
{
    char Again{ 0 };
    cout << "\nWould you like to play again?\n";
    cout << "(Y) for yes\n";
    cout << "(N) for no\n";
    cin >> Again;

    Again = toupper(Again);

    if (Again != 'Y' && Again != 'N')
    {
        cout << "Invalid selection, Try again\n";
        PlayAgain(Selection);
    }

    if (Again == 'Y')
    {
        Selection = 'Z';
    }
}

void IsValidSelection(char& ValidChoice, char CurrentChoice)
{
    if (CurrentChoice != 'R' && CurrentChoice != 'P' && CurrentChoice != 'S')
    {
        cout << "Invalid Choice, Try again\n";
        ValidChoice = 'I';
    }
    else
    {
        ValidChoice = 'V';
    }
}

//function definition for fucntions made during compilation
void LoadingScreen() 
{
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tloading screen" << endl;;
    char x = 219;
    cout << "\t\t\t\t";
    for (int i = 0; i <= 67; i++)
    {
        Sleep(100);
        cout << x;

    }
    system("cls");
}