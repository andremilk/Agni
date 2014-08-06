#include <stdio.h>
#include <omp.h>
#include <sys/time.h>
#include "getter.c"

int main(int argc, char **argv)
{
    if(argc < 3) {
        printf("Usage: agni target no_of_requests\n");
        return 0;
    }
    int i;
        
    char *target = argv[1];
    long no_of_reqs = atol(argv[2]);
    long s2xx = 0;
    long s3xx = 0;
    long s4xx = 0;
    long s5xx = 0;
    time_t start = time(NULL);
    #pragma omp parallel shared(s2xx, s3xx, s4xx, s5xx, i) num_threads(100)
    {
        #pragma omp for
            for (i = 0; i < no_of_reqs; i++) {
                int x;
                 x = (int) do_web_request(target);
                 if(x/100 == 3)
                     s3xx++;
                 else if(x/100 == 2)
                     s2xx++;
                 else if(x/100 == 4)
                     s4xx++;
                 else 
                     s5xx++;
            }
    }
    printf("\n 2xx = %ld\n", s2xx);
    printf("\n 3xx = %ld", s3xx);
    printf("\n 4xx = %ld", s4xx);
    printf("\n 5xx = %ld", s5xx);
    printf("\n time elapsed = %.2f\n", (double)time(NULL) - start);
}

