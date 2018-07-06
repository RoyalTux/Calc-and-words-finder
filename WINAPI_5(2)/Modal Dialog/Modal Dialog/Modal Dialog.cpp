#include <windows.h>
#include <tchar.h>
#include <string>
#include "resource.h"

using namespace std;

HWND hEdit1, hEdit2, hEditRez, hRez, hPlus, hMinus, hMulti, hDiv;
TCHAR text[100], first[20], second[20];
INT iFirst, iSecond, iRes, Radix = 10;

INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	// создаём главное окно приложения на основе модального диалога
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc); 
}

void EnableDisableButton()
{
	DWORD dwPosition1 = SendMessage(hEdit1, EM_GETSEL, 0, 0); // Получим границы выделения текста 1
	WORD wBeginPosition1 = LOWORD(dwPosition1);
	WORD wEndPosition1 = HIWORD(dwPosition1);

	DWORD dwPosition2 = SendMessage(hEdit2, EM_GETSEL, 0, 0); // Получим границы выделения текста 2
	WORD wBeginPosition2 = LOWORD(dwPosition2);
	WORD wEndPosition2 = HIWORD(dwPosition2);
}

INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	switch(message)
	{
	case WM_INITDIALOG:
		hEdit1 = GetDlgItem(hWnd, IDC_EDIT1);
		hEdit2 = GetDlgItem(hWnd, IDC_EDIT2);
		hEditRez = GetDlgItem(hWnd, IDC_EDIT3);
		hRez = GetDlgItem(hWnd, IDC_BUTTON1);
		hPlus = GetDlgItem(hWnd, IDC_RADIO1);
		hMinus = GetDlgItem(hWnd, IDC_RADIO2);
		hMulti = GetDlgItem(hWnd, IDC_RADIO3);
		hDiv = GetDlgItem(hWnd, IDC_RADIO4);
		CheckDlgButton(hWnd, IDC_RADIO1, BST_CHECKED);
		EnableWindow(hRez, FALSE);
		//SetWindowText(hEdit1, TEXT("0"));
		//SetWindowText(hEdit2, TEXT("0"));
		SetWindowText(hEditRez, TEXT(" результат"));
		return TRUE;
	case WM_COMMAND:
		if ((LOWORD(wp) == IDC_EDIT1 || LOWORD(wp) == IDC_EDIT2))// && (HIWORD(wp) == EN_CHANGE))
		{
			GetWindowText(hEdit1, first, 20);
			GetWindowText(hEdit2, second, 20);
			if (lstrlen(first) == 0 && lstrlen(second) == 0)
				EnableWindow(hRez, FALSE);
			else
				EnableWindow(hRez, TRUE);
		}
		if (IsDlgButtonChecked(hWnd, IDC_RADIO1) && LOWORD(wp) == IDC_BUTTON1)
		{
			GetWindowText(hEdit1, first, 20);
			GetWindowText(hEdit2, second, 20);
			iFirst = _wtoi(first);
			iSecond = _wtoi(second);
			iRes = iFirst + iSecond;
			_itow(iRes, text, Radix);
			SetWindowText(hEditRez, text);	
			return TRUE;
		}
		else if (IsDlgButtonChecked(hWnd, IDC_RADIO2) && LOWORD(wp) == IDC_BUTTON1)
		{
			GetWindowText(hEdit1, first, 20);
			GetWindowText(hEdit2, second, 20);
			iFirst = _wtoi(first);
			iSecond = _wtoi(second);
			iRes = iFirst - iSecond;
			_itow(iRes, text, Radix);
			SetWindowText(hEditRez, text);
			return TRUE;
		}
		else if (IsDlgButtonChecked(hWnd, IDC_RADIO3) && LOWORD(wp) == IDC_BUTTON1)
		{
			GetWindowText(hEdit1, first, 20);
			GetWindowText(hEdit2, second, 20);
			iFirst = _wtoi(first);
			iSecond = _wtoi(second);
			iRes = iFirst * iSecond;
			_itow(iRes, text, Radix);
			SetWindowText(hEditRez, text);
			return TRUE;
		}
		else if (IsDlgButtonChecked(hWnd, IDC_RADIO4) && LOWORD(wp) == IDC_BUTTON1)
		{
			GetWindowText(hEdit1, first, 20);
			GetWindowText(hEdit2, second, 20);
			iFirst = _wtof(first);
			iSecond = _wtof(second);
			if (iSecond > 0)
			{
				iRes = iFirst / iSecond;
			}
			else MessageBox(hWnd, TEXT("На ноль делить нельзя!"), NULL, MB_OK | MB_ICONINFORMATION);
			_itow(iRes, text, Radix);
			SetWindowText(hEditRez, text);
			return TRUE;
		}
		return TRUE;
	case WM_CLOSE:
			EndDialog(hWnd, 0); // закрываем модальный диалог
			return TRUE;
	}
	return FALSE;
}