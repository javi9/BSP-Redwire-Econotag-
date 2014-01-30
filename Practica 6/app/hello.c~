/*****************************************************************************/
/*                                                                           */
/* Sistemas Empotrados                                                       */
/* El "hola mundo" en la Redwire EconoTAG en C                               */
/*                                                                           */
/*****************************************************************************/

#include <stdint.h>

/*
 * Constantes relativas a la plataforma
 */

/* Dirección del registro de control de dirección del GPIO32-GPIO63 */
volatile uint32_t * const reg_gpio_pad_dir1    = (uint32_t *) 0x80000004;

// Direccion del registro de control de direccion del GPIO00-GPIO31

volatile uint32_t * const reg_gpio_pad_dir0 = (uint32_t *) 0x80000000;

volatile uint32_t * const reg_gpio_data_set0   = (uint32_t *) 0x80000048;
/* Dirección del registro de activación de bits del GPIO32-GPIO63 */
volatile uint32_t * const reg_gpio_data_set1   = (uint32_t *) 0x8000004c;

/* Dirección del registro de limpieza de bits del GPIO32-GPIO63 */
volatile uint32_t * const reg_gpio_data_reset1 = (uint32_t *) 0x80000054;

volatile uint32_t * const reg_gpio_data0 = (uint32_t *) 0x80000008;

/* El led rojo está en el GPIO 44 (el bit 12 de los registros GPIO_X_1) */
uint32_t const led_red_mask = (1 << (44-32));
/* El led verde está en el GPIO 45 (el bit 12 de los registros GPIO_X_1) */
uint32_t const led_green_mask= (1 <<(45-32));

uint32_t const s2_in= (1 << 23);
uint32_t const s2_out= (1 << 27);
uint32_t const s3_in= (1 << 22);
uint32_t const s3_out= (1 << 26);


/*
 * Constantes relativas a la aplicacion
 */
uint32_t const delay = 0x10000;
 
/*****************************************************************************/

/*
 * Inicialización de los pines de E/S
 */
void gpio_init(void)
{
	/* Configuramos el GPIO44 y GPIO45 para que sea de salida */
	*reg_gpio_pad_dir1 = led_red_mask | led_green_mask;
	/* Configuramos de los botones s2 y s3 de salida */	
	*reg_gpio_pad_dir0 = s2_out | s3_out;
	
	*reg_gpio_data_set0 = s2_out | s3_out;

	
}

/*****************************************************************************/


/*
 * Enciende los leds indicados en la máscara
 * @param mask Máscara para seleccionar leds
 */
void leds_on (uint32_t mask)
{
	/* Encendemos los leds indicados en la máscara */
	*reg_gpio_data_set1 = mask;
}

/*****************************************************************************/

/*
 * Apaga los leds indicados en la máscara
 * @param mask Máscara para seleccionar leds
 */
void leds_off (uint32_t mask)
{
	/* Apagamos los leds indicados en la máscara */
	*reg_gpio_data_reset1 = mask;
}

/*****************************************************************************/

/*
 * Retardo para el parpedeo
 */
void pause(void)
{
        uint32_t i;
	for (i=0 ; i<delay ; i++);
}

/*****************************************************************************/

/*
 * Máscara del led que se hará parpadear
 */
uint32_t the_led_red;
uint32_t the_led_green;
uint32_t the_s2;
uint32_t the_s3;

uint32_t GpioData;
/*
 * Programa principal
 */
int main ()
{
	gpio_init();

        the_led_red = led_red_mask;
	the_led_green = led_green_mask;
	the_s2 = s2_in;
	the_s3 = s3_in;

	while (1)
	{
		GpioData=*(reg_gpio_data0);

		if(GpioData & the_s2){
			leds_on(the_led_red);

		}

		if(GpioData & the_s3){
			leds_on(the_led_green);
                }

		pause();
		leds_off(the_led_green);
		leds_off(the_led_red);
                pause();

	}

        return 0;
}

/*****************************************************************************/

