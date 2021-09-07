# maze_simulation_template
## 一、工程结构
![avatar](./image/1.jpg)
## 二、接口说明
- **unsigned char get_ir(unsigned char num);**
    - Description：获取某编号的红外传感器数值
    - Params：红外传感器编号[1, 5]
    - Return：有墙1，无墙0  
    ![avatar](./image/3.jpg)
- **void go_rel(unsigned char relD);**
    - Description：使小车产生某种动作
    - Params：动作编号[0, 3]，直行0，右转90°1，掉头2，左转90°3
    - Return：void  
    ![avatar](./image/2.jpg)
- **void display_mazeInfo();**
    - Description：输出当前迷宫状态
    - Params：void
    - Return：void  
    ![avatar](./image/4.jpg)