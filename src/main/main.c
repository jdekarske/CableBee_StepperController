#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_system.h"

#include "constants.h"

inline void stepDelay(void)
{
	uint32_t m = esp_timer_get_time();
	uint32_t e = (m + 1); // 1 uS delay
	if (m > e)
	{ //overflow
		while (esp_timer_get_time() > e)
		{
			__asm__ __volatile__("nop");
		}
	}
	while (esp_timer_get_time() < e)
	{
		__asm__ __volatile__("nop");
	}
}

inline void step(int pin)
{
	gpio_set_level(pin, 1);
	stepDelay();
	gpio_set_level(pin, 0);
}

void app_main(void)
{
	gpio_config_t io_conf;
	//disable interrupt
	io_conf.intr_type = GPIO_INTR_DISABLE;
	//set as output mode
	io_conf.mode = GPIO_MODE_OUTPUT;
	//bit mask of the pins that you want to set,e.g.GPIO18/19
	io_conf.pin_bit_mask = STEP_OUTPUTS;
	//disable pull-down mode
	io_conf.pull_down_en = 0;
	//disable pull-up mode
	io_conf.pull_up_en = 0;
	//configure GPIO with the given settings
	gpio_config(&io_conf);

	int dir = 0;
	int cnt = 0;

	gpio_set_level(XDIR, dir);
	gpio_set_level(XSTEP, 0);
	while (1)
	{
		printf("cnt: %d\n", cnt++);
		vTaskDelay(4 / portTICK_RATE_MS);
		step(XSTEP);
		if (cnt >= 4000)
		{
			cnt = 0;
			//flip direction
			dir = !dir;
			gpio_set_level(XDIR, dir);
		}
	}
}