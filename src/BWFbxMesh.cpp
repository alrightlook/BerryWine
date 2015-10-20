#include "framework/BWFbxMesh.h"
#include "BWScene.h"
#include "BWCommon.h"

#include <iostream>

BWFbxMesh::BWFbxMesh(std::string name)
{
	mName = name;
	this->name = name;
	this->mType = BWEntityType::eMesh;
	mShader = new BWShader("MeshADS.vert", "MeshADS.frag");
}

BWFbxMesh::BWFbxMesh(std::string name, int meshNum, int indicesNum)
{
	mName = name;
	mBufferSize = meshNum;
	this->name = name;
	this->mType = BWEntityType::eMesh;

	mMeshNum = meshNum;
	mIndicesNum = indicesNum;
	mShader = new BWShader("MeshADS.vert", "MeshADS.frag");
}

BWFbxMesh::~BWFbxMesh()
{
}

float* BWFbxMesh::GetMesh()
{
	return &mMesh[0];
}

GLuint* BWFbxMesh::GetIndices()
{
	return &mIndices[0];
}

void BWFbxMesh::setMeshValue(std::vector<float> val)
{
	mMesh = val;
	mBufferSize = mMesh.size();
}

void BWFbxMesh::setNormal(float val)
{
	mNormals.push_back(val);
}

void BWFbxMesh::setMaterialAmbient(std::vector<float> val)
{
	this->mMatAmbient = val;
}


void BWFbxMesh::setMaterialSpecular(std::vector<float> val)
{
	this->mMatSpecular = val;
}

void BWFbxMesh::setMaterialDiffuse(std::vector<float> val)
{
	this->mMatDiffuse = val;
}



void BWFbxMesh::setIndiceValue(std::vector<GLuint> val)
{
	mIndices = val;
}

void BWFbxMesh::DisplayMesh()
{
	for (int i = 0; i < mMeshNum; i++ )
	{
		std::cout<<mMesh[i]<<" ";
	}

	std::cout<<"Total mMeshNum is "<< mMeshNum<<std::endl;
}

float* BWFbxMesh::getMeshVertex()
{
	return &mMesh[0];
}

float* BWFbxMesh::getNormals()
{
	return &mNormals[0];
}

GLuint* BWFbxMesh::getIndices()
{
	return &mIndices[0];
}

void BWFbxMesh::DisplayIndices()
{
	for (int i =0; i < mIndicesNum; i++)
	{
		std::cout<<mIndices[i]<<std::endl;
	}
}

void BWFbxMesh::Init()
{
	glBindVertexArray(mVao);
	GLuint vbo = RegisterVertexData(mMesh);
	mShader->registerAttribute("PositionMesh", 3, GL_FLOAT, GL_FALSE, 4* sizeof(float) , 0, 0);

	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLuint), &mIndices[0], GL_STATIC_DRAW);


	if(BWCamera::getCurrentCamera() != 0)
	{
		glm::mat4 viewMatrix = BWCamera::getCurrentCamera()->getMatrix();
		mShader->registerAttributeMatrix4("viewMat", 4, GL_FLOAT, GL_FALSE, 0, viewMatrix, 2);	
	}
	
	mShader->Link();
	mShader->Use();
	
	//We do some transformation test to the triangle here;
	//mTransform.Translate(glm::vec3(0.0f, 0.0f, -5.0f));	 doeable!
	//mTransform.Scale(glm::vec3(2.0f, 2.0f, 2.0f));

	initMaterial();
	if (BWScene::getCurrentScene() != 0)
	{
		glm::mat4 projection = BWScene::getCurrentScene()->getPerspectiveMatrix();	
		BWCommon::DebugOutputMatrix(projection);
		glUniformMatrix4fv(glGetUniformLocation(mShader->getProgramID(), "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projection));
	}
	mShader->Unuse();
	glBindVertexArray(0);
}
void BWFbxMesh::initMaterial()
{
	if (mMatAmbient.size() == 0 || mMatSpecular.size() == 0 || mMatDiffuse.size() == 0 )
	{
		return;
	}
	GLuint blockIndex = glGetUniformBlockIndex(mShader->getProgramID(), "MeshMaterial");
	GLint blockSize;
	glGetActiveUniformBlockiv(mShader->getProgramID(), blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
	GLubyte* blockBuffer;
	blockBuffer = (GLubyte*) malloc(blockSize);
	memset(blockBuffer,0, blockSize);

	const GLchar* names[]  = {"MeshMaterial.ambient", "MeshMaterial.specular", "MeshMaterial.diffuse" };

	GLuint indices[3];
	glGetUniformIndices(mShader->getProgramID(), 3, names, indices);

	GLint offset[3];
	glGetActiveUniformsiv(mShader->getProgramID(), 3, indices, GL_UNIFORM_OFFSET, offset);

	memcpy(blockBuffer + offset[0], &mMatAmbient[0], 3 * sizeof(float));
	memcpy(blockBuffer + offset[1], &mMatSpecular[0], 3 * sizeof(float));
	memcpy(blockBuffer + offset[2], &mMatDiffuse[0], 3 * sizeof(float));

	GLuint uboHandle;
	glGenBuffers(1, &uboHandle);
	glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
	glBufferData(GL_UNIFORM_BUFFER, blockSize, blockBuffer, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboHandle);
}

void BWFbxMesh::Frame()
{
	glBindVertexArray(mVao);
	mShader->EnableAttributes();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	mShader->Use();
	BWEntity::Frame();
	if(BWCamera::getCurrentCamera() != 0)
	{
		glm::mat4 viewMatrix = BWCamera::getCurrentCamera()->getMatrix();
		glUniformMatrix4fv(glGetUniformLocation(mShader->getProgramID(), "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	}

	glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
	mShader->Unuse();
	glBindVertexArray(0);
}