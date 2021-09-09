//
// Created by Cause_Hhc on 2021/9/4.
//

#include "real_driver.h"

//红外传感器组驱动程序
unsigned char HARD_getIr(unsigned char num){
  // TODO
  return 0;
}

//步进电机驱动程序
void HARD_go(unsigned char relD){
  // TODO
}

////红外传感器组驱动程序
//sbit A0 = P4^0;
//sbit A1 = P2^0;
//sbit A2 = P2^7;
//sbit irR1 = P2^1;
//sbit irR2 = P2^2;
//sbit irR3 = P2^3;
//sbit irR4 = P2^4;
//sbit irR5 = P2^5;
//bit irC=0, irL=0, irR=0, irLU=0, irRU=0;
//void init_tim2(uint us){  // 初始化TIM2
//  EA = 1;
//  ET2 = 1;
//  TH2 = RCAP2H = (65536-us)/256;
//  TL2 = RCAP2L = (65536-us)%256;
//  TR2 = 1;
//}
//void ir_on(uchar num){  // 开启第num-1号红外发射级
//  A0 = (num)&0x01;
//  A1 = (num)&0x02;
//  A2 = (num)&0x04;
//}
//uchar get_ir(uchar num){
//  if(num==1) return irL;
//  else if(num==2) return irLU;
//  else if(num==3) return irC;
//  else if(num==4) return irRU;
//  else if(num==5) return irR;
//  else return 0;
//}
//void ir_test(){ // 测试某个方向的红外
//  while(1){
//    if(irL||irR||irC){
//      beep = 0;
//    }else{
//      beep = 1;
//    }
//  }
//}
//void tim2() interrupt 5{ // TIM2中断服务函数
//static bit ir = 0;
//static unsigned char n=1;
//TF2 = 0;
//if(!ir)	{
//ir_on(n-1);
//}else{
//if(n==1){
//if(irR1)	irC=0;
//else			irC=1;
//}else if(n==2){
//if(irR2)	irLU=0;
//else			irLU=1;
//}else if(n==3){
//if(irR3)	irL=0;
//else			irL=1;
//}else if(n==4){
//if(irR4)	irR=0;
//else			irR=1;
//}else if(n==5){
//if(irR5)	irRU=0;
//else			irRU=1;
//}
//}
//if(ir)	n++;
//if(n>5)	n=1;
//ir=~ir;
//}
//
////步进电机驱动程序
//void write_pin(uchar temp){
//  P1 = temp;
//}
//void delay(uint z){  // 延时函数
//  uchar i, j;
//  while(--z){
//    _nop_();
//    i=2;
//    j=199;
//    do{
//      while(--j);
//    }while(--i);
//  }
//}
//uchar forward[]={0x11,0x33,0x22,0x66,0x44,0xcc,0x88,0x99};
//uchar reverse[]={0x11,0x99,0x88,0xcc,0x44,0x66,0x22,0x33};
//uchar for_rev[]={0x11,0x93,0x82,0xc6,0x44,0x6c,0x28,0x39};
//static uint step = 0;
//uchar fix_path(uchar i){  // 路线修正
//  step = 0;
//  while((get_ir(2)||get_ir(4)) && !get_ir(3)){
//    if(get_ir(2))	write_pin(forward[i++] | 0xf0);
//    else if(get_ir(4))	write_pin(reverse[i++] | 0x0f);
//    if(i==8)	i=0;
//    step++;
//    delay(3);
//  }
//  return i;
//}
//void go_rel(uchar relD){  // 向某个相对方向前进一格
//  uchar num;
//  uchar i, j;
//  if(relD == 0) num = 104;
//  if(relD == 1||relD == 3) num = 48;
//  if(relD == 2) num = 100;
//
//  for(j=0;j<num;j++){
//    for(i=0;i<8;i++){
//      if(relD == 1||relD == 2)	write_pin(forward[i]);
//      if(relD == 3)	write_pin(reverse[i]);
//      if(relD == 0){
//        write_pin(for_rev[i]);
//        i = fix_path(i);
//      }
//      if(relD==0)	num -= step/16;
//      delay(3);
//    }
//  }
//}
