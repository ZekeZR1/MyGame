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
#include "DirectXTK/Inc/SpriteBatch.h"

#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"

#include "EffekseerRuntime130\src\Effekseer\Effekseer.h"
#include "EffekseerRuntime130\src\EffekseerRendererDX11\EffekseerRendererDX11.h"

#include "math/Vector.h"
#include "math/Matrix.h"
#include "graphics/GraphicsEngine.h"
#include "graphics/Sprite/Sprite.h"
#include "graphics\animation\Animation.h"
#include "graphics/animation/AnimationClip.h"

#include "window\Window.h"
#include "physics/Physics.h"
#include "HID/Pad.h"

#include "graphics/SkinModel.h"
#include "graphics/Skelton.h"
#include "CFONT.h"

#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"
#include "graphics/Camera.h"
#include "GameCamera.h"
#include "IScene.h"
#include "Item\Item.h"
#include "Popup.h"

const float FRAME_BUFFER_W = 1280.0f;				
const float FRAME_BUFFER_H = 720.0f;				
static const int MAX_BONE = 512;
