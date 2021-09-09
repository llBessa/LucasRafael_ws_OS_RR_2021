#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define maxSize 60000000

int size;
int *buffer;

pthread_mutex_t mutex;

typedef struct {
    int number;
    int thread;
    int totalThreads;
}args;						// variaveis passadas na funcao das threads

// Assinaturas das funcoes

// multiplica cada numero de fatorial pelo produto algarismo por algarismo
void multiply(int fatNum);

void* threadCalc(void* args);

//calcula o fatorial de um numero passado por parametro
void factorial(int number, pthread_t *thread, int numT);

// implementacoes

// multiplica os valores de 2 ate number pelos algarismos do buffer
void* threadCalc(void* param){
    args *info = (args*) param; 
    int start = 1 + (info->thread*1000);		// define o valor inicial do loop de acordo com a thread
    int end = (info->thread + 1)*1000;			// define o valor final do loop de acordo com a thread
    if(info->number%1000 != 0 && (info->thread == info->totalThreads - 1)) end = start - 1 + info->number%1000;
    
    printf("inicializando thread %d | calculo de %d a %d\n", info->thread, start, end);
    
    pthread_mutex_lock(&mutex);					// impede as outras threads de entrarem na regiao critica
    for(int i = start; i <= end; i++){
        multiply(i);							
    }
    pthread_mutex_unlock(&mutex);				// libera o acesso a regiao critica
}

void factorial(int number, pthread_t *thread, int numT){
    buffer = (int*)malloc(maxSize*sizeof(int));             // define o tamanho do buffer
    size = 1;                                               // inicializa o tamanho do buffer
    buffer[0] = 1;                                          // inicializa o valor do fatorial com 1

    int i;      //define um contador

    pthread_mutex_init(&mutex, NULL);

    args parametros[numT];

    for(int i = 0; i < numT; i++){
    	printf("Thread %d\n",i);
        parametros[i].thread = i;
        parametros[i].number = number;
    	parametros[i].totalThreads = numT;
        pthread_create(&thread[i], NULL, threadCalc,(void*) &parametros[i]);
    }

    for (int i = 0; i < numT; i++){
        pthread_join(thread[i], NULL);
    }

    // exibe o valor final do fatorial na tela
    printf("O fatorial de %d e igual a :\n", number);
    for(i = size - 1; i >= 0; i--){
        printf("%d", buffer[i]);
    }
    printf("\n\n");   //pula linha
    free(buffer);
}

void multiply(int fatNum){
    int carry = 0;      // numero que e carregado para outras casas do numero final

    // multiplica o numero passado, algorismo por algorismo
    for(int i = 0; i < size; i++){
        // multiplica o algarismo do buffer[i] pelo valor passado e soma com o carry
        int prod = buffer[i]*fatNum + carry;

        // troca o valor do buffer[i] pelo resto da divisao do produto anterior por 10
        buffer[i] = prod%10;

        // define o valor do carry como o quociente a divisao inteira de prod por 10
        carry = prod/10;
    }

    while(carry){					// caso ainda exista valor em carry, este sera distribuido no produto final do vetor
        buffer[size] = carry%10;
        carry /= 10;
        size++;
    }
}

int main(){
    int fat;

    printf("Fatorial de : ");
    scanf("%d", &fat);              // escreve na variavel fat o valor de fatorial a ser calculado

    if(fat < 0) return 0;           // encerra o programa caso seja dado um valor invalido para calcular

    int numThreads = fat/1000;      // define o numero de threads que serao utilizadas
    if(fat%1000 != 0) numThreads++;
    printf("Threads a serem executadas : %d\n",numThreads);

    pthread_t thread[numThreads];

    factorial(fat, thread, numThreads);

    printf("O fatorial de %d possui %d algarismos\n", fat, size);
    return 0;
}
