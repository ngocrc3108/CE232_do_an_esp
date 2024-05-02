#include "../inc/door.h"

#define DOOR_MCPWM_UNIT MCPWM_UNIT_1
#define DOOR_MCPWM_TIMER MCPWM_TIMER_1

static Door_State ledState;
#define SERVO_MIN_PULSEWIDTH 500  // Độ rộng xung tối thiểu (micro giây) cho góc 0 độ
#define SERVO_MAX_PULSEWIDTH 2500 // Độ rộng xung tối đa (micro giây) cho góc 180 độ
//#define GPIO_SERVO_PWM 18         // GPIO pin cho PWM của servo
uint32_t servo_per_degree_init(int degree_of_rotation) {
    return SERVO_MIN_PULSEWIDTH + (degree_of_rotation * (SERVO_MAX_PULSEWIDTH - SERVO_MIN_PULSEWIDTH) / 180);
}

void doorInit() {
    // Initialize MCPWM module
    mcpwm_gpio_init(DOOR_MCPWM_UNIT, MCPWM0A, DOOR_GPIO); // GPIO 18 as PWM0A, to drive a motor
    // Configure MCPWM configuration parameters
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 50;  // frequency = 1kHz
    pwm_config.cmpr_a = 0;        // duty cycle of PWMxA = 0
    pwm_config.cmpr_b = 0;        // duty cycle of PWMxB = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    
    // Set MCPWM configuration for the MCPWM unit 0, timer 0
    mcpwm_init(DOOR_MCPWM_UNIT, DOOR_MCPWM_TIMER, &pwm_config);

    //TODO: get state from database (Ngoc)

    doorSetState(ledState);
}

void doorSetState(Door_State state) {
    // (Tung | Nguyen)
    if (state == DOOR_STATE_OPEN)
    {
        mcpwm_set_duty_in_us(DOOR_MCPWM_UNIT, DOOR_MCPWM_TIMER, MCPWM_OPR_A, servo_per_degree_init(90));
    }
    else if (state == DOOR_STATE_CLOSE)
    {
        mcpwm_set_duty_in_us(DOOR_MCPWM_UNIT, DOOR_MCPWM_TIMER, MCPWM_OPR_A, servo_per_degree_init(0));
    }
    
    
} 
extern void doorEventHandler(char *query) {
    // (Ngoc)
} 