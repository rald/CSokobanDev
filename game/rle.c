#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
	int ch0,ch1,count;
	while(true) {
		ch0=getchar();
		if(ch0==EOF) { 
			return 0;
		} else if(ch0=='\n') { 
			putchar('|'); 
			continue; 
		}
		while(true) {
			count=1;
			ch1=getchar();
			if(ch1==EOF) { 
				putchar(ch0);
				return 0;
			} else if(ch1=='\n') {
				putchar(ch0);
				putchar('|');
				break;
			}
			while(ch0==ch1) {
				count++;
				ch1=getchar();		
			}
			if(count>=2) {
				printf("%d%c",count,ch0);
			} else {
				if(ch0=='\n') {
					putchar('|');
				} else {
					putchar(ch0);
				}
			}
			ch0=ch1;
		}
	}
	return 0;
}
