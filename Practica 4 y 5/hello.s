@
@ Sistemas Empotrados
@ El "Practica 4" en la Redwire EconoTAG
@


@
@ Punto de entrada
@

@ SECCION DATA 		En esta seccion definimos las variables globales de nuestro programa

	.data
	

	LED_RED_MASK:
		.word	1<<(44-32)
	LED_GREEN_MASK:
		.word   1<<(45-32)
	S2_MASK_IN:  
		.word	1<<23
	S2_MASK_OUT:
		.word	1<<27
	S3_MASK_IN:
		.word	1<<22
	S3_MASK_OUT:
		.word	1<<26

        .code 32

@ SECCION TEXT

        .text
        .global _start
        .type   _start, %function



_start:

	bl	gpio_init


      @ Direcciones de los registros GPIO_DATA_SET1, y GPIO_DATA_RESET1 
      @ Para controlar el encendido y apagado del led
        
	ldr     r6, = GPIO_DATA_SET1
        ldr     r8, = GPIO_DATA_RESET1

	
loop:
	bl 	test_button	
	
     	@ Encendemos el led
	str  	r1, [r6]
	
	

   	@ Apagamos el led
        str     r1, [r8]
	
	
	
	b	loop
  

        
gpio_init:
	

	@Configuramos el GPIO44 GPIO45 para que sean de salida (led rojo y verde)
	ldr     r0, =GPIO_PAD_DIR1
        ldr     r1, =LED_RED_MASK
       	ldr	r2, [r1]
	ldr	r1, =LED_GREEN_MASK
	ldr	r3, [r1]
	orr	r1, r3 ,r2
	str	r1,[r0] 

	@ya esta cargado el registro de direccion con el puerto del led rojo configurado como salida.


	
	@configuracion de los botones S2 y s3 de salida
	
	@	Pines 27 y 26 configurado como salida en reg. dirección
	ldr	r4, = GPIO_PAD_DIR0
	ldr	r5,  =S2_MASK_OUT
	ldr	r7, [r5]
	ldr	r5,  =S3_MASK_OUT
	ldr	r9, [r5]
	orr	r5, r9, r7
	str	r5, [r4]
	
	@	Ahora metemos un 1 en el registro de datos del pin 27 y del pin 26
	ldr	r4, = GPIO_DATA_SET0
	orr	r5, r7, r9
	str	r5, [r4]	
	

	@Metemos las mascaras de los botones de entrada
	ldr	r1,=S2_MASK_IN
	ldr	r7,[r1]
	ldr	r1,=S3_MASK_IN
	ldr	r9,[r1]
	
	mov	pc, lr

test_button:
	
	ldr	r0, = GPIO_DATA0
	ldr	r10, [r0]

	@ hacemos un test entre el registro de datos y la mascara del pin del boton que esta configurado como entrada.
	
        ldr     r2, =LED_RED_MASK
  
	tst	r10, r7
	ldrne	r1, [r2]
	
	ldr	r3, =LED_GREEN_MASK

	tst	r10, r9
	ldrne	r1, [r3]
	
	mov     pc, lr


