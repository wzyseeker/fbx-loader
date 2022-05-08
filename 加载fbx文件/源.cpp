/*
    Demo Name:  Box
    Author:  Allen Sherrod
    Chapter:  Ch 1
*/

#include"工具代码\d3dx12.h"
#include<windowsx.h>
#include<DirectXMath.h>
#include<DirectXColors.h>
#include<D3Dcompiler.h>
#include<dxgi1_6.h>
#include<crtdbg.h>
#include<wrl.h>
#include<string>
#include<vector>
#include<crtdbg.h>
#include"工具代码\自由相机.h"
#include"工具代码\DDSTextureLoader.h"
#include"工具代码\按键检测.h"
#include"工具代码\共享资源.h"
#include"fbx模型加载源代码\fbx模型加载.h"
#include"工具代码\描述符堆管理.h"
#include"工具代码\物体管理.h"

#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")

using namespace DirectX;
using namespace std;
using namespace Microsoft::WRL;
using namespace DirectX::Colors;

#ifndef ThrowIfFailed
#define ThrowIfFailed(x)				\
{										\
    if(FAILED(x)) { OutPutError(__LINE__); }	\
}
#endif

void OutPutError(int line)
{
	WCHAR buffer[512];
	MultiByteToWideChar(CP_ACP, 0, __FILE__, -1, buffer, 512);

	wstring wfn = buffer;
	wfn += L" line:" + to_wstring(line) + L" ";
	OutputDebugStringW(wfn.c_str());
}

HWND mhMainWnd = nullptr; // main window handle
wstring mMainWndCaption = L"Box";

int mClientWidth = 800;
int mClientHeight = 600;

ComPtr<IDXGIFactory4> mdxgiFactory;
ComPtr<ID3D12Device> md3dDevice;
ComPtr<ID3D12Fence> mFence;
ComPtr<ID3D12CommandQueue> mCommandQueue;
ComPtr<ID3D12CommandAllocator> mDirectCmdListAlloc;
ComPtr<ID3D12GraphicsCommandList> mCommandList;
ComPtr<IDXGISwapChain> mSwapChain;
ComPtr<ID3D12DescriptorHeap> mRtvHeap;
ComPtr<ID3D12DescriptorHeap> mDsvHeap;
ComPtr<ID3D12RootSignature> mRootSignature[2];
ComPtr<ID3D12PipelineState> mPSO[2];
const int SwapChainBufferCount = 2;
ComPtr<ID3D12Resource> mSwapChainBuffer[SwapChainBufferCount];
ComPtr<ID3D12Resource> mDepthStencilBuffer;

D3D12_VIEWPORT mScreenViewport;
D3D12_RECT mScissorRect;
HANDLE m_fenceEvent;

int mCurrBackBuffer = 0;
bool      m4xMsaaState = false;    // 4X MSAA enabled
UINT      m4xMsaaQuality = 0;      // quality level of 4X MSAA

ComPtr<ID3DBlob> mvsByteCode[2];
ComPtr<ID3DBlob> mpsByteCode[2];

UINT mRtvDescriptorSize = 0;
UINT mDsvDescriptorSize = 0;
UINT mCbvSrvUavDescriptorSize = 0;

vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout[2];

DXGI_FORMAT mBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
DXGI_FORMAT mDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

UINT64 mCurrentFence = 0;

XMMATRIX mWorld = XMMatrixIdentity();
XMMATRIX mView = XMMatrixIdentity();
XMMATRIX mProj = XMMatrixIdentity();

ComPtr<ID3D12Resource> VertexBufferGPU;
ComPtr<ID3D12Resource> IndexBufferGPU;
ComPtr<ID3D12Resource> VertexBufferUploader;
ComPtr<ID3D12Resource> IndexBufferUploader;

UINT VertexByteStride = 0;
UINT VertexBufferByteSize = 0;
DXGI_FORMAT IndexFormat = DXGI_FORMAT_R16_UINT;
UINT IndexBufferByteSize = 0;
UINT IndexCount;

struct SCBUFFER
{
	XMMATRIX gViewProj;
	XMFLOAT4 gEyePosW;
	S方向光源 gDlight;
};

struct SUBUFFER
{
	XMMATRIX gWorld;
	S材质 gMat;
};

struct SCBUFFER2
{
	S方向光源 gDlight;
	XMMATRIX gViewProj;
	XMFLOAT4 gEyePosW;
};

struct SUBUFFER2
{
	S材质 gMat;
	XMMATRIX gBoneTransform[256];
};

struct SUBUFFER3
{
	XMMATRIX gWorld;
	XMMATRIX gObj;
};

SCBUFFER cbuffer;
SUBUFFER ubuffer;
SCBUFFER2 cbuffer2;
SUBUFFER2 ubuffer2;
ComPtr<ID3D12Resource> cbuffer2Upload;
ComPtr<ID3D12Resource> ubuffer2Upload;
BYTE* mMappedDatacb2 = nullptr;
BYTE* mMappedDataub2 = nullptr;
SUBUFFER3 ubuffer3;

C按键检测 按键检测;
C第三人称相机* 相机;
C共享资源* 共享资源;
C描述符堆管理* 描述符堆管理;
C物体管理* 物体管理;

LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool InitDirect3D();
void LogAdapters();
void LogAdapterOutputs(IDXGIAdapter* adapter);
void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);
void CreateCommandObjects();
void CreateSwapChain();
void CreateRtvAndDsvDescriptorHeaps();
void BuildRootSignature();
void BuildShadersAndInputLayout();
void BuildConstantBuffers();
UINT CalcConstantBufferByteSize(UINT byteSize);
void BuildBoxGeometry();
ComPtr<ID3D12Resource> CreateDefaultBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList, const void* initData,
	UINT byteSize, ComPtr<ID3D12Resource>& uploadBuffer);
