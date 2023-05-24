#include "simple_shell.h"

/**
 * print_number - Prints an integer.
 * @n: Integer to be printed
 * Return: Returns the number of integers printed.
 */
int print_number(int n)
{
	int len;
	int divisor;
	unsigned int num_to_be_checked;

	divisor = 1;
	len = 0;

	num_to_be_checked = n;

	for (; num_to_be_checked / divisor > 9; )
		divisor *= 10;

	for (; divisor != 0; )
	{
		len += write_character('0' + num_to_be_checked / divisor);
		num_to_be_checked %= divisor;
		divisor /= 10;
	}

	return (len);
}
