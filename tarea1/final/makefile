#Makefile de menu

# Tarea 1 - Sistemas Operativos
# Ricardo Churion, carnet:11-10200
# Douglas Torres, carnet:11-11027

menu: menu.o funciones.o
      :gcc menu.o funciones.o -o menu
menu.o: menu.c menu.h funciones.h
      :gcc -c menu.c
funciones.o: funciones.c funciones.h
      :gcc -c funciones.c