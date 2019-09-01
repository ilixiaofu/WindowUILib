#include <assert.h>
#include "MainWindow.h"

MainWindow::MainWindow(HINSTANCE hInstance) :hInstance(hInstance), hWnd(NULL)
{
}

MainWindow::~MainWindow() 
{
}

void MainWindow::InitWindowInstance(WCHAR* szWindowClass, WCHAR* szTitle)
{
	//GetMOduleHandle函数获得当前应用程序实例句柄
	//HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);
	assert(this->hInstance);
	// 窗口类
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = &MainWindow::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = this->hInstance;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // (HBRUSH)::GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = nullptr;

	// 注册窗口
	int iret = ::RegisterClassExW(&wcex);
	assert(iret);

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, this->hInstance, (LPVOID)this);
	assert(this->hWnd);
	ShowWindow(this->hWnd, SW_SHOW);
	UpdateWindow(this->hWnd);
}

void MainWindow::InitWindowInstance(WCHAR* szWindowClass, WCHAR* szTitle, HICON hIcon, HICON hIconSm)
{
	assert(this->hInstance);
	// 窗口类
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = &MainWindow::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = this->hInstance;
	wcex.hIcon = hIcon;
	wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // (HBRUSH)::GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL; // MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = hIconSm;

	// 注册窗口
	int iret = ::RegisterClassExW(&wcex);
	assert(iret);

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, this->hInstance, (LPVOID)this);
	assert(hWnd);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
}

int MainWindow::exec()
{
	MSG msg;
	//主消息循环:
	while (::GetMessageW(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		::DispatchMessageW(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK MainWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//if (WM_GETMINMAXINFO == message || WM_NCCREATE == message || WM_NCCALCSIZE == message)
	//{
	//	return DefWindowProcW(hWnd, message, wParam, lParam);
	//}
	MainWindow* mWindow = NULL;
	if (WM_CREATE == message)
	{
		mWindow = (MainWindow*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
		mWindow->hWnd = hWnd;
		// 通过USERDATA把HWND和C++对象关联起来
		::SetWindowLongW(hWnd, GWL_USERDATA, (LONG)mWindow);
		mWindow->OnCreate();
	}
	mWindow = (MainWindow*)::GetWindowLongW(hWnd, GWL_USERDATA);
	if (mWindow)
	{
		return mWindow->_WndProc(hWnd, message, wParam, lParam);
	}
	else
	{
		return ::DefWindowProcW(hWnd, message, wParam, lParam);
	}
}

LRESULT CALLBACK MainWindow::_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		// PAINTSTRUCT 绘图结构体，存储目标窗口可以绘图的客户端区域(client area)
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(this->hWnd, &ps); // DC(可画图的内存对象) 的句柄
		// TODO: 在此处添加使用 hdc 的任何绘图代码...
		this->OnPaint(hdc, ps);
		EndPaint(this->hWnd, &ps);
		break;
	}
	case WM_CLOSE:
	{
		this->OnClose();
		break;
	}
	case WM_DESTROY:
	{
		this->OnDestroy();
		break;
	}
	default:
	{
		return this->HandleMessage(hWnd, message, wParam, lParam);
	}
	}
	return 0;
}

LRESULT MainWindow::HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProcW(hWnd, message, wParam, lParam);
}

void MainWindow::OnCreate()
{
}

void MainWindow::OnClose()
{
	::DestroyWindow(this->hWnd);
	this->hWnd = NULL;
}
void MainWindow::OnDestroy()
{
	::PostQuitMessage(0);
}