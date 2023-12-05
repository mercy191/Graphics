#include "Grid.h"

int main()
{
    int height, widht;
    std::cout << "Enter grid widht and height: ";
    std::cin >> height >> widht;
    Grid my_grid(widht, height);
    my_grid.CreateGrid();
    std::cout << "Functional:\n"
        "1 - DDA line; "
        "2 - Bresenham line; "
        "3 - Circle;\n"
        "4 - Triangle; "
        "5 - Polygon; "
        "6 - Delaunay Triangulation;\n";
    for (bool flag = true; flag;)
    {
        std::cout << "What are we drawing?\n";
        switch (char ch = _getch())
        {
            COLORREF color;
        case '1':
        {
            Dot dot1, dot2;
            std::cout << "Enter (x1,y1) and (x2,y2): ";
            std::cin >> dot1.x >> dot1.y >> dot2.x >> dot2.y;
            color = my_grid.SetBrush();
            my_grid.LineDDA(dot1, dot2);
            break;
        }
        case '2':
        {
            Dot dot1, dot2;
            std::cout << "Enter (x1,y1) and (x2,y2): ";
            std::cin >> dot1.x >> dot1.y >> dot2.x >> dot2.y;
            color = my_grid.SetBrush();
            my_grid.LineBresenham(dot1, dot2);
            break;
        }
        case '3':
        {
            Dot dot0;
            int radius;
            std::cout << "Enter (x0,y0) and radius: ";
            std::cin >> dot0.x >> dot0.y >> radius;
            color = my_grid.SetBrush();
            my_grid.Circle(dot0, radius, color);
            break;
        }
        case '4':
        {
            Dot dot1, dot2, dot3;
            std::cout << "Enter (x1,y1), (x2,y2) and (x3,y3): ";
            std::cin >> dot1.x >> dot1.y >> dot2.x >> dot2.y >> dot3.x >> dot3.y;
            color = my_grid.SetBrush();
            my_grid.Triangle(dot1, dot2, dot3, color);
            break;
        }
        case '5':
        {
            int points;
            Dot dot;
            std::cout << "Enter number of points: ";
            std::cin >> points;
            std::vector<Dot> dots(points);
            std::cout << "Enter the coordinates of the points: ";
            for (int i = 0; i < points; ++i) {
                std::cin >> dot.x >> dot.y;
                dots[i] = dot;
            }
            color = my_grid.SetBrush();
            my_grid.Polygon(dots, color);
            break;

        }
        case '6':
        {
            int points;
            Dot dot;
            std::cout << "Enter number of points: ";
            std::cin >> points;
            std::vector<Dot> dots(points);
            std::cout << "Enter the coordinates of the points: ";
            srand(time(0));
            for (int i = 0; i < points; ++i) {
                dot.x = rand() % 119 + 1;
                dot.y = rand() & 119 + 1;
                dots[i] = dot;
            }
            color = my_grid.SetBrush();
            my_grid.Points(dots, color);
            break;
        }
        
        }
        std::cout << "More?(y/n): \n";
        flag = _getch() == 'y';
    }
}