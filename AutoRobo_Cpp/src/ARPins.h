#ifndef PINS_H_
#define PINS_H_

#include "stm32f4xx_gpio.h"
#include "ARUtils.h"

namespace AutoRobo
{
	struct Pin
	{
		static void initGPIO()
		{
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN |
			RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN;
		}

		GPIO_TypeDef* port;
		uint16_t pin; // One bit
		uint8_t pinNum;

		constexpr Pin(GPIO_TypeDef* const gpio, const uint8_t num) :
				port(gpio), pin(1 << (uint16_t)num), pinNum(num)
		{
		}

		void setHigh() const
		{
			port->BSRRL |= pin;
		}

		void setLow() const
		{
			port->BSRRH |= pin;
		}

		bool isHigh() const
		{
			return (port->IDR & pin) > 0;
		}

		bool isLow() const
		{
			return !isHigh();
		}

		void setAsOutput() const
		{
			// Output = MODER(01)
			port->MODER &= ~((uint32_t)(3 << (pinNum * 2)));
			port->MODER |= ((uint32_t)(1 << (pinNum * 2)));
		}

		void setAsInput() const
		{
			// Input = MODER(00)
			port->MODER &= ~((uint32_t)(3 << (pinNum * 2)));
		}

		void setAsAnalog() const
		{
			// Analog = MODER(11)
			port->MODER |= ((uint32_t)(3 << (pinNum * 2)));
		}

		void setAsAfio() const
		{
			// AFIO = MODER(10)
			port->MODER &= ~((uint32_t)(3 << (pinNum * 2)));
			port->MODER |= ((uint32_t)(2 << (pinNum * 2)));
		}

		void setLowSpeed() const
		{
			// LowSpeed = OSPEEDR(00)
			port->OSPEEDR &= ~((uint32_t)(3 << (pinNum * 2)));
		}

		void setMedSpeed() const
		{
			// MedSpeed = OSPEEDR(01)
			port->OSPEEDR &= ~((uint32_t)(3 << (pinNum * 2)));
			port->OSPEEDR |= ((uint32_t)(1 << (pinNum * 2)));
		}

		void setHighSpeed() const
		{
			// MedSpeed = OSPEEDR(10)
			port->OSPEEDR &= ~((uint32_t)(3 << (pinNum * 2)));
			port->OSPEEDR |= ((uint32_t)(2 << (pinNum * 2)));
		}

		void setPushPullEnabled() const
		{
			// Pushup-Pulldown enable = OTYPER(0)
			port->OTYPER &= ~((uint16_t)(1 << pinNum));
		}

		void setOpenDrain() const
		{
			// Open-drain = OTYPER(1)
			port->OTYPER |= ((uint16_t)(1 << pinNum));
		}

		void setNoPushPull() const
		{
			// No pu-pd = PUPDR(00)
			port->PUPDR &= ~((uint32_t)(3 << (pinNum * 2)));
			port->PUPDR |= ((uint32_t)(2 << (pinNum * 2)));
		}

		void setPushUp() const
		{
			// Pullup = PUPDR(01)
			port->PUPDR &= ~((uint32_t)(3 << (pinNum * 2)));
			port->PUPDR |= ((uint32_t)(1 << (pinNum * 2)));
		}

		void setPullDown() const
		{
			// Pulldown = PUPDR(10)
			port->PUPDR &= ~((uint32_t)(3 << (pinNum * 2)));
			port->PUPDR |= ((uint32_t)(2 << (pinNum * 2)));
		}
	};

	namespace MotoPins
	{
		// PWM pins
		static CONST Pin pwmFL(GPIOB, 12);
		static CONST Pin pwmFR(GPIOA, 5);
		static CONST Pin pwmBL(GPIOC, 8);
		static CONST Pin pwmBR(GPIOC, 10);
		// In1 pin -> forward on low (wheel CCW)
		static CONST Pin in1FL(GPIOB, 8);
		static CONST Pin in1FR(GPIOA, 6);
		static CONST Pin in1BL(GPIOC, 5);
		static CONST Pin in1BR(GPIOC, 11);
		// In2 pin -> backward on low (wheel CW)
		static CONST Pin in2FL(GPIOB, 9);
		static CONST Pin in2FR(GPIOA, 7);
		static CONST Pin in2BL(GPIOC, 6);
		static CONST Pin in2BR(GPIOC, 12);
		// Standby in common for left/right
		static CONST Pin standbyLeft(GPIOC, 9);
		static CONST Pin standbyRight(GPIOD, 2);
	}

	namespace ButtonPins
	{
		/*
		 *  Button multiplexer :
		 *  Address : A0 A1 EH
		 *  EN enables inputs 0-3 on low, 4-7 on high
		 */
		static CONST Pin muxA0(GPIOC, 1);
		static CONST Pin muxA1(GPIOC, 2);
		static CONST Pin muxEN(GPIOC, 3);
		static CONST Pin muxRead(GPIOC, 0);
	}

	namespace LcdPins
	{
		static CONST Pin E(GPIOC, 4);
		static CONST Pin RS(GPIOB, 10);
		static CONST Pin RW(GPIOC, 7);
		static CONST Pin D4(GPIOB, 4);
		static CONST Pin D5(GPIOB, 5);
		static CONST Pin D6(GPIOB, 3);
		static CONST Pin D7(GPIOA, 10);
	}
}

#endif