void BuildPSO();
void FlushCommandQueue();
float CalculateFrameStatsAndTime();
void OnResize();
void SetUp();
void Update(float dt);
void Draw(float dt);
void Distory();

void BuildInitResource();
void BuildModel();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	MSG msg = { 0 };

	WNDCLASS wc{};
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MsgProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"MainWnd";

	if (!RegisterClass(&wc))
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return false;
	}

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT R = { 0, 0, mClientWidth, mClientHeight };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width = R.right - R.left;
	int height = R.bottom - R.top;

	mhMainWnd = CreateWindow(L"MainWnd", mMainWndCaption.c_str(),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, hInstance, 0);
	if (!mhMainWnd)
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return false;
	}

	ShowWindow(mhMainWnd, SW_SHOW);
	UpdateWindow(mhMainWnd);

	InitDirect3D();

	while (msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// Otherwise, do animation/game stuff.
		else
		{
			float dt = CalculateFrameStatsAndTime();
			Update(dt);
			Draw(dt);
		}
	}

	Distory();

	return 0;
}

LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		按键检测.鼠标位移.x = GET_X_LPARAM(lParam);
		按键检测.鼠标位移.y = GET_Y_LPARAM(lParam);
		按键检测.鼠标位置.x = GET_X_LPARAM(lParam);
		按键检测.鼠标位置.y = GET_Y_LPARAM(lParam);
		return 0;

		// WM_ACTIVATE is sent when the window is activated or deactivated.  
		// We pause the game when the window is deactivated and unpause it 
		// when it becomes active.  
	case WM_ACTIVATE:

		return 0;

		// WM_SIZE is sent when the user resizes the window.  
	case WM_SIZE:

		return 0;

		// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
	case WM_ENTERSIZEMOVE:

		return 0;

		// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
		// Here we reset everything based on the new window dimensions.
	case WM_EXITSIZEMOVE:

		OnResize();
		return 0;

		// WM_DESTROY is sent when the window is being destroyed.
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

		// The WM_MENUCHAR message is sent when a menu is active and the user presses 
		// a key that does not correspond to any mnemonic or accelerator key. 
	case WM_MENUCHAR:
		// Don't beep when we alt-enter.
		return MAKELRESULT(0, MNC_CLOSE);

		// Catch this message so to prevent the window from becoming too small.
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
		return 0;

	case WM_KILLFOCUS:
		按键检测.归零开关状态();
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SHIFT:
			按键检测.键shift状态 = 1;
			break;

		case VK_SPACE:
			按键检测.键space状态 = 1;
			break;

		case VK_RETURN:
			按键检测.键enter状态 = 1;
			break;

		case VK_ESCAPE:
			按键检测.键escape状态 = 1;
			break;

		case 'W':
			按键检测.键W状态 = 1;
			break;

		case 'S':
			按键检测.键S状态 = 1;
			break;

		case 'D':
			按键检测.键D状态 = 1;
			break;

		case 'A':
			按键检测.键A状态 = 1;
			break;

		case 'Q':
			按键检测.键Q状态 = 1;
			break;

		case 'E':
			按键检测.键E状态 = 1;
			break;

		case 'R':
			按键检测.键R状态 = 1;
			break;

		case 'F':
			按键检测.键F状态 = 1;
			break;

		case 'X':
			按键检测.键X状态 = 1;
			break;

		case 'Z':
			按键检测.键Z状态 = 1;
			break;

		case '1':
			按键检测.键1状态 = 1;
			break;

		case '2':
			按键检测.键2状态 = 1;
			break;

		case '3':
			按键检测.键3状态 = 1;
			break;

		case '4':
			按键检测.键4状态 = 1;
			break;

		case '5':
			按键检测.键5状态 = 1;
			break;

		case '6':
			按键检测.键6状态 = 1;
			break;

		case '7':
			按键检测.键7状态 = 1;
			break;

		case '8':
			按键检测.键8状态 = 1;
			break;
		}
		return 0;

	case WM_KEYUP:
		switch (wParam)
		{
		case VK_SHIFT:
			按键检测.键shift状态 = 0;
			break;

		case VK_SPACE:
			按键检测.键space状态 = 0;
			break;

		case VK_RETURN:
			按键检测.键enter状态 = 0;
			break;

		case VK_ESCAPE:
			按键检测.键escape状态 = 0;
			PostQuitMessage(0);
			break;

		case 'W':
			按键检测.键W状态 = 0;
			break;

		case 'S':
			按键检测.键S状态 = 0;
			break;

		case 'D':
			按键检测.键D状态 = 0;
			break;

		case 'A':
			按键检测.键A状态 = 0;
			break;

		case 'Q':
			按键检测.键Q状态 = 0;
			break;

		case 'E':
			按键检测.键E状态 = 0;
			break;

		case 'R':
			按键检测.键R状态 = 0;
			break;

		case 'F':
			按键检测.键F状态 = 0;
			break;

		case 'X':
			按键检测.键X状态 = 0;
			break;

		case 'Z':
			按键检测.键Z状态 = 0;
			break;

		case '1':
			按键检测.键1状态 = 0;
			break;

		case '2':
			按键检测.键2状态 = 0;
			break;

		case '3':
			按键检测.键3状态 = 0;
			break;

		case '4':
			按键检测.键4状态 = 0;
			break;

		case '5':
			按键检测.键5状态 = 0;
			break;

		case '6':
			按键检测.键6状态 = 0;
			break;

		case '7':
			按键检测.键7状态 = 0;
			break;

		case '8':
			按键检测.键8状态 = 0;
			break;
		}
		return 0;

	case WM_MOUSEMOVE:
		按键检测.鼠标位移.x = 按键检测.鼠标位置.x - GET_X_LPARAM(lParam);
		按键检测.鼠标位移.y = 按键检测.鼠标位置.y - GET_Y_LPARAM(lParam);
		按键检测.鼠标位置.x = GET_X_LPARAM(lParam);
		按键检测.鼠标位置.y = GET_Y_LPARAM(lParam);
		按键检测.鼠标边界状态 = 0;

		if (按键检测.鼠标位置.x > mClientWidth - 5 || 按键检测.鼠标位置.x < 4
			|| 按键检测.鼠标位置.y > mClientHeight - 5 || 按键检测.鼠标位置.y < 4)
		{
			按键检测.鼠标位移.x = 按键检测.鼠标位置.x - mClientWidth / 2;
			按键检测.鼠标位移.y = 按键检测.鼠标位置.y - mClientHeight / 2;
			按键检测.鼠标边界状态 = 1;
		}
		return 0;

	case WM_MOUSEWHEEL:
		按键检测.鼠标滑轮状态 = GET_WHEEL_DELTA_WPARAM(wParam);
		return 0;

	case WM_LBUTTONDOWN:
		按键检测.鼠标左键状态 = 1;
		return 0;

	case WM_LBUTTONUP:
		按键检测.鼠标左键状态 = 0;
		return 0;

	case WM_MBUTTONDOWN:
		按键检测.鼠标中键状态 = 1;
		return 0;

	case WM_MBUTTONUP:
		按键检测.鼠标中键状态 = 0;
		return 0;

	case WM_RBUTTONDOWN:
		按键检测.鼠标右键状态 = 1;
		return 0;

	case WM_RBUTTONUP:
		按键检测.鼠标右键状态 = 0;

		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

