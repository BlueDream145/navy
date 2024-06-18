/*
** EPITECH PROJECT, 2018
** my_get.c
** File description:
**
*/

#include "navy.h"

struct request *get_request(int ac, char **as)
{
	req = malloc(sizeof(struct request));
	req->my_grid = malloc(sizeof(int) * 64);
	req->enemy_grid = malloc(sizeof(int) * 64);
	if (ac == 2) {
		req->state = SERVER;
		req->enemy_pid = 0;
		req->tour = TRUE;
	}
	else {
		req->state = CLIENT;
		req->enemy_pid = my_getnbr(as[1]);
		req->tour = FALSE;
	}
	req->file_name = as[ac - 1];
	req->player_pid = getpid();
	req->callback = NONE;
	req->enemy_len = 0;
	return (req);
}

char *get_coordinates(int index)
{
	char *result = malloc(sizeof(char) * 3);
	int current;

	if (result == NULL)
		return (NULL);
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			current = x + (8 * y);
			if (current == index) {
				result[0] = x + 65;
				result[1] = (y + 1) + '0';
				break;
			}
		}
	}
	result[2] = '\0';
	return (result);
}

int my_getnbr(char *str)
{
	int val = 0;

	while (*str) {
		if (*str >= '0' && *str <= '9') {
			val *= 10;
			val += *str - '0';
		}
		else
			return (-1);
		str++;
	}
	return (val);
}

int *my_getbinary(int nbr)
{
	int numbers[16] = { 32768, 16384, 8192, 4096, 2048, 1024, 512, 256,
		128, 64, 32, 16, 8, 4, 2, 1 };
	int *array = malloc(sizeof(int) * 16);

	if (nbr < 0 || nbr > 65535 || array == NULL)
		return (NULL);
	for (int i = 0; i < 16; i++) {
		if (numbers[i] <= nbr) {
			nbr -= numbers[i];
			array[i] = 1;
		} else
			array[i] = 0;
	}
	return (array);
}

int my_getvalue(int *bin)
{
	int numbers[16] = { 32768, 16384, 8192, 4096, 2048, 1024, 512, 256,
		128, 64, 32, 16, 8, 4, 2, 1 };
	int val = 0;

	for (int i = 0; i < 16; i++)
		if (bin[i] == 1)
			val += numbers[i];
	return (val);
}