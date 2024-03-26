#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <driver/dac_oneshot.h>
#include <esp_err.h>


static void init_dac(dac_oneshot_handle_t *handle){
dac_oneshot_config_t dac_config={
		.chan_id = DAC_CHAN_0
};
ESP_ERROR_CHECK(dac_oneshot_new_channel(&dac_config,handle));
}




void app_main(void)
{
	dac_oneshot_handle_t dac_handle;
	init_dac(&dac_handle);
	ESP_ERROR_CHECK(dac_oneshot_output_voltage(dac_handle, 255));
	printf("Dac Output Terminated!\n");
    while (true) {
       // printf("Hello from app_main!\n");
        sleep(1);
    }
}
