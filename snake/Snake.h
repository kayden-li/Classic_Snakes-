
struct color {
	short r;
	short g;
	short b;
};
struct point {
	int x;
	int y;
	color cor;
};


//设置地图信息
class Map {
public:
	int x;
	int y;

	//游戏开始处理
	void Start();
	//游戏结束处理
	void End();

	//地图信息默认填充
	Map();
	void Setmap(int, int, color);
};
//设置食物信息
class Food:protected Map {
public:
	point food;
	//食物信息填充
	void Set();
};
//设置蛇信息
class Snake:protected Food
{
private:
	Map map;
	Food _food;
	point head;
	point *body = new point;
	int length;
	int forward;
	int model;
	float speed;
	bool life;
	bool win;
public:
	//蛇信息默认填充
	Snake();
	~Snake();

	//蛇的生命获取
	bool Getlife();
	//蛇方向信息更新(一帧)
	void Direction();
	//蛇移动操作(一帧)
	void Move();
	//蛇吃到食物(判断+一帧)
	void Eat();
	//蛇死亡处理(判断)
	void Death();
	//画出蛇和食物
	void Draw();
	//更改速度，获取速度
	float Speed(float sp = 0);
};

