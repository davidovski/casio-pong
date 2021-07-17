// Pong add-in by davidovski
// Copyright (C) 2021 davidovski
//
// This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/keycodes.h>
#include <gint/clock.h>
#include <math.h>


int s1 = 0;
int s2 = 0;

float bx = 64;
float by = 32;
int bs = 2;

float vx = 0;
float vy = 0;

float s = 1;

int p1 = 24;
int p2 = 24;
int h = 16;
int w = 2;
int main(void)
{
	int tick = 1;
	bool game = true;
	while (game) {
		dclear(C_WHITE);

		drect(1, p1, 1 + w, p1 + h, C_BLACK);
		drect(125, p2, 125 + w, p2 + h, C_BLACK);

		drect(bx-1, by-1, bx+1, by+1, C_BLACK);

		dupdate();
	

		pollevent();

		if (keydown(KEY_EXIT)) 
			game = false;

		if (keydown(KEY_1) && p1 + h < 64)  
				p1 += 1;
		if (keydown(KEY_4) && p1 > 0)  
				p1 -= 1;
		if (keydown(KEY_5) && bs == 1) {
				bs = 0;
				vy = 0;
				vx = s;
		}

		if (keydown(KEY_SUB) && p2 + h < 64)  
				p2 += 1;
		if (keydown(KEY_DIV) && p2 > 0)  
				p2 -= 1;
		if (keydown(KEY_MUL) && bs == 2) {
				bs = 0;
				vy = 0;
				vx = -s;
		}

		if (bs == 1) { //player 1 serve
			bx = 5;
			by = p1 + (h/2);
		} else if (bs == 2) { // player 2 serve
			bx = 123;
			by = p2 + (h/2);
		} else {

			if (by < 1) vy *= -1; 
			if (by > 63) vy *= -1; 
			
			if (bx < 0) bs = 2;
			if (bx > 128) bs = 1;


			// collided with player 1
			if (by > p1 && by < p1+h+2 && bx <= 5) {
				int dy = p1+(h/2) - by;
				vx = fabs(vx);
				vy += dy * 0.1;

			}
			if (by > p2 && by < p2+h+2 && bx >= 123) {

				int dy =  p2+(h/2) - by;
				vx = -fabs(vx);
				vy += dy * -0.1;
			}

			bx += vx;
			by += vy;
		}

		tick++;
		sleep_us(20*1000);
	}
	game = true;
	return 0;
}
