///////////////////////////////////////////////////////////
#ifndef CLOCK_TASK_H
#define CLOCK_TASK_H
///////////////////////////////////////////////////////////

#include "driver/gpio.h"
#include "tm1637.h"

typedef struct clock_task_init_parameters_t
{
    tm1637_handle_t handle;
} clock_task_init_parameters_t;

void clock_task_init(void *pvParameter);

typedef struct clock_task_parameters_t
{
    tm1637_handle_t handle;
} clock_task_parameters_t;

void clock_task(void *pvParameter);

///////////////////////////////////////////////////////////
#endif // CLOCK_TASK_H
///////////////////////////////////////////////////////////
