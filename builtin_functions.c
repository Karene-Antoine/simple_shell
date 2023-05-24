#include "simple_shell.h"

/**
 * cd_command - Changes the working directory.
 * @line: Input from the user.
 */
void cd_command(char *line)
{
	int current_index;
	int token_total;
	char **parameter_list;
	const char *separator = "\n\t ";

	token_total = 0;
	parameter_list = token_interface(line, separator, token_total);
	if (parameter_list[0] == NULL)
	{
		single_free(2, parameter_list, line);
		return;
	}
	if (parameter_list[1] == NULL)
	{
		current_index = find_the_path("HOME");
		chdir((environ[current_index]) + 5);
	}
	else if (string_compare(parameter_list[1], "-") == 0)
		print_the_string(parameter_list[1], 0);

	else
		chdir(parameter_list[1]);
	double_free(parameter_list);
}

/**
 * env_command - Prints the environment variables.
 * @line: Input from the user.
 */
void env_command(__attribute__((unused))char *line)
{
	int index_i;
	int index_j;

	for (index_i = 0; environ[index_i] != NULL; index_i++)
	{
		for (index_j = 0; environ[index_i][index_j] != '\0'; index_j++)
			write(STDOUT_FILENO, &environ[index_i][index_j], 1);
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * exit_command - Terminate the shell process.
 * @line: Input from the user.
 */
int exit_command(char *line)
{
	if (line != NULL)
	{
		free(line);
		return EXIT_SUCCESS;
	}

	free(line);
	return EXIT_FAILURE;
}

/**
 * check_built_ins - Gets the required function.
 * @str: The name of the function that is needed.
 * Return: Upon sucess a pointer to a void function. Otherwise NULL.
 */
void (*check_built_ins(char *str))(char *str)
{
	int index;

	builtin_t builtin_list[] = {
	{"cd", cd_command},
	{"env", env_command},
	{"exit", exit_command},

		{NULL, NULL}
	};

	for (index = 0; builtin_list[index].built != NULL; index++)
	{
		if (string_compare(str, builtin_list[index].built) == 0)
		{
			return (builtin_list[index].f);
		}
	}
	return (NULL);
}

/**
 * built_in - Looks for builtin functions.
 * @command: A list of arguments to be passed to the shell.
 * @line: Input from the user.
 * Return: 0 if function is found. Otherwise -1.
 */
int built_in(char **command, char *line)
{
	void (*build)(char *);

	build = check_built_ins(command[0]);

	if (build == NULL)
		return (-1);

	if (string_compare("exit", command[0]) == 0)
		double_free(command);

	build(line);

	return (0);
}
