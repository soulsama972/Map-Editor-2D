#pragma once
#include<cmath>


#define PI 3.1415926535897932384626433832795f


class Matrix4x4
{
public:
#pragma warning (push)
#pragma warning (disable : 26495)
	Matrix4x4() { Identity(); }
	Matrix4x4(float* viewMatrix)
#pragma warning (pop)
	{
		pFloatToMatrix(viewMatrix);
	}
	union 
	{

		float m[16];
		float u[4][4];

	};
	
	
	

	inline void operator *= (float v)
	{
		for (int i = 0; i < 16; i++)
			m[i] *= v;

	}

	inline void operator /= (float v)
	{
		for (int i = 0; i < 16; i++)
			m[i] /= v;

	}

	inline Matrix4x4 operator * (Matrix4x4 m)
	{
		Matrix4x4 mm;
		mm.Mul(*this, m);
		return mm;
	}

	inline void RotX(float Angle)
	{
		float cosAng = cosf(Angle);
		float sinAng = sinf(Angle);

		u[1][1] = cosAng;
		u[2][2] = cosAng;
		u[1][2] = sinAng;
		u[2][1] = -sinAng;

	}

	inline void RotY(float Angle)
	{
		float cosAng = cosf(Angle);
		float sinAng = sinf(Angle);

		u[0][0] = cosAng;
		u[2][2] = cosAng;
		u[0][2] = sinAng;
		u[2][0] = -sinAng;
	}

	inline void RotZ(float Angle)
	{
		float cosAng = cosf(Angle);
		float sinAng = sinf(Angle);

		u[0][0] = cosAng;
		u[1][1] = cosAng;
		u[0][1] = sinAng;
		u[1][0] = -sinAng;
	}

	inline void Identity()
	{
		for (int i = 0; i < 16; i++)
		{
			if (i % 4 == 0)
				m[i] = 1;
			m[i] = 0;
		}
	}


	inline void pFloatToMatrix(float* viewMatrix)
	{
		for (int i = 0; i < 16; i++)
		{
			m[i] = viewMatrix[i];
		}
	}

	inline void Mul(const Matrix4x4 src1, const Matrix4x4 src2)
	{
		u[0][0] = src1.u[0][0] * src2.u[0][0] + src1.u[0][1] * src2.u[1][0] + src1.u[0][2] * src2.u[2][0] + src1.u[0][3] * src2.u[3][0];
		u[0][1] = src1.u[0][0] * src2.u[0][1] + src1.u[0][1] * src2.u[1][1] + src1.u[0][2] * src2.u[2][1] + src1.u[0][3] * src2.u[3][1];
		u[0][2] = src1.u[0][0] * src2.u[0][2] + src1.u[0][1] * src2.u[1][2] + src1.u[0][2] * src2.u[2][2] + src1.u[0][3] * src2.u[3][2];
		u[0][3] = src1.u[0][0] * src2.u[0][3] + src1.u[0][1] * src2.u[1][3] + src1.u[0][2] * src2.u[2][3] + src1.u[0][3] * src2.u[3][3];

		u[1][0] = src1.u[1][0] * src2.u[0][0] + src1.u[1][1] * src2.u[1][0] + src1.u[1][2] * src2.u[2][0] + src1.u[1][3] * src2.u[3][0];
		u[1][1] = src1.u[1][0] * src2.u[0][1] + src1.u[1][1] * src2.u[1][1] + src1.u[1][2] * src2.u[2][1] + src1.u[1][3] * src2.u[3][1];
		u[1][2] = src1.u[1][0] * src2.u[0][2] + src1.u[1][1] * src2.u[1][2] + src1.u[1][2] * src2.u[2][2] + src1.u[1][3] * src2.u[3][2];
		u[1][3] = src1.u[1][0] * src2.u[0][3] + src1.u[1][1] * src2.u[1][3] + src1.u[1][2] * src2.u[2][3] + src1.u[1][3] * src2.u[3][3];

		u[2][0] = src1.u[2][0] * src2.u[0][0] + src1.u[2][1] * src2.u[1][0] + src1.u[2][2] * src2.u[2][0] + src1.u[2][3] * src2.u[3][0];
		u[2][1] = src1.u[2][0] * src2.u[0][1] + src1.u[2][1] * src2.u[1][1] + src1.u[2][2] * src2.u[2][1] + src1.u[2][3] * src2.u[3][1];
		u[2][2] = src1.u[2][0] * src2.u[0][2] + src1.u[2][1] * src2.u[1][2] + src1.u[2][2] * src2.u[2][2] + src1.u[2][3] * src2.u[3][2];
		u[2][3] = src1.u[2][0] * src2.u[0][3] + src1.u[2][1] * src2.u[1][3] + src1.u[2][2] * src2.u[2][3] + src1.u[2][3] * src2.u[3][3];

		u[3][0] = src1.u[3][0] * src2.u[0][0] + src1.u[3][1] * src2.u[1][0] + src1.u[3][2] * src2.u[2][0] + src1.u[3][3] * src2.u[3][0];
		u[3][1] = src1.u[3][0] * src2.u[0][1] + src1.u[3][1] * src2.u[1][1] + src1.u[3][2] * src2.u[2][1] + src1.u[3][3] * src2.u[3][1];
		u[3][2] = src1.u[3][0] * src2.u[0][2] + src1.u[3][1] * src2.u[1][2] + src1.u[3][2] * src2.u[2][2] + src1.u[3][3] * src2.u[3][2];
		u[3][3] = src1.u[3][0] * src2.u[0][3] + src1.u[3][1] * src2.u[1][3] + src1.u[3][2] * src2.u[2][3] + src1.u[3][3] * src2.u[3][3];

		
	}

