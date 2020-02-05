#include <stdio.h>
#include <stdint.h>

uint16_t convertAdcToTemp(uint16_t adc);

int main()
{
	for(int i=0; i<1023; i++) {
		printf("Data: %d:  %d\n", i, convertAdcToTemp(i));
	}

	return 0;
}

uint16_t convertAdcToTemp(uint16_t adc) {
	return (0.25*adc + 2);
}