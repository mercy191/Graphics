#pragma once

#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <conio.h>
#include <vector>
#include <map>
#include <algorithm>

 /*Размеры отступа сетки.*/
constexpr auto INDENTX = 700;
constexpr auto INDENTY = 200;
constexpr auto CELLSIZE = 10;

 /*Цветовая палитра программы.*/
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

 /*Координаты точки.*/
struct Dot {
    int x ;
    int y ;
};

class Grid {

public:
    /*Основные функции для работы с классом.*/

    // Конструктор по умолчанию.
    Grid();  
    // Конструктор с аргументами.
    Grid(int width, int heigth);
    // Деструктор.
    ~Grid();
    // Рисует сетку.
    void CreateGrid();
    // Рисует линию по методу ЦДА.
    void LineDDA(Dot dot1, Dot dot2);
    // Рисует линию по методу Брезенхема.
    void LineBresenham(Dot dot1, Dot dot2);
    // Рисует круг.
    void Circle(Dot dot, int radius, COLORREF BorderColor);
    // Рисует треугольник.
    void Triangle(Dot dot1, Dot dot2, Dot dot3, COLORREF BorderColor);
    // Рисует многоугольник.
    void Polygon(std::vector<Dot> dots, COLORREF BorderColor);
    // Рисует множество точек.
    void Points(std::vector<Dot> dots, COLORREF BorderColor);
    // Выбирает кисть по цвету.
    COLORREF SetBrush();
       
private:
    /* Параметры сетки.*/
    HWND hwnd;
    HDC hdc;
    int start_x;
    int start_y;
    int stop_x;
    int stop_y;
    int step;
    bool net_create;   

    /*Выбор методов заполнения различных фигур.*/

    // Выбор метода заполнения круга.
    void CircleFilledMethod(Dot dot, int radius, COLORREF BorderColor);
    // Выбор метода заполения треугольника.
    void TriangleFilledMethod(Dot dot1, Dot dot2, Dot dot3, COLORREF BorderColor);
    // Выбор метода заполнения многоугольника.
    void PolygonFilledMethod(std::vector<Dot> dots, COLORREF BorderColor);
    // Выбор метода заполнения точек.
    void PointsFilledMethod(std::vector<Dot> dots, COLORREF BorderColor);

    /*Методы заполнения различных фигур.*/

    // Метод заполнения треугольника.
    void FilledTriangle(Dot dot1, Dot dot2, Dot dot3);
    // Метод заполнения затравкой.
    void FilledSeed(Dot dot, COLORREF BolderColor, COLORREF selfColor);
    // Метод заполнения списком реберных точек.
    void FilledEdgePoints(std::vector<Dot> dots, COLORREF BorderColor, COLORREF SelfColor);
    // Метод Триангуляции Делоне.
    void DelaunayTriangulation(std::vector<Dot> dots, COLORREF BorderColor, COLORREF SelfColor);

    /*Вспомогательные функции.*/

    // Закрашивает пиксель.
    void PutPixel(int left, int top, int right, int buttom);
    // Линия по методу ЦДА по оси Х.
    void LineXDDA(Dot dot1, Dot dot2);
    // Линия по методу ЦДА по оси Y.
    void LineYDDA(Dot dot1, Dot dot2);
    // Нахождение средней точки в многоугольнике.
    Dot GetMiddleDot(Dot dot1, Dot dot2);
    // Проверяет пиксель на принадлежность сетке.
    bool InGrid(int left, int top);
    // Получает номер цвета.
    char GetColor();
    // Получает самое первое ребро для Триангуляции Делоне.
    void GetFirstEdge(std::vector<Dot>& dots, int& index0, int& index1);
    // Возвращает индекс самого короткого ребра в списке.
    int MostShortEdge(std::vector<Dot>& edges);
    // Находит точку, удовлетворяющую условию Делоне.
    void JoinDot(Dot& a, Dot& b, std::vector<Dot>& dots, std::vector<Dot>& adj);
    // Находит параметр 2*t для нахождения центра описанной окружности вокруг треугольника.
    double TwoT(Dot& dot1, Dot& dot2, Dot& dot3);
    // Добавляет ребро, если это ребро не является стороной треугольников.
    void AddEdge(std::vector<Dot>& edges, std::vector<Dot>& triangle, Dot& dot1, Dot& dot2);
    // Проверяет совпадение точек.
    bool SameDots(Dot& dot1, Dot& dot2);
    // Проверяет совпадение отрезков.
    bool SameEdges(Dot& dot1, Dot& dot2, Dot& dot3, Dot& dot4);
    // Проверяет равенство треугольников.
    bool SameTriangles(Dot& dot1_1, Dot& dot1_2, Dot& dot1_3, Dot& dot2_1, Dot& dot2_2, Dot& dot2_3);
    // Проверяет ребро на принадлежность к треугольнику.
    bool EdgeInTriangle(std::vector<Dot>& triangle, Dot& dot1, Dot& dot2);
    // Добавляет треугольник.
    void AddTriangle(std::vector<Dot>& triangles, Dot& dot1, Dot& dot2, Dot& dot3);
    // Возвращает косинус угла между ребрами.
    double CosEdges(Dot& dot1, Dot& dot2, Dot& dot3);
    // Переставляет точки местами.
    void SwapDots(Dot& dot1, Dot& dot2);

};