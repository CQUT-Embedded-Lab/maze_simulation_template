//
// Created by Cause_Hhc on 2021/9/6.
//

#ifndef MAZE_SIMULATION_TEMPLATE_INTERFACE_H
#define MAZE_SIMULATION_TEMPLATE_INTERFACE_H

unsigned char get_ir(unsigned char num);  // 返回从左到右1-5红外值
void go_rel(unsigned char relD);  // 直行0，右转90°1，掉头2，左转90°3
void display_mazeInfo();  // 0北，1东，2南，3西

#endif //MAZE_SIMULATION_TEMPLATE_INTERFACE_H
