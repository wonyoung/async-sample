#include <stdio.h>

typedef long long TIME_T;
#define ONE_SECOND      (50000000)
#define PRINT_INTERVAL  (ONE_SECOND/2)

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
    static long long cnt = 0;
    if (++cnt % PRINT_INTERVAL == 0) {
        printf("Valve - Open #%lld\n", cnt / PRINT_INTERVAL);
    }
}

void close_valve(void)
{
    static long long cnt = 0;
    if (++cnt % PRINT_INTERVAL == 0)
        printf("Valve - Close #%lld\n", cnt / PRINT_INTERVAL);
}