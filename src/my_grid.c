/*
** EPITECH PROJECT, 2018
** my_grid.c
** File description:
**
*/

#include "navy.h"

void fill_grids(void)
{
	fill_enemy_grid();
	fill_my_grid();
	if (req->state == CLIENT)
		process_client();
	if (req->state == SERVER)
		process_server();
}

void fill_enemy_grid(void)
{
	for (int i = 0; i < 64; i++)
		req->enemy_grid[i] = WATER;
}

void fill_my_grid(void)
{
	char *content = read_file();
	int boat_size = 0;
	char *begin_point_boat = malloc(sizeof(char) * 2);
	char *end_point_boat = malloc(sizeof(char) * 2);

	for (int i = 0; i < 64; i++)
		req->my_grid[i] = WATER;
	for (int i = 0; content[i]; i += 8) {
		boat_size = content[i] - '0';
		begin_point_boat[0] = content[i + 2];
		begin_point_boat[1] = content[i + 3];
		end_point_boat[0] = content[i + 5];
		end_point_boat[1] = content[i + 6];
		write_boat(boat_size, begin_point_boat, end_point_boat);
		if (content[i + 7] == '\0')
			break;
	}
	free(content);
}

int check_grid_file(void)
{
	char *content = read_file();
	int *passed_boats = malloc(sizeof(int) * 4);
	int len = 0;
	int out = 0;

	if (content == NULL)
		return (FALSE);
	for (int i = 0; content[i]; i += 8) {
		out = check_grid_line(content, i);
		if (out == FALSE)
			return (FALSE);
		if (contain_boat(out, passed_boats, len) == TRUE)
			return (FALSE);
		passed_boats[len] = out;
		len++;
		if (content[i + 7] == '\0')
			break;
	}
	if (len != 4)
		return (FALSE);
	return (TRUE);
}

int check_grid_line(char *content, int i)
{
	if (my_strlen(content) - (i + 1) < 6)
		return (FALSE);
	if (content[i + 1] != ':' || content[i + 4] != ':')
		return (FALSE);
	if (!(content[i] >= '2' && content[i] <= '5') ||
		!(content[i + 3] >= '1' && content[i + 3] <= '8') ||
		!(content[i + 6] >= '1' && content[i + 6] <= '8'))
		return (FALSE);
	if (!(content[i + 2] >= 'A' && content[i + 2] <= 'H') ||
		!(content[i + 5] >= 'A' && content[i + 5] <= 'H'))
		return (FALSE);
	if ((content[i + 3] == content[i + 6]) &&
		(content[i + 5] - content[i + 2]) != (content[i] - '0' - 1))
		return (FALSE);
	if ((content[i + 2] == content[i + 5]) &&
		(content[i + 6] - content[i + 3]) != (content[i] - '0' - 1))
		return (FALSE);
	return (content[i] - '0');
}