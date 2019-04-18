#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QLibrary>
//#ifdef Q_WS_WIN
#include "windows.h"
#include "w32api.h"
#include "winuser.h"
#include "mmsystem.h"

//加载多媒体库
QLibrary mylib("Winmm.dll");
//解析游戏杆捕获函数joySetCapture
typedef int (*MyPrototype) (HWND, UINT, UINT, BOOL);
MyPrototype qJoySetCapture = (MyPrototype)mylib.resolve("joySetCapture");
//游戏杆数获得函数
typedef void (*MyPrototype1) (UINT);
MyPrototype1 qJoyReleaseCapture = (MyPrototype1)mylib.resolve("joyReleaseCapture");
//返回游戏杆位置及按钮活动函数
typedef void (*MyPrototype2) (UINT, LPJOYINFOEX);
MyPrototype2 qJoyGetPosEx = (MyPrototype2)mylib.resolve("joyGetPosEx");
//返回游戏杆位置及按钮活动函数
typedef void (*MyPrototype0) (UINT, LPJOYINFO);
MyPrototype0 qJoyGetPos = (MyPrototype0)mylib.resolve("joyGetPos");
//读取操纵杆移动阈值
typedef void (*MyPrototype3) (UINT, LPUINT);
MyPrototype3 qJoyGetThreshold = (MyPrototype3)mylib.resolve("joyGetThreshold");
//获取操纵杆属性信息，以结构体JoyCaps接收
typedef void (*MyPrototype4) (UINT, LPJOYCAPS, UINT);
MyPrototype4 qJoyGetDevCaps = (MyPrototype4)mylib.resolve("joyGetDevCapsW");
//有多少个游戏杆可以用
typedef UINT (*MyPrototype5) (void);
MyPrototype5 qJoyGetNumDevs = (MyPrototype5)mylib.resolve("joyGetNumDevs");


//#endif






#endif // JOYSTICK_H
