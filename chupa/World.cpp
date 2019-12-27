#include "World.hpp"



void World::LoadMap(std::string file)
{
	std::ifstream f(file);
	if (f.is_open())
	{

		f >> screenMap.x >> screenMap.y;
		
		while(true)
		{
			TexData r;
			f >> r.origin.x >> r.origin.y >> r.origin.z;
			f >> r.pos.x >> r.pos.y >> r.pos.z;
			f >> r.size.x >> r.size.y >> r.size.z;
			f >> r.textureId;
			listInfo.push_back(r);
			if (f.eof())
			{
				listInfo.pop_back();
				break;
			}
		}
		f.close();
	}
	
}

void World::Draw(Camera camera)
{
	for (auto& i : listInfo)
	{
		tex->AddInstance(i.origin, i.size, camera);
	}
	tex->Draw(true);
}

void World::ClearAll()
{
	listInfo.clear();
	object.clear();
	sObject.clear();
	entity.clear();
}
