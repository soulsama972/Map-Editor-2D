#include "World.hpp"

void World::LoadTextureFromFolder(std::string pathOfFolder)
{
	for (const auto& entry : std::filesystem::directory_iterator(pathOfFolder))
	{
		if (entry.path().string().find(".png") != std::string::npos)
		{
			Texture2D* t = new Texture2D(entry.path().string(), "Texture2DVs.hlsl", "Texture2DPs.hlsl", 1000);

			tex.push_back(t);

		}
	}
}


void World::LoadMap(std::string file)
{
	LoadTextureFromFolder(GetPath() + "texture");
	std::ifstream f(file );

	if (f.is_open())
	{
		
		f >> screenMap.x >> screenMap.y;
		UINT objCount = 0;
		f >> objCount;
		for(int i = 0;i<objCount;i++)
		{
			TexData r;
			f >> r.origin.x >> r.origin.y >> r.origin.z;
			f >> r.pos.x >> r.pos.y >> r.pos.z;
			f >> r.size.x >> r.size.y >> r.size.z;
			f >> r.textureId;
			listInfo.push_back(r);
		}

		f.close();
	}
	
}

void World::Draw(const Camera& camera)
{
	for (auto& i : listInfo)
	{
		tex[i.textureId]->AddInstance(i.origin, i.size, camera);
	}
	for (auto& i : tex)
	{
		i->Draw(true);
	}
//	tex->Draw(true);
}

void World::ClearAll()
{
	listInfo.clear();
	object.clear();
	sObject.clear();
	entity.clear();
	tex.clear();
}
