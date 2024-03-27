#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <esp_adc/adc_oneshot.h>
#include <hal/adc_types.h>
#include <driver/dac_oneshot.h>

static void init_dac(dac_oneshot_handle_t *handle){
dac_oneshot_config_t dac_config={
		.chan_id = DAC_CHAN_0
};
ESP_ERROR_CHECK(dac_oneshot_new_channel(&dac_config,handle));
}


void app_main(void)
{
	adc_oneshot_unit_handle_t adc1_handle;
	adc_oneshot_unit_init_cfg_t init_config1 = {
	    .unit_id = ADC_UNIT_1,
	    .ulp_mode = ADC_ULP_MODE_DISABLE,
	};
	adc_oneshot_chan_cfg_t config = {
	    .bitwidth = ADC_BITWIDTH_9,
	    .atten = ADC_ATTEN_DB_11,
	};
	int out_value;
	dac_oneshot_handle_t dac_handle;
	init_dac(&dac_handle);
	ESP_ERROR_CHECK(dac_oneshot_output_voltage(dac_handle, 39));

	ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));
	ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_0, &config));
    while (true) {
    	ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle,ADC_CHANNEL_0, &out_value ));
        printf("Result is %4d!\n", out_value);
        sleep(1);
    }
}
