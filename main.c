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

int main() {
  interface_test();
  return 0;
}
