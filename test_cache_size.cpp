#include <stdio.h>
#include <sys/time.h>
#include <mkl.h>
/*test L1/L2/L3 cache size

array size = 1 KB, time2 = 59.8610 
array size = 2 KB, time2 = 62.9373 
array size = 4 KB, time2 = 65.3366 
array size = 8 KB, time2 = 65.3836 
array size = 16 KB, time2 = 65.2164 
array size = 32 KB, time2 = 68.3513 
array size = 64 KB, time2 = 141.9215 
array size = 128 KB, time2 = 137.1971 
array size = 256 KB, time2 = 131.1001 
array size = 512 KB, time2 = 185.1292 
array size = 1024 KB, time2 = 184.5626 
array size = 2048 KB, time2 = 185.1376 
array size = 4096 KB, time2 = 186.5863 
array size = 8192 KB, time2 = 190.7395 
array size = 16384 KB, time2 = 250.2255 
array size = 32768 KB, time2 = 425.1932 
array size = 65536 KB, time2 = 442.7838 
array size = 131072 KB, time2 = 462.4742 
array size = 262144 KB, time2 = 507.7146 
array size = 524288 KB, time2 = 598.1233 
array size = 1048576 KB, time2 = 807.4850 

conclustion:    L1 cache = 32 KB
                L2 cache = 256 KB
                L3 cache = 16MB ~ 32MB

xhzhao@xhzhao-ub:~/tools/cache/build$ lscpu
Architecture:          x86_64
CPU op-mode(s):        32-bit, 64-bit
Byte Order:            Little Endian
CPU(s):                16
On-line CPU(s) list:   0-15
Thread(s) per core:    2
Core(s) per socket:    8
Socket(s):             1
NUMA node(s):          1
Vendor ID:             GenuineIntel
CPU family:            6
Model:                 63
Model name:            Intel(R) Core(TM) i7-5960X CPU @ 3.00GHz
Stepping:              2
CPU MHz:               1668.164
CPU max MHz:           3500.0000
CPU min MHz:           1200.0000
BogoMIPS:              6000.21
Virtualization:        VT-x
L1d cache:             32K
L1i cache:             32K
L2 cache:              256K
L3 cache:              20480K
NUMA node0 CPU(s):     0-15
Flags:                 fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc aperfmperf eagerfpu pni pclmulqdq dtes64 monitor ds_cpl vmx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid dca sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm epb invpcid_single ibrs ibpb stibp kaiser tpr_shadow vnmi flexpriority ept vpid fsgsbase tsc_adjust bmi1 avx2 smep bmi2 erms invpcid cqm xsaveopt cqm_llc cqm_occup_llc dtherm ida arat pln pts


*/

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
    int i = 0;
    long len = 0;
    // from 1KB to 1GB
    for(len = 1024; len <= 1024*1024*1024; len *= 2){
        //get total float numbers
        int lengthMod = len/4 - 1;

        //hit memory/cache for 64M times
        int steps = 64*1024*1024;

        //buffer size from 1KB to 1GB
        float * a = (float *)malloc(len);
        for(i = 0; i < len/4; i++) {
            a[i] = 1;
        }
        double t1 = get_time();
        //if len = L1 cache = 32KB, hit DRAM(L1 cachemiss) times = 32K/64 = 512, hit L1 cache = 64M - 512 
        //if len = L2 cache = 256KB, hit DRAM(L2 cachemiss) times = 256K/64 = 4096, hit L2 cache = 64M - 4096 
        for(i = 0; i < steps; i ++){
            //new cacheline for every iteration if cachemiss
            a[(i*16)& lengthMod]++;
        }
        double t2 = get_time();
        free(a);
        printf("array size = %ld KB, time2 = %.4f \n",len/1024 , t2-t1); 
    }


    return 1;
}
