#pragma once

#include "Object.h"

/* ----------------------
		Box
---------------------- */

struct BoxInfo
{
	float width = 1.0f;
	float height = 1.0f;
	float depth = 1.0f;
};

class Box : public Object
{
public:
	virtual ~Box();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;

private:
	BoxInfo m_info;

};

