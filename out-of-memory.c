#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>

#define MILLI_SEC 1000000
#define MAX_THREAD_SIZE 100

static pthread_t threads[MAX_THREAD_SIZE];

void *thread_start(void *arg) {
    pause();
}

int main(int argc, char *argv[]){

    size_t allocate_size = 1 * 1024 * 1024;
    struct timespec spec = {0, 1 * MILLI_SEC};

    if (argc == 2) {
        allocate_size = atoi(argv[1]);
    }

    int malloc_successed = 0;
    for(;;) {
        if(!malloc(allocate_size)) {

            fprintf(stderr, "malloc failed: errno = %d, error = %s\n", errno, strerror(errno));
            sleep(1);

            // Try to pthread_create on out of memory ...
            for( int i = 0; i < MAX_THREAD_SIZE; i++ ) {
                if(pthread_create(&threads[i], NULL, NULL, thread_start)) {
                    fprintf(stderr, "pthread_create failed: errno = %d, error = %s\n", errno, strerror(errno));
                    exit(EXIT_FAILURE);
                }
            }
        }
        printf("[%d] malloc success\n", malloc_successed++);
        nanosleep(&spec, NULL);
    }

    // never reach
    exit(EXIT_SUCCESS);
}
