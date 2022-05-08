#pragma once

#include "Object.h"

/* ----------------------
		Sphere
---------------------- */

struct SphereInfo
{
	float radius = 1.0f;
	float stack = 15.0f;
	float slice = 15.0f;
};


class Sphere : public Object
{
public:
	Sphere();
	virtual ~Sphere();
public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;


protected:
	SphereInfo m_info = {};
};