bool InitDirect3D()
{
#if defined(DEBUG) || defined(_DEBUG) 
	// Enable the D3D12 debug layer.
	{
		ComPtr<ID3D12Debug> debugController;  //启用调试层
		ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));  //获取调试接口
		debugController->EnableDebugLayer();  //启用调试层
	}
#endif

	ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&mdxgiFactory)));  //创建dxgi对象

	ComPtr<IDXGIAdapter> pAdapter;
	ThrowIfFailed(mdxgiFactory->EnumAdapters(0, &pAdapter));  //提供适配器

	ThrowIfFailed(D3D12CreateDevice(
		pAdapter.Get(),  //获取显卡信息
		D3D_FEATURE_LEVEL_12_0,
		IID_PPV_ARGS(&md3dDevice)));

	ThrowIfFailed(md3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE,  //创建栅格对象
		IID_PPV_ARGS(&mFence)));

	mRtvDescriptorSize = md3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);  //获取堆增量大小 渲染目标
	mDsvDescriptorSize = md3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);  //深度模板视图
	mCbvSrvUavDescriptorSize = md3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);  //常量缓冲区

	// Check 4X MSAA quality support for our back buffer format.  
	// All Direct3D 11 capable devices support 4X MSAA for all render 
	// target formats, so we only need to check quality support.
	//检查4X MSAA对我们的后缓冲格式的质量支持。
	//所有Direct3D 11功能设备支持4X MSAA的所有渲染
	//目标格式，所以我们只需要检查质量支持。

	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msQualityLevels;  //描述样本计数多重采用级别
	msQualityLevels.Format = mBackBufferFormat;  //显示格式
	msQualityLevels.SampleCount = 4;  //采样次数
	msQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;  //不支持选项
	msQualityLevels.NumQualityLevels = 0;  //质量等级
	ThrowIfFailed(md3dDevice->CheckFeatureSupport(  //获取图形驱动器支持功能信息
		D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS,  //查询样本数量和质量信息
		&msQualityLevels,
		sizeof(msQualityLevels)));

#ifdef _DEBUG
	LogAdapters();
#endif

	CreateCommandObjects();
	CreateSwapChain();
	CreateRtvAndDsvDescriptorHeaps();

	m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	if (m_fenceEvent == nullptr)
	{
		ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
	}

	// Reset the command list to prep for initialization commands.
	ThrowIfFailed(mCommandList->Reset(mDirectCmdListAlloc.Get(), nullptr));

	BuildInitResource();
	BuildConstantBuffers();
	BuildRootSignature();  //构建根签名
	BuildShadersAndInputLayout();  //构建着色器后输入布局
	BuildBoxGeometry();  //构建框的几何
	BuildPSO();  //构建算法

	// Execute the initialization commands.
	ThrowIfFailed(mCommandList->Close());
	ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
	mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);  //执行命令队列

	// Wait until initialization is complete.
	FlushCommandQueue();  //清除命令队列

	//初始化调整代码。
	OnResize();
	SetUp();

	return true;
}

void LogAdapters()
{
	UINT i = 0;
	IDXGIAdapter* adapter = nullptr;
	std::vector<IDXGIAdapter*> adapterList;
	while (mdxgiFactory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_ADAPTER_DESC desc;
		adapter->GetDesc(&desc);

		std::wstring text = L"***Adapter: ";
		text += desc.Description;
		text += L"\n";

		OutputDebugString(text.c_str());

		adapterList.push_back(adapter);

		++i;
	}

	for (size_t i = 0; i < adapterList.size(); ++i)
	{
		LogAdapterOutputs(adapterList[i]);
		adapterList[i]->Release();
	}
}

