/*
 * Sistemas operativos empotrados
 * Driver para el controlador de interrupciones del MC1322x
 */

#include "system.h"

/*****************************************************************************/

/**
 * Acceso estructurado a los registros de control del ITC del MC1322x
 */
typedef struct
{
	/* ESTA ESTRUCTURA SE DEFINIRÁ EN LA PRÁCTICA 8 */
	uint32_t INTCNTL;
	uint32_t NIMASK;
	uint32_t INTENNUM;
	uint32_t INTDISNUM;
	uint32_t INTENABLE;
	uint32_t INTTYPE;
	uint32_t padding[4]; // Espacio reservado
	uint32_t NIVECTOR;
	uint32_t FIVECTOR;
	uint32_t INTSRC;
	uint32_t INTFRC;
	uint32_t NIPEND;
	uint32_t FIPEND;
	
} itc_regs_t;

static volatile itc_regs_t* const itc_regs = 0x80020000;

static volatile uint32_t Reg_SC;
/**
 * Tabla de manejadores de interrupción.
 */
static itc_handler_t itc_handlers[itc_src_max];

/*****************************************************************************/

/**
 * Inicializa el controlador de interrupciones.
 * Deshabilita los bits I y F de la CPU, inicializa la tabla de manejadores a NULL,
 * y habilita el arbitraje de interrupciones Normales y rápidas en el controlador
 * de interupciones.
 */
inline void itc_init ()
{
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 8 */
	
	for (int =0; i<itc_src_max; i++)
		itc_handler[i]=NULL;

	itc_regs -> INTFRC = 0;
	
	itc_regs -> INTENABLE = 0;

	int32_t intcntl, se;
	sc=excep_disable_ints ();
	intcntl = itc_regs->INTCNTL;
	intcntl &= 0xFFE7FFFF;
	itc_regs -> INTCNTL = intcntl;
	excep_restore_ints (sc);
}

/*****************************************************************************/

/**
 * Asigna un manejador de interrupción
 * @param src		Identificador de la fuente
 * @param handler	Manejador
	ok 
*/
inline void itc_set_handler (itc_src_t src, itc_handler_t handler)
{
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 8 */
	int32_t sc;
	sc=excep_disable_ints ();
	itc_handler_t[src]=handler;
	excep_restore_ints (sc);

}

/*****************************************************************************/

/**
 * Asigna una prioridad (normal o fast) a una fuente de interrupción
 * @param src		Identificador de la fuente
 * @param priority	Tipo de prioridad
 */
inline void itc_set_priority (itc_src_t src, itc_priority_t priority)
{
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 8 */

}

/*****************************************************************************/

/**
 * Habilita las interrupciones de una determinda fuente
 * @param src		Identificador de la fuente
	ok 
*/
inline void itc_enable_interrupt (itc_src_t src)
{
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 8 */
	int32_t sc;
	sc=excep_disable_ints ();
	itc_reg -> INTENNUM=src;
	excep_restore_ints (sc);
}

/*****************************************************************************/

/**
 * Deshabilita las interrupciones de una determinda fuente
 * @param src		Identificador de la fuente
 
	ok
*/
inline void itc_disable_interrupt (itc_src_t src)
{
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 8 */
	int32_t sc;
	sc=excep_disable_ints ();
	itc_reg -> INTENNUM=src;
	excep_restore_ints (sc);
}

/*****************************************************************************/

/**
 * Fuerza una interrupción con propósitos de depuración
 * @param src		Identificador de la fuente

	ok
 */

inline void itc_force_interrupt (itc_src_t src)
{
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 8 */
	itc_reg -> INTFRC=src;
}

/*****************************************************************************/

/**
 * Desfuerza una interrupción con propósitos de depuración
 * @param src		Identificador de la fuente
		
	ok 
*/
inline void itc_unforce_interrupt (itc_src_t src)
{
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 8 */
	itc_reg -> INTFRC=src;
}

/*****************************************************************************/

/**
 * Da servicio a la interrupción normal pendiente de más prioridad.
 * Deshabilia las IRQ de menor prioridad hasta que se haya completado el servicio
 * de la IRQ para evitar inversiones de prioridad
 */
void itc_service_normal_interrupt ()
{
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 8 */
	int32_t src= itc_reg -> NIVECTOR;
	itc_handler[src]();
}

/*****************************************************************************/

/**0
 * Da servicio a la interrupción rápida pendiente de más prioridad
 */
void itc_service_fast_interrupt ()
{
	/* ESTA FUNCIÓN SE DEFINIRÁ EN LA PRÁCTICA 8 */
	int32_t src= itc_reg -> FIVECTOR;
	itc_handler[src]();
}

/*****************************************************************************/
