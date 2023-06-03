#include "pantalla.h"
#include <string.h>


#ifndef DISPLAY_MAX_DIGITS
#define DISPLAY_MAX_DIGITS 8
#endif

//!< Funcion que borra todos los espacio de memoria de los digitos
#define BorrarDatos(display)\
    memset(display->memory, 0, sizeof(display->memory));

//! Declaracion de datos privada

struct display_s {
    uint8_t digits; //!<Aqui guardo cuanto digitos tengo
    uint8_t active_digit; //!<Aqui guardo cual esta pintado en este momento, para saber cual pintar despeus
    uint8_t memory[DISPLAY_MAX_DIGITS];  //<! Tenemos un uint8_t para cada digito, maximo 8, si tengo menos quedan en blanco
    struct display_driver_s driver[1];   //Puntero a las tres funciones para borrar y pintar 
};

/*No entendi lo de struc display_driver_s driver[1];*/

//! Declaracion de variables privadas

/**
 * @brief Hago un array con los bit que tengo que pintar para cada numero
 * Para esto hago una operacio OR bit a bit con los valores creados para cada segmento
 * 
 */
static const uint8_t IMAGES[] = {
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F,//!< Numero 0
    SEGMENT_B | SEGMENT_C, //!< Numero 1
    SEGMENT_A | SEGMENT_B | SEGMENT_D | SEGMENT_E | SEGMENT_G, //!< Numero 2
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_G, //!< Numero 3
    SEGMENT_B | SEGMENT_C | SEGMENT_F | SEGMENT_G, //!<Numero 4
    SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G, //!< Numero 5
    SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G, //!< Numero 6
    SEGMENT_A | SEGMENT_B | SEGMENT_C, //!< Numero 7
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G, //!< Numero 8
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_F | SEGMENT_G, //!< Numero 9
};


//! Declaracion de funciones privadas
/**
 * @brief Funcion para asignar un espacio de memorio a un display
 * Esta funcion instanciamos un array del tipo display_s
 * @return display_t puntero a la estrctura creada de display_s
 */
static display_t DisplayAllocate(void);





//! Definicion de funciones privadas
static display_t DisplayAllocate(void) {
    static struct display_s instances[1] = {0};
    return &instances[0];
}



//! Definicion de funciones publicas
display_t DisplayCreate(uint8_t digits, display_driver_t driver) {
    
    display_t display = DisplayAllocate();
    if (display) { //!< Verifico que la asignacion de memoria haya sido exitosa
        display->digits = digits;//!<Guardo la cantidad de digitos
        display->active_digit = digits - 1; //!< Le indico que digito activo es el ultimo
        memcpy(display->driver, driver, sizeof(display->driver));//!< Copio todo lo que esta en la memoria del puntero driver en display->driver
        BorrarDatos(display);
        display->driver->ScreenTurnOff();//!< Apago todos los digitos
    }
    return display;
}

void DisplayWriteBCD(display_t display, uint8_t * number, uint8_t size){
    BorrarDatos(display);
    int numero_escribir=0;
    for(int i = 0; i < size || i<= display -> digits ; i++){
        numero_escribir=number[i];
        display->memory[i] = IMAGES[numero_escribir];
    }
}

void DisplayRefresh(display_t display){
    display->driver->ScreenTurnOff(); //Apago los digitos

    //!< Hago circular dividiendo el display activo +1 en el numero de digitos, de esta manera 
    // evito uso una sentencia if u otra 
    display->active_digit = (display->active_digit + 1) % display->digits;

    // Hago uso de la funcion de callback para prender el segmento, para saber que segmentos prender
    // voy a dentro de la memoria de cada digito voy al que esta activo 
    display->driver->SegmentsTurnOn(display->memory[display->active_digit]);

    // Hago algo parecido a la linea anterior de codigo
    display->driver->DigitTurnOn(display->active_digit);
}



 