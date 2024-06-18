/*
** EPITECH PROJECT, 2018
** my_signal.c
** File description:
**
*/

#include "navy.h"

void send_request(int type, int data)
{
	int *type_bin = my_getbinary(type);
	int *type_data = my_getbinary(data);

	usleep(8000);
	for (int i = 0; i < 16; i++) {
		if (type_bin[i] == 0)
			send_signal(SIGUSR1);
		else if (type_bin[i] == 1)
			send_signal(SIGUSR2);
	}
	usleep(8000);
	for (int i = 0; i < 16; i++) {
		if (type_data[i] == 0)
			send_signal(SIGUSR1);
		else if (type_data[i] == 1)
			send_signal(SIGUSR2);
	}
}

int send_signal(int signal)
{
	if (kill(req->enemy_pid, signal) == -1) {
		req->callback = ERROR;
		return (FALSE);
	}
	usleep(10000);
	return (TRUE);
}

void prepare_signal(int id)
{
	struct sigaction action;

	action.sa_flags = SA_SIGINFO;
	action.sa_handler = receive_signal;
	sigemptyset (&action.sa_mask);
	if (sigaction (id, &action, NULL) == -1)
		return;
}

void receive_signal(int sig)
{
	static int *msg_type = NULL;
	static int *msg_data = NULL;
	static int pos = 0;

	if (msg_type == NULL || msg_data == NULL) {
		msg_type = malloc(sizeof(int) * 16);
		msg_data = malloc(sizeof(int) * 16);
	}
	if (pos < 16)
		msg_type[pos] = get_binary_value(sig);
	else
		msg_data[pos - 16] = get_binary_value(sig);
	pos++;
	if (pos == 32)
		dispatch_packet(my_getvalue(msg_type), my_getvalue(msg_data));
	if (pos >= 32) {
		msg_type = NULL;
		msg_data = NULL;
		pos = 0;
	}
}

int get_binary_value(int sig)
{
	if (sig == SIGUSR1)
		return (0);
	else if (sig == SIGUSR2)
		return (1);
	return (-1);
}