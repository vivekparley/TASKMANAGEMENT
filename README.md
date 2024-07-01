# Dynamic Task Scheduler

This project is a C++ program designed to dynamically prioritize and schedule tasks based on a variety of factors, such as deadlines, points, and dependencies. It provides an optimized daily schedule by calculating the dynamic priority of each task and ordering them accordingly.

## Features

- **Dynamic Priority Calculation**: Tasks are prioritized based on points, deadlines, required people, current progress, and dependencies.
- **User Input**: Collects task data from the user, including name, category, deadline, location, points, total days, days left, people required, people working, progress, and dependencies.
- **Optimized Schedule Generation**: Generates and displays an optimized daily schedule based on the dynamic priorities of the tasks.
- **Category Filtering**: Allows filtering tasks by category when generating the schedule.

## Getting Started

### Prerequisites

- A C++ compiler (e.g., g++, clang++)

### Building and Running the Program

1. **Clone the Repository**:

    ```sh
    git clone https://github.com/your-username/dynamic-task-scheduler.git
    cd dynamic-task-scheduler
    ```

2. **Compile the Program**:

    ```sh
    g++ -std=c++11 -o scheduler main.cpp
    ```

3. **Run the Program**:

    ```sh
    ./scheduler
    ```

## Usage

1. **Enter the Number of Tasks**: 
   - The program will prompt you to enter the number of tasks you want to schedule.

2. **Provide Task Details**:
   - For each task, provide the following details when prompted:
     - Task name
     - Task category
     - Task deadline (format: YYYY-MM-DD HH:MM)
     - Task location
     - Task points
     - Total days for the task
     - Days left for the task
     - Number of people required
     - Number of people currently working
     - Task progress (percentage)
     - Dependencies (comma-separated task names, leave empty if none)

3. **View Optimized Schedule**:
   - The program will display the optimized daily schedule, listing tasks in order of their dynamic priority.

## Code Explanation

### Task Structure

The `Task` structure defines the properties of a task, including its name, category, deadline, location, points, total days, days left, people required, people working, progress, dynamic priority, and dependencies.

### Dynamic Priority Calculation

The `calculatePriority` function computes the dynamic priority of a task based on various factors:
- **Base Points**: Initial priority points assigned to the task.
- **Days Left**: Fewer days left increases priority.
- **People Required vs. People Working**: More people required than currently working increases priority.
- **Progress**: Higher progress decreases priority.

### Collecting Task Data

The `collectTasks` function collects task data from the user, ensures valid input, and calculates the dynamic priority of each task before adding it to the task list.

### Generating the Schedule

The `generateSchedule` function uses a priority queue to order tasks by their dynamic priority and deadline. It then displays the tasks in order of priority.

### Main Function

The `main` function initiates the task collection and schedule generation process.

## Example

```sh
Enter number of tasks: 2
Enter task name: Task 1
Enter task category: Work
Enter task deadline (YYYY-MM-DD HH:MM): 2024-07-03 12:00
Enter task location: Office
Enter task points: 50
Enter total days for the task: 5
Enter days left for the task: 3
Enter number of people required: 2
Enter number of people currently working: 1
Enter task progress (percentage): 40
Enter dependencies (comma-separated task names, leave empty if none): 

Enter task name: Task 2
Enter task category: Personal
Enter task deadline (YYYY-MM-DD HH:MM): 2024-07-02 18:00
Enter task location: Home
Enter task points: 30
Enter total days for the task: 3
Enter days left for the task: 1
Enter number of people required: 1
Enter number of people currently working: 1
Enter task progress (percentage): 20
Enter dependencies (comma-separated task names, leave empty if none): Task 1

Optimized Daily Schedule:
Task: Task 2
Category: Personal
Deadline: 2024-07-02 18:00
Location: Home
Priority: 39

Task: Task 1
Category: Work
Deadline: 2024-07-03 12:00
Location: Office
Priority: 44
