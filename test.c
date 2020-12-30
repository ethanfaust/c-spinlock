#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>

pthread_t thread1;
pthread_t thread2;
typedef uint32_t lock_t;
lock_t writeLock;

#define LOCKED 1
#define UNLOCKED 0

void spin_lock(lock_t *lock) {
  while (!__sync_bool_compare_and_swap(lock, UNLOCKED, LOCKED)) {
    // spin
  }
}
void spin_unlock(lock_t *lock) {
  *lock = UNLOCKED;
}


void* thread_func(void *arg) {
  while (true) {
    spin_lock(&writeLock);
    printf("%s", (char*)arg);
    spin_unlock(&writeLock);
  }
  return NULL;
}

int main(int argc, char **argv) {
  char *arg1 = "abc";
  char *arg2 = "def";
  pthread_create(&thread1, NULL, thread_func, arg1);
  pthread_create(&thread2, NULL, thread_func, arg2);
  pthread_join(thread1, NULL);
}
