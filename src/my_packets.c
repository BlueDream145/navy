/*
** EPITECH PROJECT, 2018
** my_packets.c
** File description:
**
*/

#include "navy.h"

void dispatch_packet(int type, int data)
{
	switch (type) {
		case HelloConnectMessage:
			handle_hello_connect(data);
			break;
		case GameFinished:
			handle_game_finished(data);
			break;
		case TurnFinished:
			handle_turn_finished(data);
			break;
		case AttackSuccess:
			handle_attack_success(data);
			break;
		case AttackFail:
			handle_attack_fail(data);
			break;
		case Attack:
			handle_attack(data);
			break;
	}
}

void handle_attack(int data)
{
	if (data < 0 || data > 64)
		return;
	my_put_str(get_coordinates(data));
	if (req->my_grid[data] >= 2) {
		req->my_grid[data] = SHOT_BOAT;
		send_request(AttackSuccess, data);
		my_put_str(": hit\n\n");
	} else {
		if (req->my_grid[data] != SHOT_BOAT)
			req->my_grid[data] = SHOT_FAIL;
		send_request(AttackFail, data);
		my_put_str(": missed\n\n");
	}
	if (boat_left() == 0) {
		req->callback = LOSE;
		req->running = FALSE;
	}
	req->tour = TRUE;
	usleep(3000);
}

void handle_attack_success(int data)
{
	if (data < 0 || data > 64)
		return;
	req->enemy_grid[data] = SHOT_BOAT;
	my_put_str(get_coordinates(data));
	my_put_str(": hit\n\n");
	usleep(10000);
	send_request(TurnFinished, boat_left());
	if (req->enemy_len == 1) {
		req->callback = WON;
		req->running = FALSE;
	}
	req->tour = FALSE;
	usleep(3000);
}

void handle_attack_fail(int data)
{
	if (data < 0 || data > 64)
		return;
	if (req->enemy_grid[data] != SHOT_BOAT)
		req->enemy_grid[data] = SHOT_FAIL;
	my_put_str(get_coordinates(data));
	my_put_str(": missed\n\n");
	usleep(8000);
	send_request(TurnFinished, boat_left());
	req->tour = FALSE;
	usleep(3000);
}