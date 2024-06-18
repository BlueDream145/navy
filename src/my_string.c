/*
** EPITECH PROJECT, 2018
** my_string.c
** File description:
**
*/

#include "navy.h"

int my_strlen(const char *str)
{
	int i;

	for (i = 0; str[i]; i++);
	return (i);
}

int my_str_isnum(const char *str)
{
	for (int i = 0; str[i]; i++)
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (FALSE);
	return (TRUE);
}

int my_str_printable(const char *str)
{
	for (int i = 0; str[i]; i++)
		if (!(str[i] >= 32 && str[i] <= 126))
			return (FALSE);
	return (TRUE);
}

char *my_strcpy(char *dest, const char *src)
{
	int i = 0;

	while (src[i] != '\0') {
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char *my_strcat(char *dest, const char *src)
{
	int dest_len = my_strlen(dest);
	int j = 0;

	for (j = 0; src[j] != '\0'; j++)
		dest[dest_len + j] = src[j];
	dest[dest_len + j] = '\0';
	return (dest);
}