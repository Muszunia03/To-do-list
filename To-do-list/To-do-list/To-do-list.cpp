
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <fstream>
using namespace std;

#define MAX_NAME_LEN 120
#define MAX_DESC_LEN 120
#define MAX_TYPE_LEN 10


class Task {

protected:

    string name;
    string date;
    string type;
    string description;
    bool completed;

public:

    Task(const string& name, const string& date, const string& type, const string& desc) :name(name), date(date), type(type), description(desc),completed(false) {}

    string GetName() const {
        return name;
    }

    string GetDate() const {
        return date;
    }

    string GetType() const {
        return type;
    }

    string GetDesc() const {
        return description;
    }

    bool IsCompleted() const {
        return completed;
    }

    void SetName(const string& name) {
        this->name = name;
    }

    void SetDate(const string& date) {
        this->date = date;
    }

    void SetType(const string& type) {
        this->type = type;
    }

    void SetDesc(const string& description) {
        this->description = description;
    }

    void SetCompletenes() {
        completed = true;
    }

    void SetWaitingAction() {
        completed = false;
    }

    void DisplayTask() {
        cout << type << "-";
        cout << name << "-";
        cout << date << "-";
        cout << description << "-";
        cout << "completenes: ";
        if (completed == true) {
            cout << "completed" << " \n";
        }
        else {
            cout << "waiting action" << " \n";
        }
        
    }

};

class To_do_list {

protected:

    std::vector <Task> tasks;

    bool isValidType(const std::string& input) {

        std::regex typePattern(R"(^(Work|Personal|Study|Exercise|Shopping|Social|Hobbies|Chores|Appointments)$)");

        return std::regex_match(input, typePattern);
    }

public:

    void Menu() {
        cout << "\n- To-Do List Menu -\n";
        cout << "1. Display Tasks\n";
        cout << "2. Add Task\n";
        cout << "3. Delete Task\n";
        cout << "4. Mark Task as Completed\n";
        cout << "5. Mark Task as Ucompleted\n";
        cout << "6. Edit Task\n";
        cout << "7. Save and exit\n";
        cout << "8. Exit without saving\n" << endl;
    }

    void TasksList() {
        for (int i = 0; i < tasks.size(); i++) {
            cout << i+1 << ". ";
            tasks[i].DisplayTask();
        }
    }

    void DisplayVector() {
        if (tasks.empty()) {
            cout << "No tasks to display!" << endl;
            return;
            run();
        }
        TasksList();   { 
            run();
        }
    }

    void AddTask() {
        string name, desc, type, date;
        string output;
        string input;

        cout << "Are you sure you want to add a task? (Y for YES, other for NO)\n";
        cin >> output;
        cin.ignore();

        if (output == "Y") {
            cout << "Enter Type of Activity you want to add: \n (Choose from: Work, Personal, Study, Exercise, Shopping, Social, Hobbies, Chores, Appointments) ";
            bool valid = false;

            while (!valid) {
                getline(cin, type);
                if (isValidType(type)) {
                    valid = true;
                    cout << "Valid type entered: " << type << endl;
                }
                else {
                    cout << "Invalid type. Please enter a valid type." << endl;
                }
            }

            cout << "Enter Name of Task you want to add:  (30 char MAX): ";
            getline(cin, name);
            if (name.length() > 30) {
                name = name.substr(0, 30);
            }

            cout << "Enter Desc. of Task you want to add: (256 char MAX): ";
            getline(cin, desc);
            if (desc.length() > 256) {
                desc = desc.substr(0, 256);
            }

            cout << "Enter Date of Task you want to add: ";
            getline(cin, date);

            tasks.emplace_back(name, date, type, desc);
            cout << "Task added, Yay ;D \n";
            run();

        }
        else {
            cout << "Ok, lets go back to the start then";
            run();
        }
    };

    void DeleteTask() {

        int number;

        if (tasks.empty()) {
            cout << "Nothing to delete :C \n";
            return;
            run();
        }
        TasksList();
        cout << "Which task you want to delete (Write number of task): ";
        cin >> number;
        if (number >= 1 && number <= tasks.size()) {
            tasks.erase(tasks.begin() + number - 1);
            cout << "Success, you have deleted the task :D\n";
            run();
        }
        else {
            cout << "invalid number of task inserted :C\n";
            DeleteTask();
        }

    }

    void Completed() {
        int number;
        if (tasks.empty()) {
            cout << "Nothing to complete :C \n";
            return;
        }

        TasksList();

        cout << "Which Task Mark as Completed?: ";
        cin >> number;
        if (number >= 1 && number <= tasks.size()) {
            if (tasks[number - 1].IsCompleted()) {
                cout << "This task is already completed :)\n";
            }
            else {
                tasks[number - 1].SetCompletenes();
                cout << "Success, you have completed the task :D\n";
            }
        }
        else {
            cout << "Invalid number of task inserted :C\n";
        }
        run();
    }

