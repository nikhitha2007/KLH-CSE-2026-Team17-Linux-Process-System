
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TOTAL_CHILDREN 3

// Function executed by each child process
void child_task(int task_number)
{
    printf("\n========== CHILD PROCESS %d ==========\n", task_number);

    printf("Child PID  : %d\n", getpid());
    printf("Parent PID : %d\n", getppid());

    printf("Child %d is executing its task...\n", task_number);

    sleep(task_number);

    printf("Child %d completed its task.\n", task_number);
    printf("Child %d is terminating.\n", task_number);

    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    // Child worker mode
    if (argc == 2)
    {
        int task_number = atoi(argv[1]);

        if (task_number >= 1 && task_number <= TOTAL_CHILDREN)
        {
            child_task(task_number);
        }

        return EXIT_FAILURE;
    }

    // Parent process
    printf("\n========================================\n");
    printf("       LINUX PROCESS MANAGEMENT SYSTEM\n");
    printf("========================================\n");

    printf("\nParent Process Started\n");
    printf("Parent PID  : %d\n", getpid());
    printf("Parent PPID : %d\n", getppid());

    fflush(stdout);

    pid_t child_pids[TOTAL_CHILDREN];

    // STEP 1: Process creation using fork()
    printf("\nCreating %d child processes...\n", TOTAL_CHILDREN);
    fflush(stdout);

    for (int i = 0; i < TOTAL_CHILDREN; i++)
    {
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("Fork failed");
            return EXIT_FAILURE;
        }

        if (pid == 0)
        {
            // Child process
            char task_number[10];

            snprintf(task_number, sizeof(task_number), "%d", i + 1);

            printf("\nChild %d created successfully!\n", i + 1);
            printf("Executing child task using exec()...\n");

            fflush(stdout);

            // STEP 2: Program execution using exec()
            execlp(argv[0], argv[0], task_number, NULL);

            perror("Exec failed");
            _exit(127);
        }
        else
        {
            // Parent stores child PID
            child_pids[i] = pid;

            printf("Child %d created with PID: %d\n",
                   i + 1, pid);
            fflush(stdout);
        }
    }

    // STEP 3: Process synchronization and monitoring
    printf("\n========================================\n");
    printf("          PROCESS MONITORING\n");
    printf("========================================\n");

    printf("Parent is waiting for all children...\n");

    for (int i = 0; i < TOTAL_CHILDREN; i++)
    {
        int status;

        pid_t result = waitpid(child_pids[i], &status, 0);

        if (result == -1)
        {
            perror("Waitpid failed");
            continue;
        }

        printf("\nChild PID %d completed.\n", result);

        if (WIFEXITED(status))
        {
            printf("Termination: Normal\n");
            printf("Exit Status: %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("Termination: By signal %d\n",
                   WTERMSIG(status));
        }
        else
        {
            printf("Termination: Other\n");
        }
    }

    // STEP 4: Parent completion
    printf("\n========================================\n");
    printf("All child processes have been monitored.\n");
    printf("Parent process completed successfully.\n");
    printf("========================================\n");

    return EXIT_SUCCESS;
}