void LogAdapterOutputs(IDXGIAdapter* adapter)
{
	UINT i = 0;
	IDXGIOutput* output = nullptr;
	while (adapter->EnumOutputs(i, &output) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_OUTPUT_DESC desc;
		output->GetDesc(&desc);

		std::wstring text = L"***Output: ";
		text += desc.DeviceName;
		text += L"\n";
		OutputDebugString(text.c_str());

		LogOutputDisplayModes(output, mBackBufferFormat);

		output->Release();

		++i;
	}
}

void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format)
{
	UINT count = 0;
	UINT flags = 0;

	// Call with nullptr to get list count.
	output->GetDisplayModeList(format, flags, &count, nullptr);

	std::vector<DXGI_MODE_DESC> modeList(count);
	output->GetDisplayModeList(format, flags, &count, &modeList[0]);

	for (auto& x : modeList)
	{
		UINT n = x.RefreshRate.Numerator;
		UINT d = x.RefreshRate.Denominator;
		std::wstring text =
			L"Width = " + std::to_wstring(x.Width) + L" " +
			L"Height = " + std::to_wstring(x.Height) + L" " +
			L"Refresh = " + to_wstring((float)n / d) + L"\n";

		::OutputDebugString(text.c_str());
	}
}

void BuildInitResource()
{
	相机 = new C第三人称相机(&按键检测, XM_PI / 2, XM_PI, 40.0f, 0.3f, 0.002f, 0.05f, XMVECTOR{ 0.0f, 0.0f, 0.0f, 0.0f });
	共享资源 = new C共享资源(md3dDevice, mCommandList);
	共享资源->加载贴图();
	描述符堆管理 = new C描述符堆管理(md3dDevice, 共享资源);
	物体管理 = new C物体管理(md3dDevice, mCommandList, 共享资源, 描述符堆管理);

	cbuffer.gDlight.颜色 = { 0.5f, 0.5f, 0.5f, 1.0f };
	cbuffer.gDlight.方向 = { 0.0f, -1.0f, 1.0f, 1.0f };

	cbuffer2.gDlight.颜色 = { 0.2f, 0.2f, 0.2f, 1.0f };
	cbuffer2.gDlight.方向 = { 0.0f, -1.0f, 1.0f, 1.0f };

	BuildModel();
}

void CreateCommandObjects()
{
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	ThrowIfFailed(md3dDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&mCommandQueue)));

	ThrowIfFailed(md3dDevice->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(mDirectCmdListAlloc.GetAddressOf())));

	ThrowIfFailed(md3dDevice->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		mDirectCmdListAlloc.Get(), // Associated command allocator
		nullptr,                   // Initial PipelineStateObject
		IID_PPV_ARGS(mCommandList.GetAddressOf())));

	// Start off in a closed state.  This is because the first time we refer 
	// to the command list we will Reset it, and it needs to be closed before
	// calling Reset.
	mCommandList->Close();
}

void CreateSwapChain()
{
	// Release the previous swapchain we will be recreating.
	mSwapChain.Reset();

	DXGI_SWAP_CHAIN_DESC sd{};
	sd.BufferDesc.Width = mClientWidth;
	sd.BufferDesc.Height = mClientHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = mBackBufferFormat;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = m4xMsaaState ? 4 : 1;
	sd.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 2;
	sd.OutputWindow = mhMainWnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH | DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;

	// Note: Swap chain uses queue to perform flush.
	ThrowIfFailed(mdxgiFactory->CreateSwapChain(
		mCommandQueue.Get(),
		&sd,
		mSwapChain.GetAddressOf()));
}

void CreateRtvAndDsvDescriptorHeaps()
{
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
	rtvHeapDesc.NumDescriptors = 2;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtvHeapDesc.NodeMask = 0;
	ThrowIfFailed(md3dDevice->CreateDescriptorHeap(
		&rtvHeapDesc, IID_PPV_ARGS(mRtvHeap.GetAddressOf())));


	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc;
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	dsvHeapDesc.NodeMask = 0;
	ThrowIfFailed(md3dDevice->CreateDescriptorHeap(
		&dsvHeapDesc, IID_PPV_ARGS(mDsvHeap.GetAddressOf())));
}

