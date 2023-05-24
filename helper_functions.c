#include "simple_shell.h"
/**
 * str_len - Finds the lenght of a string.
 * @str: String to be checked
 * Return: Returns the length of a string on success, otherwise 0.
 */
int str_len(char *str)
{
	int index_i;

	if (str == NULL)
		return (0);
	for (index_i = 0; str[index_i] != '\0'; index_i++)
		;
	return (index_i);
}

/**
 * double_free - Frees the pointer variables.
 * @to_be_freed: Memory address of the elements that need to be cleaned.
 */
void double_free(char **to_be_freed)
{
	int i;

	for (i = 0; to_be_freed[i] != NULL; i++)
		free(to_be_freed[i]);
	free(to_be_freed);
}

/**
 * single_free - Frees the n amount of pointers.
 * @n: The number of pointers to be freed.
 */
void single_free(int n, ...)
{
	va_list arguments_list;
	char *str;
	int index_i;

	va_start(arguments_list, n);
	for (index_i = 0; index_i < n; index_i++)
	{
		str = va_arg(arguments_list, char*);
		if (str == NULL)
			str = "(nil)";
		free(str);
	}
	va_end(arguments_list);
}


/**
 * print_error - Prints an error when command is not found.
 * @count: Stores number of commands being ran.
 * @av: Name of the program executing the shell.
 * @command: Missing command.
 */
void print_error(char *av, int count, char *command)
{
	print_the_string(av, 1);
	print_the_string(": ", 1);
	print_number(count);
	print_the_string(": ", 1);
	print_the_string(command, 1);
}

/**
 * execute_error - Prints executed errors.
 * @av: Name of the program executing the shell.
 * @count: Stores number of commands entered.
 * @tmp_command: Failed command.
 */

void execute_error(char *av, int count, char *tmp_command)
{
	print_error(av, count, tmp_command);
	print_the_string(": ", 1);
	perror("");
	exit(1);
}
