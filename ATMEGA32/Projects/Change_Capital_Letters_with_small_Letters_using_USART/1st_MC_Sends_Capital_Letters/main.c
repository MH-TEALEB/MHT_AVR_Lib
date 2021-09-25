/*
 * 1st MC that send Capital
 *
 * Required >> - 1st MC that Transmit Capital Letters of all letters.
 *
 * Created: 9/10/2018 4:32:32 PM
 * Author : MH_TEALEB
 */

#include "MHT_USART.h"


int main(void)
{
	uint8 ch;	// Declare variable to hold the received characters.

	MHT_USART_Init_Async_Double_Speed_Mode(12, _8BITS, NO_PARITY, _1BIT, TX_RISE_RX_FALL, TXEN_RXEN);

	MHT_USART_Transmit('A');

    while (1)
    {
		ch = MHT_USART_Receive();			// Read The received character from USART.
		if (ch >= 'a' && ch < 'z'){			// If Received character are from a to z(not included).
			ch -= ('a'- 'A');					// change from small letter to equivalent capital letter.
			MHT_USART_Transmit(ch+1);			// Send the next Capital letter.
		}else if (ch == 'z'){				// If all Letters are sent.
			MHT_USART_Transmit(' ');			// Send Space character.
		}else{								// If received characters rather than from a to z .
			MHT_USART_Transmit('A');			// Send Character A to start transmitting of letters again.
		}
    }
	return 0;
}

