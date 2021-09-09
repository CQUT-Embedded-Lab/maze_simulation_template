//
// Created by Cause_Hhc on 2021/9/6.
//

#include "interface.h"

unsigned char VENV_getIr(unsigned char num);
void VENV_go(unsigned char relD);
void VENV_display_mazeInfo();

unsigned char get_ir(unsigned char num){
  return VENV_getIr(num);
}

void go_rel(unsigned char relD){
  VENV_go(relD);
}

void display_mazeInfo(){
  VENV_display_mazeInfo();
}
