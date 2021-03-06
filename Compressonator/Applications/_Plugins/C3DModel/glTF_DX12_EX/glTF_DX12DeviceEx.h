// AMD SampleDX12 sample code
// 
// Copyright(c) 2017 Advanced Micro Devices, Inc.All rights reserved.
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

// #pragma comment(lib,"d3dcompiler.lib")
// #pragma comment(lib,"D3D12.lib")
// #pragma comment(lib,"DX12Util.lib")
// #pragma comment(lib,"glTF.lib")

#define ENABLE_RENDER_CODE

#include "GltfFeatures.h"
#include "FrameworkWindows.h"
#include "Camera.h"
#include "SwapChainDX12.h"

#ifdef ENABLE_RENDER_CODE
#include "glTF_DX12RendererEx.h"
#else
#include "ImguiDX12.h"
#include "GltfPbr.h"
#include "GltfDepthPass.h"
#include "GltfBBoxPass.h"
#endif

#include "PluginManager.h"
#define MAX_NUM_OF_NODES    2

class glTF_DX12RenderEx;
class GLTFCommon;

extern CMIPS *DX12_CMips;
//
// This is the main class, it manages the state of the sample and does all the high level work without touching the GPU directly.
// This class uses the GPU via the the SampleRenderer class. We would have a SampleRenderer instance for each GPU.
//
// This class takes care of:
//
//    - loading a scene (just the CPU data)
//    - updating the camera
//    - keeping track of time
//    - handling the keyboard
//    - updating the animation
//    - building the UI (but do not renders it)
//    - uses the SampleRenderer to update all the state to the GPU and do the rendering
//

// *1* Minimized FrameworkWindows
class glTF_DX12DeviceEx : public FrameworkWindows
{
public:
    void OnCreate(HWND hWnd);
    void OnDestroy();
    void OnRender();
    bool OnEvent(MSG msg);
    void OnResize(DWORD Width, DWORD Height);
    void SetFullScreen(bool fullscreen);

    // *1* marks changes in code from AMDUtils
    HWND                     m_hWnd;
    PluginManager           *m_pluginManager;
    int                      m_curr_Node = 0;
    int                      m_max_Nodes_loaded = 1;
    void                    *m_msghandler;
    DWORD                    m_dwNumberOfBackBuffers;

    void ShowOptions(bool onshow);
    glTF_DX12DeviceEx(GLTFCommon m_gltfLoader[MAX_NUM_OF_NODES], DWORD width, DWORD height, void *pluginManager, void *msghandler);

private:
    // pipeline objects
    ID3D12Device         *m_pDevice;
    SwapChainDX12         m_SwapChain;

    UINT                  m_nodeCount;
    ID3D12CommandQueue  **m_pDirectQueue;

    // *1* change to MAX_NUM_OF_NODES
    GLTFCommon           *m_gltfLoader[MAX_NUM_OF_NODES];


#ifdef ENABLE_RENDER_CODE
    glTF_DX12RendererEx       *m_Node[MAX_NUM_OF_NODES];;
    glTF_DX12RendererEx::State m_state;
#endif

    float                 m_roll;
    float                 m_pitch;

    float                 m_time;             // The elapsed time since the previous frame.
    double                m_deltaTime;        // The elapsed time since the previous frame.
    double                m_lastFrameTime;

#ifdef USE_ANIMATION
    bool                  m_bPlay;
#endif

};
