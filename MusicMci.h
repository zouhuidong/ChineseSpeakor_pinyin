#pragma once
//#include "musicPlayer.h"
// �˴�ֱ�ӽ�musicPlayer.h�������ͬʱ������ԭ������Ϣ��
/************************************************************************
 * ���� : ��Զ�Ĳ��                                                    *
 * QQ   : 2237505658                                                    *
 * ���� : 2237505658@qq.com                                                *
 * ����޸�  : 2020-8-17                                                *
 * ���뻷��  : Visual Studio 2019                                        *
 * EasyX�汾 : EasyX 2020-5-20                                            *
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
 * �� Debug ģʽ�½���ʾ���ֵ�����Ϣ                            *
 * �� Release ģʽ�½��������κε�����Ϣ                        *
 ****************************************************************/


 /************************************************
  *                class MusicMCI                *
  * ���ֲ��Ų�����                                    *
  * ���еײ����ֲ���                                *
  * ��ͣ���رգ�������������ȡ����ʱ��Ȳ���            *
  ************************************************/

class MusicMCI
{
private:
    MCIDEVICEID nDeviceID;                                    // �豸ID

public:
    MusicMCI()noexcept;                                        // Ĭ�Ϲ��캯��
    virtual ~MusicMCI();                                    // ����������
    bool open(LPCWSTR music)noexcept;                        // ������
    bool play()noexcept;                                    // ��������
    bool pause()noexcept;                                    // ��ͣ����
    bool stop()noexcept;                                    // ֹͣ����
    bool close()noexcept;                                    // �ر�����
    bool getCurrentTime(DWORD& pos)noexcept;                // ��ȡ��ǰ����ʱ��
    bool getTotalTime(DWORD& time)noexcept;                    // ��ȡ������ʱ��
    bool setVolume(size_t volume)noexcept;                    // ����������С
    bool setStartTime(size_t start)noexcept;                // ���ò���λ��
};