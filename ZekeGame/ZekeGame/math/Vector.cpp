#include "stdafx.h"
#include "Vector.h"
#include "Matrix.h"


void CQuaternion::SetRotation(const CMatrix& m)
{
	DirectX::XMStoreFloat4(&vec, DirectX::XMQuaternionRotationMatrix(m));
}

