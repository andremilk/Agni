#include <stdio.h>
#include <omp.h>
#include "getter.c"
/*#include <curl/curl.h>
#include <curl/easy.h>
#include <string.h>
*/
int main(int argc, char **argv)
{
    if(argc < 5) {
        printf("Usage: agni target no_of_requests rate threads\n");
        return 0;
    }
    int i, thread_id, nloops;
        
    char *target = argv[1];
    long no_of_reqs = atol(argv[2]);
    long reqs_per_sec = atol(argv[3]);
    int _threads = atol(argv[4]);
    
    #pragma omp parallel private(thread_id, nloops)
    {
        nloops = 0;
        #pragma omp for
            for (i = 0; i < no_of_reqs; i++) {
                do_web_request(target);
                ++nloops;
            }

        thread_id = omp_get_thread_num();
        printf("Thread %d performed %d interations of the loop.\n",
               thread_id, nloops);
    }
        printf("%s\n", target);
        printf("%ld\n", no_of_reqs);
        printf("%ld\n", reqs_per_sec);
        printf("%d\n", _threads);
}

