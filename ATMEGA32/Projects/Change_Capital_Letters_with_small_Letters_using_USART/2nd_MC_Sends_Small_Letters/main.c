/*
 * 2nd MC that send Small Letters.
 *
 * Required >> - 2nd MC that receive Capital Letters and Send equivalent small letters using Pooling.
 *
 * Created: 9/10/2018 4:32:32 PM
 * Author : MH_TEALEB
 */

#include "MHT_USART.h"


int main(void)
{
	uint8 ch;
	
	MHT_USART_Init_Async_Double_Speed_Mode(12, _8BITS, NO_PARITY, _1BIT, TX_RISE_RX_FALL, TXEN_RXEN);
    
	while (1)
    {
		ch = MHT_USART_Receive();			// Read The received character from USART.
		if (ch >= 'A' && ch <= 'Z'){		// If Received character are from A to Z.
			ch += ('a'- 'A');					// change from Capital letter to equivalent Small letter.
			MHT_USART_Transmit(ch);				// Send the small letter.
		}else if (ch == ' '){				// If Received space character.
				MHT_USART_Transmit(' ');		// Respond with the same Character.
		}
    }
	
	return 0;
}

