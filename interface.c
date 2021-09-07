//
// Created by Cause_Hhc on 2021/9/6.
//

#include "interface.h"
#include "real_driver.h"
#include "venv_driver.h"

unsigned char get_ir(unsigned char num){
  return VENV_getIr(num);
//  return HARD_getIr(num);
}

void go_rel(unsigned char relD){
  VENV_go(relD);
//  HARD_go(relD);
}

void display_mazeInfo(){
  VENV_display_mazeInfo();
}
