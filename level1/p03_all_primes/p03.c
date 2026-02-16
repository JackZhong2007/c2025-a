#include<stdio.h>
#include<windows.h>
int justice(int Number,int previous_prime_number[],int number){
    int whether=1;
    for(int i=0;i<number;i++){
        if(Number%previous_prime_number[i]==0){
            whether=0;
        }
    }
    return whether;
}
int main(){
    LARGE_INTEGER time_start;
    LARGE_INTEGER time_over;
    LARGE_INTEGER frequency;
    QueryPerformanceCounter(&time_start);
    QueryPerformanceFrequency(&frequency);
    int prime_number[1001]={1},number=0;
    //int *Prime_number;
    for(int i=2;i<=1000;i++){
        if(justice(i,prime_number,number)){
            printf("%d ",i);
            prime_number[number]=i;
            number++;
        }
    }
    printf("\n");
    QueryPerformanceCounter(&time_over); 
    float time_in_micro = 1000000.0 * (time_over.QuadPart - time_start.QuadPart) / frequency.QuadPart;
    printf("Running time:%f microseconds\n", time_in_micro);
    return 0;
}
//32127