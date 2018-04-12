#include <ncurses.h>
#include <string.h>
#include <signal.h>
#include "my.h"
int charNum, currX, currY, maxX, maxY, maxStringLength, filesPerLine, numberOfFiles, c, fileIndex;
char** files;


int atWhatFile(int x, int y){
	char fileNum = 0;
	fileNum += y * filesPerLine;
	fileNum += x / (maxStringLength + 1);
	return fileNum;
}

int main(int argc, char* argv[]){
	initscr();
	noecho();
	//curs_set(0);
	keypad(stdscr, TRUE);
	nodelay(stdscr, true);
	set_escdelay(0);
	erase();
	clear();
	raw();
	refresh();
	getmaxyx(curscr, maxY, maxX);
	files = &argv[1];
	numberOfFiles = argc - 1;
	int* selectedFiles = malloc(sizeof(int) * numberOfFiles);
	for(int i = 0; i < numberOfFiles; i ++){
		selectedFiles[i] = 0;
	}

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
	}

	while(1){
		refresh();
		getmaxyx(curscr, maxY, maxX);
		filesPerLine = maxX / (maxStringLength + 1);
		if(numberOfFiles >= filesPerLine * (maxY + 1) - 2){
			continue;
		} else {
			erase();
			refresh();
			break;
		}

	}

	getyx(curscr, currX, currY);
	for(int i = 0; i < numberOfFiles; i++){
		if(i < (currY + 1) * filesPerLine - 1){
			for(int j = 0; j <= maxStringLength - my_strlen(files[i]); j++){
				addstr(" ");
			}
			if(i == 0){
				attron(A_UNDERLINE);
				addstr(files[i]);
				attroff(A_UNDERLINE);
			} else {
				addstr(files[i]);
			}
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
	
	move(0, maxStringLength - my_strlen(files[0]) + 1); //cursor sits on first character of word
	//arrows, space, esc
	while(1){
		attrset(A_NORMAL);
		refresh();
		getyx(curscr, currY, currX);
		getmaxyx(curscr, maxY, maxX);
		fileIndex = atWhatFile(currX, currY);
		if((c = getch()) == 27){
			endwin();
			exit(0);
			return 1;
		} else if(c == KEY_UP){
			fileIndex = atWhatFile(currX, currY);
			if(fileIndex - filesPerLine >= 0){ //move up
				attroff(A_UNDERLINE);
				if((files[fileIndex][0] | A_STANDOUT | A_UNDERLINE) == (inch()) ){
					attron(A_STANDOUT);
				}
				addstr(files[fileIndex]);
				refresh();
				getyx(curscr, currY, currX);
				move(currY - 1, currX - my_strlen(files[fileIndex - filesPerLine]));
				attron(A_UNDERLINE);
				attroff(A_STANDOUT);
				if((files[fileIndex - filesPerLine][0] | A_STANDOUT) == (inch()) ){
					attron(A_STANDOUT);
				}
				addstr(files[fileIndex - filesPerLine]);
				attroff(A_UNDERLINE);
				attroff(A_STANDOUT);
				move(currY - 1, currX - my_strlen(files[fileIndex - filesPerLine]));
				refresh();
			} else {//wrap down
				int downLines = 0;
				while(fileIndex + (downLines * filesPerLine) < numberOfFiles){
					downLines++;
				}
				downLines--;
				if((files[fileIndex][0] | A_STANDOUT | A_UNDERLINE) == (inch()) ){
					attron(A_STANDOUT);
				}
				attroff(A_UNDERLINE);
				addstr(files[fileIndex]);
				refresh();
				getyx(curscr, currY, currX);
				move(currY + downLines, currX - my_strlen(files[fileIndex + (downLines * filesPerLine)]));
				attron(A_UNDERLINE);
				attroff(A_STANDOUT);
				if((files[fileIndex + (downLines * filesPerLine)][0] | A_STANDOUT) == (inch()) ){
					attron(A_STANDOUT);
				}
				addstr(files[fileIndex + (downLines * filesPerLine)]);
				attroff(A_UNDERLINE);
				move(currY + downLines, currX - my_strlen(files[fileIndex + (downLines * filesPerLine)]))	;
				refresh();
			}
		} else if(c == KEY_DOWN){
			fileIndex = atWhatFile(currX, currY);
			if(fileIndex + filesPerLine < numberOfFiles){ //move down
				attroff(A_UNDERLINE);
				if((files[fileIndex][0] | A_STANDOUT | A_UNDERLINE) == (inch()) ){
					attron(A_STANDOUT);
				}
				addstr(files[fileIndex]);
				refresh();
				getyx(curscr, currY, currX);
				move(currY + 1, currX - my_strlen(files[fileIndex + filesPerLine]));
				attron(A_UNDERLINE);
				attroff(A_STANDOUT);
				if((files[fileIndex + filesPerLine][0] | A_STANDOUT) == (inch()) ){
					attron(A_STANDOUT);
				}
				addstr(files[fileIndex + filesPerLine]);
				attroff(A_UNDERLINE);
				attroff(A_STANDOUT);
				move(currY + 1, currX - my_strlen(files[fileIndex + filesPerLine]));
				refresh();
			} else {//wrap up
				attroff(A_UNDERLINE);
				if((files[fileIndex][0] | A_STANDOUT | A_UNDERLINE) == (inch()) ){
					attron(A_STANDOUT);
				}
				addstr(files[fileIndex]);
				refresh();
				getyx(curscr, currY, currX);
				move(0, currX - my_strlen(files[fileIndex % filesPerLine]));
				attron(A_UNDERLINE);
				attroff(A_STANDOUT);
				if((files[fileIndex % filesPerLine][0] | A_STANDOUT) == (inch()) ){
					attron(A_STANDOUT);
				}
				addstr(files[fileIndex % filesPerLine]);
				attroff(A_UNDERLINE);
				attroff(A_STANDOUT);
				move(0, currX - my_strlen(files[fileIndex % filesPerLine]));
				refresh();
			}
		} else if(c == KEY_LEFT){
			fileIndex = atWhatFile(currX, currY);
			if( (fileIndex % filesPerLine == 0) || (fileIndex == 0) ){
				continue;
			} else {
				attroff(A_UNDERLINE);
				if((files[fileIndex][0] | A_STANDOUT | A_UNDERLINE) == (inch()) ){
					attron(A_STANDOUT);
				}
				addstr(files[fileIndex]);
				attroff(A_STANDOUT);
				currX -= (maxStringLength + 1) - my_strlen(files[fileIndex]);
				move(currY, currX);
				refresh();
				attron(A_UNDERLINE);
				currX -= my_strlen(files[fileIndex - 1]);
				move(currY, currX);
				if((files[fileIndex - 1][0] | A_STANDOUT) == (inch()) ){
					attron(A_STANDOUT);
					refresh();
				}
				addstr(files[fileIndex - 1]);
				attroff(A_STANDOUT);
				move(currY, currX);
				refresh();
			}
		} else if(c == KEY_RIGHT){
			fileIndex = atWhatFile(currX, currY);
			if( (fileIndex % filesPerLine == (filesPerLine - 1) ) || (fileIndex == numberOfFiles - 1) ){//checks if rightmost file or last file
				continue;
			} else {
				attroff(A_UNDERLINE);
				if((files[fileIndex][0] | A_STANDOUT | A_UNDERLINE) == (inch()) ){
					attron(A_STANDOUT);
				}
				addstr(files[fileIndex]);
				currX += my_strlen(files[fileIndex]) + maxStringLength - my_strlen(files[fileIndex + 1]) + 1;
				move(currY, currX);
				attron(A_UNDERLINE);
				attroff(A_STANDOUT);
				if((files[fileIndex + 1][0] | A_STANDOUT) == (inch()) ){
					attron(A_STANDOUT);
				}
				addstr(files[fileIndex + 1]);
				attroff(A_UNDERLINE);
				attroff(A_STANDOUT);
				refresh();
				getyx(curscr, currY, currX);
				currX -= my_strlen(files[fileIndex + 1]);
				move(currY, currX);
				refresh();
			}

		} else if(c == ' '){
			fileIndex = atWhatFile(currX, currY);
			if((files[fileIndex][0] | A_STANDOUT | A_UNDERLINE) == (inch()) ){
					attroff(A_STANDOUT);
					selectedFiles[fileIndex] = 0;
			} else {
				attron(A_STANDOUT);
				selectedFiles[fileIndex] = 1;
			}
			attron(A_UNDERLINE);
			addstr(files[fileIndex]);
			attroff(A_STANDOUT);
			move(currY, currX);
			refresh();
		} else if(c == KEY_RESIZE){
			erase();
			refresh();
			getmaxyx(curscr, maxY, maxX);
			int afterResizeX, afterResizeY;
			filesPerLine = maxX / (maxStringLength + 1);
			if(numberOfFiles >= filesPerLine * (maxY + 1) - 2){
				addstr("Screen is too small");
				refresh();
			}

			while(1){
				refresh();
				getmaxyx(curscr, maxY, maxX);
				filesPerLine = maxX / (maxStringLength + 1);
				if(numberOfFiles >= filesPerLine * (maxY + 1) - 2){
					continue;
				} else {
					erase();
					refresh();
					break;
				}
			}

			move(0, 0);
			getyx(curscr, currX, currY);
			for(int i = 0; i < numberOfFiles; i++){
				attrset(A_NORMAL);
				if(i < (currY + 1) * filesPerLine - 1){
					for(int j = 0; j <= maxStringLength - my_strlen(files[i]); j++){
						addstr(" ");
					}
					if(selectedFiles[i] == 1){
						attron(A_STANDOUT);
					}
					if(i == fileIndex){
						attron(A_UNDERLINE);
						refresh();
						getyx(curscr, afterResizeY, afterResizeX);
						addstr(files[i]);
						attroff(A_UNDERLINE);
					} else {
						addstr(files[i]);
					}
				} else{
					for(int j = 0; j <= maxStringLength - my_strlen(files[i]); j++){
						addstr(" ");
					}
					if(selectedFiles[i] == 1){
						attron(A_STANDOUT);
					}
					addstr(files[i]);
					currY++;
					move(currY, 0);
				}
				refresh();
			}
			move(afterResizeY, afterResizeX);
			refresh();
		} else if(c == KEY_ENTER || c == 10){
			erase();
			refresh();
			endwin();
			for(int i = 0; i < numberOfFiles; i++){
				if(selectedFiles[i] == 1){
					my_str(files[i]);
					my_str(" ");
				}
			}
			exit(0);
		}
	}
	endwin();
}