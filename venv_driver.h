//
// Created by Cause_Hhc on 2021/9/6.
//

#ifndef MAZE_SIMULATION_TEMPLATE_VENV_DRIVER_H
#define MAZE_SIMULATION_TEMPLATE_VENV_DRIVER_H

#include <stdio.h>
#include <stdlib.h>

/* 绝对方向定义：
 *  0
 * 3 1
 *  2
 */

#define START_ROW 0
#define START_COL 0
#define START_DIR 1

unsigned char VENV_getIr(unsigned char num);
void VENV_go(unsigned char relD);
void VENV_display_mazeInfo();
void VENV_test();

#endif //MAZE_SIMULATION_TEMPLATE_VENV_DRIVER_H
