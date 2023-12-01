#include "Grid.h"

void Grid::PutPixel(int left, int top, int right, int buttom)
{
    if (InGrid(left, top)) Ellipse(hdc, left, top, right, buttom);
}

void Grid::LineDDA(Dot dot1, Dot dot2)
{
    if (!net_create) CreateGrid();
    LineXDDA(dot1, dot2);
    LineYDDA(dot1, dot2);
}

void Grid::LineXDDA(Dot dot1, Dot dot2)
{
    if (dot1.x > dot2.x)
    {
        Dot temp = dot1;
        dot1 = dot2;
        dot2 = temp;
    }
    double steps = (double)(dot2.y - dot1.y) / (dot2.x - dot1.x);
    int x = dot1.x;
    int y = dot1.y;
    double double_y = dot1.y;
    int left_x = 0;
    int top_y = 0;
    while (x <= dot2.x)
    {
        left_x = start_x + x * step;
        top_y = stop_y - (y + 1) * step;
        PutPixel(left_x + 1, top_y + 1, left_x + step, top_y + step);
        double_y += steps;
        y = round(double_y);
        x++;
    }
}

void Grid::LineYDDA(Dot dot1, Dot dot2)
{
    if (dot1.y > dot2.y)
    {
        Dot temp = dot1;
        dot1 = dot2;
        dot2 = temp;
    }
    double steps = (double)(dot2.x - dot1.x) / (dot2.y - dot1.y);
    int x = dot1.x;
    int y = dot1.y;
    double double_x = dot1.x;
    int left_x = 0;
    int top_y = 0;
    while (y <= dot2.y)
    {
        left_x = start_x + x * step;
        top_y = stop_y - (y + 1) * step;
        PutPixel(left_x + 1, top_y + 1, left_x + step, top_y + step);
        double_x += steps;
        x = round(double_x);
        y++;
    }
}

void Grid::LineBresenham(Dot dot1, Dot dot2)
{
    if (!net_create) CreateGrid();

    if (dot1.x > dot2.x) {         // Делаем так, чтобы при рисовании
        Dot temp = dot1;            // линии мы всегда шли слева
        dot1 = dot2;                // на право.
        dot2 = temp;
    }

    int left_x1 = start_x + dot1.x * step, top_y1 = stop_y - (dot1.y + 1) * step; // Определяем положение левого верхнего угла (x1,y1).
    int left_x2 = start_x + dot2.x * step, top_y2 = stop_y - (dot2.y + 1) * step; // Определяем положение левого верхнего угла (x2,y2).
    PutPixel(left_x1 + 1, top_y1 + 1, left_x1 + step, top_y1 + step); // Заполняем квадрат.
    PutPixel(left_x2 + 1, top_y2 + 1, left_x2 + step, top_y2 + step); // Заполняем квадрат.    

    double dx = static_cast<double>(dot2.x - dot1.x);  // Находим коэффициент
    double dy = static_cast<double>(dot2.y - dot1.y);  // наклона прямой
    double k = dy / dx;                                // через приращение.


    if (k > 0 && dx != 0) {
        double kf = dy / dx;

        while (kf >= 0) {
            dy -= 1;
            dx -= 1;
            kf = dy / dx;
            if (kf < k && dx != 0) {       // Если наклон на данном пикселе больше,
                // чем у всей прямой, то уходим вправо
                left_x1 += step;           // на одну влетку.
                PutPixel(left_x1 + 1, top_y1 + 1, left_x1 + step, top_y1 + step); // Заполняем квадрат.
                dy += 1;
            }
            else if (kf >= k || dx == 0) {      // Если наклон на данном пикселе меньше,
                // чем у всей прямой, то уходим вверх
                top_y1 -= step;                 // на одну клетку.
                PutPixel(left_x1 + 1, top_y1 + 1, left_x1 + step, top_y1 + step); // Заполняем квадрат.
                dx += 1;
            }

        }
    }
    else if (k < 0 && dx != 0) {
        double kf = dy / dx;

        while (kf <= 0) {
            dy += 1;
            dx -= 1;
            kf = dy / dx;
            if (kf >= k && dx != 0) {      // Если наклон на данном пикселе больше,
                left_x1 += step;           // чем у всей прямой, 
                // то уходим вправо 
                PutPixel(left_x1 + 1, top_y1 + 1, left_x1 + step, top_y1 + step); // Заполняем квадрат.
                dy -= 1;
            }
            else if (kf < k || dx == 0) {      // Если наклон на данном пикселе меньше,
                // чем у всей прямой, то уходим вниз
                top_y1 += step;                // на одну клетку.
                PutPixel(left_x1 + 1, top_y1 + 1, left_x1 + step, top_y1 + step); // Заполняем квадрат.
                dx += 1;
            }

        }
    }
    else {
        if (dot1.x == dot2.x) {
            while (top_y1 != stop_y - dot2.y * step) {
                Ellipse(hdc, left_x1 + 1, top_y1 + 1, left_x1 + step, top_y1 + step); // Заполняем квадрат.
                top_y1 -= step;
            }
        }
        else if (dot1.y == dot2.y) {
            while (left_x1 != start_x + dot2.x * step) {
                Ellipse(hdc, left_x1 + 1, top_y1 + 1, left_x1 + step, top_y1 + step); // Заполняем квадрат.         
                left_x1 += step;
            }
        }
    }
}

