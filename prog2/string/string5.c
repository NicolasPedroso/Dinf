#include <stdio.h>
int main(){
    char string[101];
    printf("Digite uma string: ");
    scanf("%[A-Za-z0-9]", string);
    printf("A string digitada foi: %s",string);
return 0;
}