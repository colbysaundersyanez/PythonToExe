
#include "framework.h"
#include "test2.h"
#include <iostream>
#include <vector>
#include <string>
#include <comdef.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <direct.h>
#define ID_BTNHI 5
#define ID_BTNHII 1
#define ID_BTNHIII 2
#define ID_BTNHVI 3
#define noneFuntionID 4


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static HFONT s_hFont = NULL;
void loadImages();
HBITMAP hLogoImage;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow){
	BOOL bRet;
	const wchar_t CLASS_NAME[] = L"Window";
	WNDCLASS wc = { };
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.
	HWND hwnd = CreateWindowEx(
		0,            // Optional window styles.
		CLASS_NAME,   // Window class
		L"Window",    // Window text
		WS_OVERLAPPEDWINDOW, // Window style
		// Position/Size
		300, 300, 600, 400,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd == NULL){return 0;}
	ShowWindow(hwnd, nCmdShow);
	std::ofstream ofs;
	ofs.open("C:\\linkContainerFolder\\help.SPEC", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
	// Run the message loop (Keeps program running).
	MSG msg = {};
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (bRet == -1){MessageBox(NULL, L"loop ended", L"", MB_OK);}
		else{TranslateMessage(&msg);DispatchMessage(&msg);}
	}
	//while (GetMessage(&msg, NULL, NULL, NULL)){TranslateMessage(&msg); DispatchMessage(&msg); }
	//MessageBox(hwnd, L"Box", L"Window", MB_OK);
	return 0;
}
HWND button;
HWND buttonTwo;
HWND buttonThree;
HWND helpButton;
HWND editWindow;
char* fileNameTwo;
char* nameArray[50];
wchar_t fileName[100];
std::vector <TCHAR> lpszWords;
std::vector<wchar_t> viewFileName;
std::vector<_bstr_t> fileNameVector;
const char* nameFileTypeCh; //originally const char use wchar_t instead
_bstr_t stringTestingTwo;
TCHAR word;

void displayFile(char* path) {
	try {
		FILE* file;
		file = fopen(path, "rb");
		if (path != NULL || path == "") {
			fseek(file, 0, SEEK_END);
			int _size = ftell(file);
			rewind(file);
			char* data = (char*)malloc(_size + 1);
			fread(data, _size, 1, file);
			data[_size] = '\0';
			_bstr_t string = (_bstr_t)data;
			SetWindowText(editWindow, string);
			}
		else{ MessageBox(NULL, L"Please Enter a file/Create Source File", L"", MB_OK); }
		}
		catch (std::invalid_argument f) { MessageBox(NULL, L"Please Enter a file/Create Source File", L"", MB_OK); };
}

void moveFilePath(char* path) {
	//file adding just need to fix ofstream/fstream
	std::fstream myfile;
	myfile.open("C:\\linkContainerFolder\\linkContainers.SPEC", std::ios_base::app);
	//MessageBox(NULL, (_bstr_t)path, L"", MB_OK);
	myfile << path;
	myfile <<"\n";
	myfile.close();
	//MessageBox(NULL, (_bstr_t)path, L"", MB_OK);
}

void openFile(HWND hwnd) {
	OPENFILENAME ofn;
	//size/name of filename
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = fileName;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 100; //same as filesize
	ofn.lpstrFilter = L"All Files\0*.*\0Python Files\0*.py\0"; //filter of file types
	ofn.nFilterIndex = 2;
	GetOpenFileName(&ofn);
	//MessageBox(NULL, fileName, L"", MB_OK);
	viewFileName.push_back(fileName[0]);
	_bstr_t stringTesting(fileName);
	fileNameVector.push_back(stringTesting);
	stringTestingTwo = stringTesting;
	moveFilePath(stringTesting);
	_bstr_t linkSpec = "C:\\linkContainerFolder\\linkContainers.SPEC";
	displayFile(linkSpec);
	
	//system("pyinstaller --onefile \"" + stringTesting + "\"");
}

void generateSourceFile(HWND hwnd) {
	std::fstream file;
	system("mkdir C:\\LinkContainerFolder");
	file.open("C:\\LinkContainerFolder\\linkContainers.SPEC", std::ios::out);
	file.open("C:\\LinkContainerFolder\\help.SPEC", std::ios::out);
	MessageBox(NULL, L"File Succesfully Made", L"", MB_OK);
	if(!file){ //MessageBox(NULL, L"Error Making File", L"Error", MB_OK); 
	}
	else { MessageBox(NULL, L"File Succesfully Made", L"", MB_OK); }
	file.close();
}

