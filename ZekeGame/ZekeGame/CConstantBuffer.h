#pragma once
#include "CGPUBuffer.h"

class CConstantBuffer : public CGPUBuffer {
public:
	CConstantBuffer();
	~CConstantBuffer();
	bool Create(const void* pInitData, int bufferSize);
};

