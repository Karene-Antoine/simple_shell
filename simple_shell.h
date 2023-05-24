#ifndef _SIMPLE_SHELL_
#define _SIMPLE_SHELL_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <signal.h>
#define PROMPT "$ "


/**
 * struct builtin_d - Defines the builtins functions.
 * @f: A pointer to the right builtin function to be called.
 * @built: The name of the built in command to be checked.
 */
typedef struct builtin_d
{
	char *built;
	void (*f)(char *);
} builtin_t;

extern char **environ;

int count_the_token(char *, const char *);
char **token_interface(char *, const char *, int);
void create_the_child(char **, char *, int, char **);
char **tokenize(int, char *, const char *);
char *path_finder(char *);
void parsing_the_line(char *, size_t, int, char **);
int find_the_path(char *);
int str_len(char *);
char *search_the_directories(char **, char *);
char **tokenize_the_path(int, char *);
void double_free(char **);
char *build_the_path(char *, char *);
void single_free(int, ...);

/*Builtin functions*/
void (*check_built_ins(char *))(char *);
int built_in(char **, char *);
void env_command(char *);
void exit_command(char *);
void cd_command(char *);

/* Helper functions*/
char *string_duplicate(char *);
int string_compare(char *, char *);
int print_number(int);
void print_the_string(char *, int);
int write_character(char);

void execute_error(char *, int, char *);
void print_error(char *, int, char *);

#endif
