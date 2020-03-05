/*void write_byte(uint8_t byte)
{
	    for(int i=0;i<8;i++)
          {
	    	 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);  // Pull the CLK LOW
	    	 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, byte&0x80);// Write one BIT data MSB first
             byte = byte<<1;  // shift the data to the left
             HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);  // Pull the CLK HIGH
           }
}

void write_max (uint8_t address, uint8_t data)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);   // Pull the CS pin LOW
    write_byte(address);   //  write address
    write_byte(data);  //  write data
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);  // pull the CS HIGH
}


void max_init(void)
{
 write_max(0x09, 0x00);       //  no decoding
 write_max(0x0a, 0x03);       //  brightness intensity
 write_max(0x0b, 0x07);       //  scan limit = 8 LEDs
 write_max(0x0c, 0x01);       //  power down =0,normal mode = 1
 write_max(0x0f, 0x00);       //  no test display
}
*/