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
		USART_Transmit('H');//ѕередаем при включении
		USART_Transmit('e');//сообщение "Ok!", что свидетельствует
		USART_Transmit('l');//о правильно работе программы
		USART_Transmit('l');
		USART_Transmit('o');
		USART_Transmit(' ');
		USART_Transmit('W');
		USART_Transmit('o');
		USART_Transmit('r');
		USART_Transmit('l');
		USART_Transmit('d');
		USART_Transmit('!');
		USART_Transmit(0x0d);//переход в начало строки
		USART_Transmit(0x0a);//переход на новую строку
		_delay_ms(500);
	    while(1)
	    {
	    }
}

void USART_Init( unsigned int speed)//Инициализация модуля USART
{
		UBRR0H = (unsigned char)(speed>>8);
		UBRR0L = (unsigned char)speed;

		UCSR0B=(1<<RXEN0)|( 1<<TXEN0); //Включаем прием и передачу по USART
		UCSR0B |= (1<<RXCIE0); //Разрешаем прерывание при передаче
		UCSR0A |= (1<<U2X0); // Для 8 мгц
		UCSR0C = (1<<USBS0)|(3<<UCSZ00);
;// Обращаемся именно к регистру UCSRC (URSEL=1),
		//ассинхронный режим (UMSEL=0), без контроля четности (UPM1=0 и UPM0=0),
		//1 стоп-бит (USBS=0), 8-бит посылка (UCSZ1=1 и UCSZ0=1)
		//UCSRC |= (1<<UPM1);//четность
}

void USART_Transmit( unsigned char data ) //Функция отправки данных
{
	while ( !(UCSR0A & (1<<UDRE0)) ); //Ожидание опустошения буфера приема
	UDR0 = data; //Начало передачи данных
}
