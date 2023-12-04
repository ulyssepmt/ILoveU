#include <windows.h>
#include <math.h> //sin, cos

HWND hwnd;
HDC hdc;

DWORD WINAPI Coeur2Cristal(LPVOID lparam);
RECT rect;
BOOL InfiniteLOVE = TRUE;

int w, h;
void InitializeResolution() {
	w = GetSystemMetrics(SM_CXSCREEN) - 800;
	h = GetSystemMetrics(SM_CYSCREEN) - 200;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_CREATE:

		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		InitializeResolution();
		HDC hdc = BeginPaint(hWnd, &ps);

		HBRUSH noir = CreateSolidBrush(RGB(0, 0, 0)); // bkg noir
		SelectObject(hdc, noir);

		PatBlt(hdc, 0, 0, w, h, PATCOPY);

		EndPaint(hWnd, &ps);
		break;
	}
	case WM_NCHITTEST:
	{
		LRESULT hitTestResult = DefWindowProc(hWnd, Msg, wParam, lParam);
		return (hitTestResult == HTCAPTION) ? HTCLIENT : hitTestResult;
	}
	case WM_SYSCOMMAND:
	{
		if ((wParam & 0xfff0) == SC_CLOSE)
		{
			DestroyWindow(hWnd);
			return 0;
		}
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0x00);
		break;

	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nCmdShow)
{
	hwnd = FindWindowW(L"ILoveU", L"ILoveU");
	hdc = GetDC(hwnd);

	WNDCLASSEXW c;
	c.cbSize = sizeof(WNDCLASSEX);
	c.lpfnWndProc = WndProc;
	c.lpszClassName = L"ILoveU";
	c.style = CS_DBLCLKS;
	c.cbClsExtra = 0;
	c.cbWndExtra = 0;
	c.hInstance = GetModuleHandle(NULL);
	c.hIcon = LoadIcon(c.hInstance, IDI_APPLICATION);;
	c.hCursor = LoadCursor(NULL, IDC_ARROW);
	c.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	c.lpszMenuName = NULL;
	c.hIconSm = LoadIcon(c.hInstance, IDI_APPLICATION);

	if (!RegisterClassExW(&c))
	{
		return -1;
	}

	HWND win = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"ILoveU", L"ILoveU", WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, 0, 0, w, h, NULL, NULL, hInstance, NULL);

	ShowWindow(win, nCmdShow);
	UpdateWindow(win);
	CreateThread(0, 0, &Coeur2Cristal, 0, 0, 0);

	SetWindowPos(win, HWND_TOPMOST, ((w + 800) / 2) - (w / 2), ((h + 200) / 2) - (h / 2), w, h, SWP_SHOWWINDOW);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0 && !FALSE) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

void LoveLabel() {
	int X = 675; int Y = 200;
	//InitializeResolution(); 

	hwnd = FindWindowW(0, L"ILoveU");
	if (!hwnd) {
		MessageBoxA(0, "Zut, hwnd introuvable dans la fonction label!", "ILoveYou!", MB_OK);
	}
	hdc = GetDC(hwnd);
	HBITMAP hbm = CreateCompatibleBitmap(hdc, 1500, 900);
	HDC hdcMem = CreateCompatibleDC(hdc);

	SelectObject(hdcMem, hbm);
	BitBlt(hdcMem, 0, 0, X + 5, 500, hdc, (w / 2) - (X / 2), (h / 2) - (Y / 2), SRCCOPY);

	HFONT hFont = CreateFont(80, 30, 10, 0, FW_BOLD, TRUE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, FF_ROMAN, TEXT("Thinking of Betty"));

	SelectObject(hdcMem, hFont);
	SetTextColor(hdcMem, RGB(255, 255, 255));
	SetBkColor(hdcMem, TRANSPARENT);

	rect.right = (w / 2) + 75;
	rect.bottom = (h / 2);

	DrawTextA(hdcMem, "I Love You !", -1, &rect, DT_NOCLIP | DT_CENTER);
	for (int p = -10; p < X; p += 4) {
		BitBlt(hdc, (w / 2) - (X / 2), (h / 2) - (Y / 2), p, 500, hdcMem, 0, 0, SRCPAINT);
		Sleep(2);
	}

	ReleaseDC(hwnd, hdc);
	ReleaseDC(0, hdcMem);
	DeleteDC(hdcMem);
	DeleteDC(hdc);


}

DWORD WINAPI Coeur2Cristal(LPVOID lparam)
{
	//	InitializeResolution(); 
		// Create a msgbox here and say that u love her/him so much + 
	hwnd = FindWindowW(0, L"ILoveU");
	hdc = GetDC(hwnd);

	double x = 0;
	double y = 0;

	while (InfiniteLOVE) {
		for (double t = 0; t <= 6.0; t += 0.01) // Courbe du coeur en rouge
		{

			x = (276 - (t * 0.1)) * pow(sin(t), 3);
			y = (273 - (t * 0.1)) * cos(t) - 80 * cos(2 * t) - 40 * cos(3 * t) - cos(4 * t);

			int pixelX = (int)(floor(-x + (w / 2) - 20));
			int pixelY = (int)(floor(-y + (h / 2) - 20));

			HBRUSH rgb = CreateSolidBrush(RGB((t * 10) * 8, 0, 0));
			SelectObject(hdc, rgb);

			BitBlt(hdc, pixelX, pixelY, 10, 10, hdc, (int)t, 0, PATCOPY);
			Sleep(1);
		}

	abegin:

		RedrawWindow(0, 0, 0, 133);

		hwnd = FindWindowW(0, L"ILoveU");

		hdc = GetDC(hwnd);

		for (double v = 0; v <= (double)(floor((w * 3))); v += 0.01)
			// remplissage en reprenant la même formule utilisant v pour incrémenter par vague 
			//de couleur vers le centre
		{

			x = (276 - (v * 0.1)) * pow(sin(v), 3);
			y = (273 - (v * 0.1)) * cos(v) - 80 * cos(2 * v) - 40 * cos(3 * v) - cos(4 * v);

			int pixelX = (int)(floor(-x + (w / 2) - 20));
			int pixelY = (int)(floor(-y + (h / 2) - 20));

			int g = ((int)x ^ (int)y); //xor <3

			SetPixel(hdc, pixelX, pixelY, RGB(g, 0, 0));
		}

		LoveLabel();
		Sleep(2000);
		goto abegin;
	}

	ReleaseDC(0, hdc);

	return 0;
}