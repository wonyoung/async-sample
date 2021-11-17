#include <stdio.h>

typedef long long TIME_T;
#define ONE_SECOND      (50000000)
#define PRINT_INTERVAL  (ONE_SECOND/2)

TIME_T gCurrentTime = 0;
void tick_timer(void);
void Timer_GetTime(TIME_T *t);
int Timer_SecCheckPassTime(TIME_T *t, int sec);

#define INIT_STEP           (0)
#define OPEN_VALVE_STEP     (1)
#define CLOSE_VALVE_STEP    (2)
#define END_STEP            (3)

void open_valve(void);
void close_valve(void);

void do_valve_control(void);

int time_expired_seconds(int sec);
void transition_to_open_valve(void);
void transition_to_close_valve(void);
void transition_to_end(void);

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

        tick_timer();
    }

    return 0;
}




void tick_timer(void)
{
    gCurrentTime++;
}

void Timer_GetTime(TIME_T *t)
{
    *t = gCurrentTime;
}

int Timer_SecCheckPassTime(TIME_T *t, int sec)
{
    if (*t + sec*ONE_SECOND < gCurrentTime)
        return 1;
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

TIME_T gTimer;

int time_expired_seconds(int sec)
{
    return Timer_SecCheckPassTime(&gTimer, sec);
}

void do_valve_control(void)
{
    static int sState = INIT_STEP;
    switch(sState)
    {
        case INIT_STEP:
            transition_to_open_valve();
            sState = OPEN_VALVE_STEP;
            break;
        case OPEN_VALVE_STEP:
            open_valve();
            if (time_expired_seconds(1)) {
                transition_to_close_valve();
                sState = CLOSE_VALVE_STEP;
            }
            break;
        case CLOSE_VALVE_STEP:
            close_valve();
            if (time_expired_seconds(5)) {
                transition_to_end();
                sState = END_STEP;
            }
            break;
        case END_STEP:
        default:
            break;
    }
}

void transition_to_open_valve(void)
{
    Timer_GetTime(&gTimer);
}

void transition_to_close_valve(void)
{
    Timer_GetTime(&gTimer);
}

void transition_to_end(void)
{
}