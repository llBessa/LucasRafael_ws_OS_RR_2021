#include <stdio.h>
#include <stdlib.h>

#define maxSize 100000000

// Assinaturas das funções
// multiplica cada numero de fatorial pelo produto algarismo por algarismo
int multiply(int fatNum, int buffer[], int size);
//calcula o fatorial de um numero passado por parametro
int factorial(int number);

// implementações

int factorial(int number){
    int *buffer = (int*)malloc(maxSize*sizeof(int));        // define o tamanho do buffer
    int size = 1;                                           // inicializa o tamanho do buffer
    buffer[0] = 1;                                          // inicializa o valor do fatorial com 1

    int i;      //define um contador

    // multiplica os valores de 2 ate number e retorna o novo tamanho do buffer
    for(i = 2; i <= number; i++){
        size = multiply(i, buffer, size);
    }

    // exibe o valor final do fatorial na tela
    for(i = size - 1; i >= 0; i--){
        printf("%d", buffer[i]);
    }
    printf("\n\n");     //pula linha
    free(buffer);       //libera a memoria do buffer
    return size;
}

int multiply(int fatNum, int buffer[], int size){
    int carry = 0;      // numero que e carregado para outras casas do numero final

    // multiplica o numero passado, algorismo por algorismo
    for(int i = 0; i < size; i++){
        // multiplica o algarismo do buffer[i] pelo valor passado e soma com o carry
        int prod = buffer[i]*fatNum + carry;

        // troca o valor do buffer[i] pelo resto da divisáo do produto anterior por 10
        buffer[i] = prod%10;

        // define o valor do carry como o quociente a divisão inteira de prod por 10
        carry = prod/10;
    }
    
    while(carry){
        buffer[size] = carry%10;
        carry /= 10;                // carry = carry/10
        size++;
    }
    return size;
}

int main(){
    int fat, size;

    while(1){
        printf("Fatorial de : ");
        scanf("%d", &fat);
        if(fat < 0) break;
        printf("O fatorial de %d e igual a :\n", fat);
        size = factorial(fat);
        printf("O fatorial de %d possui %d algarismos\n", fat, size);
    }
    return 0;
}