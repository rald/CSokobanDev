#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int look;

void next() {
	look=getchar();
}

int getnum() {
	char str[4];
	str[0]='\0';
	while(isdigit(look)) {
		char tmp[]={look,'\0'};
		strcat(str,tmp);
		next();
	}
	return atoi(str);
}

int main() {
	int count;
	
	next();
	while(look!=EOF) {
		count=1;
		if(isdigit(look)) {
			count=getnum();
		}
		while(count--) {
			if(look=='|') {
				putchar('\n');
			} else {
				putchar(look);
			}
		}
		next();
	}
}