void BuildRootSignature()
{
	//着色程序通常需要资源作为输入(常量缓冲，
	//纹理采样)。根签名定义了着色器中的资源
	//程序。如果我们把着色程序看作一个函数，那么
	//将输入资源作为函数参数，则根签名即可
	//可以看作是定义函数签名。
	CD3DX12_DESCRIPTOR_RANGE texTable;
	texTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);

	// 根参数可以是表、根描述符或根常量。
	CD3DX12_ROOT_PARAMETER slotRootParameter[3];

	slotRootParameter[0].InitAsConstants(sizeof(SCBUFFER) / 4, 0);
	slotRootParameter[1].InitAsConstants(sizeof(SUBUFFER) / 4, 1);
	slotRootParameter[2].InitAsDescriptorTable(1, &texTable);

	CD3DX12_STATIC_SAMPLER_DESC linearWrap(
		0, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW

	// A root signature is an array of root parameters.
	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(3, slotRootParameter, 1, &linearWrap,
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	// create a root signature with a single slot which points to a descriptor range consisting of a single constant buffer
	ComPtr<ID3DBlob> serializedRootSig = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1_0,
		serializedRootSig.GetAddressOf(), errorBlob.GetAddressOf());

	if (errorBlob != nullptr)
	{
		OutputDebugStringA((char*)errorBlob->GetBufferPointer());
	}
	ThrowIfFailed(hr);

	ThrowIfFailed(md3dDevice->CreateRootSignature(
		0,
		serializedRootSig->GetBufferPointer(),
		serializedRootSig->GetBufferSize(),
		IID_PPV_ARGS(&mRootSignature[0])));

	//着色程序通常需要资源作为输入(常量缓冲，
	//纹理采样)。根签名定义了着色器中的资源
	//程序。如果我们把着色程序看作一个函数，那么
	//将输入资源作为函数参数，则根签名即可
	//可以看作是定义函数签名。
	CD3DX12_DESCRIPTOR_RANGE texTable2;
	texTable2.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);

	// 根参数可以是表、根描述符或根常量。
	CD3DX12_ROOT_PARAMETER slotRootParameter2[4];

	slotRootParameter2[0].InitAsConstantBufferView(0);
	slotRootParameter2[1].InitAsConstantBufferView(1);
	slotRootParameter2[2].InitAsDescriptorTable(1, &texTable2);
	slotRootParameter2[3].InitAsConstants(sizeof(SUBUFFER3) / 4, 2);

	// A root signature is an array of root parameters.
	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc2(4, slotRootParameter2, 1, &linearWrap,
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	serializedRootSig = nullptr;
	errorBlob = nullptr;

	// create a root signature with a single slot which points to a descriptor range consisting of a single constant buffer
	hr = D3D12SerializeRootSignature(&rootSigDesc2, D3D_ROOT_SIGNATURE_VERSION_1_0,
		serializedRootSig.GetAddressOf(), errorBlob.GetAddressOf());

	if (errorBlob != nullptr)
	{
		OutputDebugStringA((char*)errorBlob->GetBufferPointer());
	}
	ThrowIfFailed(hr);

	ThrowIfFailed(md3dDevice->CreateRootSignature(
		0,
		serializedRootSig->GetBufferPointer(),
		serializedRootSig->GetBufferSize(),
		IID_PPV_ARGS(&mRootSignature[1])));
}

void BuildShadersAndInputLayout()
{
	UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
	compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ComPtr<ID3DBlob> errors;
	D3DCompileFromFile(L"光源.hlsl", 0, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"VS", "vs_5_0", compileFlags, 0, &mvsByteCode[0], &errors);
	if (errors != nullptr)
		OutputDebugStringA((char*)errors->GetBufferPointer());

	D3DCompileFromFile(L"光源.hlsl", 0, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"PS", "ps_5_0", compileFlags, 0, &mpsByteCode[0], &errors);
	if (errors != nullptr)
		OutputDebugStringA((char*)errors->GetBufferPointer());

	D3DCompileFromFile(L"骨骼动画.hlsl", 0, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"VSSpot", "vs_5_0", compileFlags, 0, &mvsByteCode[1], &errors);
	if (errors != nullptr)
		OutputDebugStringA((char*)errors->GetBufferPointer());

	D3DCompileFromFile(L"骨骼动画.hlsl", 0, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"PSSpot", "ps_5_0", compileFlags, 0, &mpsByteCode[1], &errors);
	if (errors != nullptr)
		OutputDebugStringA((char*)errors->GetBufferPointer());

	mInputLayout[0] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};

	mInputLayout[1] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "WEIGHT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "BONEINDEX", 0, DXGI_FORMAT_R32G32B32A32_UINT, 0, 44, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};
}

void BuildBoxGeometry()
{

}

void BuildConstantBuffers()
{
	D3D12_HEAP_PROPERTIES HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC Desc = CD3DX12_RESOURCE_DESC::Buffer(CalcConstantBufferByteSize(sizeof(SCBUFFER2)));
	ThrowIfFailed(md3dDevice->CreateCommittedResource(
		&HeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&Desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&cbuffer2Upload)));

	HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	Desc = CD3DX12_RESOURCE_DESC::Buffer(CalcConstantBufferByteSize(sizeof(SUBUFFER2)));
	ThrowIfFailed(md3dDevice->CreateCommittedResource(
		&HeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&Desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&ubuffer2Upload)));
}

UINT CalcConstantBufferByteSize(UINT byteSize)
{
	//常数缓冲区必须是最小硬件的倍数
	//分配大小(通常为256字节)。所以四舍五入到最接近的数
	return (byteSize + 255) & ~255;
}

ComPtr<ID3D12Resource> CreateDefaultBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList, const void* initData,
	UINT byteSize, ComPtr<ID3D12Resource>& uploadBuffer)
{
	ComPtr<ID3D12Resource> defaultBuffer;

	// Create the actual default buffer resource.
	D3D12_HEAP_PROPERTIES pHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	D3D12_RESOURCE_DESC pDesc = CD3DX12_RESOURCE_DESC::Buffer(byteSize);
	ThrowIfFailed(device->CreateCommittedResource(
		&pHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&pDesc,
		D3D12_RESOURCE_STATE_COMMON,
		nullptr,
		IID_PPV_ARGS(&defaultBuffer)));

	// In order to copy CPU memory data into our default buffer, we need to create
	// an intermediate upload heap. 
	pHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	pDesc = CD3DX12_RESOURCE_DESC::Buffer(byteSize);
	ThrowIfFailed(device->CreateCommittedResource(
		&pHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&pDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&uploadBuffer)));


	// Describe the data we want to copy into the default buffer.
	D3D12_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pData = initData;
	subResourceData.RowPitch = byteSize;
	subResourceData.SlicePitch = subResourceData.RowPitch;

	//调度复制数据到默认的缓冲区资源。在高层上，helper函数是UpdateSubresources
	//将CPU内存复制到中间上传堆。然后,使用ID3D12CommandList:: CopySubresourceRegion,
	//中间上载堆数据将被复制到mBuffer。
	D3D12_RESOURCE_BARRIER pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer.Get(),
		D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
	cmdList->ResourceBarrier(1, &pBarriers);
	UpdateSubresources<1>(cmdList, defaultBuffer.Get(), uploadBuffer.Get(), 0, 0, 1, &subResourceData);
	pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer.Get(),
		D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);
	cmdList->ResourceBarrier(1, &pBarriers);

	//注意:在上述函数调用后，uploadBuffer必须保持活着，因为
	//执行实际复制的命令列表还没有被执行。
	//调用者可以在知道副本已经被执行后释放uploadBuffer。

	return defaultBuffer;
}

