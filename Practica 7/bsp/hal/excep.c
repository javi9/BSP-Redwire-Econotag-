/*
 * Sistemas operativos empotrados
 * Gestión de excepciones del MC1322x
 */

#include "system.h"

/*****************************************************************************/

/**
 * Tabla de manejadores
 */
extern volatile excep_handler_t _excep_handlers[excep_max];

/*****************************************************************************/

/**
 * Inicializa los manejadores de excepción
 */
void excep_init ()
{
	excep_set_handler (excep_irq, excep_nonnested_irq_handler);
}

/*****************************************************************************/

/**
 * Deshabilita todas las interrupciones
 * @return	El valor de los bits I y F antes de deshabilitar las interrupciones:
 * 			0: I=0, F=0	(IRQ habilitadas,    FIQ habilitadas)
 * 			1: I=0, F=1	(IRQ habilitadas,    FIQ deshabilitadas)
 * 			2: I=1, F=0	(IRQ deshabilitadas, FIQ habilitadas)
 * 			3: I=1, F=1	(IRQ deshabilitadas, FIQ deshabilitadas)
 */
inline uint32_t excep_disable_ints ()
{
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 6 */
	uint32_t EstadoBits;
	
		return 0;
}

/*****************************************************************************/

/**
 * Deshabilita las interrupciones normales
 * @return	El valor del bit I antes de deshabilitar las interrupciones:
 * 			0: I=0	(IRQ habilitadas)
 * 			1: I=1	(IRQ deshabilitadas)
 */
inline uint32_t excep_disable_irq ()
{
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 6 */
	return 0;
}

/*****************************************************************************/

/**
 * Deshabilita las interrupciones rápidas
 * @return	El valor del bit F antes de deshabilitar las interrupciones:
 * 			0: F=0	(FIQ habilitadas)
 * 			1: F=1	(FIQ deshabilitadas)
 */
inline uint32_t excep_disable_fiq ()
{
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 6 */
	return 0;
}

/*****************************************************************************/

/**
 * Restaura los antiguos valores de las máscaras de interrupción
 * @param if_bits	Valores anteriores de las máscaras
 * 						0: I=0, F=0	(IRQ habilitadas,    FIQ habilitadas)
 *			 			1: I=0, F=1	(IRQ habilitadas,    FIQ deshabilitadas)
 * 						2: I=1, F=0	(IRQ deshabilitadas, FIQ habilitadas)
 *			 			3: I=1, F=1	(IRQ deshabilitadas, FIQ deshabilitadas)
 */
inline void excep_restore_ints (uint32_t if_bits)
{
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 6 */
}

/*****************************************************************************/

/**
 * Restaura el antiguo valor de la máscara de interrupciones normales
 * @param i_bit	Valor anterior de la máscara
 * 						0: I=0	(IRQ habilitadas)
 * 						1: I=1	(IRQ deshabilitadas)
 */
inline void excep_restore_irq (uint32_t i_bit)
{
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 6 */
}

/*****************************************************************************/

/**
 * Restaura el antiguo valor de la máscara de interrupciones rápidas
 * @param f_bit	Valor anterior de la máscara
 * 						0: F=0	(FIQ habilitadas)
 * 						1: F=1	(FIQ deshabilitadas)
 */
inline void excep_restore_fiq (uint32_t f_bit)
{
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 6 */
}

/*****************************************************************************/

/**
 * Asigna un manejador de interrupción/excepción
 * @param excep		Tipo de excepción
 * @param handler	Manejador
 */
inline void excep_set_handler (excep_t excep, excep_handler_t handler)
{
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 6 */
	_excep_handlers[excep]=handler;
}

/*****************************************************************************/

/**
 * Retorna un manejador de interrupción/excepción
 * @param excep		Tipo de excepción
 */
inline excep_handler_t excep_get_handler (excep_t excep)
{
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 6 */
        return _excep_handlers[excep];
}

/*****************************************************************************/

/**
 * Manejador en C para interrupciones normales no anidadas
 * El atributo interrupt no guarda en la pila el registro spsr, por lo que
 * sólo genera manejadores para interrupciones no anidadas
 * Para poder gestionar interrupciones anidadas y sacar partiro al controlador
 * de interrupciones es necesario escribir el manejador en ensamblador
 */
void excep_nonnested_irq_handler ()
{
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 6 */
}

/*****************************************************************************/
