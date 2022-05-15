#include "pch.h"
#include "Mesh.h"
#include "Device.h"


void Mesh::Init(vector<Vertex>& p_vecVertex, vector<uint16>& p_vecIndex)
{
	if (p_vecVertex.empty() == false) {
		SetVertexBuffer(p_vecVertex);

		if (p_vecIndex.empty() == false) {
			SetIndexBuffer(p_vecIndex);
		}
	}
}

void Mesh::Render()
{
	if (m_iVertexSize > 0) {
		DEVICE->SetStreamSource(0, m_pVertex, 0, sizeof(Vertex));
		DEVICE->SetFVF(D3DFVF_CUSTOMVERTEX);

		if (m_iIndexSize > 0) {
			DEVICE->SetIndices(m_pIndex);
		}

		DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iVertexSize, 0, m_iIndexSize / 3);
	}
}

void Mesh::End()
{
	if (m_pVertex) {
		m_pVertex->Release();
		m_pVertex = nullptr;
	}
	if (m_pIndex) {
		m_pIndex->Release();
		m_pIndex = nullptr;
	}
}


void Mesh::SetVertexBuffer(vector<Vertex>& p_Vertex)
{
	m_iVertexSize = p_Vertex.size();
	int32 length = m_iVertexSize * sizeof(Vertex);
	DEVICE->CreateVertexBuffer(length, D3DUSAGE_WRITEONLY, D3DFVF_CUSTOMVERTEX, D3DPOOL_MANAGED, &m_pVertex, NULL );

	void* pointer = nullptr;
	m_pVertex->Lock(0, 0, &pointer, 0);
	::memcpy(pointer, &p_Vertex.data()[0], length);
	m_pVertex->Unlock();
}

void Mesh::SetIndexBuffer(vector<uint16>& p_Index)
{
	m_iIndexSize = p_Index.size();
	int32 length = m_iIndexSize * sizeof(uint16);
	DEVICE->CreateIndexBuffer(length, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIndex, nullptr);

	void* pointer = nullptr;
	m_pIndex->Lock(0, 0, &pointer, 0);
	::memcpy(pointer, p_Index.data(), length);
	m_pIndex->Unlock();
}

