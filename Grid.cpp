#include "Grid.h"

Grid::Grid() : start_x{ INDENTX }, start_y{ INDENTY }, step{ CELLSIZE },
stop_x{ 480 }, stop_y{ 680 }, net_create{ false }
{
    hwnd = GetConsoleWindow();
    hdc = GetDC(hwnd);
}

Grid::Grid(int width, int heigth) : start_x{ INDENTX }, start_y{ INDENTY },
step{ CELLSIZE }, net_create{ false }
{
    stop_x = start_x + step * width;
    stop_y = start_y + step * heigth;
    hwnd = GetConsoleWindow();
    hdc = GetDC(hwnd);
}

Grid::~Grid()
{
    ReleaseDC(hwnd, hdc);
}

void Grid::CreateGrid()
{
    SelectBrush(hdc, GetStockBrush(BLACK_BRUSH));
    SelectPen(hdc, GetStockPen(WHITE_PEN));

    for (int x = start_x; x <= stop_x; x += step) { // Рисуем линии по оси Y.
        MoveToEx(hdc, x, start_y, NULL);
        LineTo(hdc, x, stop_y);
    }
    for (int y = start_y; y <= stop_y; y += step) { // Рисуем линии по оси Х.
        MoveToEx(hdc, start_x, y, NULL);
        LineTo(hdc, stop_x, y);
    }
    net_create = true;
}




