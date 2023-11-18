#include "Grid.h"

HBRUSH blackBrush = CreateSolidBrush(BLACK_C);
HBRUSH beigeBrush = CreateSolidBrush(BEIGE_C);
HBRUSH yellowBrush = CreateSolidBrush(YELLOW_C);
HBRUSH pinkBrush = CreateSolidBrush(PINK_C);
HBRUSH grinBrush = CreateSolidBrush(GRIN_C);
HBRUSH redBrush = CreateSolidBrush(RED_C);
HBRUSH blueBrush = CreateSolidBrush(BLUE_C);
HBRUSH skinBrush = CreateSolidBrush(SKIN_C);
HBRUSH purpleBrush = CreateSolidBrush(PURPLE_C);
HBRUSH orangeBrush = CreateSolidBrush(ORANGE_C);

HPEN dcPen = CreatePen(PS_SOLID, 1, BLACK_C);

char Grid::GetColor()
{
    std::cout << "When color to filled?\n"
        "1 - Beige; "
        "2 - Yellow; "
        "3 - Pink; "
        "4 - Grin; "
        "5 - Red;\n"
        "6 - Blue; "
        "7 - Skin; "
        "8 - Purple; "
        "9 - Orange; "
        "0 - Black\n";
    return _getch();
}

COLORREF Grid::SetBrush()
{
    char ch = GetColor();
    switch (ch)
    {
    case '1':
        SelectBrush(hdc, beigeBrush);
        SelectPen(hdc, dcPen);
        return BEIGE_C;
    case '2':
        SelectBrush(hdc, yellowBrush);
        SelectPen(hdc, dcPen);
        return YELLOW_C;
    case '3':
        SelectBrush(hdc, pinkBrush);
        SelectPen(hdc, dcPen);
        return PINK_C;
    case '4':
        SelectBrush(hdc, grinBrush);
        SelectPen(hdc, dcPen);
        return GRIN_C;
    case '5':
        SelectBrush(hdc, redBrush);
        SelectPen(hdc, dcPen);
        return RED_C;
    case '6':
        SelectBrush(hdc, blueBrush);
        SelectPen(hdc, dcPen);
        return BLUE_C;
    case '7':
        SelectBrush(hdc, skinBrush);
        SelectPen(hdc, dcPen);
        return SKIN_C;
    case '8':
        SelectBrush(hdc, purpleBrush);
        SelectPen(hdc, dcPen);
        return PURPLE_C;
    case '9':
        SelectBrush(hdc, orangeBrush);
        SelectPen(hdc, dcPen);
        return ORANGE_C;
    case '0':
        SelectBrush(hdc, blackBrush);
        SelectPen(hdc, dcPen);
        return BLACK_C;
    }
    

}


