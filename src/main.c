#include "bsp.h"
#include "digital.h"
#include <stdbool.h>
#include <stddef.h>



int main(void){
    board_t board = BoardCreate();

    while(true){
        if(DigitalInputHasActivated(board->set_time) == true){
            DisplayWriteBCD(board->display, (uint8_t[]){1,1,1,1},4);
            DisplayRefresh(board->display);
        }

        if (DigitalInputHasActivated(board->cancel) == true){
            DisplayWriteBCD(board->display, NULL, 0);
        }

        if(DigitalInputHasActivated(board->set_time)){
    
        }

        if(DigitalInputHasActivated(board->set_alarm)== true){
            DisplayWriteBCD(board->display, (uint8_t[]){0,9,1,2},4);
            DisplayRefresh(board->display);
        }

        if(DigitalInputHasActivated(board->decrement)== true){
            DisplayWriteBCD(board->display, (uint8_t[]){1,2,3,4},4);
            DisplayRefresh(board->display);
        }

        if(DigitalInputHasActivated(board->increment)){
            DisplayWriteBCD(board->display, (uint8_t[]){5,6,7,8},4);
            DisplayRefresh(board->display);
        }

       DisplayRefresh(board->display);
    }
}