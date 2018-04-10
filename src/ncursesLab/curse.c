#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>

void downKey(char* buff){
	start_color();			/* Start color 			*/
	init_pair(1, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	for(int j = 0; j < strlen(buff); j++){
		addch(buff[j]);
	}
	attroff(COLOR_PAIR(1));
}

int  main(int argc, char* argv[]){
	initscr();
	int c;
	//char second;
	noecho();
	erase();
	clear();
	//keypad(stdscr, TRUE);
	char buff[1024];
	memset(buff, '\0', 1024);
	int i = 0;
	int x, y;
	int maxx, maxy;
	while(1){
		c = getch();
		if(c == 23){
			exit(0);
		} else if(c == 27){
			if((c = getch()) == 91){
				if((c = getch()) == 66){
					addch('\n');
					getyx(curscr, y, x);
					getmaxyx(curscr, maxy, maxx);
					if(y == maxy){
						addch('\n');
					}
					maxx--;
					downKey(buff);
					addch('\n');
					memset(buff, '\0', 1024);
					i = 0;
					continue;
				} else {
					buff[i] = 27;
					buff[i++] = 91;
					buff[i++] = c;
					i++;
					continue;
				}
			} else {
				buff[i] = 27;
				buff[i++] = c;
				i++;
				continue;
			}
		} else if(c == 127){
			if(strlen(buff) != 0){
				getyx(curscr, y, x);
				move(y, x-1);
				delch();
				i--;
				buff[i] = '\0';
			}
		}else {
			addch(c);
			buff[i] = c;
			i++;
		}
	}
}