#pragma once
#include"Model.hpp"
<<<<<<< HEAD


=======
#include<random>
#include<ctime>
class Bubble
{
public:
	fVec2 pos;
	fVec4 color;
	Bubble * neighbor[6];
	bool alive;

};
>>>>>>> a1299912828782dc60d5cdf84eb7dfba028dd530
class BubbleShooter
{
public:
	BubbleShooter(ID3D11Device* dev,fVec2 *Screen);
	~BubbleShooter();
	
	void InsertCircle(fVec2 pos, float rad, fVec4 color);
	void Draw();
private:
	bool running = false;
	Model11<VertexInstance>circle;
	fVec2* screen = nullptr;
	ID3D11Device* dev = nullptr;
	ID3D11DeviceContext* devcon = nullptr;
	Bubble bubble[16][17];
	fVec4 blue = fVec4(0, 0, 1, 1);
	fVec4 green = fVec4(0, 1, 0, 1);
	fVec4 red = fVec4(1, 0, 0, 1);
	fVec4 yellow = fVec4(1, 1, 0, 1);
	fVec4 crystal = fVec4(0, 1, 1, 1);
	fVec4 colors[6];
};

