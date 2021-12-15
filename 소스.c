#include <stdio.h>
#include <conio.h>//입력 헤더파일
#include <Windows.h>//좌표를 설정하는 헤더파일

void intro_start();//인트로를 출력하는 함수
void gotoxy(int x, int y);//x,y 좌표로 이동하는 함수
void move_arrow_key(char chr, int* x, int* y, int x_b, int y_b);//방향키를 입력받는 함수
void checkerboard();//바둑판 그리기 함수
void game_start(void);//게임을 진행하는 함수
void Draw_stone(int matrix[][20][20]);//바둑판에 바둑을 출력하기 위한 함수
int game_end(int matrix[][20][20]);//게임의 승패를 나누는 함수

int main(void)
{
    intro_start();
    system("cls");//인트로 출력후 화면 초기화
    game_start();

    return 0;

}

void intro_start()

{
    printf("오목 게임\n");
    printf("오목은 가로, 세로, 혹은 대각선으로 먼저 5개의 돌을 연달아 배치시키면 이기는 게임 입니다.\n");
    printf("사용자 2명이 돌아가며 돌을 놓습니다.\n");
    printf("흑돌과 백돌중 '흑돌'이 먼저 시작합니다\n");;
    printf("규칙을 이해하셨다면 아무키나 눌러주세요.\n");
    _getch();
}


//gotoxy() 함수 https://hyomyo.tistory.com/27
void gotoxy(int x, int y)

