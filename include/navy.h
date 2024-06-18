/*
** EPITECH PROJECT, 2017
** file.h
** File description:
**
*/

#ifndef navy_
#define navy_

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define ERROR_PID ("Invalid pid.\n")
#define ERROR_SIGNAL ("Failed to send signal.\n")
#define ERROR_FILE ("Can not open this file.\n")
#define ERROR_FATAL ("Signal failed.\n")
#define ERROR_MAP ("Bad map encodage.\n")
#define TRUE (1)
#define FALSE (0)

struct request *req;

enum state {
	CLIENT,
	SERVER
};

enum callback {
	NONE = 0,
	WON = 0,
	LOSE = 1,
	ERROR = 84
};

enum cell {
	WATER = -1,
	SHOT_BOAT = 0,
	SHOT_FAIL = 1
};

enum packets {
	HelloConnectMessage,
	GameFinished,
	TurnFinished,
	AttackSuccess,
	AttackFail,
	Attack
};

struct request {
	int *my_grid;
	int *enemy_grid;
	char *file_name;
	char *line;
	int state;
	int callback;
	int player_pid;
	int enemy_pid;
	int enemy_len;
	int tour;
	int wait;
	int running;
	int turn;
};

// main.c
int check(int ac, char **as);
void help(void);
void end_game(void);

// my_engine.c
void process(void);
int process_game(void);
void process_client(void);
void process_server(void);
void process_attack(char *line);

// my_get.c
struct request *get_request(int ac, char **as);
char *get_coordinates(int index);
int *my_getbinary(int nbr);
int my_getnbr(char *str);
int my_getvalue(int *bin);

// my_grid.c
void fill_grids(void);
void fill_enemy_grid(void);
void fill_my_grid(void);
int check_grid_file(void);
int check_grid_line(char *content, int i);

// my_handler.c
void handle_hello_connect(int data);
void handle_game_finished(int data);
void handle_turn_finished(int data);
void wait_enemy(void);
int attack_enemy(void);

// my_packets.c
void dispatch_packet(int type, int data);
void handle_attack(int data);
void handle_attack_success(int data);
void handle_attack_fail(int data);

// my_parser.c
char *read_file(void);
void write_boat(int boat_size,
	char *begin_point_boat, char *end_point_boat);
int game_finished(void);
int boat_left(void);
int contain_boat(int size, int *boats, int len);

// my_positions.c
void display_positions(void);
void display_my_positions(void);
void display_enemy_positions(void);
void display(int *cells);

// my_put.c
void my_put_char(char c);
void my_put_str(const char *str);
int my_put_nbr(int nb);

// my_reader.c
char *read_line(void);
int my_getchar(void);
char *my_realloc(char *src, int pos);

// my_signal.c
void send_request(int type, int data);
int send_signal(int signal);
void prepare_signal(int id);
void receive_signal(int sig);
int get_binary_value(int sig);

// my_string.c
int my_strlen(const char *str);
int my_str_isnum(const char *str);
int my_str_printable(const char *str);
char *my_strcpy(char *dest, const char *src);
char *my_strcat(char *dest, const char *src);

#endif /* navy */