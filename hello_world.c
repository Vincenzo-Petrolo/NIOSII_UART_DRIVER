int main()
{
	int *base_address = RXDATA;
	int reg;
	for ( int i = 0 ; i < 5; i++)
	{
		reg = *base_address;
		printf ( "%d\n", val);
		base_address += 4;
	}
	while(1);
	return 0;
}
