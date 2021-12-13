#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>


pthread_mutex_t mutex_ab; 
pthread_mutex_t mutex_bc;
pthread_mutex_t mutex_cd;
pthread_mutex_t mutex_bf;
pthread_mutex_t mutex_ce;
sem_t ab;
sem_t bc;
sem_t cd;
sem_t bf;
sem_t ce;
// Temps necessaire pour occuper un segment 
void delay_time()
{
    int milli_seconds = 1000 * 5;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

// La ligne de metro MR1 (A -> B -> C -> D)
void* ligneMR1(void* arg) {

    int pid=*((int*)arg);

    sem_wait(&ab);
    // pthread_mutex_lock(&mutex_ab);
    printf("le metro %d de la ligne MR1 traverse AB\n",pid);
     delay_time();
    printf("AB est maintenant disponible\n");
    // pthread_mutex_unlock(&mutex_ab);
    sem_post(&ab);

    pthread_mutex_lock(&mutex_bc);
    printf("Métro %d de la ligne MR1 traverse BC\n",pid);
    delay_time();
    printf("BC est maintenant disponible\n");
    pthread_mutex_unlock(&mutex_bc);

    pthread_mutex_lock(&mutex_cd);
    printf("le metro %d de la ligne MR1 traverse CD\n",pid);
    delay_time();
    printf("CD est maintenant disponible\n");
    pthread_mutex_unlock(&mutex_cd);

    printf("le metro %d de la ligne MR1 est arrive a D!\n",pid);

    pthread_exit(NULL);
}

// La ligne de metro MR2 (F -> B -> A)
void* ligneMR2(void* arg) {

    int pid=*((int*)arg);

    pthread_mutex_lock(&mutex_bf);
    printf("le metro %d de la ligne MR3 traverse FB\n",pid);
    delay_time();
    printf("BF est maintenant disponible\n");
    pthread_mutex_unlock(&mutex_bf);

    sem_wait(&ab);
    // pthread_mutex_lock(&mutex_ab);
    printf("le metro %d de la ligne MR3 traverse BA\n",pid);
    delay_time();
    printf("AB est maintenant disponible\n");
    // pthread_mutex_unlock(&mutex_ab);
    sem_post(&ab);

    printf("le metro %d de la ligne MR3 est arrive a A !\n",pid);

    pthread_exit(NULL);
}

// La ligne de metro MR3 (E -> C -> B)
void* ligneMR3(void* arg) {

    int pid=*((int*)arg);

    pthread_mutex_lock(&mutex_ce);
    printf("le metro %d de la ligne MR2 traverse EC\n",pid);
    delay_time();
    printf("CE est maintenant disponible\n");
    pthread_mutex_unlock(&mutex_ce);

    pthread_mutex_lock(&mutex_bc);
    printf("le metro %d de la ligne MR2 traverse CB\n",pid);
    delay_time();
    printf("BC est maintenant disponible\n");
    pthread_mutex_unlock(&mutex_bc);

    printf("le metro %d de la ligne MR2 est arrive a B !\n",pid);

    pthread_exit(NULL);
}

int main()
{
   
    pthread_t id;

        int* j=(int*)malloc(sizeof(int));
        *j=0;
        pthread_create(&id,NULL,ligneMR1,j);
        pthread_create(&id,NULL,ligneMR2,j);
        pthread_create(&id,NULL,ligneMR3,j);
    
    pthread_exit(NULL);
}