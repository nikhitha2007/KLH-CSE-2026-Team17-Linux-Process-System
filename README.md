# Linux Process Management System

**Operating Systems Project | Team 17**

## Project Overview

The Linux Process Management System is a C-based application that demonstrates process creation, execution, synchronization, monitoring, and termination in Linux.

It uses fundamental Linux system calls to create and manage multiple child processes. A web-based dashboard built using Flask, HTML, CSS, and JavaScript provides an interactive interface to execute the program and view its output.

## Technologies Used

- **C:** Process management implementation
- **Linux & GCC:** Execution and compilation
- **Python Flask:** Backend
- **HTML, CSS & JavaScript:** Frontend dashboard

## Key Features

- Creates three child processes using `fork()`.
- Displays process IDs using `getpid()` and `getppid()`.
- Executes child tasks using `exec()`.
- Synchronizes processes using `waitpid()`.
- Monitors process termination and exit status.
- Provides a web dashboard to run and view process execution.

## System Calls Used

| System Call | Purpose |
|---|---|
| `fork()` | Creates child processes |
| `getpid()` | Gets process ID |
| `getppid()` | Gets parent process ID |
| `execlp()` | Executes a program |
| `waitpid()` | Waits for child processes |
| `exit()` | Terminates a process |

## Project Structure

```text
Linux-Process-System/
├── process_system.c
├── app.py
├── templates/
│   └── index.html
├── static/
│   └── style.css
├── README.md
└── Linux Process System.docx
```

## How to Run

**1. Compile the C program**

```bash
gcc -Wall -Wextra process_system.c -o process_system
```

**2. Create and activate virtual environment**

```bash
python3 -m venv venv
source venv/bin/activate
```

**3. Install Flask**

```bash
pip install flask
```

**4. Start the application**

```bash
python3 app.py
```

Open `http://127.0.0.1:5000` in your browser and click **Run Process Demo**.

## Expected Result

The application creates three child processes, executes their tasks, monitors their completion, and displays their termination status through the web dashboard.

## Team Members

- Nikhitha Gondi
- Poojitha

**Team Number:** 17
