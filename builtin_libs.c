#include "simple_shell.h"

/**
 * string_compare - compares the two strings
 * @s1: First string to be checked
 * @s2: Second string to be checked
 * Return: Returns 0 if strings match, otherwise -1.
 */
int string_compare(char *s1, char *s2)
{
	int index;

	if (str_len(s1) != str_len(s2))
		return (-1);
	for (index = 0; s1[index] != '\0'; index++)
	{
		if (s1[index] != s2[index])
			return (-1);
	}
	return (0);
}

/**
 * string_duplicate - Duplicate a string
 * @src: Original string
 * Return: Returns a copy of the string.
 */
char *string_duplicate(char *src)
{
	char *destination;
	int len;
	int index_i;

	len = str_len(src);
	destination = malloc(sizeof(char) * (len + 1));

	for (index_i = 0; src[index_i] != '\0'; index_i++)
		destination[index_i] = src[index_i];
	destination[index_i] = '\0';
	return (destination);
}

/**
 * print_the_string - Prints each character of the string.
 * @str: String to be printed.
 * @new_line: Print a new line if integer is 0, otherwise a new line
 */
void print_the_string(char *str, int new_line)
{
	int index_i;

	if (str == NULL)
		str = "(null)";
	for (index_i = 0; str[index_i] != '\0'; index_i++)
		write(STDOUT_FILENO, &str[index_i], 1);
	if (new_line == 0)
		write(STDOUT_FILENO, "\n", 1);
}

/**
 * write_character - Writes a character to stdout
 * @c: Character that will be written to stdout
 * Return: Returns number of characters written on success.
 */
int write_character(char c)
{
	return (write(1, &c, 1));
}
