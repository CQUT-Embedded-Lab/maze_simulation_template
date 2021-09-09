#include "interface.h"

#define uchar unsigned char
#define SIZE 8
typedef struct {
    uchar x;
    uchar y;
}xyTypeDef;

void init_map(uchar map[SIZE][SIZE]){  // 初始化数组
  uchar i, j;
  for(i=0;i<SIZE;i++){
    for(j=0;j<SIZE;j++){
      map[i][j] = 0xff;
    }
  }
}
uchar abs_to_rel(uchar absD, uchar absD_t){  // 绝对方向->相对方向
  //absD：当前绝对方向
  //absD_t：期望转换到哪个绝对方向
  uchar relD = (absD_t - absD) % 4;
  if(relD > 127)	relD += 4;
  //返回相对方向
  return relD;
}

uchar read_ir(uchar relD){ // 读取相对方向的红外值
  if(relD == 0) return get_ir(3);  // 前红外
  if(relD == 1) return get_ir(5);  // 右红外
  if(relD == 3) return get_ir(1);  // 左红外
  return 0;
}
void collect_info(uchar maze[SIZE][SIZE], xyTypeDef now, uchar absD){ // 记录信息
  if(maze[now.y][now.x] == 0xff){  // 如果当前坐标未被写入，则写入（整个过程中低四位只写入一次）
    uchar val_wall = 0xf0;
    uchar k = 0;
    uchar i;
    for(i=0; i<4; i++){  // 循环判断4个绝对方向
      k = read_ir(abs_to_rel(absD, i));
      val_wall |= (k<<i);
    }
    maze[now.y][now.x] &= val_wall;  // 将墙的信息写入低四位
    maze[now.y][now.x] &= ((absD<<4)|0x0f);  // 将来的方向写入高四位
  }
}

uchar is_path(uchar maze[SIZE][SIZE], xyTypeDef now, uchar absD){ // 判断此方向是否连通
  return !((maze[now.y][now.x]>>absD)&0x01);
}
uchar is_new(uchar maze[SIZE][SIZE], xyTypeDef now, uchar absD){  // 判断此方向是否为新格子
  if(absD==0) return (maze[now.y-1][now.x]>>4)==0x0f;
  if(absD==1) return (maze[now.y][now.x+1]>>4)==0x0f;
  if(absD==2) return (maze[now.y+1][now.x]>>4)==0x0f;
  if(absD==3) return (maze[now.y][now.x-1]>>4)==0x0f;
  return 0;
}
uchar search_dir(uchar maze[SIZE][SIZE], xyTypeDef now, uchar flag){ // 选择方向
  uchar i;
  uchar pre = maze[now.y][now.x] >> 4;
  uchar back;
  if(!flag){ // 冲刺标记位，如果不冲刺，则需要扫描四个方向是否可走
    for(i=0; i<4; i++){
      if(is_path(maze, now, i) && is_new(maze, now, i)){ // 判断该方向是否有墙和是否走过
        return i;
      }
    }
  }
  // 如果冲刺或者四个方向不可走，直接读取高四位进行冲刺引导或回溯
  if(pre<=1) back = pre+2;
  if(pre>=2) back = pre-2;
  return back;
}

void go_to_next(xyTypeDef *now, uchar *absD, uchar absD_t){
  uchar relD = abs_to_rel(*absD, absD_t);
  // 刷新当前坐标和当前绝对方向
  if(absD_t == 0) (now->y)--;
  if(absD_t == 1) (now->x)++;
  if(absD_t == 2) (now->y)++;
  if(absD_t == 3) (now->x)--;
  *absD = absD_t;
  // 执行
  go_rel(relD);
  if(relD != 0)	go_rel(0);
}

uchar bfs(uchar maze[SIZE][SIZE],xyTypeDef beg, xyTypeDef end){ // 广度优先算法
  //参数初始化
  uchar height[SIZE][SIZE] = {0xff};  // 初始化等高表
  xyTypeDef queue_xy[15]; // 初始化队列（经过测试，长度管够）
  uchar queue_len = 1;  // 初始化队列长度标记量
  xyTypeDef queue_head;  // 初始化队头
  uchar j, i;  // 初始化迭代下标
  xyTypeDef temp;  // 初始化一个临时变量
  xyTypeDef now;  // 初始化当前位置

  init_map(height);
  height[beg.y][beg.x] = 0;
  queue_xy[0].x = beg.x;
  queue_xy[0].y = beg.y;
  while(queue_len>0){  // 当队列不为空
    queue_head = queue_xy[0];  // 队首元素出队
    queue_len--;
    for(j=0; j<queue_len; j++){  // （由于用数组模拟队列，所以需要将所有元素手动前移）
      queue_xy[j] = queue_xy[j+1];
    }
    for(i=0; i<4; i++){  // 判断四个方向
      temp = queue_head;
      if(i == 0)  temp.y = queue_head.y-1;
      if(i == 1)  temp.x = queue_head.x+1;
      if(i == 2)  temp.y = queue_head.y+1;
      if(i == 3)  temp.x = queue_head.x-1;
      if(temp.x>127||temp.y>127)  continue;
      if(is_path(maze, queue_head, i) && height[temp.y][temp.x]==255){  // 如果该坐标连通且第一次访问
        height[temp.y][temp.x] = height[queue_head.y][queue_head.x] + 1;  // 该坐标等高表+1
        queue_xy[queue_len++] = temp;  // 该坐标入队
      }
    }
  }

  // 等高表建立完毕，开始反向查找最优路径
  now.x = end.x;
  now.y = end.y;
  while(!(now.x==0&& now.y==0)){  // 如果还没到起点
    for(i=0; i<4; i++){  // 扫描四个方向
      temp = now;
      if(i == 0)  temp.y = now.y-1;
      if(i == 1)  temp.x = now.x+1;
      if(i == 2)  temp.y = now.y+1;
      if(i == 3)  temp.x = now.x-1;
      if(temp.x>127||temp.y>127)  continue;
      if(is_path(maze, now, i) && (height[temp.y][temp.x]==height[now.y][now.x]-1)){  // 如果该坐标连通且高度递减
        maze[temp.y][temp.x] |= 0xf0; // 初始化迷宫数组该坐标的高四位
        maze[temp.y][temp.x] &= ((i<<4)|0x0f);  // 将这个方向写入高四位
        now = temp;  // 切换焦点
        break;
      }
    }
  }
  return 1;
}

int main() {
  uchar maze[SIZE][SIZE] = {0xff}; // 定义迷宫数组，整个迷宫的数据均存储在这里
  uchar absD = 1;	// 定义开始时的绝对方向
  uchar absD_t;		// 定义目标方向（暂无）
  uchar flag = 0;		// 定义冲刺标记量

  xyTypeDef beg;	// 定义起点坐标
  xyTypeDef now;	// 定义当前坐标
  xyTypeDef end;	// 定义终点坐标
  beg.x = 0;
  beg.y = 0;
  now = beg;
  end.x = 7;
  end.y = 7;

  init_map(maze);

  while(1){
    if(now.x==end.x&&now.y==end.y&&flag){ // 如果冲刺完毕，退出程序
      break;
    }
    if(now.x==beg.x&&now.y==beg.y&&absD==3){  // 如果回溯到起点，开始冲刺
      flag = bfs(maze, beg, end);
    }

    collect_info(maze, now, absD);				// （1）记录迷宫信息
    absD_t = search_dir(maze, now, flag);	// （2）确定下一个方向
    go_to_next(&now, &absD, absD_t);			// （3）执行该方向

    display_mazeInfo();
  }
  return 0;
}
