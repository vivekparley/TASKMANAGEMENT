#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <cmath>

using namespace std;

// Task structure definition
struct Task {
    string name;
    string category;
    chrono::system_clock::time_point deadline;
    string location;
    int points;
    int total_days;
    int days_left;
    int people_required;
    int people_working;
    int progress;
    int dynamicPriority;
    vector<string> dependencies;

    // Comparator to order tasks by dynamic priority and deadline
    bool operator<(const Task& other) const {
        if (dynamicPriority == other.dynamicPriority) {
            return deadline > other.deadline; // Earlier deadline has higher priority
        }
        return dynamicPriority < other.dynamicPriority; // Higher dynamic priority has higher priority
    }
};

// Function to calculate the dynamic priority of a task
int calculatePriority(int basePoints, int totalDays, int daysLeft, int peopleRequired, int peopleWorking, double progress) {
    int priority = basePoints;
    double scalingFactor = static_cast<double>(priority) / totalDays;
    int dayPenalty = static_cast<int>(scalingFactor * (totalDays - daysLeft));
    priority += dayPenalty;
    int peoplePenalty = static_cast<int>((peopleRequired - peopleWorking) * scalingFactor);
    priority += peoplePenalty;
    double progressPenalty = progress / 100.0;
    priority *= (1 - progressPenalty);
    return round(priority);
}

// Function to convert a string to a time_point
chrono::system_clock::time_point stringToTimePoint(const string& dateTime) {
    tm t = {};
    istringstream ss(dateTime);
    ss >> get_time(&t, "%Y-%m-%d %H:%M");
    t.tm_isdst = -1; // Not set by get_time; tell mktime to determine DST
    return chrono::system_clock::from_time_t(mktime(&t));
}

// Function to convert a time_point to a string
string timePointToString(const chrono::system_clock::time_point& tp) {
    time_t time = chrono::system_clock::to_time_t(tp);
    tm *tm = localtime(&time);
    ostringstream oss;
    oss << put_time(tm, "%Y-%m-%d %H:%M");
    return oss.str();
}

// Function to update the dynamic priority of a task
void updateDynamicPriority(Task& task) {
    task.dynamicPriority = calculatePriority(task.points, task.total_days, task.days_left, task.people_required, task.people_working, task.progress);
}

// Function to collect task data from the user
vector<Task> collectTasks() {
    vector<Task> tasks;
    int n;

    cout << "Enter number of tasks: ";
    cin >> n;
    cin.ignore(); // Ignore newline character

    for (int i = 0; i < n; ++i) {
        Task task;
        string deadlineStr;
        string dependency;

        cout << "Enter task name: ";
        getline(cin, task.name);
        if (task.name.empty()) {
            cout << "Task name cannot be empty. Please enter a valid name." << endl;
            --i;
            continue;
        }

        cout << "Enter task category: ";
        getline(cin, task.category);

        cout << "Enter task deadline (YYYY-MM-DD HH:MM): ";
        getline(cin, deadlineStr);
        if (deadlineStr.empty()) {
            cout << "Task deadline cannot be empty. Please enter a valid deadline." << endl;
            --i;
            continue;
        }
        task.deadline = stringToTimePoint(deadlineStr);

        cout << "Enter task location: ";
        getline(cin, task.location);

        cout << "Enter task points: ";
        if (!(cin >> task.points)) {
            cout << "Invalid input for points. Please enter an integer value." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            --i;
            continue;
        }

        cout << "Enter total days for the task: ";
        if (!(cin >> task.total_days)) {
            cout << "Invalid input for total days. Please enter an integer value." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            --i;
            continue;
        }

        cout << "Enter days left for the task: ";
        if (!(cin >> task.days_left)) {
            cout << "Invalid input for days left. Please enter an integer value." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            --i;
            continue;
        }

        cout << "Enter number of people required: ";
        if (!(cin >> task.people_required)) {
            cout << "Invalid input for people required. Please enter an integer value." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            --i;
            continue;
        }

        cout << "Enter number of people currently working: ";
        if (!(cin >> task.people_working)) {
            cout << "Invalid input for people working. Please enter an integer value." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            --i;
            continue;
        }

        cout << "Enter task progress (percentage): ";
        if (!(cin >> task.progress)) {
            cout << "Invalid input for progress. Please enter an integer value." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            --i;
            continue;
        }
        cin.ignore(); // Ignore newline character

        cout << "Enter dependencies (comma-separated task names, leave empty if none): ";
        getline(cin, dependency);
        stringstream ss(dependency);
        while (ss.good()) {
            string dep;
            getline(ss, dep, ',');
            if (!dep.empty()) {
                task.dependencies.push_back(dep);
            }
        }

        // Update dynamic priority before adding the task
        updateDynamicPriority(task);
        tasks.push_back(task);
    }

    return tasks;
}

// Function to generate and display the optimized daily schedule
void generateSchedule(vector<Task>& tasks, const string& categoryFilter = "") {
    priority_queue<Task> pq;

    // Push all tasks to the priority queue
    for (auto& task : tasks) {
        if (categoryFilter.empty() || task.category == categoryFilter) {
            updateDynamicPriority(task); // Update dynamic priority before pushing to queue
            pq.push(task);
        }
    }

    cout << "Optimized Daily Schedule:" << endl;
    while (!pq.empty()) {
        Task task = pq.top();
        pq.pop();
        cout << "Task: " << task.name << "\nCategory: " << task.category << "\nDeadline: " << timePointToString(task.deadline)
             << "\nLocation: " << task.location << "\nPriority: " << task.dynamicPriority << "\n" << endl;
    }
}

int main() {
    vector<Task> tasks = collectTasks();
    generateSchedule(tasks);
    return 0;
}