void BuildPSO()
{
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
	ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	psoDesc.InputLayout = { mInputLayout[0].data(), (UINT)mInputLayout[0].size() };
	psoDesc.pRootSignature = mRootSignature[0].Get();
	psoDesc.VS =
	{
		reinterpret_cast<BYTE*>(mvsByteCode[0]->GetBufferPointer()),
		mvsByteCode[0]->GetBufferSize()
	};
	psoDesc.PS =
	{
		reinterpret_cast<BYTE*>(mpsByteCode[0]->GetBufferPointer()),
		mpsByteCode[0]->GetBufferSize()
	};
	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	psoDesc.RasterizerState.FrontCounterClockwise = false;
	psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = mBackBufferFormat;
	psoDesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
	psoDesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
	psoDesc.DSVFormat = mDepthStencilFormat;
	ThrowIfFailed(md3dDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&mPSO[0])));

	ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	psoDesc.InputLayout = { mInputLayout[1].data(), (UINT)mInputLayout[1].size() };
	psoDesc.pRootSignature = mRootSignature[1].Get();
	psoDesc.VS =
	{
		reinterpret_cast<BYTE*>(mvsByteCode[1]->GetBufferPointer()),
		mvsByteCode[1]->GetBufferSize()
	};
	psoDesc.PS =
	{
		reinterpret_cast<BYTE*>(mpsByteCode[1]->GetBufferPointer()),
		mpsByteCode[1]->GetBufferSize()
	};
	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	psoDesc.RasterizerState.FrontCounterClockwise = false;
	psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = mBackBufferFormat;
	psoDesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
	psoDesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
	psoDesc.DSVFormat = mDepthStencilFormat;
	ThrowIfFailed(md3dDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&mPSO[1])));
}

void FlushCommandQueue()
{
	// Advance the fence value to mark commands up to this fence point.
	mCurrentFence++;

	// Add an instruction to the command queue to set a new fence point.  Because we 
	// are on the GPU timeline, the new fence point won't be set until the GPU finishes
	// processing all the commands prior to this Signal().
	ThrowIfFailed(mCommandQueue->Signal(mFence.Get(), mCurrentFence));

	// Wait until the GPU has completed commands up to this fence point.
	if (mFence->GetCompletedValue() < mCurrentFence)
	{
		// Fire event when GPU hits current fence.  
		ThrowIfFailed(mFence->SetEventOnCompletion(mCurrentFence, m_fenceEvent));

		// Wait until the GPU hits current fence event is fired.
		WaitForSingleObject(m_fenceEvent, INFINITE);
	}
}

float CalculateFrameStatsAndTime()
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static UINT CurrentTime = 0.0f;
	static float LastTime = 0.0f;
	static float dt = 0.0f;

	frameCnt++;
	dt = ((float)GetTickCount64() - CurrentTime) / 1000;
	CurrentTime = GetTickCount64();

	// Compute averages over one second period.
	if ((CurrentTime - LastTime) >= 1000.0f)
	{
		LastTime = CurrentTime;

		wstring fpsStr = to_wstring(frameCnt);
		wstring windowText = mMainWndCaption +
			L"    fps: " + fpsStr;

		SetWindowTextW(mhMainWnd, windowText.c_str());

		// Reset for next average.
		frameCnt = 0;
	}

	return dt;
}

