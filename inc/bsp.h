#include "digital.h"
#include <stdint.h>
#include <stdbool.h>

// Creo el struct tipo board
typedef struct board_s{
	digital_output_t led_azul;
	digital_output_t led_rojo;
	digital_output_t led_amarillo;
	digital_output_t led_verde;
	
	digital_input_t boton_prueba;
	digital_input_t boton_cambiar;
	digital_input_t boton_prender;
	digital_input_t boton_apagar;
	
} const * const board_t; //La direccion de memoria del puntero y los almacenado es constante


board_t BoardCreate(void);