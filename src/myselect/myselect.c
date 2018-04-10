#include <ncurses.h>
#include <signal.h>
#include "my.h"
int charNum, currX, currY, maxX, maxY, maxStringLength, filesPerLine, numberOfFiles;
char** files;


void fileSelect(){

}

void selectDisplay(){
	clear();
	refresh();
	getmaxyx(curscr, maxY, maxX);
	filesPerLine = maxX / (maxStringLength + 1);
	if(numberOfFiles >= filesPerLine * (maxY + 1) - 2){
		addstr("Window too small, please enlarge it");
		refresh();
		return;
	}

	getyx(curscr, currX, currY);
	for(int i = 0; i < numberOfFiles; i++){
		if(i < (currY + 1) * filesPerLine - 1){
			for(int j = 0; j <= maxStringLength - my_strlen(files[i]); j++){
				addstr(" ");
			}
			addstr(files[i]);
		} else{
			for(int j = 0; j <= maxStringLength - my_strlen(files[i]); j++){
				addstr(" ");
			}
			addstr(files[i]);
			currY++;
			move(currY, 0);
		}
		refresh();
	}
	fileSelect();
}

void windowResized(int sig){
	clear();
	endwin();
	selectDisplay();
}

int main(int argc, char* argv[]){
	signal(SIGWINCH, windowResized);
	initscr();
	erase();
	refresh();
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
	filesPerLine = maxX / (maxStringLength + 1); // +1 for the space 
	if(numberOfFiles >= filesPerLine * (maxY + 1) - 2){
		addstr("Screen is too small"); //screen is too small
		refresh();
	} else {
		selectDisplay();	
	}

	
	while(1){

	}
	endwin();
}