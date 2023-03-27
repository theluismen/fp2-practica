#-------------------------------------------------------------------------------
# OPCIONS PER A GENERAR ELS OBJECTES I EXECUTABLES
#-------------------------------------------------------------------------------
CC		:= gcc
CCFLAGS	:= -Wall -gdwarf-3 -O0 -I./inc
TARGET	:= demo.exe
OBJS	:= ./obj/main.o ./obj/funciones.o ./obj/funciones_propias.o
#-------------------------------------------------------------------------------
# CREAR LOS ARCHIVOS NECESARIOS
#-------------------------------------------------------------------------------
$(TARGET) : ./obj/main.o ./obj/funciones.o ./obj/funciones_propias.o
	$(CC) $(CCFLAGS) $(OBJS) -o $(TARGET)

./obj/%.o : ./src/%.c
	$(CC) $(CCFLAGS) -c $< -o $@

#-------------------------------------------------------------------------------
# CLEAN
#-------------------------------------------------------------------------------
clean :
	@rm -fv $(TARGET) ./obj/*.o
