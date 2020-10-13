#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int ncount;    // �����尣 �����Ǵ� �ڿ� 
pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER; // ������ �ʱ�ȭ 
 // pthread_mutex_t ����ü!
 // pthread_mutex_lock() :  critical section ����! 
void* do_loop(void *data) 
{ 
    int i; 
    for (i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex); // ����� �����Ѵ�. 
        printf("loop1 : %d\n", ncount); 
        ncount ++; 
        pthread_mutex_unlock(&mutex); // ����� �����Ѵ�. 
        sleep(1); 
    } 
} 
 
void* do_loop2(void *data) 
{ 
    int i; 
 
    // ����� �������� ������ do_loop ���� �̹� �����  
    // ��������� ����� �����ɶ����� ��ٸ���.   
    for (i = 0; i < 10; i++) { 
        pthread_mutex_lock(&mutex); // ����� �����Ѵ�. 
        printf("loop2 : %d\n", ncount); 
        ncount++;
        pthread_mutex_unlock(&mutex); // ����� �����Ѵ�.
        sleep(2);
    }
} 
 
int main() 
{ 
    int thr_id; 
    pthread_t p_thread[2]; 
    int status; 
    int a = 1; 
 
    ncount = 0; 
    thr_id = pthread_create(&p_thread[0], NULL, do_loop, (void *)&a); 
    sleep(1); 
    thr_id = pthread_create(&p_thread[1], NULL, do_loop2, (void *)&a); 
 
    pthread_join(p_thread[0], (void *) &status); 
    pthread_join(p_thread[1], (void *) &status); 
 
    status = pthread_mutex_destroy(&mutex); 
    printf("code  =  %d", status); 
    printf("programing is end"); 
    return 0; 
} 


/*
  pthread_mutex_lock() �� pthread_mutex_unlock() ������ 
  critical section �� �ѹ��� �ϳ��� �����常 �����Ҽ� �ְ�, 
  ���� �� critical section => mutex_lock �� ������ �����尡 �����Ҷ����� �ٸ� ������� �����¿� �ִٰ�,
   �ռ� �����尡 critical section �� ������=> mutex_unlock ���������� �����ϰ� �ȴ�.  


*/

