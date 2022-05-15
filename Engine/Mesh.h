#pragma once

#include "Vertex.h"


/* ----------------
		Mesh   
---------------- */
class Mesh
{
public:
	void Init(vector<Vertex>& p_vecVertex, vector<uint16>& p_vecIndex);
	void Render();
	void End();


	void SetVertexBuffer(vector<Vertex>& p_vecVertex);
	void SetIndexBuffer(vector<uint16>& p_vecIndex);

private:
	int32 m_iVertexSize = 0;
	LPDIRECT3DVERTEXBUFFER9 m_pVertex = nullptr;
	int32 m_iIndexSize = 0;
	LPDIRECT3DINDEXBUFFER9 m_pIndex = nullptr;
};

