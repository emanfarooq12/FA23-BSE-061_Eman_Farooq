#include <iostream>
using namespace std;

class Patient
{
public:
  string name;
  int orderOfArrival;
  string condition;
  int severityLevel;
  Patient *next;

  Patient(string name, int orderOfArrival, string condition, int severityLevel)
  {
    this->name = name;
    this->orderOfArrival = orderOfArrival;
    this->condition = condition;
    this->severityLevel = severityLevel;
    next = NULL;
  }
};

// Class for Patient List
class PatientList
{
public:
  Patient *head;
  Patient *tail;

  PatientList()
  {
    head = tail = NULL;
  }

  void addPatientByPriority(string name, int orderOfArrival, string condition, int severityLevel)
  {
    Patient *newPatient = new Patient(name, orderOfArrival, condition, severityLevel);

    // If there are no patients in the list
    if (head == NULL)
    {
      head = tail = newPatient;
      return;
    }

    // New Patient with the Highest Severity
    if (severityLevel < head->severityLevel)
    {
      newPatient->next = head;
      head = newPatient;
      return;
    }
    Patient *current = head;
    Patient *previous = NULL;

    // Patient with Intermediate Severity
    while (current != NULL && current->severityLevel <= severityLevel)
    {
      previous = current;
      current = current->next;
    }

    previous->next = newPatient;
    newPatient->next = current;

    // Patient with the Lowest Severity
    if (current == NULL)
    {
      tail = newPatient;
    }
  }

  // View Patient List
  void viewPatients()
  {
    cout << "===================View Patient List=======================" << endl;
    Patient *current = head;
    if (current == NULL)
    {
      cout << "No patients available.\n";
      return;
    }
    while (current != NULL)
    {
      cout << "Name: " << current->name << "  Arrival Order: "
           << current->orderOfArrival << "  Condition: " << current->condition << "  Severity: " << current->severityLevel << endl;
      current = current->next;
    }
  }
};

int main()
{
  PatientList patientQueue;
  int exitFlag = 0;
  while (exitFlag != 1)
  {
    cout << "====================Medical Scheduling========================" << endl;
    cout << "1) Add Patient" << endl;
    cout << "2) View Patients" << endl;
    cout << "3) Exit" << endl;
    cout << "--------------------------------------------------------------" << endl;

    int choice;
    cout << "Enter Your Choice: ";
    cin >> choice;

    if (choice == 1)
    {
      cout << "====================Add Patient========================" << endl;
      string name;
      int orderOfArrival;
      string condition;
      int severityLevel;

      cout << "Enter Patient Name: ";
      cin >> name;

      cout << "Enter Arrival Order: ";
      cin >> orderOfArrival;

      cout << "Enter Condition: ";
      cin.ignore();
      getline(cin, condition);

      // Set Severity Level Based on Condition
      if (condition == "Heart Attack" || condition == "Stroke")
        severityLevel = 1;
      else if (condition == "Broken Leg" || condition == "Severe Burn" || condition == "Fractured Arm")
        severityLevel = 2;
      else if (condition == "Fever" || condition == "Food Poisoning" || condition == "Migraine")
        severityLevel = 3;
      else if (condition == "Mild Cold" || condition == "Small Cut")
        severityLevel = 4;
      else
      {
        cout << "Invalid condition entered.\n";
        continue;
      }

      patientQueue.addPatientByPriority(name, orderOfArrival, condition, severityLevel);
    }
    else if (choice == 2)
    {
      patientQueue.viewPatients();
    }
    else if (choice == 3)
    {
      exitFlag = 1;
      cout << "Exiting the program...\n";
      break;
    }
    else
    {
      cout << "Invalid choice. Try again!\n";
    }
  }
  return 0;
}
