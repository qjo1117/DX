#include "pch.h"
#include "ResourcesManager.h"
#include "PathManager.h"
#include "Device.h"
#include "Texture.h"

void ResourcesManager::Init()
{
}

void ResourcesManager::End()
{
}

Ref<Texture> ResourcesManager::LoadFromTexture(const wstring& p_path)
{
	wstring fullPath = GET_SINGLE(PathManager)->FindPath(TEXTURE_PATH_KEY) + p_path;

	LPDIRECT3DTEXTURE9 tex = nullptr;
	::D3DXCreateTextureFromFileW(DEVICE, fullPath.c_str(), &tex);
	Ref<Texture> texture = make_shared<Texture>();
	texture->SetTexture(tex);
	return texture;
}
