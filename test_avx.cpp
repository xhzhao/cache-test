#include <stdio.h>
#include <sys/time.h>
#include <mkl.h>
/*This test depends on the avx optimization
O2: foreach time = 33.6439, skip16 time = 25.5270
O3: foreach time = 26.0448, skip16 time = 25.9586

conclusion: AVX instruction will do 16 multiple in parallel
*/

#define WARMUP 1

//get the system time in ms
double get_time(void)
{
#if 0
    struct timeval start;
    gettimeofday(&start,NULL);
    double time = start.tv_sec * 1000 + start.tv_usec /1000;
    return time; 
#else
    double time = dsecnd() * 1000;
    return time;
#endif
}


int main(void)
{
    int len = 64 * 1024 * 1024; // 64*4MB = 256MB, L3 cache is 20M only
    float * a = (float *)malloc(len * sizeof(float));
    float * b = (float *)malloc(len * sizeof(float));
    int i = 0;
    int j = 0;
    //init buffer value, and load to cache
    for (i = 0; i < len; i ++) {
        a[i]=1;
        b[i]=1;
    }
    double t1 = get_time();
    for (i = 0; i < len; i++) {
        a[i] *= 3;
    }
    double t2 = get_time();
    for (j = 0; j < len; j+= 16) {
        b[j]*=3;
    }
    double t3 = get_time();
    //check result
    for (i = 0; i < len; i++) {
        if(a[i] != 3) {
            break;
        }
    }
    for (j = 0; j < len; j+=16) {
        if(b[j] != 3){
            break;
        }
    }
    if (i < len) {
        printf("check failed: a , index = %d\n", i);
    } else if ( j < len) {
        printf("check failed: b , index = %d\n", j);
    } else {
        printf("foreach time = %.4f, skip16 time = %.4f \n", t2-t1, t3-t2 ); 
    }

    return 1;
}
