#ifdef PROJECT7_1
int main(void)
{
	uint16_t divisor_val, status_val;
	uart_controller_t controller;
	uint8_t arriving_char;
	
	/*init uart controller*/
	uart_init(&controller, BASE_ADDR);

	printf("NIOSII_UART_DRIVER_project4\n\n");
	
	/*Compute divisor*/
	divisor_val = (alt_timestamp_freq()/BAUDRATE)-1;
	/*Update divisor*/
	uart_set_divisor(&controller, divisor_val);

	/*disabling all interrupts for polling*/
	uart_set_control(&controller, 0x0, 0xFFFF);
	
	for(EVER)
	{
		uart_read_rxdata(&controller, &arriving_char);
		printf("%c", arriving_char);
		uart_read_status(&controller, &status_val);
		if ((status_val)&0x1) == 1)
		{
			printf("parity error detected");
			uart_clear_status(&controller);
		}
	}
	return(0);
}