	inline void Translate(float t[3])
	{
		this->u[3][0] = t[0];
		this->u[3][1] = t[1];
		this->u[3][2] = t[2];
	}

};

template<typename T>
class vec2
{
public:
	T x, y;

	inline vec2()
	{
		x = (T)0;
		y = (T)0;
	}

	inline vec2(const vec2& src)
	{
		x = src.x;
		y = src.y;
	}
	template<typename K>
	inline vec2(const K& x, const K& y)
	{
		this->x = static_cast<T>(x);
		this->y = static_cast<T>(y);
	}

	inline T GetLength()
	{
		return x * x + y * y;
	}

	inline T GetMagnitude()
	{
		return (T)sqrt(GetLength());
	}

	inline vec2 GetNormalize()
	{
		T magnitude = GetMagnitude();
		return vec2(x / magnitude, y / magnitude);
	}

	inline vec2 operator+(const vec2 v)
	{
		return vec2(x + v.x, y + v.y);
	}

	inline vec2 operator-(const vec2 v)
	{
		return vec2(x - v.x, y - v.y);
	}

	inline vec2 operator*(const vec2 v)
	{
		return vec2(x * v.x, y * v.y);
	}

	inline vec2 operator/(const vec2 v)
	{
		return vec2(x / v.x, y / v.y);
	}

	inline vec2 operator-(const float f)
	{
		return vec2(x - f, y - f);
	}
	inline T* ToPointer()
	{
		return reinterpret_cast<T*>(this);
	}


};


template<typename T>
class vec3
{
public:
	T x, y, z;

	inline vec3()
	{
		x = (T)0;
		y = (T)0;
		z = (T)0;
	}

	inline vec3(const vec3& src)
	{
		x = src.x;
		y = src.y;
		z = src.z;
	}

	template<typename K>
	inline vec3(const K& x, const K& y,const K & z)
	{
		this->x = static_cast<T>(x);
		this->y = static_cast<T>(y);
		this->z = static_cast<T>(z);
	}

	inline T GetDot(const vec3<T>& v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline vec3 Cross(const vec3<T>& v)
	{

		return vec3(y * v.z - z - v.y,x * v.z - z * v.x, x * v.y - y * v.x);
	}
	inline T GetLength()
	{
		return (T)sqrt(GetDot(*this));
	}

	inline vec3 GetNormalize()
	{
		T magnitude = GetLength();
		return vec3(x / magnitude, y / magnitude,z/magnitude);
	}
	
	inline bool	 operator==(const vec3 v)
	{
		return (x == v.x && y == v.y && v.z == z);
	}

	inline vec3 operator+(const vec3 v)
	{
		return vec3(x + v.x, y + v.y, z + v.z);
	}

	inline vec3 operator-(const vec3 v)
	{
		return vec3(x - v.x, y - v.y, z - v.z);
	}

	inline vec3 operator*(const vec3 v)
	{
		return vec3(x * v.x, y * v.y, z * v.z);
	}

	inline vec3 operator/(const vec3 v)
	{
		return vec3(x / v.x, y / v.y, z / v.z);
	}

	inline vec3 operator/(float  v)
	{
		return vec3(x / v, y / v, z / v);
	}

	inline vec3 operator*(float  v)
	{
		return vec3(x * v, y * v, z * v);
	}
	inline T* ToPointer()
	{
		return reinterpret_cast<T*>(this);
	}
};


template<typename T>
class vec4
{
public:
	T x, y, z, w;

	inline vec4()
	{
		x = (T)0;
		y = (T)0;
		z = (T)0;
		w = (T)0;
	}