void OnResize()
{
	// Flush before changing any resources.
	FlushCommandQueue();

	ThrowIfFailed(mCommandList->Reset(mDirectCmdListAlloc.Get(), nullptr));

	// Release the previous resources we will be recreating.
	for (int i = 0; i < SwapChainBufferCount; ++i)
		mSwapChainBuffer[i].Reset();
	mDepthStencilBuffer.Reset();

	//// Resize the swap chain.
	//ThrowIfFailed(mSwapChain->ResizeBuffers(
	//	SwapChainBufferCount,
	//	mClientWidth, mClientHeight,
	//	mBackBufferFormat,
	//	DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH));

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(mRtvHeap->GetCPUDescriptorHandleForHeapStart());
	for (UINT i = 0; i < SwapChainBufferCount; i++)
	{
		ThrowIfFailed(mSwapChain->GetBuffer(i, IID_PPV_ARGS(&mSwapChainBuffer[i])));
		md3dDevice->CreateRenderTargetView(mSwapChainBuffer[i].Get(), nullptr, rtvHeapHandle);
		rtvHeapHandle.Offset(1, mRtvDescriptorSize);
	}

	// Create the depth/stencil buffer and view.
	D3D12_RESOURCE_DESC depthStencilDesc;
	depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthStencilDesc.Alignment = 0;
	depthStencilDesc.Width = mClientWidth;
	depthStencilDesc.Height = mClientHeight;
	depthStencilDesc.DepthOrArraySize = 1;
	depthStencilDesc.MipLevels = 1;

	// Correction 11/12/2016: SSAO chapter requires an SRV to the depth buffer to read from 
	// the depth buffer.  Therefore, because we need to create two views to the same resource:
	//   1. SRV format: DXGI_FORMAT_R24_UNORM_X8_TYPELESS
	//   2. DSV Format: DXGI_FORMAT_D24_UNORM_S8_UINT
	// we need to create the depth buffer resource with a typeless format.  
	depthStencilDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;

	depthStencilDesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
	depthStencilDesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
	depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE optClear;
	optClear.Format = mDepthStencilFormat;
	optClear.DepthStencil.Depth = 1.0f;
	optClear.DepthStencil.Stencil = 0;
	D3D12_HEAP_PROPERTIES pHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	ThrowIfFailed(md3dDevice->CreateCommittedResource(
		&pHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&depthStencilDesc,
		D3D12_RESOURCE_STATE_COMMON,
		&optClear,
		IID_PPV_ARGS(mDepthStencilBuffer.GetAddressOf())));

	// Create descriptor to mip level 0 of entire resource using the format of the resource.
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Format = mDepthStencilFormat;
	dsvDesc.Texture2D.MipSlice = 0;
	md3dDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), &dsvDesc, mDsvHeap->GetCPUDescriptorHandleForHeapStart());

	// Transition the resource from its initial state to be used as a depth buffer.
	D3D12_RESOURCE_BARRIER Barriers = CD3DX12_RESOURCE_BARRIER::Transition(mDepthStencilBuffer.Get(),
		D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE);
	mCommandList->ResourceBarrier(1, &Barriers);

	// Execute the resize commands.
	ThrowIfFailed(mCommandList->Close());
	ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
	mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// Wait until resize is complete.
	FlushCommandQueue();

	// Update the viewport transform to cover the client area.
	mScreenViewport.TopLeftX = 0;
	mScreenViewport.TopLeftY = 0;
	mScreenViewport.Width = static_cast<float>(mClientWidth);
	mScreenViewport.Height = static_cast<float>(mClientHeight);
	mScreenViewport.MinDepth = 0.0f;
	mScreenViewport.MaxDepth = 1.0f;

	mScissorRect = { 0, 0, mClientWidth, mClientHeight };

	mProj = XMMatrixPerspectiveFovRH(XM_PI / 3, (float)mClientWidth / mClientHeight, 1.0f, 1000.0f);
}

void BuildModel()
{
	物体管理->加入静态物体FBX(L"线条", L"模型\\线条.FBX", DXGI_FORMAT_R16_UINT, 0.1);
	物体管理->静态物体[L"线条"]->导出mds文件(L"线条.mds");

	//物体管理->加入静态物体MDS(L"线条", L"模型\\线条\\线条.mds");
	物体管理->加入静态物体MDS(L"球体", L"模型\\球体.mds");
	//物体管理->加入动态物体FBX(L"角色", L"模型\\八重樱.FBX", DXGI_FORMAT_R32_UINT, 0.5);
	//物体管理->动态物体[L"角色"]->导出mdd文件(L"八重樱.mdd");
	物体管理->加入动态物体MDD(L"角色", L"模型\\mixamo2\\mixamo2.mdd");  //打开加入动态物体时，请关闭此功能避免重复
	描述符堆管理->生成描述符堆();
}

void SetUp()
{
	// The window resized, so update the aspect ratio and recompute the projection matrix.
	mProj = XMMatrixPerspectiveFovRH(XM_PI / 3, (float)mClientWidth / mClientHeight, 1.0f, 10000.0f);

	for (int i = 0; i < 256; i++)
	{
		ubuffer2.gBoneTransform[i] = XMMatrixIdentity();
	}
}

void Update(float dt)
{
	// Convert Spherical to Cartesian coordinates.
	float x = 2.0f;
	float z = 5.0f;
	float y = 5.0f;

	// Build the view matrix.
	XMVECTOR pos = XMVectorSet(x, y, z, 1.0f);
	XMVECTOR target = XMVECTOR{ 0.0f, 0.0f, 0.0f, 0.0f };
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX view;
	相机->相机(&view);

	XMMATRIX ViewProj = view * mProj;

	// Update the constant buffer with the latest worldViewProj matrix.
	cbuffer.gViewProj = ViewProj;
	XMStoreFloat4(&cbuffer.gEyePosW, 相机->相机坐标);

	cbuffer2.gViewProj = ViewProj;
	XMStoreFloat4(&cbuffer2.gEyePosW, 相机->相机坐标);

	ubuffer3.gWorld = XMMatrixIdentity();
}

