# created by Eng Ahmed Sameh in Mastering embedded systems diploma unit 3 lesson 3

#CC stands for C compiler as it is used to change compiler toolchain
CC=arm-none-eabi-
#CFlags means the option used while compiling
CFLAGS=-mcpu=cortex-m3 -mthumb -gdwarf-2
#INCS stands for include as we should include all files in the folders
INCS=-I .
#Libs stands for libraries as it is used to include libraries made before
LIBS=

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
As=$(wildcard *.s)
AsOBJ=$(As:.s=.o)

ProjectName= learn-in-depth_cortexM3


# Add an @ before a command to stop it from being printed
all: $(ProjectName).bin
	@echo '***************Done***************'
	
	
# the 2> log is used to forward error messages into a log file so that the terminal stays clean
# we can't insert comments besides the commands or the target: dependency, comments must be in sperated lines
# %.o meany any file.o, $@ means target file, $< means first dependency file 
%.o: %.s
	$(CC)as.exe $(CFLAGS) $< -o $@ 2> log
	
%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@
	
$(ProjectName).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=Map_file.map
	
$(ProjectName).bin: $(ProjectName).elf
	$(CC)objcopy.exe -O binary $< $@
		
clean_all:
	rm *.o *.elf *.bin
	
clean: 
	rm *.elf *.bin