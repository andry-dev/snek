#include "input/Common.h"


#define WIN32_LEAN_AND_MEAN
#include <windows.h>

struct terminal_context_t
{
    DWORD hStdin;
    DWORD hStdout;
    DWORD mode;
    unsigned short col;
    unsigned short rows;
};

struct terminal_context_t* initTerm()
{
    struct terminal_context_t* ret = malloc(sizeof(struct terminal_context_t));
    DWORD temp_mode;
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    COORD baseCoords = {0,0};

    ret->hStdin = GetStdHandle(STD_INPUT_HANDLE);
    ret->hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(ret->hStdout, baseCoords);
    
    GetConsoleScreenBufferInfo(ret->hStdout, &bufferInfo);

    ret->col = bufferInfo.srWindow.Right - bufferInfo.srWindow.Left + 1;
    ret->rows = bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top + 1;
    
    GetConsoleMode(ret->hStdin, &ret->mode);
    
    temp_mode = ret->mode;

    temp_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);

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

char getch(TerminalContext* context)
{
    TCHAR input = 0;
    ReadConsole(context->hStdin, &input, 1, NULL, NULL);
    return (char)input;
}

void drawToTerm(struct terminal_context_t* context, char* buffer, int size)
{
    WriteConsole(context->hStdout, buffer, size, NULL, NULL);
}

void clearTerm(struct terminal_context_t* context)
{
    COORD baseCoords = {0,0};
    SetConsoleCursorPosition(context->hStdout, baseCoords);
}
