#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h> 

#define MAX_ARGS 10
#define WORD_SIZE 1024

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define RESET "\033[0m"

char* read_input();
char** parse_input(char* input);
void execute(char** args);
int forkbomb(char **args);
int cat(char** args);
void clear();
int cowsay(char** args);
int rm(char** args);


void background_blue(){
	printf("\033[48;5;12m");
}

void prompt() {
	background_blue();
    printf("\033]0;Amina and Kerim\007"); 

    char *username;
    char hostname[HOST_NAME_MAX + 1];

    username = getlogin();
    gethostname(hostname, HOST_NAME_MAX + 1);

    //char cwd[PATH_MAX]; // this line of code stores the current working directory

    printf("\033[0;33m"); //set color to yellow
    printf("%s@%s", username, hostname);
    printf("\033[0m"); //reset color

    printf(":~$ ");
}

char* read_input() {
    char* input = NULL;
    ssize_t buffer_size = 0;
    getline(&input, &buffer_size, stdin);
    return input;
}




char** parse_input(char* input) {
    char** args = malloc(MAX_ARGS * sizeof(char*));
    char* token = strtok(input, " \n");
    int i = 0;
    while (token != NULL) {
        args[i] = token;
        token = strtok(NULL, " \n");
        i++;
    }
    args[i] = NULL;
    return args;
}



void execute(char** args) {
    int fd[2];
    pid_t pid;
    int fd_in = STDIN_FILENO;

    while (*args != NULL) {
        if (strcmp(*args, "|") == 0) {
            if (pipe(fd) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }

            pid = fork();
            if (pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                close(fd[0]);
                dup2(fd_in, STDIN_FILENO);
                if (*(args+1) != NULL) {
                    dup2(fd[1], STDOUT_FILENO);
                }
                close(fd[1]);
                execute(args+1);
                exit(EXIT_SUCCESS);
            } else {
                wait(NULL);
                close(fd[1]);
                fd_in = fd[0];
                args++;
            }
        } else if (strcmp(*args, "cat") == 0) {
            cat(args+1);
            return;
        } else if (strcmp(*args, "clear") == 0) {
            clear();
            return;
        } else if (strcmp(*args, "cowsay") == 0) {
            cowsay(args+1);
            return;
        } else if (strcmp(*args, "rm") == 0) {
            rm(args+1);
            return;
        }
        args++;
    }
}

int cat(char **args)
{
	char text[WORD_SIZE];

    // HELP
    if (args[1] != NULL)
    {
        if (strcmp(args[1], "h") == 0)
        {
            background_blue();
            printf("\n USAGE: cat [argument] file1 file2 etc.");
            printf("\n cat arguments:");
            printf("\n o - writes from console to output.txt");
            printf("\n o file1 file2 etc. - writes from files to output.txt");
            printf("\n one or more files - prints contents of file(s) on screen.");
            printf("\n no args - acts as echo until \"quit\" is entered.");
            return 1;
        }
    }
    // OBICNO ISPISIVANJE IZ FAJLOVA
    if ((args[1] != NULL) && strcmp(args[1], "o") != 0)
    {
        int c;
        FILE *file=fopen(args[1], "r");
        
        if (args[2] != NULL)
        {
            for (int i = 1; args[i] != NULL; i++)
            {
                file = fopen(args[i], "r");
                if (file)
                {
                    while ((c = getc(file)) != EOF)
                        putchar(c);
                    fclose(file);
                }
            }
            return 1;
        }
        if (file)
        {
            while ((c = getc(file)) != EOF)
                putchar(c);
            fclose(file);
        }
        return 1;
    }

    // ECHO
    if (args[1] == NULL)
    {
        while (1)
        {
            scanf("%[^\n]%*c", text);
            if ((strcmp(text, "quit") == 0))
            {
                return 1;
            }
            printf("%s\n", text);
        }
    }

    /*Ouput vise fajlova*/
    if (args[1] != NULL && strcmp(args[1], "o") == 0 && args[2] != NULL)
    {
        FILE *f;
        f = fopen("output.txt", "w");
        if (f == NULL)
        {
            printf("fastshell: Error opening file!\n");
            return 1;
        }
        int c;
        FILE *file;

        for (int i = 2; args[i] != NULL; i++)
        {
            file = fopen(args[i], "r");
            if (file)
            {
                while ((c = getc(file)) != EOF)
                    fprintf(f, "%c", c);
                fclose(file);
            }
        }
        fclose(f);
        return 1;
    }
    if (args[1] != NULL && strcmp(args[1], "o") == 0 && args[2] == NULL)
    {
        FILE *f;
        f = fopen("output.txt", "w");
        if (f == NULL)
        {
            printf("fastshell: Error opening file!\n");
            return 1;
        }
        while (1)
        {
            scanf("%[^\n]%*c", text);
            if ((strcmp(text, "quit") == 0))
            {
                fclose(f);
                return 1;
            }
            fprintf(f, "%s\n", text);
        }
    }
    return 1;
}

