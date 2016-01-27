#ifndef TEXTURE_H
#define TEXTURE_H

#include "enums.h"
#include "rendermanager.h"

class Texture
{
protected:
	int id;
public:
	Texture()
	{
		this->id = 0;
	}

	Texture(int id)
	{
		this->id = id;
	}

	~Texture()
	{
		if (id != 0 && RenderManager::getEngine() != 0)
			RenderManager::getEngine()->deleteTexture(id);
		this->id = 0;
	}

	int getID()
	{
		return id;
	}

	void setID(int id)
	{
		this->id = id;
	}

	static int genTexture()
	{
		int res = RenderManager::getEngine()->genTexture();
		return res;
	}

	static void activeTextureSlot(int slot)
	{
		RenderManager::getEngine()->activeTextureSlot(slot);
	}

	virtual void use() = 0;

	virtual void setFilter(TextureFilterMode min, TextureFilterMode mag) = 0;

	virtual void genMipmap() = 0;
};

#endif