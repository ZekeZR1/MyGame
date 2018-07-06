#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <math.h>
#include <vector>
#include <list>
#include <D3Dcompiler.h>
#include <Windows.h>
#include <d3d11.h>
#include <map>
#include <functional>
#include <algorithm>

#include "DirectXTK/Inc/Model.h"
#include "DirectXTK/Inc/Effects.h"	
#include "DirectXTK/Inc/CommonStates.h"
#include "DirectXTK/Inc/SpriteFont.h"
#include "DirectXTK/Inc/DDSTextureLoader.h"


#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch\btGhostObject.h"

#include "graphics/GraphicsEngine.h"
#include "math/Matrix.h"
#include "math/kMath.h"
#include "graphics/Sprite/Sprite.h"
#include "graphics/Camera.h"

const float FRAME_BUFFER_W = 1280.0f;				
const float FRAME_BUFFER_H = 720.0f;				