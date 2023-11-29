#include "Grid.h"

Dot Grid::GetMiddleDot(Dot dot1, Dot dot2)
{
    Dot result;
    result.x = int(round((dot1.x + dot2.x) / 2));
    result.y = int(round((dot2.y + dot1.y) / 2));
    return result;
}

void Grid::GetFirstEdge(std::vector<Dot>& dots, int& index0, int& index1)
{
    // сначала найдем a0 - самую левую точку
    int min_x = 999999999;
    int i = 0, min_i = 0;
    for (i = 0; i < dots.size(); i++) {
        int x = dots[i].x;
        if (x < min_x) { min_x = x; min_i = i; }
    }
    index0 = min_i;
    // теперь среди остальных вершин выбираем идущую круче всех вверх -
    // то есть с наименьшим угловым коэффициентом (dy/dx - минимум)
    double k_min = 2e99;
    int min_diff = 999999999;
    for (i = 0; i < dots.size(); i++) {
        if (i == index0) continue;
        int dx = dots[i].x - dots[index0].x;			// так как (index0) самая левая точка, то dx>=0
        int dy = dots[i].y - dots[index0].y;				// dy - любое
        double kA = dx == 0 ? -2e99 : dy / (double)dx;
        if (kA < k_min) {
            k_min = kA;
            min_diff = abs(dx) + abs(dy);
            min_i = i;
            continue;
        }
        // Если же коэффициенты равны, выберем более короткий вектор:
        if (kA == k_min) {
            int diff1 = abs(dx) + abs(dy);
            if (diff1 < min_diff) { min_diff = diff1; min_i = i; }
        }
    }
    index1 = min_i;
}

int Grid::MostShortEdge(std::vector<Dot>& edges)
{
    int len = 2147483647; // INT_MAX;
    int i_min = -1;
    for (int i = 0; i < edges.size(); i += 2) {
        int a = edges[i].x - edges[i + 1].x;
        int b = edges[i].y - edges[i + 1].y;
        int sum_sq = a * a + b * b;
        if (sum_sq < len) {
            i_min = i;
            len = sum_sq;
        }
    }
    return i_min;
}

void Grid::JoinDot(Dot& dot1, Dot& dot2, std::vector<Dot>& dots, std::vector<Dot>& adj)
{
    double min_2t = 1e99;
    adj.clear();
    for (int i = 0; i < dots.size(); i++) {
        Dot dot3;
        dot3.x = dots[i].x;
        dot3.y = dots[i].y;

        int triangle_sq = (dot2.x - dot1.x) * (dot3.y - dot1.y) - (dot2.y - dot1.y) * (dot3.x - dot1.x);
        if (triangle_sq <= 0) {
            continue;
        }

        double TwoT_ = -TwoT(dot1, dot2, dot3);
        if (TwoT_ == min_2t) {
            adj.push_back(dot3); // еще одна точка на одной и той же окружности
        }

        if (TwoT_ < min_2t) {
            min_2t = TwoT_;
            adj.clear();
            adj.push_back(dot3);
        } // нашли новую окружность, меньше прежней
    }
}

double Grid::TwoT(Dot& dot1, Dot& dot2, Dot& dot3)
{
    double d = double(dot3.y - dot2.y) * (dot2.x - dot1.x) - double(dot3.x - dot2.x) * (dot2.y - dot1.y);
    if (d == 0) return 1e99;
    return (double(dot3.x - dot2.x) * (dot1.x - dot3.x) + double(dot3.y - dot2.y) * (dot1.y - dot3.y)) / d;
}

void Grid::AddEdge(std::vector<Dot>& edges, std::vector<Dot>& triangles, Dot& dot1, Dot& dot2)
{
    for (int i = 0; i < edges.size(); i += 2) {
        if (SameEdges(dot1, dot2, edges[i], edges[i + 1]))
        {
            edges.erase(edges.begin() + i, edges.begin() + i + 2);
            return;
        }
    }
    if (EdgeInTriangle(triangles, dot1, dot2)) return;	// Если есть такой отрезок, то ничего не делаем.
    edges.push_back(dot1);
    edges.push_back(dot2);
}

bool Grid::SameDots(Dot& dot1, Dot& dot2)
{
    if (dot1.x == dot2.x && dot1.y == dot2.y) return true;
    return false;
}

bool Grid::SameEdges(Dot& dot1, Dot& dot2, Dot& dot3, Dot& dot4)
{
    if (SameDots(dot1, dot3) && SameDots(dot2, dot4)) return true;
    if (SameDots(dot1, dot4) && SameDots(dot2, dot3)) return true;
    return false;
}

bool Grid::SameTriangles(Dot& dot1_1, Dot& dot1_2, Dot& dot1_3, Dot& dot2_1, Dot& dot2_2, Dot& dot2_3)
{
    if (SameDots(dot1_1, dot2_1)) return SameEdges(dot1_2, dot1_3, dot2_2, dot2_3);
    if (SameDots(dot1_1, dot2_2)) return SameEdges(dot1_2, dot1_3, dot2_1, dot2_3);
    if (SameDots(dot1_1, dot2_3)) return SameEdges(dot1_2, dot1_3, dot2_1, dot2_2);
    return false;
}

bool Grid::EdgeInTriangle(std::vector<Dot>& triangles, Dot& dot1, Dot& dot2) 
{
    int k = 0;
    for (int i = 0; i < triangles.size(); i += 3)
        for (int j = 0; j < 3; j++, k++) {
            if (SameDots(triangles[k], dot1)) {
                if (j == 0) {
                    if (SameDots(triangles[k + 1], dot2) || SameDots(triangles[k + 2], dot2)) return true;
                }
                if (j == 1) {
                    if (SameDots(triangles[k - 1], dot2) || SameDots(triangles[k + 1], dot2)) return true;
                }
                if (j == 2) {
                    if (SameDots(triangles[k - 2], dot2) || SameDots(triangles[k - 1], dot2)) return true;
                }
            }
        }
    return false;
}

void Grid::AddTriangle(std::vector<Dot>& triangles, Dot& dot1, Dot& dot2, Dot& dot3, int& index)
{
    index = -1;
    for (int i = 0; i < triangles.size(); i += 3) {
        if (SameTriangles(triangles[i], triangles[i + 1], triangles[i + 2], dot1, dot2, dot3))
            return;
    }
    // Такого треугольника нет в списке, добавим его.			
    index = triangles.size();
    triangles.push_back(dot1);
    triangles.push_back(dot2);
    triangles.push_back(dot3);
}

double Grid::CosEdges(Dot& dot1, Dot& dot2, Dot& dot3)
{
    int x0 = dot1.x - dot2.x;
    int y0 = dot1.y - dot2.y;
    int x1 = dot3.x - dot2.x;
    int y1 = dot3.y - dot2.y;

    double L = (x0 * x0 + y0 * y0) * (x1 * x1 + y1 * y1);
    if (L == 0) return 0;
    double co = (x0 * x1 + y0 * y1) / sqrt(L);
    if (co > 1) co = 1;
    if (co < -1) co = -1;

    return co;
}

void Grid::SwapDots(Dot& dot1, Dot& dot2)
{
    std::swap(dot1.x, dot2.x);
    std::swap(dot1.y, dot2.y);
}