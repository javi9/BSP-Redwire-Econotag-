/*
 * Sistemas Empotrados
 * Linker script para la Redwire EconoTAG
 * Runtime de C para ser cargado por la BIOS de la placa
 */

/*
 * Punto de entrada
 */
ENTRY(_vector_table)

/*
 * Mapa de memoria de la placa
 */
MEMORY
{
        ram   : org = 0x00400000,       len = 0x00018000        /*  96 KB */
	flash : org = 0x00000000,	len =0x00100000
}

SECTIONS
{
	/* Imagen del firmware */
	/* Generar una sección al principio de la RAM que organice las secciones del firmware al comienzo de la RAM de la 	plataforma */

	.startup:
	{
		*(.startup);	// Este codigo fuerza al cargador a ejecutar la primera instruccion desde la flash
	} > flash

	/* Seccion .vectors*/
	.vectors:
	{
		. + 0x20;	    // Reservamos espacio para la tabla de vectores y la tabla de manejadores
		_excep_handlers = .;
		. += 0x20;	
	} > ram
	_ram_base_boot = 0x00300000; // Direccion de inicio de la ram antes del remapeo

	.text:
	{
		_text_start = .;
		*(.text);	// El cargador se ejecuta desde la flash
		_text_end = .;
	} > ram AT > flash
	_text_flash_start = LOADADDR(.text);


	/* Seccion .rodata*/
	/* Generamos una seccion para variables constantes*/
	.rodata :
	{
		*(.rodata*);
		. =ALING(4);
	}> flash

	/* Seccion .data*/
	/* Generamos una seccion para varibles inicializadas */
	.data:
	{
		_data_start = .;
		*(.data);
		.=ALING(4);
		_data_end= .;
	} > ram AT > flash
	_data_flash_start= LOADADDR(.data);


	/* Seccion .bss */
	/* Generamos una sección para las variables globales sin inicializar 
	   bss -> variables inicializadas a cero.
	   common -> variables sin inicializar.		
	*/
	.bss : 
	{
		_bss_start= .;
		*(.bss);
		. = ALING(4);
		*(COMMON);// Variables sin inicializar
		. = ALING(4);
		_bss_end= .;
	} > ram	

	 /* Gestión de las pilas */
	/* Generar una sección al final de la RAM para las pilas de cada modo y definir símbolos para el tope de cada pila */
	/* Definimos una zona de 2kb al final de la ram para alojar la pila
	   En este caso nos interesa usar direcciones VMA en vez de regiones de memoria
	*/
	_ram_limit = ORIGIN(ram) + LENGTH(ram);
	
	_sys_stack_size = 1024 ;
	_irq_stack_size = 256 ;
	_fiq_stack_size = 256 ;
	_svc_stack_size = 256 ;
	_abt_stack_size =16 ;
	_und_stack_size =16 ;
	_stacks_size = _stacks_top - _stacks_bottom ;

	.stack _ram_limit - _stack_size:
	{
		_stacks_bottom = . ;
		. += _sys_stack_size ;
		_sys_stack_top = . ;
		. += _svc_stack_size ;
		_svc_stack_top = . ;
		. += _abt_stack_size ;
		_abt_stack_top = . ;
		. += _und_stack_size ;
		_und_stack_top = . ;
		. += _irq_stack_size ;
		_irq_stack_top = . ;
		. += _fiq_stack_size ;
		_fiq_stack_top = . ;
		_stacks_top = . ;

	}

	
	/* Gestión del heap */
	/* Generar una sección que ocupe el espacio entre la sección .bss y las pilas para el heap, con los símbolos de inicio y 		   fin del heap */
	_heap_size = _stack_bottom - _bss_end;
	.heap _bss_end:
	{
		_heap_start= .;
		. += heap_size;		//Ubicamos el heap desde el final de .bss hasta el comienzo de la pila.
		_heap_end= .;	
	}



 	

}

