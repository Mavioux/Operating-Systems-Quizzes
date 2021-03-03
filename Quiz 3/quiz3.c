int execvpWithTimeout(int secTimeout, char** cmd) {

    // Fork into two threads
    int status = -1;
    int pid0 = fork();
    
    if(pid0 < 0) {
        printf("Error in forking the first child thread\n");
        exit(0);
    }
    else if(pid0 == 0) {
        // We are inside the first child thread
        // printf("Countdown thread id: %d\n", getpid());
        // Sleep for secTimeout seconds
        // printf("I am inside %d\n" ,getpid());
        sleep(secTimeout);
        // printf("You should return 2 and kill your master's child thread\n");
        exit(2);
    }
    else {
        // We are inside the parent thread
        // Fork again to create the second child thread and the same parent thread
        // printf("I am inside %d\n" ,getpid());
        int pid1 = fork();

        if(pid1 < 0) {
            printf("Error in forking the second child thread\n");
            exit(0);
        }
        else if (pid1 == 0)
        {
            // We are inside the second child thread
            // printf("Execution thread id: %d\n", getpid());
            // printf("I am the child two with pid: %d\n", pid1);
            // Execute the command
            // printf("I am inside %d\n" ,getpid());
            execvp(cmd[2], &cmd[2]);
        }
        else {
            // We are inside a copy of the parent thread which we dont care about so lets kill it
            // printf("copy master thread id: %d\n", getpid());
        }
        // We are inside the master thread
        // printf("real master thread id: %d\n", getpid());
        // printf("I am the master thread with id: %d\n", pid1);
        // printf("I am inside %d\n" ,getpid());
        // printf("Master thread id: %d\n", getpid());
        // We wait for the first thread that returns and depending on its status we kill the other one
        // Then we kill the thread with the command execution since it is a copy of the main thread
        // and we don't want it to return
        wait(&status);
        if (WIFEXITED(status)) {
            status = WEXITSTATUS(status);
        }

        // Check for 0 or 2 or else case
        if(status == 0) {
            // printf("You should return 0 and kill your master's child thread\n");
            // Kill the timeout thread
            kill(pid0, SIGKILL);                
            // printf("Killed timeout (%d) due to correct execution.\n", pid0);
        }
        else if(status == 2) {
            // printf("You should return 2 and kill your master's child thread\n");
            // Kill the execution thread
            kill(pid1, SIGKILL);
            // printf("Killed execution(%d) due to timeout.\n", pid1);
        }
        else {
            // printf("You should return 1 and kill your master's child thread\n");
            status = 1;
            // Kill the timeout thread
            kill(pid0, SIGKILL);
            // printf("Killed timeout(%d) due to execution and error.\n", pid0);                
        }
        // printf("returning\n");
        return status;
    }  
}