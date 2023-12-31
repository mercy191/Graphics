#include "Grid.h"

void Grid::CircleFilledMethod(Dot dot, int radius, COLORREF BorderColor)
{
    std::cout << "What method to fill?\n"
        "1 - Filling method;\n"
        "2 - Seeding method;\n";
    switch (char ch = _getch())
    {
        COLORREF SelfColor;
    case '1':
    {
        Dot dot2;
        Dot dot3;
        SelfColor = SetBrush();
        for (int i = 0; i < 40; ++i) {
            dot2.x = dot.x + round(sin(0.157 * i) * (radius - 1));
            dot2.y = dot.y + round(cos(0.157 * i) * (radius - 1));
            dot3.x = dot.x + round(sin(0.157 * (i + 4)) * (radius - 1));
            dot3.y = dot.y + round(cos(0.157 * (i + 4)) * (radius - 1));
            this->FilledTriangle(dot, dot2, dot3);
        }
        break;
    }
    case '2':
    {
        SelfColor = SetBrush();
        BorderColor = GetPixel(hdc, start_x + dot.x * step + step / 2, stop_y - (dot.y + 1) * step + step / 2);
        this->FilledSeed(dot, BorderColor, SelfColor);
        break;
    }

    }
}

void Grid::TriangleFilledMethod(Dot dot1, Dot dot2, Dot dot3, COLORREF BorderColor)
{
    std::cout << "What method to fill?\n"
        "1 - Filling method;\n"
        "2 - Seeding method;\n";
    switch (char ch = _getch())
    {
        COLORREF SelfColor;
    case '1':
    {
        SelfColor = SetBrush();
        this->FilledTriangle(dot1, dot2, dot3);
        break;
    }
    case '2':
    {
        Dot dot = GetMiddleDot(dot1, GetMiddleDot(dot2, dot3));
        SelfColor = SetBrush();
        BorderColor = GetPixel(hdc, start_x + dot.x * step + step / 2, stop_y - (dot.y + 1) * step + step / 2);
        this->FilledSeed(dot, BorderColor, SelfColor);
        break;
    }

    }
}

void Grid::PolygonFilledMethod(std::vector<Dot> dots, COLORREF BorderColor)
{
    std::cout << "What method to fill?\n"
        "1 - Edgepoints method;\n"
        "2 - Seeding method;\n"
        "3 - Delaynay Triangulation\n";
    switch (char ch = _getch())
    {
        COLORREF SelfColor;
    case '1':
    {
        SelfColor = SetBrush();
        this->FilledEdgePoints(dots, BorderColor, SelfColor);
        break;
    }
    case '2':
    {
        Dot dot = GetMiddleDot(GetMiddleDot(dots[0], dots[1]), GetMiddleDot(dots[dots.size() - 1], dots[dots.size() - 2]));
        SelfColor = SetBrush();
        BorderColor = GetPixel(hdc, start_x + dot.x * step + step / 2, stop_y - (dot.y + 1) * step + step / 2);
        this->FilledSeed(dot, BorderColor, SelfColor);
        break;
    }
    case '3':
    {
        SelfColor = SetBrush();
        this->DelaunayTriangulation(dots, BorderColor, SelfColor);
        break;
    }

    }
}

void Grid::PointsFilledMethod(std::vector<Dot> dots, COLORREF BorderColor)
{
    std::cout << "What method to fill?\n"
        "1 - Delaynay Triangulation\n";
    switch (char ch = _getch())
    {
        COLORREF SelfColor;
    case '1':
    {
        SelfColor = SetBrush();
        this->DelaunayTriangulation(dots, BorderColor, SelfColor);
        break;
    }

    }
}

