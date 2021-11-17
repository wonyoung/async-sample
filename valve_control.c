#include <stdio.h>

typedef long long TIME_T;
#define ONE_SECOND (50000000)

void open_valve(void);
void close_valve(void);

int main(void)
{
    for (TIME_T t = 0; t < ONE_SECOND; t++)
        open_valve();

    for (TIME_T t = 0; t < ONE_SECOND*5; t++)
        close_valve();

    return 0;
}




void open_valve(void)
{
    static TIME_T t = 0;
    if (t % (ONE_SECOND/2) == 0)
        printf("Valve - Open\n");
    t++;
}

void close_valve(void)
{
    static TIME_T t = 0;
    if (t % (ONE_SECOND/2) == 0)
        printf("Valve - Close\n"); 
    t++;
}