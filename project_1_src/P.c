#define MAX 5000
#include <stdio.h>
int main(){
	char input[MAX];
	scanf("%[^\n]s", input);
	printf("%s\n", input);
}
