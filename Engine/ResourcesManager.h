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


// 텍스처 사용법보고 대충 얼마나 할지 계산해보자