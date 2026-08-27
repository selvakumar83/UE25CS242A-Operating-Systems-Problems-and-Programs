// program to demonstrate fork() and wait() 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int arr[] = {5, 10, 15, 20, 25, 30, 35, 40};
    int n = sizeof(arr) / sizeof(arr[0]);

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork Failed");
        return 1;
    }

    if (pid == 0) {
        // Child Process
        int childSum = 0;

        printf("\nChild Process (PID: %d)\n", getpid());

        for (int i = 0; i < n / 2; i++) {
            childSum += arr[i];
            printf("Child adding %d -> Partial Sum = %d\n",
                   arr[i], childSum);
            sleep(1);
        }

        printf("Child Final Sum = %d\n", childSum);

        // Exit code should be <=255
        exit(childSum);
    }
    else {
        // Parent Process
        int parentSum = 0;
        int status;

        printf("Parent Process (PID: %d)\n", getpid());

        for (int i = n / 2; i < n; i++) {
            parentSum += arr[i];
            printf("Parent adding %d -> Partial Sum = %d\n",
                   arr[i], parentSum);
            sleep(1);
        }

        printf("\nParent waiting for child...\n");

        wait(&status);

        int childSum = WEXITSTATUS(status);

        printf("Child returned Sum = %d\n", childSum);
        printf("Parent Sum = %d\n", parentSum);

        printf("\nTotal Array Sum = %d\n", childSum + parentSum);
    }

    return 0;
}
