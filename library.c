//
// Created by Cause_Hhc on 2021/9/4.
//

#include "library.h"

static int now_row = START_ROW;
static int now_col = START_COL;
static int now_dir = START_DIR;

static char maze_array[17][17] = {
        "*****************",
        "*ooooo*ooooooo*o*",
        "*****o*****o*o*o*",
        "*ooooooooooo*o*o*",
        "*o***o*******o*o*",
        "*o*ooooooooooooo*",
        "*o*****o***o*****",
        "*o*ooooooooooooo*",
        "*o*****o*****o*o*",
        "*ooooo*ooooo*o*o*",
        "*****o*o*****o*o*",
        "*ooooooooooo*o*o*",
        "*o*o*****o*o*o***",
        "*o*o*ooooo*ooooo*",
        "*o*o*****o*o*****",
        "*o*ooooooo*ooooo*",
        "*****************"
};

void VENV_display_mazeInfo(){
  for(int i=0; i<17; i++){
    for(int j=0; j<17; j++){
      if(now_row==i/2 && now_col==j/2 && i%2 && j%2) {
        printf("%d ", now_dir);
      }else if(maze_array[i][j]=='*') {
        printf("N ");
      }else if(maze_array[i][j]=='o') {
        printf("  ");
      }
    }
    printf("\n");
  }
  printf("\n");
}

void VENV_display_irInfo(){
  printf("front:%d\n", VENV_getIr(3));
  printf("right:%d\n", VENV_getIr(5));
  printf("left:%d\n", VENV_getIr(1));
}

static unsigned char rel_to_abs(unsigned char absD, unsigned char relD){  // 绝对方向->相对方向
  unsigned char absD_t = (absD+relD) % 4;
  return absD_t;
}

unsigned char VENV_getIr(unsigned char num){
  unsigned char relD=2;
  if(num==3){  // 前红外
    relD = 0;
  }else if(num == 5){  // 右红外
    relD = 1;
  }else if(num == 1){  // 左红外
    relD = 3;
  }
  unsigned char absD = rel_to_abs(now_dir, relD);
  char res = 0;
  if(absD==0){
    res = maze_array[now_row*2][now_col*2+1];
  }else if(absD==1){
    res = maze_array[now_row*2+1][now_col*2+2];
  }else if(absD==2){
    res = maze_array[now_row*2+2][now_col*2+1];
  }else if(absD==3){
    res = maze_array[now_row*2+1][now_col*2];
  }
  if(res=='*'){
    return 1;
  } else{
    return 0;
  }
}

void VENV_go(unsigned char relD){
  unsigned char absD = rel_to_abs(now_dir, relD);
  if(absD != now_dir){
    now_dir = absD;
  } else{
    int d_row=0, d_col=0;
    char res = 0;
    if(absD==0){
      d_row = -1;
      res = maze_array[now_row*2][now_col*2+1];
    }else if(absD==1){
      d_col = 1;
      res = maze_array[now_row*2+1][now_col*2+2];
    }else if(absD==2){
      d_row = 1;
      res = maze_array[now_row*2+2][now_col*2+1];
    }else if(absD==3){
      d_col = -1;
      res = maze_array[now_row*2+1][now_col*2];
    }
    if(res=='*'){
      printf("No way!\n");
    } else{
      now_row += d_row;
      now_col += d_col;
      now_dir = absD;
    }
  }
}

void VENV_test(){
  setbuf(stdout, 0);
  VENV_display_mazeInfo();
  VENV_display_irInfo();
  while(1){
    fflush(stdin);
    int input = getc(stdin);
    VENV_go(input-'0');
    VENV_display_mazeInfo();
    VENV_display_irInfo();
  }
}