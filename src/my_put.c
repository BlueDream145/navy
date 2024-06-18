/*
** EPITECH PROJECT, 2018
** my_put.c
** File description:
**
*/

#include "navy.h"

void my_put_char(char c)
{
	const int output_general = 1;
	const int write_size = 1;

	write(output_general, &c, write_size);
}

void my_put_str(const char *str)
{
	for (int i = 0; str[i]; i++)
		my_put_char(str[i]);
}

int my_put_nbr(int nb)
{
	if (nb > 9)
		my_put_nbr(nb / 10);
	else if (nb < 0) {
		nb = nb * -1;
		write(1, "-", 1);
		my_put_nbr(nb / 10);
	}
	my_put_char(nb % 10 + '0');
	return (0);
}