{
    COORD Pos = { x - 1, y - 1 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}





//키보드의 방향키를 입력 받는 함수
void move_arrow_key(char key, int* x, int* y)
{
    switch (key) {
    case 72:												// key값의 ASCII코드가 72번일 때 (위쪽 방향키)
        if (*y - 1 < 0)										// y-1 했을 때 0 미만이면 처리 안함
            break;
        else												// 0미만이 아닐경우에는 y값을 1 감소
            *y -= 1;
        break;
    case 80:												// key값의 ASCII코드가 80번일 때 (아래쪽 방향키)
        if (*y + 1 > 18)										// y+1 했을 때 18을 초과하면 처리 안함
            break;
        else												// 18을 초과하지 않았을 경우 y값 1 증가
            *y += 1;
        break;
    case 75:												// key값의 ASCII코드가 75번일 때 (왼쪽 방향키)
        if (*x - 2 < 0)										// x-2 했을 때 0 미만이면 경우 처리 안함
            break;
        else												// 0 미만이 아닐경우에는 x값 2 감수 (콘솔창에서는 y값 1이 x값 2와 유사합니다)
            *x -= 2;
        break;
    case 77:												// key값의 ASCII코드가 77번일 때 (오른쪽 방향키)
        if (*x + 2 > 36)											// x+2했을 때 36을 초과하면 처리 안함
            break;
        else												// 36을 초과하지 않았을 경우 x값 2 증가
            *x += 2;
        break;

    default:												//그 외의 경우, 처리 안함
        break;
    }
}



//바둑판 그리기 함수

void checkerboard()
{
    int i;
    int j;
    /************************첫째줄 시작****************/

    printf("┌ ");//첫줄의 시작은 ┌로 시작합니다.

    for (i = 0; i < 16; i++) //for문을 사용하여 ㅜ모양을 그려주는것을 반목합니다. ex) ┌ ┬┬┬┬┬┬┬┬┬ <-이런식으로
    {
        printf("┬ ");
    }
    printf("┐\n");//첫줄의 마무리는 ┐입니다. 그래서 다 그려지면 ┌ ┬┬┬┬┬┬┬┬┬ ┐이 됩니다.


/**************첫째줄 종료, 둘째줄 ~ 18째줄 시작**************/

    for (i = 0; i < 16; i++) {
        printf("├ ");//첫줄과 마지막줄을 제외한 줄은 전부 ㅏ 모양으로 시작합니다. 2~18줄을 표현하기위해 for문 i<17을 사용하였습니다.
        for (j = 0; j < 16; j++) {
            printf("┼ ");//두번째줄 부턴 ┼ 모양을 반복해 주어야 합니다. 이 역시 ㅏ와ㅓ를 제외한 나머지를 반복 -> for문 i<17
        }
        printf("┤\n");//2~18줄 마지막은 ㅓ 모양입니다.
    }


    /*******************2~17번째줄 종료, 18번째줄 시작**************/

    printf("└ ");// 마지막 줄의 시작은 ㄴ 모양입니다.
    for (i = 0; i < 16; i++) {
        printf("┴ ");//위의 코드와 같은 원리로 마지막줄은 ㅗ 모양으로 반복됩니다. 위와 동일.
    }
    printf("┘");//마지막줄의 마지막은 ┘ 모양입니다. 
}



//게임을 진행시키는 함수
//https://jaimemin.tistory.com/180 참조

void game_start(void)
{
    int x = 1, y = 1, other = 0;
    int coordinate[2][20][20] = { 0 };
    char key, judge = 0;
    char* stone[2] = { "○","●" };

    do
    {
        gotoxy(1, 1);
        checkerboard();
        gotoxy(x, y);
        printf("%s", stone[other]);
        Draw_stone(coordinate);
        gotoxy(1, 20);

        if (other)//누구의 차례인지 보여줌
            printf("●차례입니다.\n");
        else
            printf("○차례입니다.\n");

        gotoxy(1, 21);//21번째줄로가서

        printf("방향키로 움직이고 스페이스바를 누르시오.\n");//도움말을 출력해줌

        key = _getch();//사용자로부터 키를 입력받기.

        if (key == 27) //esc를 누르면 종료 

            exit(0);

        else if (key == 32) //사용자로부터 스페이스바가 입력되면 (즉, 사용자가 돌을 놓으면)

        {

            coordinate[other][(x + 1) / 2][y] = 1;//other(0=흑돌,1=백돌), matrix[색깔(other)] [(x + 1) / 2] [y]의 배열의 값을 1로 초기화.

            judge = game_end(coordinate);//judge 변수에, game_end의 함수를 거쳐 리턴된 값을 대입

            if (judge != 0)//judge변수가 0이 아니라면
            {
                gotoxy(1, 20);//20번째줄에
                printf("☆★☆★ 축하합니다!!!!!! %s 님이 승리 하셨습니다! ☆★☆★\n ", stone[other]);//축하멘트를 남기고
                system("pause");//프로그램을 정지한후
                exit(0);//종료
            }

            other = 1 - other;//judge가 0이라면 다음 사용자의 턴으로 넘어가고, 반복문 위로 올라가 다시 반복 시작.

        }
        else if (key >= 72)//입력받은키가 방향키라면
            move_arrow_key(key, &x, &y);//방향키만큼 이동하는 함수로.
    } while (1);

}



//바둑판 위에 돌을 차례로 둘 때, 사용자가 원하는 위치에 바둑돌을 출력해주는 함수.

void Draw_stone(int coordinate[][20][20])
{

    int i, x, y;
    char* stone[2] = { "○", "●" };

    for (i = 0; i < 2; i++)
        for (x = 1; x < 19; x++)
            for (y = 1; y < 19; y++)
            {
                if (coordinate[i][x][y] == 1)
                {
                    gotoxy(x * 2 - 1, y);//game_start함수에서 배열값을 (x+1)/2로 받아 주었으니, 출력은 반대로 2를 곱해준후 1을 뺌으로써 사용자가 원했던 위치에 출력.
                    printf("%s", stone[i]);
                }
            }

}

//오목의 승패 갈림 판별 함수
//가로, 세로는 혼자, 대각선은 참조.
//대각선 참고 영상 https://youtu.be/YLP_mcU-LBs?t=470

/*여담이지만 대각선을 참조하려고 찾다 보니 영상속의 개발자분도 저랑 아예 같은 방법을 사용하셨습니다... 그렇다고 제가 했다는 증거를 밝힐수 있는 방법도 없어서,
주석을 최대한 자세히 달아 제가 했다는것을 최대한 증명하고자 하였습니다.*/

int game_end(int coordinate[][20][20])
{
    int count = 0;

    //가로로 5개 판별.
    for (int i = 0; i < 2; i++)//백돌과 흑돌, 두개에 대한 반복이니 i는 2까지 반복
    {
        for (int y = 1; y < 20; y++)//가로축이니 y가 같은 곳에서 찾아야하니 y를 첫번째 for으로 채택
        {
            count = 0; //y축이 변경될때마다 카운트는 0으로 초기화
            for (int x = 1; x < 20; x++)//x의 값이 증가 하는 반복문
            {
                if (coordinate[i][x][y])//coordinate, 즉 [돌의 색깔] [x좌표] [y좌표]의 배열에서 x좌표만 증가하는 상황이다. 거기서i와 y는 같은데 x만 다른 배열을 찾는것이 관건이므로
                    count++;//사용자가 바둑돌을 놓을때마다 이 상황을 대입해서 카운트 값을 증가.
                else
                    count = 0;//만약 사용자가 다음 바둑돌을 놓았는데 y가 다르다면 카운트는 다시 0으로 시작해서 반복.

                if (count == 5)//이러다가 카운트가 5가된다면
                    return 1;//0이아닌 다른 값을 리턴해서 승리 했음을 알림.
            }
        }
    }
    //세로 5개, 가로의 상황에서 x만 다른 배열을 찾냐 y만 다른 배열을 찾냐의 문제이므로 이하는 생략, 위와 동일.
    for (int i = 0; i < 2; i++)
    {
        for (int x = 1; x < 20; x++)
        {
            count = 0;
            for (int y = 1; y < 20; y++)
            {
                if (coordinate[i][x][y])
                    count++;
                else
                    count = 0;
                if (count == 5)
                    return 1;
            }
        }
    }

    for (int i = 0; i < 2; i++)// 왼쪽 위 - 오른쪽 아래(＼)로 5개일 경우
    {
        for (int x = 1; x < 16; x++) //대각선이므로 15개 까지 존재할수 있다.
        {
            count = 0; //새로운 대각선일 때 count는 0으로 시작해야함
            for (int y = 1; y < 16; y++) //대각선이므로 15개까지만 존재할수 있다.
            {
                int temp1 = x; //x와 y값을 저장
                int temp2 = y;
                for (int j = 0; j < 5; j++)
                {
                    if (coordinate[i][temp1++][temp2++])
                        count++;
                    else
                        count = 0;
                }
                if (count == 5)
                    return 1;
            }
        }
    }
    // 왼쪽 아래 - 오른쪽 위(/)로 5개일 경우
    for (int i = 0; i < 2; i++)
    {
        for (int x = 1; x < 16; x++) //대각선이므로 15개까지만 존재할수 있다.
        {
            count = 0;
            for (int y = 5; y < 20; y++) //대각선이기 때문에 5부터 시작
            {
                int temp1 = x;
                int temp2 = y;
                for (int j = 0; j < 5; j++)
                {
                    if (coordinate[i][temp1++][temp2--])
                        count++;
                    else
                        count = 0;
                }
                if (count == 5)
                    return 1;
            }
        }
    }
    return 0; //게임이 안 끝났으면 0 반환
}
