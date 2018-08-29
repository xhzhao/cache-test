#include <stdio.h>
#include <sys/time.h>
#include <mkl.h>
/*This test depends on the avx optimization
STACK = 1
    stack, stride = 1, time = 29.4080 
    stack, stride = 2, time = 31.6226 
    stack, stride = 4, time = 31.1303 
    stack, stride = 8, time = 30.6847 
    stack, stride = 16, time = 31.2129 
    stack, stride = 32, time = 22.2457 
    stack, stride = 64, time = 13.3314 
    stack, stride = 128, time = 5.8636 
    stack, stride = 256, time = 2.9014 
    stack, stride = 512, time = 1.6758 
    stack, stride = 1024, time = 1.1264 

    conclusion: cacheline size = 16 * 4 = 64 byte


STACK = 0
    nonstack, stride = 1, time = 36.4998
    nonstack, stride = 2, time = 28.4608
    nonstack, stride = 4, time = 26.8833
    nonstack, stride = 8, time = 28.8979
    nonstack, stride = 16, time = 26.4360
    nonstack, stride = 32, time = 19.2076
    nonstack, stride = 64, time = 12.7136
    nonstack, stride = 128, time = 5.4694
    nonstack, stride = 256, time = 2.6909
    nonstack, stride = 512, time = 1.4637
    nonstack, stride = 1024, time = 0.9121

*/

#define STACK 1

//get the system time in ms
double get_time(void)
{
/*
    struct timeval start;
    gettimeofday(&start,NULL);
    double time = start.tv_sec * 1000 + start.tv_usec /1000;
    return time; 
*/
    double time = dsecnd() * 1000;
    return time;

}


int main(void)
{
    int len = 64 * 1024 * 1024; // 64*4MB = 256MB, L3 cache is 20M only
    float * a = (float *)malloc(len * sizeof(float));
    float * b = (float *)malloc(len * sizeof(float));
    int i = 0;
    int j = 0;
    int k = 0;
    double t1,t2;
#if STACK
    //load a to cache
    for(i = 0; i < len; i ++){
        a[i]=1;
        b[i]=1;
    }
    t1 = get_time();
    for(i = 0; i < len; i ++){
        a[i]*=3;
    }
    t2 = get_time();
    printf("stack, stride = 1, time = %.4f \n", t2-t1 ); 
    t1 = get_time();
    for(i = 0; i < len; i +=2){
        a[i]*=3;
    }
    t2 = get_time();
    printf("stack, stride = 2, time = %.4f \n", t2-t1 ); 
    t1 = get_time();
    for(i = 0; i < len; i += 4){
        a[i]*=3;
    }
    t2 = get_time();
    printf("stack, stride = 4, time = %.4f \n", t2-t1 ); 
    t1 = get_time();
    for(i = 0; i < len; i += 8){
        a[i]*=3;
    }
    t2 = get_time();
    printf("stack, stride = 8, time = %.4f \n", t2-t1 ); 
    t1 = get_time();
    for(i = 0; i < len; i +=16){
        a[i]*=3;
    }
    t2 = get_time();
    printf("stack, stride = 16, time = %.4f \n", t2-t1 ); 
    t1 = get_time();
    for(i = 0; i < len; i +=32){
        a[i]*=3;
    }
    t2 = get_time();
    printf("stack, stride = 32, time = %.4f \n", t2-t1 ); 
    t1 = get_time();
    for(i = 0; i < len; i +=64){
        a[i]*=3;
    }
    t2 = get_time();
    printf("stack, stride = 64, time = %.4f \n", t2-t1 ); 
    t1 = get_time();
    for(i = 0; i < len; i +=128){
        a[i]*=3;
    }
    t2 = get_time();
    printf("stack, stride = 128, time = %.4f \n", t2-t1 ); 
    t1 = get_time();
    for(i = 0; i < len; i +=256){
        a[i]*=3;
    }
    t2 = get_time();
    printf("stack, stride = 256, time = %.4f \n", t2-t1 ); 
    t1 = get_time();
    for(i = 0; i < len; i +=512){
        a[i]*=3;
    }
    t2 = get_time();
    printf("stack, stride = 512, time = %.4f \n", t2-t1 ); 
    t1 = get_time();
    for(i = 0; i < len; i += 1024){
        a[i]*=3;
    }
    t2 = get_time();
    printf("stack, stride = 1024, time = %.4f \n", t2-t1 ); 

#else

    for(i = 0; i < len; i++){
        a[i] = 1;
    }
    for(k = 1; k <= 1024; k*=2){
        t1 = get_time();
        for(i = 0; i < len; i += k){
            a[i]*=3;
        }
        t2 = get_time();
        printf("nonstack, stride = %d, time = %.4f\n", k, t2-t1 );
    }


#endif

    return 1;
}
