/*
** EPITECH PROJECT, 2018
** my_engine.c
** File description:
**
*/

#include "navy.h"

void process(void)
{
	if (open(req->file_name, O_RDONLY) <= 0) {
		my_put_str(ERROR_FILE);
		req->callback = 84;
		return;
	}
	my_put_str("my_pid: ");
	my_put_nbr(req->player_pid);
	my_put_char('\n');
	prepare_signal(SIGUSR1);
	prepare_signal(SIGUSR2);
	fill_grids();
	display_positions();
	end_game();
}

int process_game(void)
{
	int result;

	while (req->running == TRUE && game_finished() == FALSE) {
		if (req->tour == TRUE) {
			result = attack_enemy();
			if (result == -2)
				return (-1);
			if (result == -1)
				continue;
		}
		else
			wait_enemy();
	}
	return (0);
}

void process_client(void)
{
	my_put_str("successfully connected\n\n");
	send_request(HelloConnectMessage, req->player_pid);
}

void process_server(void)
{
	my_put_str("waiting for enemy connexion...\n\n");
	while (req->enemy_pid == 0);
	usleep(100);
	my_put_str("enemy connected\n\n");
}

void process_attack(char *line)
{
	char nbr = line[1] - '0';
	int letter = (line[0] - 65);
	int index = -1;

	for (int i = letter; i < 64; i += 8) {
		if ((i - letter) / 8 >= nbr - 1 &&
			(i - letter) / 8 <= nbr - 1) {
			index = i;
		}
	}
	send_request(Attack, index);
	while (req->tour != FALSE);
	usleep(100);
}