#include <graphics.h>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
// variables declaration
int pacmanX = 320;
int pacmanY = 240;
char pacmanDirection = 'U';
int ghostX[4] = {120,120,520,520};
int ghostY[4] = {120,350,120,350};
char ghostDirection[4] = {'D','U','L','R'};
int color[4] = {1, 3, 4, 5};
int coin[16][12];
int score = 0;
// functions declaration
void win()
{
    setfillstyle(8, 2);
    bar(0,0,640,480);
    setcolor(15);
    settextstyle(3 , 0 , 6);
    outtextxy(170 , 200 , "You win :)");
    while (true)
    {
        if(kbhit()) exit(0);
    }
}
void drawMap()
{
    setcolor(2);
	setfillstyle(1, 2);
	bar(70, 70, 260, 90);
	bar(70, 70, 90, 170);
    bar(150, 70, 170, 330);
    bar(70, 310, 90, 390);
    bar(70, 390, 260, 410);
    bar(380, 70, 550, 90);
    bar(550, 70, 570, 170);
    bar(380, 390, 550, 410);
    bar(550, 310, 570, 410);
    bar(470, 390, 490, 150);
    line(1,1,630,1);//divar
    line(630,1,630,465);
    line(630,465,1,465);
    line(1,1,1,465);
    if(score >=125) win();
}
void drawMap2()
{
    setcolor(2);
	setfillstyle(1, 2);
	bar(100, 70, 400, 90);
	bar(390, 70, 410, 300);
    bar(190, 390, 500, 410);
    bar(190, 410, 210, 220);
    bar(510, 150, 570, 260);
    bar(60, 300, 100, 420);

    line(1,1,630,1);
    line(630,1,630,465);
    line(630,465,1,465);
    line(1,1,1,465);
    if(score >=129) win();
}
void clearPlayer(int x, int y)
{
    setfillstyle(1, 0);
    circle(x, y, 22);
}
void drawPacman(int x, int y, char dir)
{
    setcolor(0);
    setfillstyle(SOLID_FILL , 14);
    if(dir == 'U')
    {
        pieslice(x , y, 120, 60, 20);
        setfillstyle(SOLID_FILL,0);
        fillellipse(x-10, y, 5, 5);
    }
    if(dir == 'D')
    {
        pieslice(x , y, 300, 240, 20);
        setfillstyle(SOLID_FILL,0);
        fillellipse(x+10, y, 5, 5);
    }
    if(dir == 'R')
    {
        pieslice(x , y, 30, 330, 20);
        setfillstyle(SOLID_FILL,0);
        fillellipse(x, y-10, 5, 5);
    }
    if(dir == 'L')
    {
        pieslice(x , y, 210, 150, 20);
        setfillstyle(SOLID_FILL,0);
        fillellipse(x, y-10, 5, 5);
    }
}
void drawGhost(int x, int y, char dir, int _color)
{
    setcolor(0);
    setfillstyle(SOLID_FILL,_color);
    fillellipse(x , y, 18, 18);
    setfillstyle(SOLID_FILL, 0);
    fillellipse(x - 5, y - 5, 3, 3);
    fillellipse(x + 5, y - 5, 3, 3);
}
void movePacman(char ch)
{
    int rad = 18;
    if(ch == 'w')
    {
        if(getpixel(pacmanX, pacmanY-21) == 2 or getpixel(pacmanX-rad, pacmanY-21) == 2 or getpixel(pacmanX+rad, pacmanY-21) == 2)
            ch = 'z';
        else
        {
            pacmanDirection = 'U';
            pacmanY--;
        }
    }
    if(ch == 's')
    {
        if(getpixel(pacmanX, pacmanY+21) == 2 or getpixel(pacmanX+rad, pacmanY+21) == 2 or getpixel(pacmanX-rad, pacmanY+21) == 2)
            ch = 'z';
        else
        {
            pacmanDirection = 'D';
            pacmanY++;
        }
    }
    if(ch == 'a')
    {
        if(getpixel(pacmanX-21, pacmanY) == 2 or getpixel(pacmanX-21, pacmanY+rad) == 2 or getpixel(pacmanX-21, pacmanY-rad) == 2)
            ch = 'z';
        else
        {
            pacmanDirection = 'L';
            pacmanX--;
        }
    }
    if(ch == 'd')
    {
        if(getpixel(pacmanX+21, pacmanY) == 2 or getpixel(pacmanX+21, pacmanY+rad) == 2 or getpixel(pacmanX+21, pacmanY-rad) == 2)
            ch = 'z';
        else
        {
            pacmanDirection = 'R';
            pacmanX++;
        }
    }
}
char chooseDirection(char HorV)
{
    for(int i = 0 ; i < 4 ; i ++)
    {
        if(HorV == 'H')
        {
            if(pacmanX<ghostX[i]) return 'L';
            else               return 'R';
        }
        else
        {
            if(pacmanY<ghostY[i]) return 'U';
            else               return 'D';
        }
    }
}
void moveGhost()
{
    for(int i = 0 ; i < 4 ; i ++)
    {
        int rad = 18;
        if(ghostDirection[i] == 'U')
        {
            if(getpixel(ghostX[i], ghostY[i]-21) == 2 or getpixel(ghostX[i]-rad, ghostY[i]-21) == 2 or getpixel(ghostX[i]+rad, ghostY[i]-21) == 2)
                ghostDirection[i] = chooseDirection('H');
            else if(pacmanY > ghostY[i])
                ghostDirection[i] = 'D';
            else if(pacmanY == ghostY[i])
            {
                if(pacmanX < ghostX[i]) ghostDirection[i] = 'L';
                else                 ghostDirection[i] = 'R';
            }
            else
                ghostY[i]--;
        }
        if(ghostDirection[i] == 'D')
        {
            if(getpixel(ghostX[i], ghostY[i]+21) == 2 or getpixel(ghostX[i]+rad, ghostY[i]+21) == 2 or getpixel(ghostX[i]-rad, ghostY[i]+21) == 2)
                ghostDirection[i] = chooseDirection('H');
            else if(pacmanY < ghostY[i])
                ghostDirection[i] = 'U';
            else if(pacmanY == ghostY[i])
            {
                if(pacmanX < ghostX[i]) ghostDirection[i] = 'L';
                else                 ghostDirection[i] = 'R';
            }
            else
                ghostY[i]++;
        }
        if(ghostDirection[i] == 'L')
        {
            if(getpixel(ghostX[i]-21, ghostY[i]) == 2 or getpixel(ghostX[i]-21, ghostY[i]+rad) == 2 or getpixel(ghostX[i]-21, ghostY[i]-rad) == 2)
                ghostDirection[i] = chooseDirection('V');
            else if(pacmanX > ghostX[i])
                ghostDirection[i] = 'R';
            else if(pacmanX == ghostX[i])
            {
                if(pacmanY < ghostY[i]) ghostDirection[i] = 'U';
                else                 ghostDirection[i] = 'D';
            }
            else
                ghostX[i]--;
        }
        if(ghostDirection[i] == 'R')
        {
            if(getpixel(ghostX[i]+21, ghostY[i]) == 2 or getpixel(ghostX[i]+21, ghostY[i]+rad) == 2 or getpixel(ghostX[i]+21, ghostY[i]-rad) == 2)
                ghostDirection[i] = chooseDirection('V');
            else if(pacmanX < ghostX[i])
                ghostDirection[i] = 'L';
            else if(pacmanX == ghostX[i])
            {
                if(pacmanY < ghostY[i]) ghostDirection[i] = 'U';
                else                 ghostDirection[i] = 'D';
            }
            else
                ghostX[i]++;
        }
    }
}
void randomMoveGhost()
{
    for(int i = 0 ; i < 4 ; i ++)
    {
        int rad = 18;
        if(ghostDirection[i] == 'U')
        {
            if(getpixel(ghostX[i], ghostY[i]-21) == 2 or getpixel(ghostX[i]-rad, ghostY[i]-21) == 2 or getpixel(ghostX[i]+rad, ghostY[i]-21) == 2)
                ghostDirection[i] = chooseDirection('H');
            else
                ghostY[i]--;
        }
        if(ghostDirection[i] == 'D')
        {
            if(getpixel(ghostX[i], ghostY[i]+21) == 2 or getpixel(ghostX[i]+rad, ghostY[i]+21) == 2 or getpixel(ghostX[i]-rad, ghostY[i]+21) == 2)
                ghostDirection[i] = chooseDirection('H');
            else
                ghostY[i]++;
        }
        if(ghostDirection[i] == 'L')
        {
            if(getpixel(ghostX[i]-21, ghostY[i]) == 2 or getpixel(ghostX[i]-21, ghostY[i]+rad) == 2 or getpixel(ghostX[i]-21, ghostY[i]-rad) == 2)
                ghostDirection[i] = chooseDirection('V');
            else
                ghostX[i]--;
        }
        if(ghostDirection[i] == 'R')
        {
            if(getpixel(ghostX[i]+21, ghostY[i]) == 2 or getpixel(ghostX[i]+21, ghostY[i]+rad) == 2 or getpixel(ghostX[i]+21, ghostY[i]-rad) == 2)
                ghostDirection[i] = chooseDirection('V');
            else
                ghostX[i]++;
        }
    }
}
void checkGameOver()
{
    for(int i = 0 ; i < 4 ; i ++)
    {
        if(abs(pacmanX-ghostX[i])<30 and abs(pacmanY - ghostY[i])<30)
        {
            setfillstyle(8, 4);
            bar(0,0,640,480);
            setcolor(15);
            settextstyle(3 , 0 , 6);
            outtextxy(150 , 200 , "GAME OVER");
            pacmanX = 320;
            pacmanY = 240;
            ghostX[0] = 120;
            ghostX[1] = 120;
            ghostX[2] = 520;
            ghostX[3] = 520;
            ghostY[0] = 120;
            ghostY[1] = 350;
            ghostY[2] = 120;
            ghostY[3] = 350;
            ghostDirection[0] = 'D';
            ghostDirection[1] = 'U';
            ghostDirection[2] = 'L';
            ghostDirection[3] = 'R';
            pacmanDirection = 'U';
            while(true)
            {
                if(kbhit())
                {
                    setfillstyle(1, 0);
                    bar(0,0,640,480);
                    return;
                }
            }
        }
    }
}