void clear() {
    system("clear");
}

int cowsay(char **args)
{
    char message[WORD_SIZE];
    
    if (args[1] != NULL)
    {
        if (strcmp(args[1], "h") == 0)
        {
            background_blue();
            printf("How to use: cowsay <text>\n");
            printf("o - output what the cow will say to output.txt\n");
            return 1;
        }
    }
    if (args[1] != NULL && strcmp(args[1], "o") == 0)
    {
        FILE *f = fopen("output.txt", "w");
        if (f == NULL)
        {
            printf("Error opening file!\n");
            return 1;
        }
        
        printf("Enter text: \n");
        scanf("%[^\n]%*c", message);
        fprintf(f, " %s\n", message);
        fprintf(f, "         \\   ^__^\n");
        fprintf(f, "          \\  (oo)\\_______\n");
        fprintf(f, "             (__)\\       )\\/\\\n");
        fprintf(f, "                 ||----w |\n");
        fprintf(f, "                 ||     ||\n");
        printf("Done\n");
        fclose(f);
    }
    else
    {
	printf(" _______________\n");
	    printf("< %s >\n", args[1]);
	    printf(" ---------------\n");
	    printf("        \\   ^__^\n");
	    printf("         \\  (oo)\\_______\n");
	    printf("            (__)\\       )\\/\\\n");
	    printf("                ||----w |\n");
	    printf("                ||     ||\n");
    }
    
    if (args[1] != NULL && strcmp(args[1], "h") != 0 && strcmp(args[1], "o") != 0)
    {
        printf("Invalid input.\nType cowsay h for help\n");
        return 1;
    }
    return 1;
}



int rm(char **args) {
    if (args[1] == NULL) {
        printf("rm: missing operand\n");
        return 1;
    }
    int status = 0;
    for (int i = 1; args[i] != NULL; i++) {
        if (unlink(args[i]) != 0) {
            printf("rm: cannot remove '%s': No such file or directory\n", args[i]);
            status = 1;
        }
    }
    return status;
}


int forkbomb(char **args) {
    if (args[1] != NULL) {
        if (strcmp(args[1], "h") == 0) {
            background_blue();
            printf("\nTo use type: forkbomb");
            printf("\nThis may harm your computer system.");
            return 1;
        }
        printf("Wrong input format, no arguments needed, only command.");
        return 1;
    }
    char response;
    printf("Are you sure you want to continue? Press 'y' for YES or 'n' for NO\n");
    scanf("%c", &response);
    
    while (response != 'y' && response != 'n') {
        printf("Invalid input!\n Press 'y' for YES or 'n' for NO\n");
	   scanf("%c", &response);
    }
    
    if (response == 'y') {
        while (1)
        {
            fork();
        }
    }
    
    else {
        return 1;
    }
}






int main() {
    while (1) {
    		prompt();
        printf(">");
        char* input = read_input();
        char** args = parse_input(input);
        execute(args);
        free(input);
        free(args);
    }
    return 0;
}


