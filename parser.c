#include "simple_shell.h"
/**
 * parsing_the_line - Searches for commands and arguments.
 * @line: Points to a string.
 * @size: Stores size_t numbers.
 * @command_counter: Stores number of commands entered into the shell.
 * @av: Program executing the shell.
 */
void parsing_the_line(char *line, size_t size, int command_counter, char **av)
{
	const char *separator = "\n\t ";
	ssize_t read_len;
	char **parameter_list;
	int index_i;
	int token_total;

	token_total = 0;
	write(STDOUT_FILENO, PROMPT, str_len(PROMPT));
	read_len = getline(&line, &size, stdin);
	if (read_len != -1)
	{
		parameter_list = token_interface(line, separator, token_total);
		if (parameter_list[0] == NULL)
		{
			single_free(2, parameter_list, line);
			return;
		}
		index_i = built_in(parameter_list, line);
		if (index_i == -1)
			create_the_child(parameter_list, line, command_counter, av);
		for (index_i = 0; parameter_list[index_i] != NULL; index_i++)
			free(parameter_list[index_i]);
		single_free(2, parameter_list, line);
	}
	else
		exit_command(line);
}

/**
 * create_the_child - Creates the child to execute another program.
 * @param_array: Contains the names of a program and its parameters.
 * @line: Line to be read.
 * @count: Stores the number of commands being entered.
 * @av: Program executing the shell.
 */
void create_the_child(char **param_array, char *line, int count, char **av)
{
	int index_i;
	int status;
	pid_t id;
	struct stat buffer;
	int check;
	char *command;
	char *temporary_command;

	id = fork();
	if (id == 0)
	{
		temporary_command = param_array[0];
		command = path_finder(param_array[0]);
		if (command == NULL)
		{
			/*Looking for file in current directory*/
			check = stat(temporary_command, &buffer);
			if (check == -1)
			{
				print_error(av[0], count, temporary_command);
				print_the_string(": not found", 0);
				single_free(2, line, temporary_command);
				for (index_i = 1; param_array[index_i]; index_i++)
					free(param_array[index_i]);
				free(param_array);
				exit(100);
			}
			/*file exist in cwd or has full path*/
			command = temporary_command;
		}
		param_array[0] = command;
		if (param_array[0] != NULL)
		{
			if (execve(param_array[0], param_array, environ) == -1)
				execute_error(av[0], count, temporary_command);
		}
	}
	else
		wait(&status);
}

/**
 * token_interface - Makes token functions accessible to other programs.
 * @line: Input from the user.
 * @delim: Separator for the line.
 * @token_count: Counts the number of tokens in a string.
 * Return: Returns an array of tokens, otherwise returns NULL.
 */
char **token_interface(char *line, const char *delim, int token_count)
{
	char **parameter_list;

	token_count = count_the_token(line, delim);
	if (token_count == -1)
	{
		free(line);
		return (NULL);
	}
	parameter_list = tokenize(token_count, line, delim);
	if (parameter_list == NULL)
	{
		free(line);
		return (NULL);
	}

	return (parameter_list);
}

/**
 * tokenize - Breaks a string down into tokens.
 * @token_count: Counts the number of tokens in the array.
 * @line: String that is separated by a separator.
 * @delim: Separator to separate tokens.
 * Return: Returns an array of pointers, otherwise returns NULL.
 */
char **tokenize(int token_count, char *line, const char *delim)
{
	char **buf;
	int index_i;
	char *line_cp;
	char *token;

	line_cp = string_duplicate(line);
	buf = malloc(sizeof(char *) * (token_count + 1));
	if (buf == NULL)
		return (NULL);
	token = strtok(line_cp, delim);
	for (index_i = 0; token != NULL; index_i++)
	{
		buf[index_i] = string_duplicate(token);
		token = strtok(NULL, delim);
	}
	buf[index_i] = NULL;
	free(line_cp);
	return (buf);
}

/**
 * count_the_token - Counts number of tokens in a string.
 * @line: String to be separated.
 * @delim: Separator to separate tokens.
 * Return: Returns the total number of tokens on success, otherwise -1.
 */
int count_the_token(char *line, const char *delim)
{
	char *token;
	char *str;
	int index_i;

	str = string_duplicate(line);
	if (str == NULL)
		return (-1);
	token = strtok(str, delim);
	for (index_i = 0; token != NULL; index_i++)
		token = strtok(NULL, delim);
	free(str);
	return (index_i);
}
