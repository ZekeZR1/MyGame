#pragma once
#pragma comment(lib, "winmm.lib")

#include <mmsystem.h>
#include <list>
#include "CFONT.h"

using namespace std;

#define FPSCOUNTER_QUERYPER_COUNTER        1
#define FPSCOUNTER_TIMEGETTIME             2

class CFPSCounter
{
private:
	int m_iCounterFlag;                // �g�p����v���֐��̔���t���O
	LARGE_INTEGER m_Counter;           // �N���b�N�J�E���g��
	double m_dFreq;                    // 1�b������N���b�N�J�E���g���i���g���j
	LONGLONG m_OldLongCount;           // �ȑO�̃N���b�N�J�E���g��
	DWORD m_dwTGTOldCount;             // �ȑO�̎����i�~���b�j
	list<double> m_dwDefTimeLst;       // ���ԃ��X�g
	UINT m_uiNum;                      // �ړ����όv�Z���̃f�[�^��
	double m_dwSumTimes;               // ���ʕ����̍��v�l

public:
	CFPSCounter(unsigned int smp = 10);
public:
	virtual ~CFPSCounter(void);

	// FPS�l���擾
	double GetFPS();
	//FPS�l��`��
	void Draw();
	// �T���v������ύX
	void SetSampleNum(unsigned int smp);

protected:
	// ���݂̎������擾
	double GetCurDefTime();

	// FPS���X�V
	double UpdateFPS(double Def);
private:
	//Font
	DirectX::SpriteBatch* pSpriteBatch;
	DirectX::SpriteFont* pSpriteFont;
	wchar_t wfps[256];
	double fps;
};
