int main()
{
	int *reg = (int *) RXDATA;
	for ( int i = 0 ; i < 5; i++)
	{
		printf ( "%d\n", *reg);
		reg++;
	}
	for(EVER);
	return 0;
}
