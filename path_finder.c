#include "simple_shell.h"

/**
 * path_finder - Finds the full path of the program
 * @command: Command to be executed.
 * Return: Returns the full path of the program on success, otherwise NULL.
 */
char *path_finder(char *command)
{
	char *str = "PATH";
	char **tokens;
	char *constructed_path;
	char *directory;
	int current_index;

	current_index = find_the_path(str);
	tokens = tokenize_the_path(current_index, str);
	if (tokens == NULL)
		return (NULL);

	directory = search_the_directories(tokens, command);
	if (directory == NULL)
	{
		double_free(tokens);
		return (NULL);
	}

	constructed_path = build_the_path(directory, command);
	if (constructed_path == NULL)
	{
		double_free(tokens);
		return (NULL);
	}

	double_free(tokens);

	return (constructed_path);
}
/**
 * find_the_path - Finds the index.
 * @str: Environment variable that needs to be found.
 * Return: Returns the index of the environment variable, otherwise -1.
 */
int find_the_path(char *str)
{
	int index_i;
	int string_len;
	int index_j;

	string_len = str_len(str);
	for (index_i = 0; environ[index_i] != NULL; index_i++)
	{
		for (index_j = 0; index_j < string_len; index_j++)
		{
			if (environ[index_i][index_j] != str[index_j])
				break;
		}
		if (index_j == string_len && environ[index_i][index_j] == '=')
			return (index_i);
	}
	return (-1);
}

/**
 * tokenize_the_path - Separates a string into tokens.
 * @index: Index of the path.
 * @str: string to be separated.
 * Return: Returns an array of pointers to strings on success, otherwise NULL.
 */
char **tokenize_the_path(int index, char *str)
{
	char *env_variable;
	const char *separator = ":\n";
	int token_total;
	int len;
	char **path_tokens;

	len = str_len(str);
	token_total = 0;
	/*Moving the pointer len of str plus = sign*/
	env_variable = environ[index] + (len + 1);
	path_tokens = token_interface(env_variable, separator, token_total);
	if (path_tokens == NULL)
		return (NULL);

	return (path_tokens);
}

/**
 * search_the_directories - Searches for a specific file.
 * @path_tokens: An array containing the different paths.
 * @command: Command to be used.
 * Return: Returns a string with the command file, otherwise returns NULL.
 */
char *search_the_directories(char **path_tokens, char *command)
{
	int index_i, d;
	char *buffer;
	char *cwd;
	struct stat status_buffer;
	size_t size;

	buffer = NULL;
	size = 0;
	cwd = getcwd(buffer, size);
	if (cwd == NULL)
		return (NULL);
	if (command[0] == '/')
		command = command + 1;
	for (index_i = 0; path_tokens[index_i] != NULL; index_i++)
	{
		d = chdir(path_tokens[index_i]);
		if (d == -1)
		{
			perror("ERROR!");
			return (NULL);
		}
		d = stat(command, &status_buffer);
		if (d == 0)
		{
			chdir(cwd);
			free(cwd);
			return (path_tokens[index_i]);
		}
	}
	chdir(cwd);
	free(cwd);
	return (NULL);
}

/**
 * build_the_path - Builds the full path.
 * @directory: A directory in the path.
 * @command: A file in a directory of the path.
 * Return: Returns the full path of the command, otherwise NULL.
 */
char *build_the_path(char *directory, char *command)
{
	int index_i, index_j;
	int len;
	int directory_len;
	char *built;
	int command_length;

	if (directory == NULL || command == NULL)
		return (NULL);
	directory_len = str_len(directory) + 1;
	command_length = str_len(command) + 1;
	len = directory_len + command_length;

	built = malloc(sizeof(char) * len);
	if (built == NULL)
		return (NULL);

	for (index_i = 0; index_i < len; index_i++)
	{
		for (index_j = 0; directory[index_j] != '\0'; index_j++, index_i++)
			built[index_i] = directory[index_j];
		built[index_i] = '/';
		index_i++;
		for (index_j = 0; command[index_j] != '\0'; index_j++, index_i++)
			built[index_i] = command[index_j];
	}
	built[--index_i] = '\0';
	return (built);
}
