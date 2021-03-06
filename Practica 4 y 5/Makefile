###############################################################################
# Makefile de prueba para la Redwire EconoTAG                                 #
###############################################################################

# Este makefile está escrito para una shell bash
SHELL = /bin/bash

###############################################################################
# Paths y nombres de directorios                                              #
###############################################################################

# Directorio de la toolchain de GNU
TOOLS_PATH = /home/javi9/Documentos/build/bin

###############################################################################
# Herramientas y cadena de desarrollo                                         #
###############################################################################

# Herramientas del sistema
RM            = rm -rf

# Cadena de desarrollo
CROSS_COMPILE = $(TOOLS_PATH)/arm-econotag-elf-
AS            = $(CROSS_COMPILE)as
LD            = $(CROSS_COMPILE)ld
OBJCOPY       = $(CROSS_COMPILE)objcopy
OPENOCD       = $(TOOLS_PATH)/openocd


# Flags
ASFLAGS = -gstabs -mcpu=arm7tdmi -mfpu=softfpa
LDFLAGS = -Teconotag.ld

###############################################################################
# Ficheros                                                                    #
###############################################################################

# Aplicación
PROGNAME = hello
OBJ      = $(PROGNAME).o
ELF      = $(PROGNAME).elf
BIN      = $(PROGNAME).bin

# Detalles de la plataforma
SRAM_BASE = 0x00400000

###############################################################################
# Reglas                                                                      #
###############################################################################

# Construcción
.PHONY: all
all: $(ELF) $(BIN)

$(BIN) : $(ELF)
	$(OBJCOPY) -O binary $< $@

$(ELF) : $(OBJ)
	$(LD) $(LDFLAGS) $< -o $@

%.o : %.s
	$(AS) $(ASFLAGS) $< -o $@

# Ejecución
.PHONY: halt
halt: check_openocd
	@echo "Deteniendo el procesador ..."
	@echo -e "halt" | nc -i 1 localhost 4444 > /dev/null

.PHONY: run
run: $(BIN) check_openocd
	@echo "Ejecutando el programa ..."
	@echo -e "soft_reset_halt\n load_image $(BIN) $(SRAM_BASE)\n resume $(SRAM_BASE)" | nc -i 1 localhost 4444  > /dev/null

# Depuración
.PHONY: openocd
openocd:
	@echo "Lanzando openocd ..."
	@xterm -e "$(OPENOCD) -f interface/redbee-econotag.cfg -f board/redbee.cfg" &
	@sleep 1

.PHONY: check_openocd
check_openocd:
	@if [ ! `pgrep openocd` ]; then make -s openocd; fi

.PHONY: openocd-term
openocd-term: check_openocd
	@echo "Abriendo terminal ..."
	@telnet localhost 4444

# Limpieza
.PHONY: clean
clean:
	$(RM) $(BIN) $(ELF) $(OBJ) *~
