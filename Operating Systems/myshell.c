//Project 1 Due: 1/21/14
//Steven Pan	span3@ucsc.edu

#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **get_line();
char **savedargs = NULL;
int progId = 0;

typedef struct {
    char *path_in;
    char *path_out;
    char *path_pipe;
} argPaths;

typedef struct {
    int left_paren;
    int right_paren;
    int file_in;
    int file_out;
    int pipe;
    int background;
    int semicolon;
} argFlags;

void splitArgs (int *i, char **args){
	    int pos = *i + 1;
		int store = 0;
        int count = 0;
        for (pos = pos; args[pos] != NULL; pos++) {
            count++;
        }
        //account for null
        args[(*i)+1] = NULL;
        savedargs = calloc (pos + 1, sizeof (char *));
        assert (savedargs != NULL);
        for (store = store; store < count; store++) {
            savedargs[store] = args[*i];
            args[(*i)++] = NULL;
        }
        savedargs[store] = NULL;
}

void removeParen (int *i, char **args) {
    int pos = *i;
    for (pos = pos; args[pos] != NULL; pos++) {
	    //check for left and then right parentheses, remove them if found.
        if (strcmp (args[pos], "(") == 0) {
            args[pos] = " ";
        }
		if (strcmp (args[pos], ")") == 0) {
            if (args[pos + 1] != NULL)
                args[pos] = args[pos + 1];
            else
                args[pos] = NULL;
        }
    }
}

int processSym (int *i, char **args, argFlags *flags, argPaths *paths) {
    switch (args[*i][0]){
	    case '&' : flags->background = 1; 
		           break;
        case ';' : flags->semicolon = 1;
		           if (!flags->left_paren)
				      splitArgs (i, args);
                   break;
        case '(' : flags->left_paren = 1;
                   removeParen (i, args); break;
        case ')' : flags->right_paren = 1; break;
                   removeParen (i, args); break;
		//File input and output
        case '<' : flags->file_in = 1;
		           if (args[*i+1] != NULL)
				       paths->path_in = args[*i + 1];
                   break;
        case '>' : flags->file_out = 1;
		           if (args[*i+1] != NULL)
				       paths->path_in = args[*i + 1];
                   break;				   
		case '|' : flags->pipe = 1;
                   if (args[*i+1] != NULL)
				       paths->path_in = args[*i + 1];
                   break;
        default : break;
    }
    return 1;
}

void parseArgs (argFlags *flags, argPaths *paths, char **args, char **child_args) {
    int i = 0;
	int j = 0;
    for (i = j = 0; args[i] != NULL; i++) {
        if (strlen (args[i]) == 1 && processSym (&i, args, flags, paths)) {
            if (flags->left_paren) {
                i++;
                break;
            }
            continue;
        }
        child_args[j++] = args[i];
    }
    if (flags->left_paren) {
        for (i = i; args[i] != NULL; i++)
            child_args[j++] = args[i];
    }

    child_args[j] = NULL;
}

void execute (argFlags *flags, argPaths *paths, char **child_args) {

    // Change the current working directory if requested
    if (strcmp (child_args[0],"cd") == 0) {
        /*
         * If the argument doesn't contain a path, change the directory
         * to home. If an invalid path was passed, notify user.
         */
        if (chdir((child_args[1] == NULL) ? getenv("HOME") : child_args[1]) == -1) {
            printf ("%s: %s: no such file or directory\n", child_args[0], child_args[1]);
        }
    } 
	else {
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            if (flags->background)
                setpgid (0, 0);
            /*
             * Creates a file from the path provided if file not
             * found. Redirects the output to the file specified.
             */
            if (flags->file_out) {
                freopen (paths->path_out, "w", stdout);
            }
            if (flags->file_in) {
                freopen (paths->path_in,"r",stdin);
            }
            if(execvp (child_args[0], child_args) != 0) {
                printf ("Command: %s not found\n", child_args[0]);
                exit(1);
            }
        } 
		else {
            /* Parent */
            int status;
            progId = pid;

            /* Don't wait if background */
            if (!flags->background)
                waitpid (-1, &status, 0);
            else {
                printf ("Process %d in background.\n", (int) pid);
            }
        }
    }
}

int exitCheck (char **args) {
    if (args[0] == NULL) return 1;
    if (strcmp (args[0],"exit") == 0) exit(0);
    return 0;
}
void sig_handler() {
    int status;
    waitpid(-1, &status, WNOHANG);
}

void kill_sig() {
    if (progId != 0) {
        kill (progId,SIGKILL);
        progId = 0;
    }
}

void beginShell (int loop) {
	int clearArgs = 0;
	//Usage of terminate variable, which decides if shell needs to stop looping, came from
	//a friend who took the class previously.
    int terminate = 0;
    char **args;
    argFlags flags = {0,0,0,0,0,0,0};
    argPaths paths = {NULL,NULL,NULL};

    if (loop == 0) {
        terminate = 1;
        loop = 1;
    }

    while (loop) {
        char cwd[1024];
        getcwd(cwd, sizeof (cwd));
        if (savedargs == NULL) {
            printf ("$ ");
            args = get_line();
        }
		else {
            args = malloc (sizeof (savedargs) * sizeof (char *));
            assert (args != NULL);
            int i = 0;
			while (savedargs[i] != NULL {
                args[i] = savedargs[i];
				i++
            }
            args[i] = NULL;
            savedargs = NULL;
            clearArgs = 1;
        }
	    if(exitCheck (args)) continue;
        char **child_args = malloc (sizeof (args) * sizeof (char *));
        assert (child_args != NULL);
        parseArgs (&flags, &paths, args, child_args);
		//if left parenthese are found, run the shell again for the parameters inside
        if (flags.left_paren) {
            int one_loop = 0;
            savedargs = child_args;
            beginShell (one_loop);
            chdir (cwd);
            terminate = 0;
        } 
		else {
            execute (&flags, &paths, child_args);
        }      
		flags.left_paren = 0;
		flags.right_paren = 0;
		flags.file_in = 0;
        flags.file_out = 0;
		flags.pipe = 0;
		flags.background = 0;
		flags.semicolon = 0;

        child_args = NULL;
		printf("\n");
		if (clearArgs) {
            clearArgs = 0;
            args = NULL;
        }
		if (terminate && !flags.semicolon)
     	    loop = 0;
    }
}

int main() {
    int loop = 1;
    signal (SIGINT, kill_sig);
    signal (SIGCHLD, sig_handler);
    beginShell (loop);

    exit (0);
}
