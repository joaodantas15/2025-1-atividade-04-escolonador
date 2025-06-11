#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <math.h>

void* cpu_thread(void* arg) {
    printf("Thread CPU-bound %ld iniciada\n", (long)arg);
    double sum = 0;
    for(int i = 0; i < 10000000; i++) {
        sum += pow(1.0, i) / tgamma(i+1);
    }
    printf("Thread CPU-bound %ld terminou (resultado: %f)\n", (long)arg, sum);
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
        pthread_t thread_cpu1, thread_cpu2, thread_io1, thread_io2;
        pthread_create(&thread_cpu1, NULL, cpu_thread, (void*)1);
        pthread_create(&thread_cpu2, NULL, cpu_thread, (void*)2);
        pthread_create(&thread_io1, NULL, io_thread, (void*)1);
        pthread_create(&thread_io2, NULL, io_thread, (void*)2);
        pthread_join(thread_cpu1, NULL);
        pthread_join(thread_cpu2, NULL);
        pthread_join(thread_io1, NULL);
        pthread_join(thread_io2, NULL);
    } else if (pid > 0) {
        printf("Processo pai (PID: %d)\n", getpid());
        wait(NULL);
    }
    return 0;
}
