
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


//���õ�ͼ��Ϣ
class Map {
public:
	int x;
	int y;

	//��Ϸ��ʼ����
	void Start();
	//��Ϸ��������
	void End();

	//��ͼ��ϢĬ�����
	Map();
	void Setmap(int, int, color);
};
//����ʳ����Ϣ
class Food:protected Map {
public:
	point food;
	//ʳ����Ϣ���
	void Set();
};
//��������Ϣ
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
	//����ϢĬ�����
	Snake();
	~Snake();

	//�ߵ�������ȡ
	bool Getlife();
	//�߷�����Ϣ����(һ֡)
	void Direction();
	//���ƶ�����(һ֡)
	void Move();
	//�߳Ե�ʳ��(�ж�+һ֡)
	void Eat();
	//����������(�ж�)
	void Death();
	//�����ߺ�ʳ��
	void Draw();
	//�����ٶȣ���ȡ�ٶ�
	float Speed(float sp = 0);
};

