#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"

#include "dw3000_hw.h"
#include "dwhw.h"
#include "dwmac.h"
#include "dwphy.h"
#include "dwproto.h"
#include "ranging.h"

static void twr_done_cb(uint64_t src, uint64_t dst, uint16_t dist,
						 uint16_t num)
{
    //printf("TWR Done %04X: %d cm \n", (uint16_t)dst, dist);
}

void test_twr(void)
{
    // decadriver init
    dw3000_hw_init();
    dw3000_hw_reset();
    dw3000_hw_init_interrupt();

    // libdeca init
    dwhw_init();
    dwphy_config();
    dwphy_set_antenna_delay(DWPHY_ANTENNA_DELAY);

    dwmac_init(1, 2, dwprot_rx_handler, NULL, NULL);
    
    dwmac_set_frame_filter();
    twr_init(TWR_PROCESSING_DELAY, false);
    twr_set_observer(twr_done_cb);

    // two way ranging to 0x0001
    twr_start(0x0001);
}

void app_main()
{
    test_twr();
}