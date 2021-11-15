#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){
	char string[1024], t;
	int i, j = 0, k;
	FILE *A = fopen("A.txt", "w");
    printf("Enter:\n");
    gets (string);
    char *string2 = (char*) malloc (strlen(string) - 1);
    string = tolower(string);
	for(i = 0; i < strlen(string); i++){
		if (string[i] >= 'a' && string[i] <= 'z'){
            string2[j] = string[i];
			j++;
		} else{
			i++;
		}
	}
	for(i = 0; i < strlen(string2) - 1; i++){
		for(k = 0; k < strlen(string2) - i - 1; k++){
			if(string2[k] > string2[k + 1]){
				t = string2[k];
                string2[k] = string2[k + 1];
                string2[k  + 1] = t;
			}
		}
	}
	fprintf(A, "%s", string2);
	fclose(A);
	free(str);
	return 0;
}
