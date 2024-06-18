/*
** EPITECH PROJECT, 2018
** my_handler.c
** File description:
**
*/

#include "navy.h"

void handle_hello_connect(int data)
{
	req->enemy_pid = data;
	usleep(3000);
}

void handle_game_finished(int data)
{
	if (data == -1)
		return;
	req->running = FALSE;
	req->callback = 0;
	usleep(3000);
}

void handle_turn_finished(int data)
{
	req->enemy_len = data;
	req->turn = TRUE;
	usleep(3000);
}

void wait_enemy(void)
{
	my_put_str("waiting for enemy's attack...\n");
	req->turn = FALSE;
	while (req->turn != TRUE && req->running == TRUE);
	usleep(100);
	req->tour = TRUE;
	if (req->state == SERVER)
		display_positions();
	usleep(3000);
}

int attack_enemy(void)
{
	my_put_str("attack: ");
	req->line = read_line();
	if (req->line == NULL) {
		req->callback = 0;
		return (-2);
	}
	if (my_strlen(req->line) != 2 ||
	!(req->line[0] >= 'A' && req->line[0] <= 'H') ||
	!(req->line[1] >= '0' && req->line[1] <= '8')) {
		my_put_str("wrong position\n");
		return (-1);
	}
	process_attack(req->line);
	if (req->state == CLIENT)
		display_positions();
	req->tour = FALSE;
	return (0);
}