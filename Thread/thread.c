#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int matriz[3][3];
int result = 0;
pthread_mutex_t mutex;

void *filho1(void *arg) {
    printf("\nFilho1:Calculando...\n");
    int result1 = matriz[0][0] * matriz[1][1] * matriz[2][2] +
                  matriz[0][1] * matriz[1][2] * matriz[2][0] +
                  matriz[0][2] * matriz[1][0] * matriz[2][1];

    pthread_mutex_lock(&mutex);
    result += result1;
    pthread_mutex_unlock(&mutex);
    printf("Resultado do filho1: %d\n",result1);
    printf("Filho1:saindo...\n");
}

void *filho2(void *arg) {
    printf("\nFilho2:Calculando...\n");
    int result2 = (matriz[0][2] * matriz[1][1] * matriz[2][0] +
                   matriz[0][0] * matriz[1][2] * matriz[2][1] +
                   matriz[0][1] * matriz[1][0] * matriz[2][2]) * -1;

    pthread_mutex_lock(&mutex);
    result += result2;
    pthread_mutex_unlock(&mutex);
    printf("Resultado do filho2: %d\n",result2);
    printf("Filho2:saindo...\n");
}

int main(int argc, char *argv[]) {
    FILE *file = fopen("matriz.txt", "r");
    char line[20];
    fgets(line, sizeof(line), file);
    char *token = strtok(line, " ");
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matriz[i][j] = atoi(token);
            token = strtok(NULL, " ");
        }
    }

    fclose(file);
    printf("matriz: ");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ",matriz[i][j]);
        }
        printf("\n\t");
    }

    pthread_t thread_id[2];
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&thread_id[0], NULL, filho1, NULL);
    pthread_create(&thread_id[1], NULL, filho2, NULL);

    pthread_join(thread_id[0], NULL);
    pthread_join(thread_id[1], NULL);

    printf("\nO determinante da matriz eh: %d\n", result);

    pthread_mutex_destroy(&mutex);

    return 0;
}
