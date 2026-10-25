#include <Windows.h>

const char* className = "MouseInputWindowApp";

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR args, int nCmdShow)
{
	HWND hWnd;
	MSG message;
	WNDCLASSEX wndClassEx;
	
	wndClassEx.hInstance = hInstance;
	wndClassEx.lpszClassName = className;
	wndClassEx.lpfnWndProc = WindowProcedure;
	wndClassEx.style = CS_DBLCLKS;
	wndClassEx.cbSize = sizeof(WNDCLASSEX);
	wndClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClassEx.lpszMenuName = NULL;
	wndClassEx.cbClsExtra = 0;
	wndClassEx.cbWndExtra = 0;
	wndClassEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	
	if (!RegisterClassEx(&wndClassEx))
	{
		return 0;
	}
	
	hWnd = CreateWindowEx(0, className, "Mouse Input Window App", WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 544, 400, HWND_DESKTOP, NULL, hInstance, NULL);
	
	ShowWindow(hWnd, nCmdShow);
	
	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		
		DispatchMessage(&message);
	}
	
	return message.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT paintStruct;
	
	static int x;
	static int y;
	static BOOL drawing = FALSE;
	
	switch (message)
	{
		case WM_LBUTTONDOWN:
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			
			drawing = TRUE;
			
			break;
		case WM_MOUSEMOVE:
			if (drawing)
			{
				hdc = GetDC(hWnd);
				
				MoveToEx(hdc, x, y, NULL);
				
				x = LOWORD(lParam);
				y = HIWORD(lParam);
				
				LineTo(hdc, x, y);
				ReleaseDC(hWnd, hdc);
			}
			
			break;
		case WM_LBUTTONUP:
			drawing = FALSE;
			
			break;
		case WM_LBUTTONDBLCLK:
			InvalidateRect(hWnd, NULL, TRUE);
			
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &paintStruct);
			
			TextOut(hdc, 0, 0, "Mouse", 5);
			
			EndPaint(hWnd, &paintStruct);
			
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	
	return 0;
}
