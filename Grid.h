#pragma once

#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <conio.h>
#include <vector>
#include <map>
#include <algorithm>

 /*������� ������� �����.*/
constexpr auto INDENTX = 700;
constexpr auto INDENTY = 200;
constexpr auto CELLSIZE = 10;

 /*�������� ������� ���������.*/
constexpr auto BLACK_C = RGB(0, 0, 2);
constexpr auto BEIGE_C = RGB(88, 54, 53);
constexpr auto YELLOW_C = RGB(255, 202, 64);
constexpr auto PINK_C = RGB(148, 4, 119);
constexpr auto RED_C = RGB(255, 0, 0);
constexpr auto BLUE_C = RGB(92, 204, 204);
constexpr auto GRIN_C = RGB(152, 211, 13);
constexpr auto SKIN_C = RGB(255, 178, 115);
constexpr auto PURPLE_C = RGB(72, 3, 111);
constexpr auto ORANGE_C = RGB(255, 116, 0);

 /*���������� �����.*/
struct Dot {
    int x ;
    int y ;
};

class Grid {

public:
    // ����������� �� ���������.
    Grid();  
    // ����������� � �����������.
    Grid(int width, int heigth);
    // ����������.
    ~Grid();
    // ������ �����.
    void CreateGrid();
    // ������ ����� �� ������ ���.
    void LineDDA(Dot dot1, Dot dot2);
    // ������ ����� �� ������ ����������.
    void LineBresenham(Dot dot1, Dot dot2);
    // ������ ����.
    void Circle(Dot dot, int radius, COLORREF BorderColor);
    // ������ �����������.
    void Triangle(Dot dot1, Dot dot2, Dot dot3, COLORREF BorderColor);
    // ������ �������������.
    void Polygon(std::vector<Dot> dots, COLORREF BorderColor);
    // �������� ����� �� �����.
    COLORREF SetBrush();
       
private:
    /* ��������� �����.*/
    HWND hwnd;
    HDC hdc;
    int start_x;
    int start_y;
    int stop_x;
    int stop_y;
    int step;
    bool net_create;

    // ����������� �������.
    void PutPixel(int left, int top, int right, int buttom);
    // ����� �� ������ ��� �� ��� �.
    void LineXDDA(Dot dot1, Dot dot2);
    // ����� �� ������ ��� �� ��� Y.
    void LineYDDA(Dot dot1, Dot dot2);
    // ����� ������ ���������� �����.
    void CircleFilledMethod(Dot dot, int radius, COLORREF BorderColor);
    // ����� ����� ��������� ������������.
    void TriangleFilledMethod(Dot dot1, Dot dot2, Dot dot3, COLORREF BorderColor);
    // ����� ���������� ��������������.
    void PolygonFilledMethod(std::vector<Dot> dots, COLORREF BorderColor);
    // ����� ���������� ������������.
    void FilledTriangle(Dot dot1, Dot dot2, Dot dot3);
    // ����� ���������� ���������.
    void FilledSeed(Dot dot, COLORREF BolderColor, COLORREF selfColor);
    // ����� ���������� ������� �������� �����.
    void FilledEdgePoints(std::vector<Dot> dots, COLORREF BorderColor, COLORREF SelfColor);
    // ����� ������������ ������.
    void DelaunayTriangulation(std::vector<Dot> dots, COLORREF BorderColor, COLORREF SelfColor);
    // ���������� ������� ����� � ��������������.
    Dot GetMiddleDot(Dot dot1, Dot dot2);
    // ��������� ������� �� �������������� �����.
    bool InGrid(int left, int top);
    // �������� ����� �����.
    char GetColor();   
};