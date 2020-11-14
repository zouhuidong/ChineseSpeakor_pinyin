#pragma once
//#include "musicPlayer.h"
// 此处直接将musicPlayer.h放在这里，同时保留了原作者信息：
/************************************************************************
 * 作者 : 悠远的苍穹                                                    *
 * QQ   : 2237505658                                                    *
 * 邮箱 : 2237505658@qq.com                                                *
 * 最后修改  : 2020-8-17                                                *
 * 编译环境  : Visual Studio 2019                                        *
 * EasyX版本 : EasyX 2020-5-20                                            *
 ************************************************************************/

#ifdef _DEBUG
#include <iostream>
#endif

#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <ctime>
#include <cmath>
#include <io.h>
#include <conio.h>
#include <graphics.h>
#include <windows.h>
#include <mmsystem.h>
#include <Digitalv.h>
#pragma comment(lib, "winmm.lib")

using std::wstring;
using std::vector;
using std::array;


/****************************************************************
 * 在 Debug 模式下将显示各种调试信息                            *
 * 在 Release 模式下将不会有任何调试信息                        *
 ****************************************************************/


 /************************************************
  *                class MusicMCI                *
  * 音乐播放操作层                                    *
  * 进行底层音乐播放                                *
  * 暂停，关闭，设置音量，获取播放时间等操作            *
  ************************************************/

class MusicMCI
{
private:
    MCIDEVICEID nDeviceID;                                    // 设备ID

public:
    MusicMCI()noexcept;                                        // 默认构造函数
    virtual ~MusicMCI();                                    // 虚析构函数
    bool open(LPCWSTR music)noexcept;                        // 打开音乐
    bool play()noexcept;                                    // 播放音乐
    bool pause()noexcept;                                    // 暂停音乐
    bool stop()noexcept;                                    // 停止播放
    bool close()noexcept;                                    // 关闭音乐
    bool getCurrentTime(DWORD& pos)noexcept;                // 获取当前播放时间
    bool getTotalTime(DWORD& time)noexcept;                    // 获取音乐总时长
    bool setVolume(size_t volume)noexcept;                    // 设置音量大小
    bool setStartTime(size_t start)noexcept;                // 设置播放位置
};