void Grid::FilledTriangle(Dot dot1, Dot dot2, Dot dot3)
{
    int x_dots[3] = { dot1.x, dot2.x, dot3.x };
    int y_dots[3] = { dot1.y, dot2.y, dot3.y };

    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            if (y_dots[j] < y_dots[j + 1])
            {
                int tmp = y_dots[j + 1];
                y_dots[j + 1] = y_dots[j];
                y_dots[j] = tmp;
                tmp = x_dots[j + 1];
                x_dots[j + 1] = x_dots[j];
                x_dots[j] = tmp;
            }
    dot3.y = y_dots[0]; dot2.y = y_dots[1]; dot1.y = y_dots[2];
    dot3.x = x_dots[0]; dot2.x = x_dots[1]; dot1.x = x_dots[2];

    int x1, x2, sy = dot3.y;
    for (; sy >= dot2.y; --sy)
    {
        if (dot2.y != dot3.y) {
            x1 = dot3.x + int(round((dot1.x - dot3.x) * (sy - dot3.y) / (dot1.y - dot3.y)));
            x2 = dot3.x + int(round((dot2.x - dot3.x) * (sy - dot3.y) / (dot2.y - dot3.y)));
            LineDDA({ x1, sy }, { x2, sy });
        }       
    }
    for (; sy >= dot1.y; --sy)
    {
        x1 = dot3.x + int(round((dot1.x - dot3.x) * (sy - dot3.y) / (dot1.y - dot3.y)));
        x2 = dot2.x + int(round((dot1.x - dot2.x) * (sy - dot2.y) / (dot1.y - dot2.y)));
        LineDDA({ x1, sy }, { x2, sy });
    }

}

void Grid::FilledSeed(Dot dot, COLORREF BorderColor, COLORREF SelfColor)
{
    int x = dot.x;
    int y = dot.y;
    int left_x = start_x + dot.x * step;
    int top_y = stop_y - (dot.y + 1) * step;
    if (!InGrid(left_x, top_y)) return;
    auto c = GetPixel(hdc, left_x + step / 2, top_y + step / 2);
    if ((c == BorderColor) && (c != SelfColor))
    {
        PutPixel(left_x + 1, top_y + 1, left_x + step, top_y + step);
        this->FilledSeed({ x - 1, y }, BorderColor, SelfColor);
        this->FilledSeed({ x + 1, y }, BorderColor, SelfColor);
        this->FilledSeed({ x, y - 1 }, BorderColor, SelfColor);
        this->FilledSeed({ x, y + 1 }, BorderColor, SelfColor);
    }
}

void Grid::FilledEdgePoints(std::vector<Dot> dots, COLORREF BorderColor, COLORREF SelfColor)
{  
    std::map<int, std::vector<int>> edgepoints;
    std::vector<std::pair<Dot, Dot>> edges;

    for (int i = 1; i < dots.size(); ++i) {
        Dot dot1 = dots[i - 1];
        Dot dot2 = dots[i];
        if (dot1.y != dot2.y)
            edges.push_back(std::make_pair(dot1, dot2));
    }
    if (dots[dots.size() - 1].y != dots[0].y) {
        edges.push_back(std::make_pair(dots[dots.size() - 1], dots[0]));
    }

    for (auto& edge : edges) {
        int y1 = edge.first.y;
        int y2 = edge.second.y;
        int x1 = edge.first.x;
        int x2 = edge.second.x;
        if (y1 > y2) {
            std::swap(y1, y2);
            std::swap(x1, x2);
        }
        
        double ctg = double(x2 - x1) / double(y2 - y1);

        for (int y = y1; y < y2; ++y) {          
            int x = x1 + std::round(ctg * (y - y1)); 

            auto iter = edgepoints.find(y);
            if (iter != edgepoints.end()) {
                iter->second.push_back(x);
                std::sort(iter->second.begin(), iter->second.end());
            }
            else {
                std::vector<int> vec;
                vec.push_back(x);
                edgepoints.emplace(y, vec);
            }           
        }
    }

    int y_min = dots[0].y;
    int y_max = dots[0].y;

    for (int i = 0; i < dots.size(); ++i) {
        if (y_min > dots[i].y) y_min = dots[i].y;
        if (y_max < dots[i].y) y_max = dots[i].y;
    }

    for (int y = y_min; y < y_max; ++y) {
        std::vector<int> vec = edgepoints[y];
        for (int i = 1; i < vec.size(); i += 2) {
            int x1 = vec[i - 1]; 
            int x2 = vec[i];

            while (x1 <= x2) {
                int left_x = start_x + x1 * step;
                int top_y = stop_y - (y + 1) * step;
                auto c = GetPixel(hdc, left_x + step / 2, top_y + step / 2);
                if (c != BorderColor) {
                    PutPixel(left_x + 1, top_y + 1, left_x + step, top_y + step);
                }
                ++x1;
            }
        }
    }  
}

