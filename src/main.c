

#include "digital.h"
#include "bsp.h"
#include <stdbool.h>
#include <stddef.h>

static board_t board;

int main(void){

    board = BoardCreate();


    while(true){
        if(DigitalInputHasActivate(board->decrement)|DigitalInputHasActivate(board->increment)){
            DisplayWriteBCD(board->display, (uint8_t[]){4,5,6,7},4);
            DisplayRefresh(board->display);
        }
        if(DigitalInputHasActivate(board->accept)){
            DisplayWriteBCD(board->display, (uint8_t[]){0,1,2,3},4);
            DisplayRefresh(board->display);
        }
        
        if (DigitalInputHasActivate(board->cancel)|DigitalInputHasActivate(board->set_alarma)){
            DisplayWriteBCD(board->display, (uint8_t[]){8,9,0,1},4);
            DisplayRefresh(board->display);
        }
        if(DigitalInputHasActivate(board->set_time)){
            DisplayWriteBCD(board->display, (uint8_t[]){0,0,0,0},4);
            DisplayRefresh(board->display);
        }

        DisplayRefresh(board->display);
    }
}
