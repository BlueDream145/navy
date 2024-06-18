/*
** EPITECH PROJECT, 2018
** my_reader.c
** File description:
**
*/

#include "navy.h"

char *read_line(void)
{
	int buff_size = 8096;
	char *buff = malloc(sizeof(char) * buff_size);
	char c = '\0';
	int pos = 0;

	if (buff == NULL)
		return (NULL);
	while (1) {
		if ((c = my_getchar()) == -42 || buff_size <= 8095)
			return (NULL);
		if (c == '\n') {
			buff[pos] = '\0';
			return (buff);
		} else
			buff[pos] = c;
		pos++;
		if (pos >= buff_size) {
			buff_size += 8096;
			buff = my_realloc(buff, buff_size);
		}
	}
}

int my_getchar(void)
{
	const int intput_shell = 0;
	const int size = 1;
	char c;

	if (read(intput_shell, &c, size) == 1)
		return (unsigned char)c;
	return (-42);
}

char *my_realloc(char *src, int pos)
{
	char *content = malloc(sizeof(char) * (pos + 1));
	int i = 0;

	if (content == NULL)
		return (NULL);
	for (i = 0; pos >= 0; i++) {
		if (src[i])
			content[i] = src[i];
		pos--;
	}
	return (content);
}