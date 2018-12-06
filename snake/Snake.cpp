#include "Snake.h"
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include<iostream>
#include<easyx.h>

enum direction {
	up,
	down,
	left,
	right,

	low,
	middle,
	high,

	pen,
};



Map::Map() {
	x = 1000;
	y = 700;
	initgraph(x + x / 2, y);
	setbkcolor(RGB(200, 200, 200));
	cleardevice();
}

void Map::Setmap(int x, int y, color cor) {
	x = x;
	y = y;
	initgraph(x + x / 2, y);
	setbkcolor(RGB(cor.r, cor.g, cor.b));
	cleardevice();
}

void Food::Set() {
	srand((unsigned int)time(NULL));
	food.cor.r = rand() % 255;
	food.cor.g = rand() % 255;
	food.cor.b = rand() % 255;
	food.x = rand() % (Map::x - 20) + 10;
	food.y = rand() % (Map::y - 20) + 10;
}

Snake::Snake()
{
	srand((unsigned int)time(NULL));
	head.x = 50;
	head.y = 50;
	head.cor.r = rand() % 255;
	head.cor.g = rand() % 255;
	head.cor.b = rand() % 255;
	forward = right;
	speed = 200;
	length = 0;
	life = true;
	win = false;
	_food.Set();
}

Snake::~Snake()
{
}

bool Snake::Getlife() {
	return life;
}

void Snake::Direction() {
	char c;
	char c2;
	c = _getch();
	switch (c)
	{
	case 'w':
		if(forward != down || length == 0)
			forward = up;
		break;
	case 's':
		if(forward != up || length == 0)
			forward = down;
		break;
	case 'a':
		if(forward != right || length == 0)
			forward = left;
		break;
	case 'd':
		if(forward != left || length == 0)
			forward = right;
		break;
	case NULL:
		break;
	default:
		c2 = _getch();
		switch (c2)
		{
		case 'H':
			if (forward != down || length == 0)
				forward = up;
			break;
		case 'P':
			if (forward != up || length == 0)
				forward = down;
			break;
		case 'K':
			if (forward != right || length == 0)
				forward = left;
			break;
		case 'M':
			if (forward != left || length == 0)
				forward = right;
			break;
		default:
			break;
		}
		break;
	}
}

void Snake::Move() {
	//每节迭代
	for (int i = length; i > 0; --i) {
		body[i].x = body[i - 1].x;
		body[i].y = body[i - 1].y;
	}
	body[0].x = head.x;
	body[0].y = head.y;
	//头部改变
	switch (forward)
	{
	case up:head.y -= 10; break;
	case down:head.y += 10; break;
	case left:head.x -= 10; break;
	case right:head.x += 10; break;
	default:
		break;
	}
}

void Snake::Eat() {
	//增加节数，更新食物信息
	//此帧不改变蛇长度
	if (head.x <= _food.food.x + 9 && head.y <= _food.food.y + 9 && head.x >= _food.food.x - 9 && head.y >= _food.food.y - 9) {
		body[length].cor = _food.food.cor;
		++length;
		Snake::_food.Set();
		std::cout << food.x << "    " << food.y;
	}
}

float Snake::Speed(float sp) {
	if (sp == 0)
		speed = 20;
	else if (sp == low)
		speed = 30;
	else if (sp == middle)
		speed = 15;
	else if (sp == high)
		speed = 7;
	speed = speed - length / speed;
	return speed;
}

void Snake::Death() {
	//蛇自身碰撞
	for (int i = 0; i < length; ++i) {
		if (head.x == body[i].x && head.y == body[i].y)
			life = false;
	}
	//蛇碰撞墙壁
	if (head.x > Map::x || head.y > Map::y || head.x < 0 || head.y < 0)
		life = false;
	//游戏胜利
	if (length == Map::x*Map::y) {
		life = false;
		win = true;
	}
	if (!life) {

	}
}

void Snake::Draw() {
	char s[10], s2[7] = "score:";
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 30;
	_tcscpy_s(f.lfFaceName, _T("宋体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);

	//游戏背景色设置
	if (model != pen) {
		setbkcolor(RGB(28, 28, 28));
		cleardevice();
	}
	setfillcolor(RGB(54, 54, 54));
	//得分板设置
	fillrectangle(map.x, 0, map.x + map.x / 2, map.y);
	//得分板字体设置
	_stprintf_s(s, _T("%d"), length);
	outtextxy(map.x + map.x / 10, 100, s2);
	outtextxy(map.x + map.x / 10 + 100, 100, s);
	//画出蛇
	setfillcolor(RGB(head.cor.r, head.cor.g, head.cor.b));
	fillcircle(head.x, head.y, 15);
	for (int i = 0; i < length; ++i) {
		setfillcolor(RGB(body[i].cor.r, body[i].cor.g, body[i].cor.b));
		fillrectangle(body[i].x - 10, body[i].y - 10, body[i].x + 10, body[i].y + 10);
	}
	setfillcolor(RGB(_food.food.cor.r, _food.food.cor.g, _food.food.cor.b));
	fillellipse(_food.food.x - 5, _food.food.y - 5, _food.food.x + 5, _food.food.y + 5);
}