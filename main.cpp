#include <iostream>
#include <cstdio>
#include <windows.h>

using namespace std;

int * getRGBAt(int x, int y){
    static int rgbList[3];

    HDC hDC = GetDC(HWND_DESKTOP);
    COLORREF rgb;

    rgb = GetPixel(hDC, x, y);

    rgbList[0] = (int)GetRValue(rgb);
    rgbList[1] = (int)GetGValue(rgb);
    rgbList[2] = (int)GetBValue(rgb);
    return rgbList;
}

void click() 
{
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(input));
    ZeroMemory(&input, sizeof(input));
    Sleep(1);
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(input));
}

void main(int argc, char** argv)
{
    int timer = 0;
    bool hasClickedRecently = false;
    while (true) {
        timer++;
        POINT cursor;
        GetCursorPos(&cursor);
        int* vals = getRGBAt(cursor.x, cursor.y);
        //cout << "RGB: " << vals[0] << ", " << vals[1] << ", " << vals[2]  << "  X:"<<cursor.x<< " Y:"<<cursor.y << endl;
        if (vals[0] == 75 && vals[1] == 219 && vals[2] == 106) {
            // This is so that the program will not click multiple times for the reaction test
            // Delay of 500ms before the program can click again
            if (timer > 500) {
                hasClickedRecently = false;
            }
            if (!hasClickedRecently) {
                cout << "Clicked" << endl;
                click();
                timer = 0;
                hasClickedRecently = true;
            }
        }
        Sleep(1);
    }
}