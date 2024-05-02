#include "../inc/door.h"


static Door_State ledState;
#define SERVO_MIN_PULSEWIDTH 500  // Độ rộng xung tối thiểu (micro giây) cho góc 0 độ
#define SERVO_MAX_PULSEWIDTH 2500 // Độ rộng xung tối đa (micro giây) cho góc 180 độ
//#define GPIO_SERVO_PWM 18         // GPIO pin cho PWM của servo
uint32_t servo_per_degree_init(int degree_of_rotation) {
    return SERVO_MIN_PULSEWIDTH + (degree_of_rotation * (SERVO_MAX_PULSEWIDTH - SERVO_MIN_PULSEWIDTH) / 180);
}

void doorInit() {
    gpio_reset_pin(DOOR_GPIO);
    gpio_set_direction(DOOR_GPIO, GPIO_MODE_OUTPUT);

    //TODO: get state from database (Ngoc)

    doorSetState(ledState);
}

void doorSetState(Door_State state) {
    // (Tung | Nguyen)
    if (state == DOOR_STATE_OPEN)
    {
        mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, servo_per_degree_init(90));
    }
    else if (state == DOOR_STATE_CLOSE)
    {
        mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, servo_per_degree_init(0));
    }
    
    
} 
extern void doorEventHandler(char *query) {
    // (Ngoc)
} 