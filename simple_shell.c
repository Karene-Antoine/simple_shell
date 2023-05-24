#include "simple_shell.h"

/**
 * main - Entry point of the program.
 * @ac: Total parameters passed to the executable file.
 * @av: Name of the program.
 * Return: Always 0.
 */
int main(__attribute__((unused)) int ac, char **av)
{
	size_t size;
	int command_total;
	char *line_to_be_parsed;

	command_total = 0;
	signal(SIGINT, SIG_IGN);
	do {
		command_total++;
		line_to_be_parsed = NULL;
		size = 0;
		parsing_the_line(line_to_be_parsed, size, command_total, av);

	} while (1);

	return EXIT_SUCCESS;
}
