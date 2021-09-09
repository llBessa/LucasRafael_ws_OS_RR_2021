#include <stdio.h>
#include <math.h>
#include <string.h>
// #include <openssl/bn.h>
// #include <pthread.h>

typedef double lf;

lf produto;

lf fatorial(lf number, lf product){
    if(number == 0) return product;
    else{
        return fatorial(number - 1, number*product);
    }
}

int countBase10(char *number){
    int i = 0;
    while(number[i + 1] != '\0'){
        i++;
    }
    return i;
}

lf calculeFactorial(lf number){
    int divisions = (int) number/100;
    fatorial(number, 1);
}

int main(){
    lf number;
    char array[1000000];
    while(1){
        printf("Fatorial de : ");
        scanf("%lf", &number);
        if(number < 0) break;
        sprintf(array, "%.0lf", fatorial(number, 1));
        printf("\nO fatorial de %.0lf e igual a %s e possui %d 0s\n",number,array, countBase10(array));
    }
    return 0;
}
