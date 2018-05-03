#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "my.h"
#include <ncurses.h>

char* currentPath;
pid_t pidChild = -1;

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
void bufferWordShift(char* command, int currPos, int buffLength, char* word, int wordLength){
	for(int i = buffLength; i > currPos + wordLength - 1; i--){//already incremented bufferlength
		command[i] = command[i - wordLength];
	}
	int j = 0;
	for(int i = currPos; i < currPos + wordLength; i++){
		command[i] = word[j];
		j++;
	}
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

int cutWord(char* command, int currPos, int buffLength, char* clipboard, int hasCutWord){//returns length of word from currPos
	int i = currPos - 1;
	int retInt = 0;
	while(command[i] == ' ' && i >= 0){//move backward until word
		i--;
		retInt++;
	}
	while(command[i] != ' ' && i >= 0){//count until start of word
		i--;
		retInt++;
	}
	// cut the word if not at end
	int clipLength = my_strlen(clipboard);
	if(hasCutWord){
		if(currPos != buffLength){
			addstr("HERE");
			for(int i = currPos; i < buffLength; i++){//already incremented bufferlength
				bufferShift(clipboard, 0, clipLength, command[i - retInt]);
				command[i - retInt] = command[i];
				command[i] = '\0';
			}
		} else {
			for(int i = buffLength; i > buffLength - retInt - 1; i--){
				bufferShift(clipboard, 0, clipLength, command[i]);
				command[i] = '\0';
			}
		}
	} else {
		char* copyStr = (char*)malloc(1024);
		memset(copyStr, '\0', 1024);
		memset(clipboard, '\0', 1024);
		int j = 0;
		if(currPos != buffLength){
			for(int i = currPos; i < buffLength; i++){//already incremented bufferlength
				copyStr[retInt - j - 1] = command[i];
				command[i - retInt] = command[i];
				command[i] = '\0';
				j++;
			}
		} else {
			for(int i = buffLength; i > buffLength - retInt - 1; i--){
				copyStr[retInt - j - 1] = command[i];
				command[i] = '\0';
				j++;
			}
		}
		strcpy(clipboard, copyStr);
	}
	return retInt;
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
	int hasCutWord = 0;
	if(commandCount == commandCap){
		return 0;
	}
	char* clipboard = (char*)malloc(1024);
	memset(clipboard, '\0', 1024);
	while(1){
		//exit other while loop to reset
		refresh();
		getyx(curscr, y, x);
		move(y++, 0);
		refresh();
		currentPath = getcwd(NULL, 0);
		char* currentCommand = (char*)malloc(1024);
		memset(currentCommand, '\0', 1024);
		commandBufferLength = 0;
		currentPositionBuffer = 0;
		writePrompt();
		free(currentPath);
		while(1){
			inputChar = getch();
			if(inputChar == 1){//CTRL+A
				//Move to the start of the current command
				getyx(curscr, y, x);
				move(y, x - currentPositionBuffer);
				currentPositionBuffer = 0;
			} else if(inputChar == 3){//CTRL+C
				endwin();
				exit(0);
				return 0;
			} else if(inputChar == 5){//CTRL+E
				//Move to the end of the current command
				getyx(curscr, y, x);
				move(y, x + commandBufferLength - currentPositionBuffer);
				currentPositionBuffer = commandBufferLength;
			} else if( inputChar == 12){//CTRL+L
				//Clear the terminal except for the current command
				getyx(curscr, y, x);
				clear();
				move(0, 0);
				writePrompt();
				addstr(currentCommand);
				move(0, x);
			} else if(inputChar == 21){//CTRL+U
				//Cut a line into the clipboard. Works with Ctrl W
				hasCutWord = 0;
				memset(clipboard, '\0', 1024);
				strcpy(clipboard, currentCommand);
				memset(currentCommand, '\0', 1024);
				commandBufferLength = 0;
				currentPositionBuffer = 0;
				clear();
				writePrompt();
			} else if(inputChar == 23){//CTRL+W
				//Cuts a word into the clipboard
				hasCutWord = 1; //set has word to true
				int wordLength = cutWord(currentCommand, currentPositionBuffer, commandBufferLength, clipboard, hasCutWord);
				getyx(curscr, y, x);
				clearLine();
				writePrompt();
				addstr(currentCommand);
				currentPositionBuffer -= wordLength;
				commandBufferLength -= wordLength;
				move(y, x - wordLength);
			} else if(inputChar == 25){//CTRL+Y
				//Paste clipboard
				int clipLength = my_strlen(clipboard);
				if(currentPositionBuffer != commandBufferLength){
					getyx(curscr, y, x);
					commandBufferLength += clipLength;
					bufferWordShift(currentCommand, currentPositionBuffer, commandBufferLength, clipboard, clipLength);
					clearLine();
					writePrompt();
					addstr(currentCommand);
					move(y, x + clipLength);
					currentPositionBuffer += clipLength;
				} else {//either at 0 or end
					strcpy(&currentCommand[currentPositionBuffer], clipboard);
					currentPositionBuffer += clipLength;
					commandBufferLength += clipLength;
					clearLine();
					writePrompt();
					addstr(currentCommand);
				}
			} else if(inputChar == KEY_LEFT){
				if(currentPositionBuffer != 0){
					getyx(curscr, y, x);
					move(y, --x);
					currentPositionBuffer--;
					hasCutWord = 0;
				}
			} else if(inputChar == KEY_RIGHT){
				if(currentPositionBuffer != commandBufferLength){
					getyx(curscr, y, x);
					move(y, ++x);
					currentPositionBuffer++;
					hasCutWord = 0;
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
				getyx(curscr, y, x);
				move(++y, 0);
				refresh();
				char** stuff = my_str2vect(currentCommand);
				if(my_strcmp(stuff[0], "cd") == 0){
					if(chdir(stuff[1]) < 0){
						my_str("The directory \'");
						my_str(stuff[1]);
						my_str("\' does not exist.\n");
					}
					currentPath = getcwd(NULL, 0);
				} else if(my_strcmp(stuff[0], "exit") == 0){
					my_str("Bye");
					exit(0);
					return 0;
				} else if(my_strcmp(stuff[0], "help") == 0){
					my_str("HELP\ncd - change directory\nhelp - get this message\nexit - exit MINISHELL\n");
				} else {
					if((pidChild = fork()) < 0){
						perror("DAS BROKE\n");
						exit(0);
					} else if(pidChild == 0){						
						if(execvp(stuff[0], stuff) < 0){
							my_str("YOU DID SOMETHING WRONG\n");
							exit(0);	
						}
					}
					wait(NULL);
				}
				break;
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