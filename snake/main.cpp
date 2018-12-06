#include<iostream>
#include<conio.h>
#include<graphics.h>
#include<time.h>
#include<process.h>
#include"Snake.h"
#include<windows.h>
#include<stdio.h>
#pragma comment(lib,"winmm.lib") 

#define MAXSTAR 200

struct STAR
{
	double	x;
	int		y;
	double	step;
	int		color;
};

STAR star[MAXSTAR];

void InitStar(int i)
{
	star[i].x = rand() % 1000;
	star[i].y = rand() % 700;
	star[i].step = (rand() % 5000) / 1000.0 + 1;
	star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);	// 速度越快，颜色越亮
	star[i].color = RGB(star[i].color, star[i].color, star[i].color);
}
void MoveStar(int i)
{
	// 擦掉原来的星星
	putpixel((int)star[i].x, star[i].y, 0);

	// 计算新位置
	star[i].x += star[i].step;
	if (star[i].x > 1000)	InitStar(i);

	// 画新星星
	putpixel((int)star[i].x, star[i].y, star[i].color);
}



void Onethread();
void Twothread(Snake);
void Thirdthread();
int main() {
	srand((unsigned)time(NULL));
	Snake snake;
	/*
	线程方法，效果不佳
	*/
	//std::thread first(Onethread);
	//std::thread second(Twothread, snake);
	/*
	音乐播放后蛇无法移动
	*/
	//std::thread third(Thirdthread);
		while (snake.Getlife()) {
			if (_kbhit())
				snake.Direction();
			else
				Sleep(snake.Speed(5));
			snake.Move();
			snake.Eat();
			snake.Death();
			snake.Draw();
			Onethread();
		}

	/*
	线程方法，效果不佳
	*/
	//first.join();
	//second.join();
	//third.join();


	system("pause");
	return 0;
}

void Thirdthread() {
	PlaySound("G:\\programTest.wav", NULL, SND_FILENAME | SND_ASYNC);
}

void Twothread(Snake snake) {
	while (snake.Getlife())
	{
		if (_kbhit())
			snake.Direction();
		else
			Sleep(snake.Speed(5));
		snake.Move();
		snake.Eat();
		snake.Death();
		snake.Draw();
		Sleep(10);
	}
	
}

void Onethread() {
	//while (true) {
		srand((unsigned)time(NULL));
		for (int i = 0; i < MAXSTAR; i++)
		{
			InitStar(i);
			star[i].x = rand() % 1000;
		}
		for (int i = 0; i < MAXSTAR; i++)
			MoveStar(i);
		Sleep(50);

	//}
}