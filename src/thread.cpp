#include <pthread.h>
#include <unistd.h>

#include <iostream>

pthread_mutex_t mutex;

void *thread1(void *arg) {
  int a = 0;

  printf("arg: %d\n", reinterpret_cast<int *>(arg));

  while (true) {
    pthread_mutex_lock(&mutex);
    printf("thread:%d a[%d]\n", reinterpret_cast<int *>(arg), ++a);
    pthread_mutex_unlock(&mutex);
    sleep(2);
  }
  return NULL;
}
// 운영체제마다 스레드 스케줄링 다르다. 염두해 두기

int main(int argc, char *argv[]) {
  pthread_t s_thread[2];
  int id = 77;
  int id2 = 88;
  pthread_mutex_init(&mutex, NULL);

  pthread_create(&s_thread[0], NULL, thread1, &id);
  pthread_create(&s_thread[1], NULL, thread1, &id2);
  while (true) {
    printf("main loop\n");
    sleep(1);
  }

  // pthread_join(s_thread[0], NULL);
  // pthread_join(s_thread[1], NULL);
  // 다른스레드가 끝날때까지 기다렸다가 그스레드가 리턴한값을 받아오는 역할
}