void Grid::Circle(Dot dot, int radius, COLORREF BorderColor)
{
    if (!net_create) CreateGrid();

    int x = radius;
    int y = 0;
    int true_radius = radius / sqrt(2);

    int left_x = start_x + dot.x * step;
    int top_y = stop_y - (dot.y + 1) * step;
    while (abs(x) >= true_radius)
    {
        PutPixel(left_x + x * step + 1, top_y + y * step + 1, left_x + x * step + step, top_y + y * step + step);
        PutPixel(left_x + x * step + 1, top_y - y * step + 1, left_x + x * step + step, top_y - y * step + step);
        PutPixel(left_x - x * step + 1, top_y + y * step + 1, left_x - x * step + step, top_y + y * step + step);
        PutPixel(left_x - x * step + 1, top_y - y * step + 1, left_x - x * step + step, top_y - y * step + step);
        PutPixel(left_x + y * step + 1, top_y + x * step + 1, left_x + y * step + step, top_y + x * step + step);
        PutPixel(left_x + y * step + 1, top_y - x * step + 1, left_x + y * step + step, top_y - x * step + step);
        PutPixel(left_x - y * step + 1, top_y + x * step + 1, left_x - y * step + step, top_y + x * step + step);
        PutPixel(left_x - y * step + 1, top_y - x * step + 1, left_x - y * step + step, top_y - x * step + step);
        int dh = x * x + (y - 1) * (y - 1) - radius * radius;
        int dc = (x - 1) * (x - 1) + (y - 1) * (y - 1) - radius * radius;
        if (abs(dh) > abs(dc)) --x;
        --y;
    }
    CircleFilledMethod(dot, radius, BorderColor);
}

void Grid::Triangle(Dot dot1, Dot dot2, Dot dot3, COLORREF BorderColor)
{
    std::cout << "What method to draw?\n"
        "1 - DDA;\n"
        "2 - Bresenham;\n";
    switch (char ch = _getch())
    {
    case '1':
        LineDDA(dot1, dot2);
        LineDDA(dot1, dot3);
        LineDDA(dot2, dot3);
        break;
    case '2':
        LineBresenham(dot1, dot2);
        LineBresenham(dot1, dot3);
        LineBresenham(dot2, dot3);
        break;
    }

    TriangleFilledMethod(dot1, dot2, dot3, BorderColor);
}

void Grid::Polygon(std::vector<Dot> dots, COLORREF BorderColor)
{
    std::cout << "What method to draw?\n"
        "1 - DDA;\n"
        "2 - Bresenham;\n";
    switch (char ch = _getch())
    {
    case '1':
        for (int i = 1; i < dots.size(); ++i) {
            LineDDA(dots[i - 1], dots[i]);
        }
        LineDDA(dots[0], dots[dots.size() - 1]);
        break;
    case '2':
        for (int i = 1; i < dots.size(); ++i) {
            LineBresenham(dots[i - 1], dots[i]);
        }
        LineBresenham(dots[0], dots[dots.size() - 1]);
        break;
    }
    
    PolygonFilledMethod(dots, BorderColor);
}

void Grid::Points(std::vector<Dot> dots, COLORREF BorderColor) 
{
    for (Dot dot : dots) {
        int left_x = start_x + dot.x * step;
        int top_y = stop_y - (dot.y + 1) * step;
        PutPixel(left_x + 1, top_y + 1, left_x + step, top_y + step);
    }

    PointsFilledMethod(dots, BorderColor);
}

bool Grid::InGrid(int left, int top)
{
    if (left >= start_x && left < stop_x && top >= start_y && top < stop_y) return true;
    else return false;
}
