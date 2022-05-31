#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// #include <semaphore.h>

int flag = 0;
int row = 0;
int m;
int n;
int thread_count;
int A[100][100];
int B[100];
int C[100];
pthread_mutex_t lock;

void* task(void* rank);
int main()
{
    printf("Thread count ");
    long thread;
    pthread_t* thread_handles;

    // thread_count = strtol(argv[1],NULL,10);
    scanf("%d",&thread_count);
    // printf("Thread count %d",thread_count);
    thread_handles = malloc(thread_count*(sizeof(pthread_t)));
    scanf("%d",&m);
    scanf("%d",&n);

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&A[i][j]);
        }
    }

    for(int i=0;i<n;i++){
        scanf("%d",&B[i]);
    }
    // printf("%d",B[n-1]);
    pthread_mutex_init(&lock,NULL);
    for(thread =0;thread < thread_count;thread++){
        pthread_create(&thread_handles[thread],NULL,task,(void*)thread);
    }

    for(thread=0;thread<thread_count;thread++){
        pthread_join(thread_handles[thread],NULL);
    }

    for(int i=0;i<m;i++){
        printf("%d\n",C[i]);
    }

}

void* task(void* rank){
    long my_rank = (long) rank;
    int local_m = m/thread_count;
    int my_first_row = local_m*my_rank;
    int my_last_row = (local_m)*(my_rank+1) - 1;

    // for(int i=my_first_row;i<=my_last_row;i++){
    //     C[i] = 0;
    //     for(int j=0;j<n;j++){
    //         C[i] += A[i][j]*B[j];
    //     }
    // }
    while(row<m){
    while (my_rank !=flag);
    
    
    // int curr ;
    // while(row<m){
    //     // pthread_mutex_lock(&lock);
        printf("rank = %ld\n",my_rank);
    //     curr = row;
    //     row++;
    //     // pthread_mutex_unlock(&lock);
        // C[curr] = 0;
        //  for(int j=0;j<n;j++){
        //     C[curr] += A[curr][j]*B[j];
        // }
    // }
    C[row] = 0;
    for(int j=0;j<n;j++){
            C[row] += A[row][j]*B[j];
    }
    row++;

    flag = (flag+1)%(thread_count);
    }

    return NULL; 

}