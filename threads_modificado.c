#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <math.h>

// Novo cálculo de CPU-bound: Série de Gregory-Leibniz para Pi
void* cpu_thread(void* arg) {
    printf("Thread CPU-bound %ld iniciada (calculando Pi)\n", (long)arg);
    double pi = 0.0;
    for(long i = 0; i < 200000000; i++) {
        pi += 4.0 * (i % 2 == 0 ? 1 : -1) / (2.0 * i + 1.0);
    }
    printf("Thread CPU-bound %ld terminou (resultado: %f)\n", (long)arg, pi);
    return NULL;
}

void* io_thread(void* arg) {
    printf("Thread I/O-bound %ld iniciada\n", (long)arg);
    sleep(2);
    printf("Thread I/O-bound %ld terminou\n", (long)arg);
    return NULL;
}

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("\nProcesso filho (PID: %d)\n", getpid());
        // Adicionando mais uma thread de cada tipo
        pthread_t thread_cpu1, thread_cpu2, thread_cpu3, thread_io1, thread_io2, thread_io3;

        pthread_create(&thread_cpu1, NULL, cpu_thread, (void*)1);
        pthread_create(&thread_cpu2, NULL, cpu_thread, (void*)2);
        pthread_create(&thread_cpu3, NULL, cpu_thread, (void*)3); // Nova thread CPU

        pthread_create(&thread_io1, NULL, io_thread, (void*)1);
        pthread_create(&thread_io2, NULL, io_thread, (void*)2);
        pthread_create(&thread_io3, NULL, io_thread, (void*)3); // Nova thread I/O

        pthread_join(thread_cpu1, NULL);
        pthread_join(thread_cpu2, NULL);
        pthread_join(thread_cpu3, NULL);
        pthread_join(thread_io1, NULL);
        pthread_join(thread_io2, NULL);
        pthread_join(thread_io3, NULL);
    } else if (pid > 0) {
        printf("Processo pai (PID: %d)\n", getpid());
        wait(NULL);
    }
    return 0;
}