    void WaitingAction() {
        int number;
        if (tasks.empty()) {
            cout << "Nothing to complete :C \n";
            return;
        }

        TasksList();

        cout << "Which Task Mark as Waiting Action?: ";
        cin >> number;
        if (number >= 1 && number <= tasks.size()) {
            if (!tasks[number - 1].IsCompleted()) {
                cout << "This task is already marked as waiting action :)\n";
            }
            else {
                tasks[number - 1].SetWaitingAction();
                cout << "Why changing it back? Ok, nvm, I understand\n";
            }
        }
        else {
            cout << "Invalid number of task inserted :C\n";
        }
        run();
    }

    void EditTask() {
        string completenes;
        string type;
        if (tasks.empty()) {
            cout << "No tasks to edit!" << endl;
            return;
        }
        cout << "Tasks:" << endl;

        for (int i = 0; i < tasks.size(); ++i) {
            if (tasks[i].IsCompleted() == 0) {
                completenes = "Completed";
            }
            else {
                completenes = "Waiting Action";
            }
            cout << i + 1 << ". " << tasks[i].GetType() << "-" << tasks[i].GetName() << "-" << tasks[i].GetDate() << "-" << tasks[i].GetDesc() << "-" << completenes << endl;
        }
        cout << "Enter the task number to edit: ";
        int number;
        cin >> number;
        cin.ignore(); // Ignore remaining newline character

        if (number >= 1 && number <= tasks.size()) {
            Task& task = tasks[number - 1];
            string type, name, description, dueDate;

            cout << "Enter new type (current: " << task.GetType() << "): ";
            bool valid = false;
            while (!valid) {
                getline(cin, type);
                if (isValidType(type)) {
                    valid = true;
                }
                else {
                    cout << "Invalid type. Please enter a valid type." << endl;
                    cout << "Enter new type (current: " << task.GetType() << "): ";
                }
            }

            cout << "Enter new task name (current: " << task.GetName() << "): ";
            getline(cin, name);

            cout << "Enter new task description (current: " << task.GetDesc() << "): ";
            getline(cin, description);

            cout << "Enter new task due date (current: " << task.GetDate() << "): ";
            getline(cin, dueDate);

            task.SetType(type);
            task.SetName(name);
            task.SetDesc(description);
            task.SetDate(dueDate);
            cout << "Task updated successfully!" << endl;
            run();
        }
        else {
            cout << "Invalid task number!" << endl;
            run();
        }
    }

    void GetFromFile() {
        ifstream file("tasks.txt");
        string line;
        regex pattern(R"(([^-]+)-([^-]+)-([^-]+)-([^-\n]+)-(Completed|Waiting Action))");
        smatch matches;

        if (file.is_open()) {
            while (getline(file, line)) {
                if (regex_match(line, matches, pattern)) {
                    string type = matches[1].str();
                    string name = matches[2].str();
                    string date = matches[3].str();
                    string description = matches[4].str();
                    bool completed = matches[5].str() == "Completed";

                    tasks.emplace_back(name, date, type, description);
                    if (completed) {
                        tasks.back().SetCompletenes();
                    }
                }
                else {
                    cout << "Line not matching expected format: " << line << endl;
                }
            }
            file.close();
            cout << "Tasks successfully loaded from file" << endl;
        }
        else {
            cout << "Error while opening the file" << endl;
        }
    }

    void SaveToFile() {


        ofstream outFile("tasks.txt");
        if (!outFile) {
            cerr << "Error with the output file opening \n";
            return;
        }

        for (const auto& task : tasks) {
            outFile << task.GetType() << '-' << task.GetName() << '-' << task.GetDate() << '-' << task.GetDesc() << '-' << (task.IsCompleted() ? "Completed" : "Waiting Action") << '\n';
        }

        outFile.close();
        cout << "Tasks successfully saved to " << "tasks.txt" << endl;
    
    }

    void run() {
        Menu();
        int choice;
        cout << "What do you want to do? " << endl;
        cin >> choice;
        cout << endl;
            switch (choice) {
            case 1:
                DisplayVector();
                break;
            case 2:
                AddTask();
                break;
            case 3:
                DeleteTask();
                break;
            case 4:
                Completed();
                break;
            case 5:
                WaitingAction();
                break;
            case 6:
                EditTask();
                break;
            case 7:
                SaveToFile();
                cout << "Exiting Program, Everything is saved. Have a nice day. Cya!\n";
                break;
            case 8:
                cout << "Exiting Program. Have a nice day. Cya!\n";
                break;
            default:
                cout << "Invalid choice. Try Again";
        }

    }
};

int main()
{
    std::cout << "Hello World!\n";
    To_do_list ToDoList;
    ToDoList.GetFromFile();
    ToDoList.run();
}


