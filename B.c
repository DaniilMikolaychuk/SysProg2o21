#include <stdio.h>
#include <string.h>

int main(){
	FILE *file = fopen("A.txt", "r");
	char string[1024];
	fgets(string, 1024, file);
	int i, j, a = 0;
	for(i = 0; i < strlen(string) - 1; i++){
		if(i > 0 && string[i] != string[i-1]) {
            printf("%c :", string[i]);
            for (j = 0; j < strlen(string) - 1; j++) {
                if (string[i] == string[j]) {
                    a++;
                }
            }
            printf("%d\n", a);
            a = 0;
        } else {
            continue;
        }
	}
	return 0;
}