void Draw(float dt)
{
	// Reuse the memory associated with command recording.
	// We can only reset when the associated command lists have finished execution on the GPU.
	ThrowIfFailed(mDirectCmdListAlloc->Reset());

	// A command list can be reset after it has been added to the command queue via ExecuteCommandList.
	// Reusing the command list reuses memory.
	ThrowIfFailed(mCommandList->Reset(mDirectCmdListAlloc.Get(), mPSO[0].Get())); //换静态物体时请将这里改成0

	mCommandList->RSSetViewports(1, &mScreenViewport);
	mCommandList->RSSetScissorRects(1, &mScissorRect);

	// Indicate a state transition on the resource usage.
	D3D12_RESOURCE_BARRIER pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(mSwapChainBuffer[mCurrBackBuffer].Get(),
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	mCommandList->ResourceBarrier(1, &pBarriers);

	// Clear the back buffer and depth buffer.
	D3D12_CPU_DESCRIPTOR_HANDLE RenderTargetView = CD3DX12_CPU_DESCRIPTOR_HANDLE(
		mRtvHeap->GetCPUDescriptorHandleForHeapStart(), mCurrBackBuffer, mRtvDescriptorSize);
	mCommandList->ClearRenderTargetView(RenderTargetView, LightSteelBlue, 0, nullptr);
	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView = mDsvHeap->GetCPUDescriptorHandleForHeapStart();
	mCommandList->ClearDepthStencilView(DepthStencilView, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

	// Specify the buffers we are going to render to.
	mCommandList->OMSetRenderTargets(1, &RenderTargetView, true, &DepthStencilView);

	mCommandList->SetDescriptorHeaps(1, 描述符堆管理->描述符堆.GetAddressOf());

	mCommandList->SetGraphicsRootSignature(mRootSignature[0].Get());

	mCommandList->SetGraphicsRoot32BitConstants(0, sizeof(SCBUFFER) / 4, &cbuffer, 0);

	if (按键检测.键1状态)
	{
		物体管理->动态物体[L"角色"]->当前轨道 = 0;
		物体管理->动态物体[L"角色"]->动画轨道[0].当前时间 = 0.0f;
		物体管理->动态物体[L"角色"]->动画轨道[0].速度 = 0.2f;
	}

	if (按键检测.键2状态)
	{
		物体管理->动态物体[L"角色"]->当前轨道 = 1;
		物体管理->动态物体[L"角色"]->动画轨道[1].当前时间 = 0.0f;
	}

	if (按键检测.键3状态)
	{
		物体管理->动态物体[L"角色"]->当前轨道 = 2;
		物体管理->动态物体[L"角色"]->动画轨道[2].当前时间 = 0.0f;
	}

	if (按键检测.键4状态)
	{
		物体管理->动态物体[L"角色"]->当前轨道 = 3;
		物体管理->动态物体[L"角色"]->动画轨道[3].当前时间 = 0.0f;
	}

	if (按键检测.键5状态)
	{
		物体管理->动态物体[L"角色"]->当前轨道 = 4;
		物体管理->动态物体[L"角色"]->动画轨道[4].当前时间 = 0.0f;
	}

	物体管理->动态物体[L"角色"]->更新时间(dt);

	XMMATRIX* B = 0;
	B = 物体管理->动态物体[L"角色"]->获取当前骨骼变换();

	//for (int i = 0; i < 物体管理->动态物体[L"角色"]->m根节点->子节点数量; i++)
	{
		//遍历骨骼树(&物体管理->动态物体[L"角色"]->m根节点->子节点[i], B);
	}

	mCommandList->SetPipelineState(mPSO[1].Get());
	mCommandList->SetGraphicsRootSignature(mRootSignature[1].Get());

	cbuffer2Upload->Map(0, nullptr, (void**)&mMappedDatacb2);
	memcpy(mMappedDatacb2, &cbuffer2, sizeof(SCBUFFER2));
	cbuffer2Upload->Unmap(0, nullptr);
	mCommandList->SetGraphicsRootConstantBufferView(0, cbuffer2Upload->GetGPUVirtualAddress());

	//物体管理->动态物体[L"角色"]->更新时间(dt);
	XMMATRIX* OBJ = 0;
	B = 物体管理->动态物体[L"角色"]->获取当前骨骼变换();
	for (int i = 0; i < 物体管理->动态物体[L"角色"]->骨骼数量; i++)
	{
		ubuffer2.gBoneTransform[i] = B[i];
	}
	ubuffer2.gMat = 物体管理->动态物体[L"角色"]->属性->元素[0]->材质;
	ubuffer2Upload->Map(0, nullptr, (void**)&mMappedDataub2);
	memcpy(mMappedDataub2, &ubuffer2, sizeof(SUBUFFER2));
	ubuffer2Upload->Unmap(0, nullptr);
	mCommandList->SetGraphicsRootConstantBufferView(1, ubuffer2Upload->GetGPUVirtualAddress());

	for (int i = 0; i < 物体管理->动态物体[L"角色"]->属性->元素.size(); i++)
	{
		ubuffer3.gObj = 物体管理->动态物体[L"角色"]->获取当前物体变换(i);
		ubuffer3.gWorld = XMMatrixScaling(0.1f, 0.1f, 0.1f);
		mCommandList->SetGraphicsRootDescriptorTable(2,
			描述符堆管理->资源描述[物体管理->动态物体[L"角色"]->物体名称键 + L"." +
			物体管理->动态物体[L"角色"]->属性->元素[i]->物体名称 + L"纹理srv"]->hGPU描述符);

		mCommandList->SetGraphicsRoot32BitConstants(3, sizeof(SUBUFFER3) / 4, &ubuffer3, 0);

		物体管理->动态物体[L"角色"]->绘制网格(i);
	}

	按键检测.鼠标位移 = POINT{ 0, 0 };

	// Indicate a state transition on the resource usage.
	pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(mSwapChainBuffer[mCurrBackBuffer].Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	mCommandList->ResourceBarrier(1, &pBarriers);

	// Done recording commands.
	ThrowIfFailed(mCommandList->Close());

	// Add the command list to the queue for execution.
	ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
	mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// swap the back and front buffers
	ThrowIfFailed(mSwapChain->Present(0, DXGI_PRESENT_ALLOW_TEARING));
	mCurrBackBuffer = (mCurrBackBuffer + 1) % SwapChainBufferCount;

	//等待直到帧命令完成。这种等待是低效的
	//为简单起见。稍后我们将展示如何组织我们的渲染代码
	//我们不需要等待每一帧。
	FlushCommandQueue();
}

void Distory()
{
	CloseHandle(m_fenceEvent);
	delete 相机;
	delete 共享资源;
	delete 描述符堆管理;
	delete 物体管理;
	_CrtDumpMemoryLeaks();
}