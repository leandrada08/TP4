#include "digital.h"
#include "chip.h"


/** @brief Defino las macros
 * 
*/

#ifndef OUTPUT_INSTANCES

#define OUTPUT_INSTANCES   4 //Si no esta definido, lo defino en 4. Porque esto permite rehusar?

#endif

#ifndef INPUT_INSTANCES

#define INPUT_INSTANCES   4 //Si no esta definido, lo defino en 4. Porque esto permite rehusar?

#endif


struct digital_output_s
{
    uint8_t port;
    uint8_t pin;
    bool allocated:1;
};

struct digital_input_s
{
    uint8_t port;
    uint8_t pin;
    bool inverted:1;  //Analiza si la entrada opera con logicas invertida
    bool allocated:1;
    bool last_state:1; //Ultimo estado reportado
};

//struct alumno_s instancias[50]={0};

/*Declaro funcion para asignar un descriptor al crear una salida digital*/
digital_output_t DigitalOutputAllocated(void);

digital_output_t DigitalOutputAllocated(void){
    digital_output_t output = NULL; //<! Defino una estructura vacia, para devolverla

    static struct digital_output_s instances(OUTPUT_INSTANCES)={0}; //Porque no lo asigno afuera?

    for (int i = 0; i < OUTPUT_INSTANCES; i++)
    {
        if (!instances[i].allocated)//<! Verifico si allocated de instance[i] es = 0
        {
            instances[i].allocate = true;
            output= &instances[i]; //<! Como esta disponible, devuelvo este espacio
            break;
        }
        
    }
    return output
}

/*Declaro funcion para asignar un descriptor al crear una input digital*/
digital_input_t DigitalInputAllocated(void);

digital_input_t DigitalInputAllocated(void){
    digital_input_t input = NULL; //<! Defino una estructura vacia, para devolverla

    static struct digital_input_s instances(INPUT_INSTANCES)={0}; //Porque no lo asigno afuera?

    for (int i = 0; i < INPUT_INSTANCES; i++)
    {
        if (!instances[i].allocated)//<! Verifico si allocated de instance[i] es = 0
        {
            instances[i].allocate = true;
            input= &instances[i]; //<! Como esta disponible, devuelvo este espacio
            break;
        }
        
    }
    return input
}




digital_output_t DigitalOutputCreate(uint8_t port, uint8_t pin){
    digital_input_t output= DigitalOutputAllocated;
    if (output)
    {
        output->port=port;
        output->pin=pin;
        Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port, output->pin, false);
        Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, output->port, output->pin, true);
    }
    return output;
}



void DigitalOutputToggle(digital_output_t output){
    Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, output->port, output->pin);
}


void DigitalOutputActivate(digital_output_t output){
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port , output->pin , true);
}


void DigitalOutputDesactivate(digital_output_t output){
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port , output->pin , false);
}







void DigitalInputGetState(digital_input_t input){
    return input->inverted ^ Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, input->port, input->pin);
} //Osea, tengo que agregarle esta declaracion a todas los return?



/*
Las siguientes funciones no se pueden usar juntas, ya que cada una
actualiza el estado
*/

void DigitalInputHasChange(digital_input_t input){
    bool state = DigitalInputGetState(LPC_GPIO_PORT,input->port,input->pin);
    bool result = state != input->last_state;
    input->last_state=state;
    return result;
}

void DigitalInputHasActivate(digital_input_t input){
    bool state = DigitalInputGetState(LPC_GPIO_PORT,input->port,input->pin);
    bool result = state && !input->last_state;
    input->last_state=state;
    return result;
}


void DigitalInputHasDesactivated(digital_input_t input){
    bool state = DigitalInputGetState(LPC_GPIO_PORT,input->port,input->pin);
    bool result = !state && input->last_state; //Consultar si esta bien, porque el nego ambas
    input->last_state=state;
    return result;
}
