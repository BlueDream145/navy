/*
** EPITECH PROJECT, 2018
** main.c
** File description:
**
*/

#include "navy.h"

int main(int ac, char **as)
{
	int error;

	if (ac != 2 && ac != 3)
		return (ERROR);
	error = check(ac, as);
	if (error != 42)
		return (error);
	req = get_request(ac, as);
	if (req == NULL)
		return (ERROR);
	if (ac == 3 && kill(req->enemy_pid, 0) == -1) {
		my_put_str(ERROR_PID);
		return (ERROR);
	}
	if (check_grid_file() == FALSE) {
		my_put_str(ERROR_MAP);
		return (ERROR);
	}
	process();
	return (req->callback);
}

int check(int ac, char **as)
{
	if (ac == 2) {
		if ((my_strlen(as[1]) == 1 && as[1][0] == 'h') ||
			(my_strlen(as[1]) == 2 && as[1][1] == 'h')) {
			help();
			return (NONE);
		}
	} else if (my_str_isnum(as[1]) == FALSE)
		return (ERROR);
	if (ac == 3 && my_getnbr(as[1]) <= 0)
		return (ERROR);
	return (42);
}

void help(void)
{
	const char *usage = "USAGE\n           "
		"./navy [first_player_pid] navy_positions\n\n";
	const char *description = "DESCRIPTION\n";
	const char *description_content = "           first_player_pid   "
		"only for the 2nd player.  pid of the first player.\n"
		"           navy_positions     file representing "
		"the positions of the ships.\n";

	my_put_str(usage);
	my_put_str(description);
	my_put_str(description_content);
}

void end_game(void)
{
	req->running = TRUE;
	if (process_game() == -1)
		req->callback = NONE;
	else
		if (req->callback == WON)
			my_put_str("I won\n");
		else if (req->callback == LOSE)
			my_put_str("Enemy won\n");
}