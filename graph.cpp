#include <iostream>

using namespace std;

void initmap(char m[7][7])
{
    for (int i=0; i<7; i++)
        for (int j=0; j<7; j++)
           m[i][j] = ' ';
}

void planets(char m[7][7])
{
    m[0][3] = 'A';
    m[4][0] = 'B';
    m[4][6] = 'C';
    m[2][0] = 'D';
    m[6][3] = 'E';
    m[2][6] = 'F';
    m[4][2] = 'G';
    m[2][4] = 'H';
    m[4][4] = 'I';
    m[2][2] = 'J';
}

void connect(char m[7][7], int a, int b)
{
    switch (a) {
    case 1:     // A
        if (b == 4)     // connect to D
        {
            m[0][0] = '+';
            m[0][1] = '-';
            m[0][2] = '-';
            m[1][0] = '|';
        }
        if (b == 6)     // connect to F
        {
            m[0][6] = '+';
            m[0][5] = '-';
            m[1][6] = '|';
        }
        if (b == 10)     // connect to J
        {
            m[0][2] = '+';
            m[1][2] = '|';
        }
        if (b == 8)      // connect to H
        {
            m[0][4] = '+';
            m[1][4] = '|';
        }
        break;
    case 2:     // B
        if (b == 4)     // connect to D
        {
            m[3][0] = '|';
        }
        if (b == 5)     // connect to E
        {
            m[6][0] = '+';
            m[6][1] = '-';
            m[6][2] = '-';
            m[5][0] = '|';
        }
        if (b == 7)     // connect to G
        {
            m[4][1] = '-';
        }
        break;
    case 3:     // C
        if (b == 6)     // connect to F
        {
            m[3][6] = '|';
        }
        if (b == 5)     // connect to E
        {
            m[6][6] = '+';
            m[6][5] = '-';
            m[6][4] = '-';
            m[5][6] = '|';
        }
        if (b == 9)     // connect to I
        {
            m[4][5] = '-';
        }
        break;
    case 4:     // D
        if (b == 10)     // connect to J
        {
            m[2][1] = '-';
        }
        break;
    case 5:     // E
        if (b == 7)     // connect to G
        {
            m[6][2] = '+';
            m[5][2] = '|';
        }
        if (b == 9)     // connect to I
        {
            m[6][4] = '+';
            m[5][4] = '|';
        }
        break;
    case 6:     //
        if (b == 8)     // connect to H
        {
            m[2][5] = '-';
        }
        break;
    case 7:     // G
        if (b == 10)     // connect to J
        {
            m[3][2] = '|';
        }
        if (b == 9)     // connect to I
        {
            m[4][3] = '-';
        }
        break;
    case 8:     // H
        if (b == 10)     // connect to J
        {
            m[2][3] = '-';
        }
        if (b == 9)     // connect to I
        {
            m[3][4] = '|';
        }
        break;

    }

}

void edges(char m[7][7])
{
    connect(m,1,4);     // A-D
    connect(m,1,10);    // A-j
    connect(m,1,8);     // A-H
    connect(m,1,6);     // A-F
    connect(m,2,4);     // B-D
    connect(m,2,5);     // B-E
    connect(m,2,7);     // B-G
    connect(m,3,6);     // C-F
    connect(m,3,5);     // C-E
    connect(m,3,9);     // C-I
    connect(m,4,10);    // D-J
    connect(m,5,7);     // E-G
    connect(m,5,9);     // E-I
    connect(m,6,8);     // F-H
    connect(m,7,10);    // G-J
    connect(m,7,9);     // G-I
    connect(m,8,10);    // H-J
    connect(m,8,9);     // H-I
}

void display(char m[7][7])
{
    cout << endl;
    for (int i=0; i<7; i++)
    {
        cout << "  ";
        for (int j=0; j<7; j++)
           cout << m[i][j];
        cout << endl;
    }
}

int main()
{
    char map[7][7];

    initmap(map);

    planets(map);

    edges(map);

    display(map);

    return 0;
}