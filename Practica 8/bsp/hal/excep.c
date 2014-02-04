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
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 7 */
	uint32_t EstadoBits;
	
	asm volatile ( "mrs %[b], cpsr\n\t"
		       "orr r12, %[b], #0xC0\n\t"
		       "msr cpsr_c, r12"
			: [b] "=r" (EstadoBits)
			:
			: "r12", "cc");
	
		return ((EstadoBits>>6)&3); /*Devuelve 0 si se ha hecho correctamente*/
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
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 7 */
	uint32_t EstadoBits;

	asm volatile ( "mrs %[b], cpsr\n\t"
		       "orr r12, %[b], #0x80\n\t"
		       "msr cpsr_c, r12"
		       :[b] "=r" (EstadoBits)
		       :
		       :"r12", "cc");
	return ((EstadoBits>>7)&1);
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
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 7 */
	uint32_t EstadoBits;

	asm volatile ( "mrs %[b], cpsr\n\t"
		       "orr r12, %[b], #0x40\n\t"
		       "msr cpsr_c, r12"
		       :[b] "=r" (EstadoBits)
		       :
		       :"r12", "cc");
	return ((EstadoBits>>6)&1);

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
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 7 */
	asm volatile(	"mrs r12, cpsr\n\t"
			"bic r12, r12, #0xC0\n\t"
			"orr r12, r12, %[b], LSL #6\n\t"
			"msr cpsr_c, r12"
			:
			: [b] "r" (if_bits & 3)
			: "r12", "cc");
	
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
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 7 */
	asm volatile(	"mrs r12, cpsr\n\t"
			"bic r12, r12, #0x80\n\t"
			"orr r12, r12, %[b], LSL #7\n\t"
			"msr cpsr_c, r12"
			:
			: [b] "r" (i_bit & 1)
			: "r12", "cc");
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
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 7 */
	asm volatile(	"mrs r12, cpsr\n\t"
			"bic r12, r12, #0x40\n\t"
			"orr r12, r12, %[b], LSL #6\n\t"
			"msr cpsr_c, r12"
			:
			: [b] "r" (f_bit & 1)
			: "r12", "cc");
}

/*****************************************************************************/

/**
 * Asigna un manejador de interrupción/excepción
 * @param excep		Tipo de excepción
 * @param handler	Manejador
 */
inline void excep_set_handler (excep_t excep, excep_handler_t handler)
{
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 7 */
	_excep_handlers[excep]=handler;
}

/*****************************************************************************/

/**
 * Retorna un manejador de interrupción/excepción
 * @param excep		Tipo de excepción
 */
inline excep_handler_t excep_get_handler (excep_t excep)
{
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 7 */
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
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 7 */
	itc_service_normal_interrupt();
}

/*****************************************************************************/
