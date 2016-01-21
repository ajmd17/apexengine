#ifndef SHADER_H
#define SHADER_H

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <iostream>
using std::ostream;

#include "enums.h"
#include "shader_util.h"
#include "material.h"

#include "../math/vector2f.h"
#include "../math/vector3f.h"
#include "../math/vector4f.h"
#include "../math/matrix4f.h"

class Environment;
class Mesh;
class Camera;

class Shader
{
protected:
	Material currentMaterial;
	int id;
private:

	ShaderProperties properties;
	Matrix4f worldMatrix, viewMatrix, projectionMatrix;
public:
	int *m_shaderIDs, m_shaderCounter; 
	// don't mess with this, used by the OpenGL renderer to count up and properly store shader IDs in the shader

	Shader(ShaderProperties properties, string vs_code, string fs_code);

	~Shader();

	const int &getProgramID()
	{
		return this->id;
	}

	void setProgramID(int id)
	{
		this->id = id;
	}

	void create();

    void use();
    
    virtual void end();

	void compileShader();

	void addProgram(ShaderType type, string &code);

	virtual void applyMaterial(Material &material);

	void setDefaultValues();

	virtual void update(Environment &environment, Camera &cam, Mesh &mesh);

	void setUniform(string name, int i);

	void setUniform(string name, float f);

	void setUniform(string name, float x, float y);

	void setUniform(string name, float x, float y, float z);

	void setUniform(string name, float x, float y, float z, float w);
	
	void setUniform(string name, Matrix4f &mat);

	void setUniform(string name, Vector2f &vec)
	{
		this->setUniform(name, vec.x, vec.y);
	}
	
	void setUniform(string name, Vector3f &vec)
	{
		this->setUniform(name, vec.x, vec.y, vec.z);
	}

	void setUniform(string name, Vector4f &vec)
	{
		this->setUniform(name, vec.x, vec.y, vec.z, vec.w);
	}

	void addVertexProgram(string &code)
	{
		addProgram(ShaderType::VertexShader, code);
	}

	void addFragmentProgram(string &code)
	{
		addProgram(ShaderType::FragmentShader, code);
	}

	ShaderProperties &getProperties()
	{
		return this->properties;
	}

};


#endif