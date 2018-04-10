#include <ncurses.h>
#include <signal.h>
#include "my.h"
int charNum, currX, currY, maxX, maxY, maxStringLength, filesPerLine, numberOfFiles;
char** files;

void selectDisplay(){
	clear();
	refresh();
	getmaxyx(curscr, maxY, maxX);
	filesPerLine = maxX / (maxStringLength + 1);
	getyx(curscr, currX, currY);
	charNum = 0;
	int filesThisLine = 0;
	for(int i = 0; i < numberOfFiles; i++){
		if(filesThisLine < filesPerLine){
			for(int j = 0; j < maxStringLength - my_strlen(files[i]); j++){
				addstr(" ");
			}
			addstr(files[i]);
			filesThisLine++;
			refresh();
		} else{
			filesThisLine = 1;
			for(int j = 0; j <= maxStringLength - my_strlen(files[i]); j++){
				addstr(" ");
			}
			addstr(files[i]);
			move(currY + 1, 0);
			currY++;
			refresh();
		}
	}
}

void windowResized(int sig){
	clear();
	endwin();
	selectDisplay();
}

int main(int argc, char* argv[]){
	signal(SIGWINCH, windowResized);
	maxStringLength = 0;
	initscr();
	erase();
	getmaxyx(curscr, maxY, maxX);
	files = &argv[1];
	numberOfFiles = argc - 1;

	//find max string length
	for(int i = 1; i < argc; i++){
		if(my_strlen(argv[i]) > maxStringLength){
			maxStringLength = my_strlen(argv[i]);
		}
	}

	//find number of filenames for line
	filesPerLine = maxX / (maxStringLength + 1);
	if( (filesPerLine * maxY) <= (argc - 1) ){
		my_str("Screen is too small"); //screen is too small
	}

	selectDisplay();
	while(1){

	}
	endwin();
}