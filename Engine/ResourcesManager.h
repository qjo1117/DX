#pragma once

enum class RESOURCE_TPYE
{
	NONE = -1,
	TEXTURE,
	END,
};



/*-------------------------
	 ResourcesManager
--------------------------*/
class ResourcesManager
{
	DECLARE_SINGLE(ResourcesManager);
public:
	void Init();
	void End();


};


// �ؽ�ó �������� ���� �󸶳� ���� ����غ���