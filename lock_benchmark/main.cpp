#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <getopt.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>

struct stOptions {
   uint32_t max;
};
typedef void(*func)(uint32_t max, const std::string& desc);

struct stRunner {
    func entry;
    std::string name;
};

uint32_t g_base_time;

#define MAX_LOCK_TYPE 10
#define END_BENCHMARK(max, desc) \
        do { \
            uint32_t cost = st_count.End(); \
            printf("%s: count:%u cost-total: %u cost-per(ns):%u\n", desc.c_str(), max, cost ,(cost - g_base_time) / max); \
        } while(0)

#define CREATE_NEW_TEST(func_table, index, callback, desc) \
        do { \
            if(index >= MAX_LOCK_TYPE) { \
                printf("index too large,check MAX_LOCK_TYPE\n"); \
            } \
            struct stRunner runner = {callback, desc}; \
            func_table[index] =  runner; \
        } while(0)



void useage(char* proc) {
    fprintf(stdout, "usage:%s\n\t -c max \n\t -h|H|? for help\n", proc) ;
    exit(0);
}

class stTimeCount {
public:
    stTimeCount() { Start();}
    void Start() {
        clock_gettime(CLOCK_MONOTONIC,&tp_start_);
    }
    uint32_t End() {
        timespec tp_end_;
        clock_gettime(CLOCK_MONOTONIC,&tp_end_);
        uint32_t cost = (tp_end_.tv_sec - tp_start_.tv_sec )*1000000000 + (tp_end_.tv_nsec - tp_start_.tv_nsec);
    }
private:
    timespec tp_start_;
};

void mutex_benchmark(uint32_t max,const std::string &desc)
{
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    stTimeCount st_count;
    for(uint32_t i = 0; i < max;i++) {
       pthread_mutex_lock(&mutex);
       pthread_mutex_unlock(&mutex);
    }
    END_BENCHMARK(max, desc);
}

void rwlock_benchmark(uint32_t max, const std::string &desc)
{
    pthread_rwlock_t lock= PTHREAD_RWLOCK_INITIALIZER;
    stTimeCount st_count;

    for(uint32_t i = 0; i < max;i++) {
       pthread_rwlock_rdlock(&lock);
       pthread_rwlock_unlock(&lock);
    }
    END_BENCHMARK(max, desc);
}

void spinlock_benchmark(uint32_t max, const std::string &desc) {
    pthread_spinlock_t lock;
    pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE);
    stTimeCount st_count;
    for(uint32_t i =0; i < max; i++) {
        pthread_spin_lock(&lock);
        pthread_spin_unlock(&lock);
    }
    END_BENCHMARK(max, desc);
    pthread_spin_destroy(&lock);
}

void base(uint32_t max, const std::string &desc) {
    stTimeCount st_count;
    for(uint32_t i = 0; i < max;i++) {
    }
    uint32_t cost = st_count.End();
    g_base_time = cost / max;
    END_BENCHMARK(max, desc);
}


int main(int argc,char* argv[]) {
    char ch;
    struct stOptions options;
    if(argc < 2) {
       useage(argv[0]) ;
    }
    while((ch = getopt(argc, argv, "c:hH?")) != -1) {
        switch(ch) {
            case 'c':
            {
                options.max = atoi(optarg);
                break;
            }
            case 'h': /* falls through */
            case 'H':
            case '?':
            {
                useage(argv[0]);
                break;
            }
            default:
                useage(argv[0]);
                break;
        }
    }
    struct stRunner lock_types[MAX_LOCK_TYPE];
    int index  = 0;
    CREATE_NEW_TEST(lock_types, index++, base, "base for");
    CREATE_NEW_TEST(lock_types, index++, mutex_benchmark, "mutex");
    CREATE_NEW_TEST(lock_types, index++, rwlock_benchmark, "rwlock");
    CREATE_NEW_TEST(lock_types, index++, spinlock_benchmark, "spinlock");

    for(int i = 1;i <= index; i++) {
        if(lock_types[i].entry != NULL)
            lock_types[i].entry(options.max,lock_types[i].name);
    }
    return 0;
}