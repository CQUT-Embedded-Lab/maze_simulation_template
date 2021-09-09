#include "interface.h"
#include <stdio.h>

void interface_test(){
  setbuf(stdout, 0);
  int count=0;
  while(count++<100){
    display_mazeInfo();
    printf("front:%d\n", get_ir(3));
    printf("right:%d\n", get_ir(5));
    printf("left:%d\n", get_ir(1));

    fflush(stdin);
    int rel_dir = getc(stdin)-'0';
    go_rel(rel_dir);
  }
}

unsigned char abs_to_rel(unsigned char absD, unsigned char absD_t){
  //absD：当前绝对方向
  //absD_t：期望转换到哪个绝对方向
  unsigned char relD = (absD_t - absD) % 4;
  if(relD > 127)	relD += 4;
  //返回相对方向
  return relD;
}

void test(){
  setbuf(stdout, 0);
  int count=0;
  int now_dir = 1;
  while(count++<100){
    display_mazeInfo();
    printf("front:%d\n", get_ir(3));
    printf("right:%d\n", get_ir(5));
    printf("left:%d\n", get_ir(1));

    fflush(stdin);
    int abs_dir = getc(stdin)-'0';
    if(abs_dir!=now_dir){
      go_rel(abs_to_rel(now_dir, abs_dir));
    }
    go_rel(0);
    now_dir = abs_dir;
  }
}

int main() {
  test();
  interface_test();
  return 0;
}
