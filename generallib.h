#define SSLIBVER 0001
#ifndef GENERALLIB
#define GENERALLIB

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <math.h>
#include <ctype.h>

#pragma once

static int getch(){
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    return ch;
}

void revStr(char *str) {
    int i = 0;
    int lenfounded;
    while(str [i] != '\0'){
        lenfounded++;
	i++;
    }
    i = 0;

    int j = lenfounded;

    while (i < j) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;

        i++;
        j--;
    }
}

static int chStrInt(const char *str){
    int result = 0;
    int sign = 1;
    int i = 0;
    while (!(str [i] == '0' || str [i] == '1' || str [i] == '2' || str [i] == '3' || str [i] == '4' || str [i] == '5' || str [i] == '6' || str [i] == '7' || str [i] == '8' || str [i] == '9' || str [i] == '-' || str [i] == '+')){
        i++;
    }
    if (str [i] == '-'){
        sign = -1;
	i++;
    } else if (str [i] == '+' ){
        i++;
    }

    while (str [i] != '\0' && isdigit(str [i])){
	result = result * 10 + (str [i] - '0');
	i++;
    }

    return result * sign;
}

static void chIntStr(const int *ycc, const char *str){
    int sign = 1;
    char returned[64];
    int i = 0;
    int k = 0;
    int keepf;
    int k_int = *ycc;
    if(*ycc < 0){
        sign = -1;
	k_int = *ycc * sign;
    }

    while (k_int >= 10){
        keepf = k_int % 10;
	returned [i] = keepf + '0';
        k_int -= keepf;
	k_int /= 10;
	i++;
    }

    keepf = k_int % 10;
    returned [i] = keepf + '0';
    
    i++;

    if (sign < 0){
        returned [i] = '-';
    }
    
    revStr(str);

}

#endif
