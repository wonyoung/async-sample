#include <stdio.h>

typedef long long TIME_T;
#define ONE_SECOND      (50000000)
#define PRINT_INTERVAL  (ONE_SECOND/2)

#define OPEN_VALVE_STEP     (1)
#define CLOSE_VALVE_STEP    (2)

void open_valve(void);
void close_valve(void);

void do_valve_control(void);

int main(void)
{
    while(1)
    {
        do_valve_control();

        // do_motor_control();
        // do_pump_control();

        // do_led_control();

        // do_something_else1();
        // do_something_else2();
    }

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

int gState = OPEN_VALVE_STEP;

void do_valve_control(void)
{
    switch(gState)
    {
        case OPEN_VALVE_STEP:
            open_valve();
            break;
        case CLOSE_VALVE_STEP:
            close_valve();
            break;
        default:
            break;
    }
}