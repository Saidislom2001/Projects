#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void loadTasks(vector<string>& tasks) {
    ifstream file("tasks.txt");
    string task;

    while (getline(file, task)) {
        if (!task.empty()) {
            tasks.push_back(task);
        }
    }
    file.close();
}

void saveTasks(const vector<string>& tasks) {
    ofstream file("tasks.txt");

    for (const string& task : tasks) {
        file << task << endl;
    }

    file.close();
}

void viewTasks(const vector<string>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks available." << endl;
    } else {
        cout << "Your tasks:" << endl;
        for (size_t i = 0; i < tasks.size(); i++) {
            cout << i + 1 << ". " << tasks[i] << endl;
        }
    }
}

void addTask(vector<string>& tasks) {
    string task;

    cout << "Enter task: ";
    cin.ignore();
    getline(cin, task);

    if (!task.empty()) {
        tasks.push_back(task);
        saveTasks(tasks);
        cout << "Task added successfully.\n";
    } else {
        cout << "Task cannot be empty.\n";
    }
}

void removeTask(vector<string>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks to remove." << endl;
        return;
    }

    viewTasks(tasks);
    size_t taskNumber;

    cout << "Enter the number of the task to remove: ";
    cin >> taskNumber;

    if (taskNumber < 1 || taskNumber > tasks.size()) {
        cout << "Invalid task number.\n";
    } else {
        tasks.erase(tasks.begin() + taskNumber - 1);
        saveTasks(tasks);
        cout << "Task removed successfully.\n";
    }
}

int main() {
    vector<string> tasks;
    loadTasks(tasks);

    int choice;

    do {
        cout << "\n===== To-Do List Manager =====\n";
        cout << "1. View tasks\n";
        cout << "2. Add task\n";
        cout << "3. Delete task\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewTasks(tasks);
                break;
            case 2:
                addTask(tasks);
                break;
            case 3:
                removeTask(tasks);
                break;
            case 4:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}