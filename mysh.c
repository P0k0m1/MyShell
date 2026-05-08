#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>

int main(int argc, char *argv[], char *envp[]) 
{ 
    (void)argc;
    (void)argv;
    (void)envp;
    char c, tmp[100];
    int print_prompt = 1;
    bzero(tmp, 100);
    
    c = '\0';

    /* do some initializations. */ 
    while (c != EOF) 
    {

        if (print_prompt) 
        {
            printf("mysh# ");  // prompt with trailing space
            fflush(stdout);
            print_prompt = 0; // will only print again after newline
        }
        c = getchar();
        switch (c) 
        {
         case '\n': 
         {
            print_prompt = 1; // next command should print prompt

                if(strlen(tmp) > 0) 
                {
                    // Step 1: Remove leading/trailing and collapse repeated spaces/tabs
                    char clean[100];
                    int i = 0, j = 0, space_flag = 0;

                    // skip leading whitespace
                    while(tmp[i] != '\0' && (tmp[i] == ' ' || tmp[i] == '\t')) i++;

                    for(; tmp[i] != '\0'; i++) 
                    {
                        if(tmp[i] == ' ' || tmp[i] == '\t') 
                        {
                            if(!space_flag) {  // first space
                                clean[j++] = ' ';
                                space_flag = 1;
                            }
                        } else {
                            clean[j++] = tmp[i];
                            space_flag = 0;
                        }
                    }

                    // remove trailing space if any
                    if(j > 0 && clean[j-1] == ' ') j--;
                    clean[j] = '\0';

                    // Step 2: Ignore whitespace-only lines
                    if(j == 0) {
                        bzero(tmp, 100);
                        break;
                    }

                    // Step 3: Tokenize on whitespace (space or tab)
                    char *args[20];
                    int arg_count = 0;
                    char *token = strtok(clean, " \t");
                    while(token != NULL && arg_count < 19) {
                        args[arg_count++] = token;
                        token = strtok(NULL, " \t");
                    }
                    args[arg_count] = NULL;

                    // Step 4: Built-in commands
                    if(strcmp(args[0], "exit") == 0) {
                        return 0;
                    }
                    else if(strcmp(args[0], "mypwd") == 0) {
                        char cwd[256];
                        if(getcwd(cwd, sizeof(cwd)) != NULL) {
                            printf("%s\n", cwd);
                        }
                    }
                    else if(strcmp(args[0], "mycd") == 0) {
                        if(arg_count < 2) {
                            printf("usage: mycd <path>\n");
                        } else {
                            if(chdir(args[1]) != 0) {
                                printf("No such directory\n");
                            }
                        }
                    }
                    // Step 5: External alias commands
                    else if(strcmp(args[0], "myls") == 0 || strcmp(args[0], "mygrep") == 0) {
                        int pid = fork();
                        if(pid < 0) {
                            printf("Fork failed\n");
                        } else if(pid == 0) { // child
                            if(strcmp(args[0], "myls") == 0) args[0] ="ls";
                            if(strcmp(args[0], "mygrep") == 0) args[0] = "grep";
                            execvp(args[0], args);
                            printf("Execution failed\n");
                            exit(1);
                        } else { // parent
                            waitpid(pid, NULL, 0); // wait for child
                        }
                    }
                    // Step 6: Unknown command
                    else {
                        printf("Command not found\n");
                    }
                }

                // Step 7: Clear buffer for next input
                bzero(tmp, 100);

                break;
            }
            default: 
                if(strlen(tmp) < 99) // prevent buffer overflow
                    strncat(tmp, &c, 1); 
                break; 
        } 
    } 
    /* some processing before terminating. */ 
    return 0; 
} 
