#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#define F_CPU 16000000UL
#define BAUD 115200

void USART_Init( unsigned int speed);
void USART_Transmit( unsigned char data );

void setup() {

}

void loop() {
		USART_Init (16);//115200
		USART_Transmit('H');//�������� ��� ���������
		USART_Transmit('e');//��������� "Ok!", ��� ���������������
		USART_Transmit('l');//� ��������� ������ ���������
		USART_Transmit('l');
		USART_Transmit('o');
		USART_Transmit(' ');
		USART_Transmit('W');
		USART_Transmit('o');
		USART_Transmit('r');
		USART_Transmit('l');
		USART_Transmit('d');
		USART_Transmit('!');
		USART_Transmit(0x0d);//������� � ������ ������
		USART_Transmit(0x0a);//������� �� ����� ������
		_delay_ms(500);
	    while(1)
	    {
	    }
}

void USART_Init( unsigned int speed)//������������� ������ USART
{
		UBRR0H = (unsigned char)(speed>>8);
		UBRR0L = (unsigned char)speed;

		UCSR0B=(1<<RXEN0)|( 1<<TXEN0); //�������� ����� � �������� �� USART
		UCSR0B |= (1<<RXCIE0); //��������� ���������� ��� ��������
		UCSR0A |= (1<<U2X0); // ��� 8 ���
		UCSR0C = (1<<USBS0)|(3<<UCSZ00);
;// ���������� ������ � �������� UCSRC (URSEL=1),
		//������������ ����� (UMSEL=0), ��� �������� �������� (UPM1=0 � UPM0=0),
		//1 ����-��� (USBS=0), 8-��� ������� (UCSZ1=1 � UCSZ0=1)
		//UCSRC |= (1<<UPM1);//��������
}

void USART_Transmit( unsigned char data ) //������� �������� ������
{
	while ( !(UCSR0A & (1<<UDRE0)) ); //�������� ����������� ������ ������
	UDR0 = data; //������ �������� ������
}