	inline vec4(const vec4& src)
	{
		x = src.x;
		y = src.y;
		z = src.z;
		w = src.w;
	}

	template<typename K>
	inline vec4(const K& x, const K& y, const K& z , const K& w)
	{
		this->x = static_cast<T>(x);
		this->y = static_cast<T>(y);
		this->z = static_cast<T>(z);
		this->w = static_cast<T>(w);
	}

	inline T GetLength()
	{
		return x * x + y * y + z * z + w * w;
	}

	inline T GetMagnitude()
	{
		return (T)sqrt(GetLength());
	}

	inline vec4 GetNormalize()
	{
		T magnitude = GetMagnitude();
		return vec4(x / magnitude, y / magnitude);
	}

	inline void Transform(const vec3<float>  v, const Matrix4x4  m)
	{
		
		x = v.x * m.u[0][0] + v.y * m.u[1][0] + v.z * m.u[2][0] + m.u[3][0];
		y = v.x * m.u[0][1] + v.y * m.u[1][1] + v.z * m.u[2][1] + m.u[3][1];
		z = v.x * m.u[0][2] + v.y * m.u[1][2] + v.z * m.u[2][2] + m.u[3][2];
		w = v.x * m.u[0][3] + v.y * m.u[1][3] + v.z * m.u[2][3] + m.u[3][3];
	}

	inline vec4 operator+(const vec4 v)
	{
		return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	inline vec4 operator-(const vec4 v)
	{
		return vec4(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	inline vec4 operator*(const vec4 v)
	{
		return vec4(x * v.x, y * v.y, z * v.z, w * v.w);
	}

	inline vec4 operator/(const vec4 v)
	{
		return vec4(x / v.x, y / v.y, z / v.z, w / v.w);
	}

	inline T* ToPointer()
	{
		return reinterpret_cast<T*>(this);
	}
};


using fVec2 = vec2<float>;
using fVec3 = vec3<float>;
using fVec4 = vec4<float>;


inline bool WorldToScreen(float* viewMatrix, fVec3 pos, fVec2& newPos, fVec2 screenSize, bool transpose)
{
	auto TransfromCoord = [](float x, float f)
	{
		return f * (x + 1) * 0.5f;
	};
	fVec4 vec4;
	Matrix4x4 view = viewMatrix;

	///*if (transpose)
	//	*/view.Transpose(view);

	vec4.Transform(pos, view);

	if (vec4.w < 0.5f)
		return false;

	vec4.x /= vec4.w;
	vec4.y /= vec4.w;

	newPos.x = TransfromCoord(vec4.x, screenSize.x);
	newPos.y = TransfromCoord(-vec4.y, screenSize.y);

	return true;
}

inline fVec2 GetScale(fVec2 s,fVec2 screen)
{
	return fVec2(s.x / screen.x, s.y / screen.y);
}

inline fVec2 GetTransalte(fVec2 t, fVec2 c, fVec2 screen)
{
	return fVec2((t.x + c.x / 2) * 2 / screen.x - 1, 1 - 2 * (t.y + c.y / 2) / screen.y);
}


inline Matrix4x4 LookAtRH(fVec3 eye, fVec3 target, fVec3 up)
{
	fVec3 zaxis = (eye - target);    // The "forward" vector.
	zaxis = zaxis.GetNormalize();
	fVec3 xaxis = up.Cross(zaxis);// The "right" vector.
	xaxis = xaxis.GetNormalize();
	fVec3 yaxis =zaxis.Cross( xaxis);     // The "up" vector.

	// Create a 4x4 view matrix from the right, up, forward and eye position vectors
	Matrix4x4 viewMatrix;
	viewMatrix.u[0][0] = xaxis.x;
	viewMatrix.u[1][0] = xaxis.y;
	viewMatrix.u[2][0] = xaxis.z;
	viewMatrix.u[3][0] = -xaxis.GetDot(eye);

	viewMatrix.u[0][1] = yaxis.x;
	viewMatrix.u[1][1] = yaxis.y;
	viewMatrix.u[2][1] = yaxis.z;
	viewMatrix.u[3][1] = -yaxis.GetDot(eye);

	viewMatrix.u[0][2] = zaxis.x;
	viewMatrix.u[1][2] = zaxis.y;
	viewMatrix.u[2][2] = zaxis.z;
	viewMatrix.u[3][2] = -zaxis.GetDot(eye);

	viewMatrix.u[0][3] = 0.0f;
	viewMatrix.u[1][3] = 0.0f;
	viewMatrix.u[2][3] = 0.0f;
	viewMatrix.u[3][3] = 1;

	return viewMatrix;
}