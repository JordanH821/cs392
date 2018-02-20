#include "my.h"
void my_int(int i){
    i = (long)i;
    if(i == 0){
        my_char('0');
    }
    if(i < 0){
        if(i == -2147483648){
            my_str("-2147483648");
            return;
        }
        my_char('-');
        i = -i;
    }
    long j = i;
    long length = 1;
    while(i != 0){
        i/=10;
        length *= 10;
    }
    length/=10;
    while(length != 0){
        long dig = j / length;
        my_char(dig + '0');
        j -= dig * length;
        length /= 10;
    }
}