void loadImages() {
	hLogoImage = (HBITMAP)LoadImageW(NULL, L"helpImage.png", IMAGE_BITMAP, 720, 720, LR_LOADFROMFILE);
}

void convertFiles() {
	try {
		//system("pyinstaller --onefile \"" + stringTestingTwo + "\"");
		for (int x = 0; x <= fileNameVector.size() - 1; x++) {
			_bstr_t bstr = fileNameVector.at(x);

			std::ifstream ifs ("cmd.exe");
			if (ifs.is_open()) {}
			else{
				if(SysStringLen(bstr) == 0 || bstr.GetBSTR() == NULL){ MessageBox(NULL, L"running", L"Empty", MB_OK); }
				else {
					//MessageBox(NULL, L"running", bstr, MB_OK);
					system("pyinstaller --onefile \"" + bstr + "\"");
				}
			}
		}
	}
	catch (std::runtime_error e) { MessageBox(NULL, L"error", L"error", MB_OK); }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE: {
		HINSTANCE hInstance = GetModuleHandle(NULL);
		button = CreateWindow(L"Button", L"Select File", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 10, 110, 30, hwnd, (HMENU) ID_BTNHI, GetModuleHandle(NULL), NULL);
		buttonTwo = CreateWindow(L"Button", L"Change To EXE", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 130, 10, 110, 30, hwnd, (HMENU)ID_BTNHII, GetModuleHandle(NULL), NULL);
		buttonThree = CreateWindow(L"Button", L"Generate Source File", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 250, 10, 150, 30, hwnd, (HMENU)ID_BTNHIII, GetModuleHandle(NULL), NULL);
		editWindow = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_BORDER | ES_AUTOVSCROLL, 10, 50, 565, 300, hwnd, NULL, NULL, NULL);
		helpButton = CreateWindow(L"Button", L"?", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_TEXT, 410, 10, 40, 30, hwnd, (HMENU)ID_BTNHVI, GetModuleHandle(NULL), NULL);
		SendMessage(helpButton, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));
		//SendMessage(helpButton, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hLogoImage);
		//HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
		//SendMessage(helpButton, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hIcon);

		generateSourceFile(hwnd);
		break;
	}
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
			
			case ID_BTNHI: {
				openFile(hwnd);
				//MessageBox(hwnd, L"Box", L"Window", MB_OK);
				break;
			}
			case noneFuntionID: {
				MessageBox(hwnd, L"Box", L"Window", MB_OK);
				break;
			}
			case ID_BTNHII: {
				convertFiles();
				break;
			}
			case ID_BTNHIII: {
				generateSourceFile(hwnd);
				break;
			}
			case ID_BTNHVI: {
				std::fstream myFile;
				//myFile.open()
				myFile.open("C:\\linkContainerFolder\\help.SPEC", std::ifstream::out | std::ifstream::trunc);
				myFile.close();
				myFile.open("C:\\linkContainerFolder\\help.SPEC", std::ios_base::app);
				myFile << "* The Source File is generated automatically when the program is started. \n \n";
				myFile << "* You have a button provided in case there is no C:\\linkContainers \n \n";
				myFile << "* To run the program click the select file button and find the python file(s) you wish to convert \n";
				myFile << "*Avoid having the files in seperate directories to avoid confusion and make sure you have full access to directory";
				myFile.close();
				//myFile.open("C:\\linkContainerFolder\\help.SPEC", std::ios::out | std::ios::trunc);
				//myFile.close();
				_bstr_t helpLink = "C:\\linkContainerFolder\\help.SPEC";
				displayFile(helpLink);
				break;
			}
		}
		break;
	}
					 
	//case WM_DESTROY:
		//MessageBox(hwnd, L"Box", L"Quit", MB_OK);
		//PostQuitMessage(0);
		//return 0;
	case WM_CLOSE:
		if (MessageBox(hwnd, L"Really quit?", L"Exit", MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(hwnd);
			PostQuitMessage(0);
		}
		return 0;
		
	default:
		return DefWindowProcW(hwnd, uMsg, wParam, lParam);
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(hwnd, &ps);
		break;
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}