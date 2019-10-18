#pragma once
#include"Model.hpp"
class BubbleShooter
{
public:
	BubbleShooter(ID3D11Device* dev);
	~BubbleShooter();
	void InsertCircle(fVec2 pos, float rad, fVec4 color, bool filled = true);
private:
	Model11<VertexInstance>circle;
	ID3D11Device* dev = nullptr;
	ID3D11DeviceContext* devcon = nullptr;
};

