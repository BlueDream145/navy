/*
** EPITECH PROJECT, 2018
** my_positions.c
** File description:
**
*/

#include "navy.h"

void display_positions(void)
{
	display_my_positions();
	display_enemy_positions();
}

void display_my_positions(void)
{
	my_put_str("my positions:\n");
	display(req->my_grid);
	my_put_str("\n");
}

void display_enemy_positions(void)
{
	my_put_str("enemy's positions:\n");
	display(req->enemy_grid);
	my_put_char('\n');
}

void display_cell(int cell)
{
	if (cell == WATER)
		my_put_char('.');
	if (cell == SHOT_FAIL)
		my_put_char('o');
	if (cell == SHOT_BOAT)
		my_put_char('x');
	if (cell >= 2)
		my_put_nbr(cell);
}

void display(int *cells)
{
	my_put_str(" |A B C D E F G H\n");
	my_put_str("-+---------------\n");
	for (int i = 0; i < 8; i++) {
		my_put_nbr(i + 1);
		my_put_char('|');
		for (int n = (i * 8); n < (i * 8) + 8; n++) {
			display_cell(cells[n]);
			if (n + 1 < (i * 8) + 8)
				my_put_char(' ');
		}
		my_put_char('\n');
	}
}