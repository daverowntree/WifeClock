
void vw_setup(uint16_t speed);
uint16_t vw_crc(uint8_t *ptr, uint8_t count);
uint8_t vw_symbol_6to4(uint8_t symbol);
void vw_set_tx_pin(uint8_t pin);
void vw_set_rx_pin(uint8_t pin);
void vw_set_ptt_pin(uint8_t pin);
void vw_set_ptt_inverted(uint8_t inverted);
void vw_pll();
void vw_tx_start();
void vw_tx_stop();
void vw_rx_start();
void vw_rx_stop();
void vw_wait_tx();
void vw_wait_rx();
uint8_t vw_wait_rx_max(unsigned long milliseconds);
uint8_t vw_send(uint8_t* buf, uint8_t len);
uint8_t vw_have_message();
uint8_t vw_get_message(uint8_t* buf, uint8_t* len);
void radio_isr(void);

