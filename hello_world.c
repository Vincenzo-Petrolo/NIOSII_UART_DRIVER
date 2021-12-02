#define CR 13
#define BS 8

#ifdef PROJECT8_1
int main(void)
{
	uint16_t divisor_val, status_val;
	uart_controller_t controller;
	uint8_t[64+1] arriving_string;
	int i;
	
	/*init uart controller*/
	uart_init(&controller, BASE_ADDR);

	printf("NIOSII_UART_DRIVER_project8\n\n");
	
	/*Compute divisor*/
	divisor_val = (alt_timestamp_freq()/BAUDRATE)-1;
	/*Update divisor*/
	uart_set_divisor(&controller, divisor_val);
	
	/*disabling all interrupts for polling*/
	uart_set_control(&controller, 0x0, 0xFFFF);
	
	for(EVER) {
		for(i = 0; i < 64; i++)
		{
			uart_read_rxdata(controller, arriving_string[i]);
			if ( arriving_string[i] == CR )
				break;
			if ( arriving_string[i] == BS )
				i -= 2;	
		}
		
		string[i] = '\0';
		printf("%s", arriving_string);
	}
	return 0; 