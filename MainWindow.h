#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#ifndef _WINDOWS_
#include <Windows.h>
#endif _WINDOWS_

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
	HINSTANCE getHInstance() const;
	HWND getHWnd() const;

private:
	// 原始窗口过程
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK _WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE hInstance;
	HWND hWnd;
};

#endif // !_MAIN_WINDOW_H_