void drawCoin()
{
    for(int i=1; i<16; i++)
    {
        for(int j=1; j<12; j++)
        {
            if(coin[i][j] == 0 && getpixel( i * 40 , j * 40) !=2)
            {
                if(abs(pacmanX-i*40) < 20 && abs(pacmanY-j*40) < 20)
                {
                    coin[i][j] = 1;
                    score++;
                }
                setcolor(14);
                setfillstyle(1, 14);
                fillellipse(i*40, j*40, 5, 5);
            }

        }
    }
}
void printScore()
{
    settextstyle(3 , 0 , 3);
    setcolor(13);
    std::string s;
    std::stringstream out;
    out << score;
    s = out.str();
    const char* charScore = s.c_str();

    outtextxy(5,5, "Score:");
    outtextxy(80,5, charScore);
}
main()
{
    initwindow(640 , 480 );
	char ch = 'w';
    bool selected = false;
    bool difficult = false;
    bool map1 = false;
    while(!selected)
    {
        setfillstyle(8, 2);
        bar(0,0,640,480);
        setcolor(15);
        settextstyle(3 , 0 , 3);
        outtextxy(100 , 200 , "Wants to play Easy or Hard?(e/h)");
        if(kbhit())
        {
            char c = getch();
            if(c == 'h') difficult = true;
            if(c == 'e') difficult = false;
            selected = true;
        }
    }
    selected = false;
    while(!selected)
    {
        setfillstyle(8, 2);
        bar(0,0,640,480);
        setcolor(15);
        settextstyle(3 , 0 , 3);
        outtextxy(70 , 200 , "Wants to play the first map or second?(1/2)");
        if(kbhit())
        {
            char c = getch();
            if(c == '1') map1 = true;
            if(c == '2') map1 = false;
            selected = true;
        }
    }
    setfillstyle(1, 0);
    bar(0,0,640,480);
	while(true)
    {
        if(kbhit()) ch = getch();
        movePacman(ch);
        if(difficult) moveGhost();
        else          randomMoveGhost();
        checkGameOver();
        setcolor(9);
        drawCoin();
        if(map1) drawMap();
        else     drawMap2();
        printScore();
        for(int i = 0 ; i < 4 ; i ++)
            drawGhost(ghostX[i], ghostY[i], ghostDirection[i], color[i]);
        drawPacman(pacmanX, pacmanY, pacmanDirection);
        delay(1);
        for(int i = 0 ; i < 4 ; i ++)
            clearPlayer(ghostX[i], ghostY[i]);
        clearPlayer(pacmanX, pacmanY);
    }
	getch();
}
