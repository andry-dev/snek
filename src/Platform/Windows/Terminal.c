#include "Terminal.h"


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <signal.h>

struct terminal_context_t
{
    HANDLE hStdin;
    HANDLE hStdout;
    DWORD mode;
    sigset_t signals;
    unsigned short col;
    unsigned short rows;
};

struct terminal_context_t* initTerm()
{
    struct terminal_context_t* ret = malloc(sizeof(struct terminal_context_t));
    DWORD temp_mode;
    COORD baseCoords = {0,0};
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    ret->hStdin = GetStdHandle(STD_INPUT_HANDLE);
    ret->hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(ret->hStdout, baseCoords);
    GetConsoleScreenBufferInfo(ret->hStdout, &bufferInfo);

    ret->col = bufferInfo.srWindow.Right - bufferInfo.srWindow.Left;
    ret->rows = bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top + 1;
    
    GetConsoleMode(ret->hStdin, &ret->mode);
    
    temp_mode = ret->mode;

    temp_mode &= ~ENABLE_ECHO_INPUT;
    temp_mode &= ~ENABLE_LINE_INPUT;

    SetConsoleMode(ret->hStdin, &temp_mode);
    
    return ret;
}

Vec2i getTermSize(struct terminal_context_t* context)
{
    Vec2i ret;

    ret.x = context->col;
    ret.y = context->rows;

    return ret;
}

void deinitTerm(struct terminal_context_t* context)
{
    SetConsoleMode(context->hStdin, &context->mode);

    if(context)
    {
        free(context);
    }
}

char getch(struct terminal_context_t* context)
{
    INPUT_RECORD event;
    int test = 0;
    if(WaitForSingleObject(context->hStdin, 0) == WAIT_OBJECT_0)
    {
    	ReadConsoleInput(context->hStdin, &event, 1, &test);
		if((event.EventType == KEY_EVENT)
            &&  !event.Event.KeyEvent.bKeyDown)
        {
        	return event.Event.KeyEvent.uChar.AsciiChar;
        }	
    }
    return 0;
}

void drawToTerm(struct terminal_context_t* context, char* buffer, int size)
{
	int test = 0;
    WriteConsole(context->hStdout, buffer, size, &test, NULL);
}

void clearTerm(struct terminal_context_t* context)
{
    COORD baseCoords = {0,0};
    SetConsoleCursorPosition(context->hStdout, baseCoords);
}

int querySignals(struct terminal_context_t* context)
{
	char c = getch (context);
    if (GetKeyState(VK_CONTROL) && (c == 's' || c == 'S'))
    {
        return 1;
    }
	return 0;
}
