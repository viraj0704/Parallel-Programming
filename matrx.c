#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// #include <semaphore.h>

int flag = 0;
int row = 0;

int n;
int thread_count;
int A[10001];
int C[10001][10001];
pthread_mutex_t lock;
int value = 0;

void* task(void* rank);
int res(int,int);
int main()
{
    //printf("Thread count ");
    long thread;
    pthread_t* thread_handles;
    value = 0;
    row = 0;
    flag = 0;
    
    // thread_count = strtol(argv[1],NULL,10);
    scanf("%d",&thread_count);
    // printf("Thread count %d",thread_count);
    thread_handles = malloc(thread_count*(sizeof(pthread_t)));
    // scanf("%d",&m);
    scanf("%d",&n);

    
    for(int j=0;j<n;j++){
        scanf("%d",&A[j]);
    }
    

    
    // printf("%d",B[n-1]);
    pthread_mutex_init(&lock,NULL);
    for(thread =0;thread < thread_count;thread++){
        pthread_create(&thread_handles[thread],NULL,task,(void*)thread);
    }

    for(thread=0;thread<thread_count;thread++){
        pthread_join(thread_handles[thread],NULL);
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
        printf("%d ",C[i][j]);
        }
        printf("\n");
    }

    free(thread_handles);

}

void* task(void* rank){
    long my_rank = (long) rank;
    
    // for(int i=my_first_row;i<=my_last_row;i++){
    //     C[i] = 0;
    //     for(int j=0;j<n;j++){
    //         C[i] += A[i][j]*B[j];
    //     }
    // }
    while(row < n){
        int curr;
        int j;
        pthread_mutex_lock(&lock);
        curr = row;
        row++;
        pthread_mutex_unlock(&lock);
        printf("curr = %d \n",curr);
        for(j=curr;j<n;j++){
            C[curr][j] = res(curr,j);
            C[j][curr] = res(curr,j);
        }
    }

    return NULL; 

}

int res(int i,int j){
    return A[i] + A[j];
}