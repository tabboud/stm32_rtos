# User level modifications

PROJECT_NAME 		= blinky
PROJECT_DIR 		= $(CURDIR)
TOOLCHAIN_ROOT 		= /usr/local/Cellar/gcc-arm-none-eabi-48/20131218
TOOLCHAIN_PREFIX 	= arm-none-eabi
FREERTOS  			= $(abspath ../FreeRTOS/Source)
BUILD_DIR 			= $(PROJECT_DIR)/build

###############################################
MKDIR_P = mkdir -p

# Optimization level, can be [0, 1, 2, 3, s].
OPTLVL:=0
DBG:=-g

STARTUP:=$(CURDIR)/hardware
LINKER_SCRIPT:=$(CURDIR)/util/stm32_flash.ld

# Include Paths
APP_INC =  -I.
APP_INC += -I..
APP_INC += -I$(CURDIR)/hardware
APP_INC += -I$(FREERTOS)
APP_INC += -I$(FREERTOS)/include
APP_INC += -I$(FREERTOS)/portable/GCC/ARM_CM4F
APP_INC += -I$(CURDIR)/Libraries/CMSIS/Device/ST/STM32F4xx/Include
APP_INC += -I$(CURDIR)/Libraries/CMSIS/Include
APP_INC += -I$(CURDIR)/Libraries/STM32F4xx_StdPeriph_Driver/inc
APP_INC += -I$(CURDIR)/config


# vpath is used so object files are written to the current directory instead
# of the same directory as their source files
vpath %.c $(CURDIR)/Libraries/STM32F4xx_StdPeriph_Driver/src \
	  $(CURDIR)/Libraries/syscall $(CURDIR)/hardware $(FREERTOS) \
	  $(FREERTOS)/portable/MemMang $(FREERTOS)/portable/GCC/ARM_CM4F 

vpath %.s $(STARTUP)

# Assembly Source Files
# APP_HW_SRC_S
ASRC=startup_stm32f4xx.s

# Util Source Files
# APP_UTIL_SRC_C
SRC+=syscalls.c

# Hardware Source Files
# APP_HW_SRC_C
SRC+=stm32f4xx_it.c
SRC+=system_stm32f4xx.c

# FreeRTOS Source Files
# APP_RTOS_SRC_C
SRC+=croutine.c
SRC+=event_groups.c
SRC+=list.c
SRC+=queue.c
SRC+=tasks.c
SRC+=timers.c
SRC+=port.c
SRC+=heap_4.c

# Standard Peripheral Source Files
# APP_LIB_SRC_C
SRC+=misc.c
SRC+=stm32f4xx_adc.c
SRC+=stm32f4xx_dac.c
SRC+=stm32f4xx_dma.c
SRC+=stm32f4xx_exti.c
SRC+=stm32f4xx_flash.c
SRC+=stm32f4xx_gpio.c
SRC+=stm32f4xx_i2c.c
SRC+=stm32f4xx_rcc.c
SRC+=stm32f4xx_rng.c
SRC+=stm32f4xx_spi.c
SRC+=stm32f4xx_syscfg.c
SRC+=stm32f4xx_tim.c
SRC+=stm32f4xx_usart.c

# Main Source Files
# APP_MAIN_SRC_C
SRC+=main.c
SRC+=mptask.c

CDEFS=-DUSE_STDPERIPH_DRIVER
CDEFS+=-DSTM32F4XX
CDEFS+=-DHSE_VALUE=8000000
CDEFS+=-D__FPU_PRESENT=1
CDEFS+=-D__FPU_USED=1
CDEFS+=-DARM_MATH_CM4

MCUFLAGS=-mcpu=cortex-m4 -mthumb -mfloat-abi=hard
COMMONFLAGS=-O$(OPTLVL) $(DBG) -Wall
CFLAGS=$(COMMONFLAGS) $(MCUFLAGS) $(APP_INC) $(CDEFS)
LDLIBS=$(TOOLCHAIN_ROOT)/arm-none-eabi/lib/armv7e-m/fpu/libc_s.a $(TOOLCHAIN_ROOT)/arm-none-eabi/lib/armv7e-m/fpu/libm.a
LDFLAGS=$(COMMONFLAGS) -fno-exceptions -ffunction-sections -fdata-sections -nostartfiles -Wl,--gc-sections,-T$(LINKER_SCRIPT)

CC 		= $(TOOLCHAIN_PREFIX)-gcc
LD 		= $(TOOLCHAIN_PREFIX)-gcc
AS 		= $(TOOLCHAIN_PREFIX)-as
AR 		= $(TOOLCHAIN_PREFIX)-ar
GDB 	= $(TOOLCHAIN_PREFIX)-gdb
OBJCOPY = $(TOOLCHAIN_PREFIX)-objcopy

OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)

$(BUILD_DIR)/%.o: %.c
	@echo [CC] $(notdir $<)
	@$(CC) $(CFLAGS) $< -c -o $@

all: dir $(OBJ)
	@echo [AS] $(ASRC)
	@$(AS) -o $(ASRC:%.s=$(BUILD_DIR)/%.o) $(STARTUP)/$(ASRC)
	@echo [LD] $(PROJECT_NAME).elf
	@$(CC) -o $(BUILD_DIR)/$(PROJECT_NAME).elf $(LDFLAGS) $(OBJ) $(ASRC:%.s=$(BUILD_DIR)/%.o) $(LDLIBS)
	@echo [OBJCOPY] $(PROJECT_NAME).hex
	@$(OBJCOPY) -O ihex $(BUILD_DIR)/$(PROJECT_NAME).elf $(BUILD_DIR)/$(PROJECT_NAME).hex
	@echo [OBJCOPY] $(PROJECT_NAME).bin
	@$(OBJCOPY) -O binary $(BUILD_DIR)/$(PROJECT_NAME).elf $(BUILD_DIR)/$(PROJECT_NAME).bin

.PHONY: clean

dir:
	$(MKDIR_P) $(BUILD_DIR)

clean:
	@echo [RM] OBJ
	@rm -f $(OBJ)
	@echo [RM] BUILD
	@rm -rf $(BUILD_DIR)

flash:
	@st-flash write $(BUILD_DIR)/$(PROJECT_NAME).bin 0x8000000
