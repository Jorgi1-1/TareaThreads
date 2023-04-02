#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREADS_NO 10

void* print_hello_world(void* args)
{
    int* thread_num = (int*)args;
    if (*thread_num % 2 == 0) 
    {
        printf("Hola, soy un hilo par con identificador %d.\n", *thread_num);
    } 
    else 
    {
        printf("Hola, soy un hilo impar con identificador %d.\n", *thread_num);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[THREADS_NO];
    int state, i;
    int thread_num[THREADS_NO];

    for (i = 0; i < THREADS_NO; i++) 
    {
        thread_num[i] = i;
        state = pthread_create(&threads[i], NULL, print_hello_world, &thread_num[i]);
        printf("Main creo un hilo en la iteración %d.\n", i);

        if (state != 0) 
        {
            perror("pthread_create() error.");
            exit(-1);
        }
    }

    for (i = 0; i < THREADS_NO; i++) 
    {
        pthread_join(threads[i], NULL);
    }

    exit(0);
}
