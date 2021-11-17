#include <stdio.h>
#include "async.h"

typedef long long TIME_T;
#define ONE_SECOND      (50000000)
#define PRINT_INTERVAL  (ONE_SECOND/2)

TIME_T gCurrentTime = 0;
void tick_timer(void);
void Timer_GetTime(TIME_T *t);
int Timer_SecCheckPassTime(TIME_T *t, int sec);

void open_valve(void);
void close_valve(void);

async do_valve_control(struct async *st);

void transition_to_open_valve(void);
void transition_to_close_valve(void);
void transition_to_end(void);

int main(void)
{
    struct async st;
    async_init(&st);
    while(1)
    {
        async_call(do_valve_control, &st);

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

#define await_for(sec, stmt) \
    Timer_GetTime(&gTimer);\
    await((stmt, Timer_SecCheckPassTime(&gTimer, sec)))

async do_valve_control(struct async *st)
{
    async_begin(st);
        transition_to_open_valve();
        async_yield;

        await_for(1, open_valve());

        transition_to_close_valve();

        await_for(5, close_valve());

        transition_to_end();
    async_end;
}

void transition_to_open_valve(void)
{
}

void transition_to_close_valve(void)
{
}

void transition_to_end(void)
{
}