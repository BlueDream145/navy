/*
** EPITECH PROJECT, 2018
** my_parser.c
** File description:
**
*/

#include "navy.h"

char *read_file(void)
{
	int fd = open(req->file_name, O_RDONLY);
	char *buff = malloc(sizeof(char) * 4096);
	int offset = 0;

	if (fd <= 0 || buff == NULL) {
		my_put_str(ERROR_FILE);
		return (NULL);
	}
	while (read(fd, buff + offset, 1) > 0 && offset < 4095)
		offset += 1;
	buff[offset] = '\0';
	close(fd);
	return (buff);
}

void write_boat(int boat_size, char *begin_point_boat, char *end_point_boat)
{
	char f_nbr = (begin_point_boat[1] - '0');
	char s_nbr = (end_point_boat[1] - '0');
	int f_letter = (begin_point_boat[0] - 65);
	int s_letter = (end_point_boat[0] - 65);

	if (f_letter == s_letter) {
		for (int i = f_letter; i < 64; i += 8)
			if ((i - f_letter) / 8 >= f_nbr - 1 &&
				(i - f_letter) / 8 <= s_nbr - 1)
				req->my_grid[i] = boat_size;
	}
	else if (f_nbr == s_nbr) {
		for (int i = (f_nbr - 1) * 8; i < ((f_nbr - 1) * 8) + 8; i++)
			if ((i - ((f_nbr - 1) * 8)) >= f_letter
				&& (i - ((f_nbr - 1) * 8)) <= s_letter)
				req->my_grid[i] = boat_size;
	}
}

int game_finished(void)
{
	int contain = FALSE;

	for (int i = 0; i < 64; i++) {
		if (req->my_grid[i] >= 2) {
			contain = TRUE;
			break;
		}
	}
	if (contain == FALSE) {
		req->callback = 1;
		send_request(GameFinished, 0);
		req->running = FALSE;
		return (TRUE);
	}
	return (FALSE);
}

int boat_left(void)
{
	int len = 0;

	for (int i = 0; i < 64; i++)
		if (req->my_grid[i] >= 2)
			len++;
	return (len);
}

int contain_boat(int size, int *boats, int len)
{
	for (int i = 0; i < len; i++)
		if (boats[i] == size)
			return (TRUE);
	return (FALSE);
}