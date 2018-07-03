#pragma once

HWND g_hwnd = NULL;

void InitWindow(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, const TCHAR* appName);
bool DispachWindoMessage();
 