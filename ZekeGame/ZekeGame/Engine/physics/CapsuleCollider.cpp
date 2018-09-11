/*!
* @brief	カプセルコライダー。
*/

#include "stdafx.h"
#include "CapsuleCollider.h"


/*!
* @brief	デストラクタ。
*/
CapsuleCollider::~CapsuleCollider()
{
	delete shape;
}