void Grid::DelaunayTriangulation(std::vector<Dot> dots, COLORREF BorderColor, COLORREF SelfColor)
{
    std::vector<Dot> triangles; // ������ ���������� ������������� �� ������������ ������
    std::vector<Dot> edges;     // ������ �����.
    std::vector<Dot> adj;       // ������ ������, �������������� � �����.
    Dot dot1, dot2, dot3;

    if (dots.size() < 3) {
        return;
    }

    // ��������� ��������� �����.
    int i0 = 0, i1 = 0; 
    GetFirstEdge(dots, i0, i1);   
    edges.push_back(dots[i0]);
    edges.push_back(dots[i1]);
    


    while (edges.size() > 0) { // ���� ���� �����, ������� �� �� ����������
        // ������� ����� �������� ����� � ������
        int index = MostShortEdge(edges);
        dot1 = edges[index];
        dot2 = edges[index + 1];
        edges.erase(edges.begin() + index, edges.begin() + index + 2);
        JoinDot(dot1, dot2, dots, adj);

        
        if (adj.size() == 0) continue;	// ���� �������������� ������ ��� - ������ ���� ������.

        if (adj.size() == 1) {  // ���� �������������� ������� ������ ����.
            dot3 = adj[0];
            int triangle_sq = (dot2.x - dot1.x) * (dot3.y - dot1.y) - (dot2.y - dot1.y) * (dot3.x - dot1.x);
            if (triangle_sq <= 0) return;

            // ������� ����� � ������, ���� ��� �� �������� ������� ������������.
            AddEdge(edges, triangles, dot1, dot3); // (dot1,dot3)
            AddEdge(edges, triangles, dot3, dot2); // (dot3,dot2)
            AddTriangle(triangles, dot1, dot2, dot3);
            continue;
        }

        // ������� ������, ����� ������������� ������ ���������.
        // ����������� �� � ������� ����������� �������� ���� <dot2, dot1, adj[i]>
        for (int i = 1; i < adj.size(); ++i) {
            double a0 = CosEdges(dot2, dot1, adj[i - 1]);
            double a1 = CosEdges(dot2, dot1, adj[i]);
            if (a0 < a1) {
                SwapDots(adj[i - 1], adj[i]);
                if (i > 1) i -= 2;
            }

        }

        // ������ ���� <dot2, dot1, adj[i]> ����������.
        // ��������� ������������
        // dot1, dot2, adj[0],
        // dot1, adj[0], adj[1],
        // ...
        // dot1, adj[k-2], adj[k-1],
        AddEdge(edges, triangles, adj[0], dot2);      // (adj[0], dot2)
        AddTriangle(triangles, dot1, dot2, adj[0]);

        for (int i = 1; i < adj.size(); ++i) {
            AddEdge(edges, triangles, adj[i], adj[i - 1]); // (adj[i], adj[i-1])
            AddTriangle(triangles, dot1, adj[i], adj[i - 1]);
        }

        AddEdge(edges, triangles, dot1, adj[adj.size() - 1]); // (dot1, adj[last])
    }

    // ���������� ������ ������� � ������ ����������� ���, ����� ��� ������� ���� > 0.
    for (int i = 0; i < triangles.size(); i += 3) {
        int triangle_sq = (triangles[i + 1].x - triangles[i].x) * (triangles[i + 2].y - triangles[i].y) - 
            (triangles[i + 1].y - triangles[i].y) * (triangles[i + 2].x - triangles[i].x);
        if (triangle_sq < 0) {
            SwapDots(triangles[i], triangles[i + 1]);
        }
    }

    // ������� ������������ �� �����.
    for (int i = 0; i < triangles.size(); i += 3) {

        LineDDA(triangles[i], triangles[i + 1]);
        LineDDA(triangles[i], triangles[i + 2]);
        LineDDA(triangles[i + 1], triangles[i + 2]);
    }
}
