#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "my.h"
#include <ncurses.h>

char* currentPath;

void writePrompt(){
	attron(COLOR_PAIR(1));
	addstr("NSMINISHELL: ");
	attroff(COLOR_PAIR(1));
	refresh();
	attron(COLOR_PAIR(2));
	currentPath = getcwd(NULL, 0);
	addstr(currentPath);
	attroff(COLOR_PAIR(2));
	refresh();
	attron(COLOR_PAIR(3));
	addstr(" $: ");
	attroff(COLOR_PAIR(3));
	refresh();
}

void deleteKey(char* command, int currPos, int buffLength){
	if(currPos == 0){
		return;
	}
	for(int i = currPos; i < buffLength - 1; i++){
		command[currPos] = command[currPos + 1];
	}
	command[buffLength] = '\0';
	int x, y;
	getyx(curscr, y, x);
	move(y, x - 1);
	delch();
}

void bufferShift(char* command, int currPos, int buffLength, char insert){
	for(int i = buffLength; i > currPos; i--){
		command[i] = command[i - 1];
	}
	command[currPos] = insert;
}

void clearLine(){
	int x, y;
	getyx(curscr, y, x);
	while(x > 0){
		delch();
		x--;
		move(y, x);
	}
}

int main(int argc, char* argv[]){
	initscr();
	erase();
	noecho();
	refresh();
	start_color();
	keypad(stdscr, TRUE);
	//nodelay(stdscr, true);
	raw();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	int commandCap = 10;
	char **commands = malloc(commandCap* sizeof(char *));
	int inputChar;
	for (int i = 0; i < commandCap; i++) {
	    commands[i] = (char *)malloc(1024);
	    memset(commands[i], '\0', 1024);
	}
	int commandCount = 0;
	int commandBufferLength = 0;
	int currentPositionBuffer = 0;
	int x, y;
	if(commandCount == commandCap){
		return 0;
	}
	while(1){
		currentPath = getcwd(NULL, 0);
		char* currentCommand = (char*)malloc(1024);
		commandBufferLength = 0;
		writePrompt();
		free(currentPath);
		while(1){
			inputChar = getch();
			if(inputChar == 1){//CTRL+A
				//Move to the start of the current command
			} else if(inputChar == 3){//CTRL+C
				endwin();
				exit(0);
				return 0;
			} else if(inputChar == 5){//CTRL+E
				//Move to the end of the current command
			} else if( inputChar == 12){//CTRL+L
				//Clear the terminal except for the current command
			} else if(inputChar == 21){//CTRL+U
				//Cut a line into the clipboard. Works with Ctrl W
			} else if(inputChar == 23){//CTRL+W
				//Cuts a word into the clipboard
			} else if(inputChar == 25){//CTRL+Y
				//Paste clipboard
			} else if(inputChar == KEY_LEFT){
				if(currentPositionBuffer != 0){
					getyx(curscr, y, x);
					move(y, --x);
					currentPositionBuffer--;
				}
			} else if(inputChar == KEY_RIGHT){
				if(currentPositionBuffer != commandBufferLength){
					getyx(curscr, y, x);
					move(y, ++x);
					currentPositionBuffer++;
				}
			} else if(inputChar == 127){
				deleteKey(currentCommand, currentPositionBuffer, commandBufferLength);
				if(commandBufferLength != 0){
					commandBufferLength--;
				}
				if(currentPositionBuffer != 0){
					currentPositionBuffer--;
				}
			} else if(inputChar == KEY_ENTER || inputChar == 10){
				addstr(currentCommand);
			} else {
				if(currentPositionBuffer != commandBufferLength){//add character mid buffer
					commandBufferLength++;
					bufferShift(currentCommand, currentPositionBuffer, commandBufferLength, (char)inputChar);
					// currentCommand[currentPositionBuffer] = (char)inputChar;
					currentPositionBuffer++;
					// commandBufferLength++;
					getyx(curscr, y, x);
					clearLine();
					writePrompt();
					addstr(currentCommand);
					move(y, x + 1);
				} else {
					currentCommand[commandBufferLength] = (char)inputChar;
					commandBufferLength++;
					currentPositionBuffer++;
					addch(inputChar);
				}
			}
		}
	}

}