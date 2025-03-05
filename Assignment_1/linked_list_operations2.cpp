2. C++ Implementation

#include <iostream>
#include <string>

using namespace std;

// Structure for a Task node
struct Task {
    int taskID;
    string description;
    int priority;
    Task* next;
};

// Class for Task Management System
class TaskManager {
private:
    Task* head;  // Head pointer to the linked list

public:
    // Constructor
    TaskManager() {
        head = nullptr;
    }

    // Function to add a new task in priority order
    void addTask(int id, string desc, int priority) {
        Task* newTask = new Task{id, desc, priority, nullptr};

        // If list is empty or new task has highest priority, insert at head
        if (!head || newTask->priority > head->priority) {
            newTask->next = head;
            head = newTask;
        } else {
            // Insert in sorted order based on priority
            Task* temp = head;
            while (temp->next && temp->next->priority >= newTask->priority) {
                temp = temp->next;
            }
            newTask->next = temp->next;
            temp->next = newTask;
        }
        cout << "Task added successfully!\n";
    }

    // Function to remove the highest priority task (from the start)
    void removeHighestPriorityTask() {
        if (!head) {
            cout << "No tasks to remove!\n";
            return;
        }
        Task* temp = head;
        head = head->next;
        cout << "Removed task with ID: " << temp->taskID << " (Highest Priority Task)\n";
        delete temp;
    }

    // Function to remove a task by its ID
    void removeTaskByID(int id) {
        if (!head) {
            cout << "No tasks to remove!\n";
            return;
        }
        if (head->taskID == id) {
            Task* temp = head;
            head = head->next;
            delete temp;
            cout << "Task with ID " << id << " removed successfully!\n";
            return;
        }
        Task* temp = head;
        while (temp->next && temp->next->taskID != id) {
            temp = temp->next;
        }
        if (!temp->next) {
            cout << "Task with ID " << id << " not found!\n";
            return;
        }
        Task* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        cout << "Task with ID " << id << " removed successfully!\n";
    }

    // Function to view all tasks
    void viewTasks() {
        if (!head) {
            cout << "No tasks available!\n";
            return;
        }
        Task* temp = head;
        cout << "\nTask List (Sorted by Priority):\n";
        while (temp) {
            cout << "ID: " << temp->taskID << ", Description: " << temp->description
                 << ", Priority: " << temp->priority << "\n";
            temp = temp->next;
        }
    }

    // Destructor to free memory
    ~TaskManager() {
        while (head) {
            Task* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Main function with menu
int main() {
    TaskManager tm;
    int choice, id, priority;
    string description;

    do {
        cout << "\nTask Management System\n";
        cout << "1. Add a New Task\n";
        cout << "2. View All Tasks\n";
        cout << "3. Remove the Highest Priority Task\n";
        cout << "4. Remove a Task by ID\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Task ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Task Description: ";
                getline(cin, description);
                cout << "Enter Task Priority: ";
                cin >> priority;
                tm.addTask(id, description, priority);
                break;

            case 2:
                tm.viewTasks();
                break;

            case 3:
                tm.removeHighestPriorityTask();
                break;

            case 4:
                cout << "Enter Task ID to remove: ";
                cin >> id;
                tm.removeTaskByID(id);
                break;

            case 5:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}


---

.