#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include <windows.h>

class MainWindow
{
public:
	MainWindow(HINSTANCE hInstance);
	virtual ~MainWindow();
	void InitWindowInstance(WCHAR* szWindowClass, WCHAR* szTitle);
	void InitWindowInstance(WCHAR* szWindowClass, WCHAR* szTitle, HICON hIcon, HICON hIconSm);
	int exec();

protected:
	virtual LRESULT HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnCreate();
	virtual void OnPaint(HDC hdc, PAINTSTRUCT ps) = 0;
	virtual void OnClose();
	virtual void OnDestroy();

private:
	// 原始窗口过程
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK _WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE hInstance;
	HWND hWnd;
};


#endif // !__MAIN_WINDOW_H__