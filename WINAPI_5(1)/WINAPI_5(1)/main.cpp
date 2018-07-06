#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <string>
#include <Windowsx.h>

#define WM_POSITION WM_APP

HWND hText, hWord, hEntry;
TCHAR text[100];
TCHAR* buffer;
std::wstring string1;
int x, y;

INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;

	case WM_INITDIALOG:
		hText = GetDlgItem(hWnd, IDC_EDIT1);
		hWord = GetDlgItem(hWnd, IDC_EDIT2);
		hEntry = GetDlgItem(hWnd, IDC_BUTTON1);
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_EDIT1)
		{
			x = 0, y = 0;
			delete[] buffer;
			EnableWindow(hWord, TRUE);
			EnableWindow(hEntry, TRUE);

			int length = SendMessage(hText, WM_GETTEXTLENGTH, 0, 0);
			buffer = new TCHAR[length + 1];
			memset(buffer, 0, length + 1);
			GetWindowText(hText, buffer, length + 1);
		}
		else if (LOWORD(wParam) == IDC_EDIT2)
		{
			x = 0, y = 0;
			GetWindowText(hWord, text, 100);
		}
		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			int pos1 = 0, pos2 = 1, pos3 = 0;
			string1 = buffer;

			if (x == 0 && y == 0)
			{
				pos1 = string1.find(text);
				if (pos1 == -1)
				{
					MessageBox(hWnd, TEXT("Ничего не найдено"), TEXT("Ошибка"), MB_OK | MB_ICONINFORMATION);
					return TRUE;
				}
				pos3 = pos1 + 1;
				while (true)
				{
					if (string1[pos3] == text[pos2])
					{
						pos2++;
						pos3++;
					}
					else{
						break;
					}
				}
				x = pos1;
				y = pos3;
				SendMessage(hText, EM_SETSEL, pos1, pos3); // выделить весь текст в Edit Control
				SendMessage(hText, WM_POSITION, 0, 0); // определить текущие координаты курсора
			}
			else{
				pos1 = string1.find(text, y);
				if (pos1 == -1)
				{
					MessageBox(hWnd, TEXT("Ничего не найдено"), TEXT("Ошибка"), MB_OK | MB_ICONINFORMATION);
					return TRUE;
				}
				pos3 = pos1 + 1;
				while (true)
				{
					if (string1[pos3] == text[pos2])
					{
						//if (wcslen(string1)
						pos2++;
						pos3++;
					}
					else{
						break;
					}
				}
				x = pos1;
				y = pos3;
				SendMessage(hText, EM_SETSEL, pos1, pos3); // выделить весь текст в Edit Control
				SendMessage(hText, WM_POSITION, 0, 0); // определить текущие координаты курсора
			}


		}
		return TRUE;
	}
	return FALSE;
}