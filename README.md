Dynamic Task Scheduler
This project is a C++ program designed to dynamically prioritize and schedule tasks based on a variety of factors, such as deadlines, points, and dependencies. It provides an optimized daily schedule by calculating the dynamic priority of each task and ordering them accordingly.

Features
Dynamic Priority Calculation: Tasks are prioritized based on points, deadlines, required people, current progress, and dependencies.
User Input: Collects task data from the user, including name, category, deadline, location, points, total days, days left, people required, people working, progress, and dependencies.
Optimized Schedule Generation: Generates and displays an optimized daily schedule based on the dynamic priorities of the tasks.
Category Filtering: Allows filtering tasks by category when generating the schedule.
Getting Started
Prerequisites
A C++ compiler (e.g., g++, clang++)
Building and Running the Program
Clone the Repository:

sh
Copy code
git clone https://github.com/your-username/dynamic-task-scheduler.git
cd dynamic-task-scheduler
Compile the Program:

sh
Copy code
g++ -std=c++11 -o scheduler main.cpp
Run the Program:

sh
Copy code
./scheduler
Usage
Enter the Number of Tasks:

The program will prompt you to enter the number of tasks you want to schedule.
Provide Task Details:

For each task, provide the following details when prompted:
Task name
Task category
Task deadline (format: YYYY-MM-DD HH
)
Task location
Task points
Total days for the task
Days left for the task
Number of people required
Number of people currently working
Task progress (percentage)
Dependencies (comma-separated task names, leave empty if none)
View Optimized Schedule:

The program will display the optimized daily schedule, listing tasks in order of their dynamic priority.
Code Explanation
Task Structure
The Task structure defines the properties of a task, including its name, category, deadline, location, points, total days, days left, people required, people working, progress, dynamic priority, and dependencies.

Dynamic Priority Calculation
The calculatePriority function computes the dynamic priority of a task based on various factors:

Base Points: Initial priority points assigned to the task.
Days Left: Fewer days left increases priority.
People Required vs. People Working: More people required than currently working increases priority.
Progress: Higher progress decreases priority.
Collecting Task Data
The collectTasks function collects task data from the user, ensures valid input, and calculates the dynamic priority of each task before adding it to the task list.

Generating the Schedule
The generateSchedule function uses a priority queue to order tasks by their dynamic priority and deadline. It then displays the tasks in order of priority.

Main Function
The main function initiates the task collection and schedule generation process.

