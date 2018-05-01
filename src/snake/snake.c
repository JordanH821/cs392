#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>

typedef struct snakePart* SnakePart;
struct snakePart {
	int x;
	int y;
};

int main(int argc, char* argv[]){
	initscr();
	int maxX, maxY, bodyLength = 3, score = 0, deaths = 0, pelletX, pelletY, headX, headY, direction = 1;
	getmaxyx(curscr, maxY, maxX);
	SnakePart* moves = (SnakePart*)malloc(1000* sizeof(SnakePart));
	for(int i = 0; i < 1000; i++)
		moves[i] = (SnakePart) malloc(sizeof(struct snakePart));
	char* scoreBuff = malloc(10);
	char* deathsBuff = malloc(10);
	char* lengthBuff = malloc(10);
	// for(int i = 0; i < 1000; i++){
	// 	snakePart[i] = (snakePart)malloc(sizeof(snakePart))
	// }


	headX = maxX / 2;
	headY = maxY / 2;
	moves[0]->x = headX;
	moves[0]->y = headY;
	moves[1]->x = headX - 1;
	moves[1]->y = headY;
	moves[2]->x = headX - 2;
	moves[2]->y = headY;


	while(1){
		refresh();
		move(0, 0);
		noecho();
		sprintf(scoreBuff, "%d", score);
		addstr("Score: ");
		addstr(scoreBuff);
		sprintf(deathsBuff, "%d", deaths);
		addstr(" Deaths: ");
		addstr(deathsBuff);
		sprintf(lengthBuff, "%d", bodyLength);
		addstr(" Length: ");
		addstr(lengthBuff);

		//put snake
		mvwaddch(curscr, moves[0]->y, moves[0]->x, '@');
		for(int i = 1; i < bodyLength; i++){
			mvwaddch(curscr, moves[i]->y, moves[i]->x, '#');
		}
		//put pellets	

		pelletX = rand() % maxX;
		pelletY = rand() % maxY;
		while(mvgetch(pelletY, pelletX) != ' ' || pelletY != 0){
			pelletX = rand() % maxX;
			pelletY = rand() % maxY;
		}
		mvwaddch(curscr, pelletY, pelletX, '$');
		

		//if head takes apple



		//move the snake
		for(int j = 1; j < bodyLength; j++){
			moves[j]->x = moves[j-1]->x;
			moves[j]->y = moves[j-1]->y;
		}

		//adjust head position
		if(direction == 0){
			moves[0]->y = moves[0]->y + 1;
		} else if(direction == 1){
			moves[0]->x = moves[0]->x + 1;
		} else if(direction == 2){
			moves[0]->y = moves[0]->y - 1;
		} else if(direction == 3){
			moves[0]->x = moves[0]->x - 1;
		} 
		//test head
		if(mvgetch(moves[0]->y, moves[1]->x) != ' '){
				deaths++;
				score = 0;
				bodyLength = 3;
				moves[0]->x = headX;
				moves[0]->y = headY;
				moves[1]->x = headX - 1;
				moves[1]->y = headY;
				moves[2]->x = headX - 2;
				moves[2]->y = headY;
		}

		//if head takes apple
		sleep(->5);
		beep();
		refresh();
	}
	return 0;
}