#pragma once
class Object
{
public:
	Object(float objHight,float objWidth,bool isDestroyable);
	Object() = default;
	void setObjHight(float objHight);
	void setObjWidth(float objWidth);
	void setIsDestroyable(float isDestroyable);
protected:

private:
	float objHight =0;
	float objWidth =0;
	bool isDestroyable = false;
	/*drawable*/


};

