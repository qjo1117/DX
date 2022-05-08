#pragma once


class Utils
{
public:
	static wstring Str2Wstr(const string& str)
	{
		int32 len;
		int32 slength = static_cast<int32>(str.length()) + 1;
		len = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		::MultiByteToWideChar(CP_ACP, 0, str.c_str(), slength, buf, len);
		wstring ret(buf);
		delete[] buf;
		return ret;
	}
	static string Wstr2Str(const wstring& str)
	{
		int32 len;
		int32 slength = static_cast<int32>(str.length()) + 1;
		len = ::WideCharToMultiByte(CP_ACP, 0, str.c_str(), slength, 0, 0, 0, 0);
		string r(len, '\0');
		::WideCharToMultiByte(CP_ACP, 0, str.c_str(), slength, &r[0], len, 0, 0);
		return r;
	}

	/* ----------- 불편해서 만든것 ----------- */
	static Matrix CreateScaling(const Vec3& scaling)
	{
		Matrix mat;
		::D3DXMatrixScaling(&mat, scaling.x, scaling.y, scaling.z);
		return mat;
	}
	static Matrix CreateRotationX(float angle)
	{
		Matrix mat;
		::D3DXMatrixRotationX(&mat, angle);
		return mat;
	}
	static Matrix CreateRotationY(float angle)
	{
		Matrix mat;
		::D3DXMatrixRotationY(&mat, angle);
		return mat;
	}
	static Matrix CreateRotationZ(float angle)
	{
		Matrix mat;
		::D3DXMatrixRotationZ(&mat, angle);
		return mat;
	}
	static Matrix CreateTranslation(const Vec3& trans)
	{
		Matrix mat;
		::D3DXMatrixTranslation(&mat, trans.x, trans.y, trans.z);
		return mat;
	}

	static Vec3 Translation(const Matrix& mat) 
	{
		return { mat.m[3][0], mat.m[3][1] ,mat.m[3][2] };
	}

	static Matrix Identity()
	{
		Matrix mat;
		::D3DXMatrixIdentity(&mat);
		return mat;
	}


	static Vec3 Forward()
	{
		return Vec3{ 0.0f, 0.0f, 1.0f };
	}
	static Vec3 BackForward()
	{
		return Vec3{ 0.0f, 0.0f, -1.0f };
	}
	static Vec3 Right()
	{
		return Vec3{ 1.0f, 0.0f, 0.0f };
	}
	static Vec3 Left()
	{
		return Vec3{ -1.0f, 0.0f, 0.0f };
	}
	static Vec3 Up()
	{
		return Vec3{ 0.0f, 1.0f, 0.0f };
	}
	static Vec3 Down()
	{
		return Vec3{ 0.0f, -1.0f, 0.0f };
	}
	static Vec3 Zero()
	{
		return Vec3{ 0.0f, 0.0f, 0.0f };
	}
	static Vec3 One()
	{
		return Vec3{ 1.0f, 1.0f, 1.0f };
	}

	/* ------------- Color ------------- */

	static D3DXCOLOR Red()
	{
		return D3DXCOLOR{ 1.0f, 0.0f, 0.0f, 1.0f };
	}
	static D3DXCOLOR Green()
	{
		return D3DXCOLOR{ 0.0f, 1.0f, 0.0f, 1.0f };
	}
	static D3DXCOLOR Blue()
	{
		return D3DXCOLOR{ 0.0f, 0.0f, 1.0f, 1.0f };
	}
	static D3DXCOLOR Cyan()
	{
		return D3DXCOLOR{ 0.0f, 1.0f, 1.0f, 1.0f };
	}
	static D3DXCOLOR Yellow()
	{
		return D3DXCOLOR{ 1.0f, 1.0f, 0.0f, 1.0f };
	}
	static D3DXCOLOR Black()
	{
		return D3DXCOLOR{ 0.0f, 0.0f, 0.0f, 1.0f };
	}
	static D3DXCOLOR White()
	{
		return D3DXCOLOR{ 1.0f, 1.0f, 1.0f, 1.0f };
	}
};