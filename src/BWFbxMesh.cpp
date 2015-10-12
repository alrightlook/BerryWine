#include "framework/BWFbxMesh.h"
#include "BWScene.h"
#include "BWCommon.h"

#include <iostream>

BWFbxMesh::BWFbxMesh(std::string name, int meshNum, int indicesNum)
{
	mName = name;
	mMesh = (float*) malloc(meshNum);
	mIndices = (GLuint*) malloc(indicesNum);
	mNormals = (float*) malloc(indicesNum);
	mBufferSize = meshNum;
	this->name = name;
	this->mType = BWEntityType::eMesh;

	mMeshNum = meshNum;
	mIndicesNum = indicesNum;
	mShader = new BWShader("MeshADS.vert", "MeshADS.frag");
}

BWFbxMesh::~BWFbxMesh()
{
	free(mMesh);
	free(mIndices);
}

float* BWFbxMesh::GetMesh()
{
	return mMesh;
}

GLuint* BWFbxMesh::GetIndices()
{
	return mIndices;
}

void BWFbxMesh::setMeshValue(int index, float val)
{
	mMesh[index] = val;
}

void BWFbxMesh::setNormal(int index, float val)
{
	mNormals[index] = val;
}

void BWFbxMesh::setIndiceValue(int index, int val)
{
	mIndices[index] = val;
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
	return mMesh;
}

float* BWFbxMesh::getNormals()
{
	return mNormals;
}

GLuint* BWFbxMesh::getIndices()
{
	return mIndices;
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
	/*glBindVertexArray(mVao);
	GLuint vbo = RegisterVertexData((void*)mMesh);
	mShader->registerAttribute("PositionMesh", 3, GL_FLOAT, GL_FALSE, 1 * sizeof(float) , 0, 0);

	if(BWCamera::getCurrentCamera() != 0)
	{
		glm::mat4 viewMatrix = BWCamera::getCurrentCamera()->getMatrix();
		mShader->registerAttributeMatrix4("viewMat", 4, GL_FLOAT, GL_FALSE, 0, viewMatrix, 1);	
	}


	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndicesNum * sizeof(GLuint), mIndices, GL_STATIC_DRAW);


	mShader->Link();
	mShader->Use();
	if (BWScene::getCurrentScene() != 0)
	{
		glm::mat4 projection = BWScene::getCurrentScene()->getPerspectiveMatrix();	
		BWCommon::DebugOutputMatrix(projection);
		glUniformMatrix4fv(glGetUniformLocation(mShader->getProgramID(), "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projection));
	}
	mShader->Unuse();
	glBindVertexArray(0);
	std::cout<<"Indeices num :" << mIndicesNum<< std::endl;*/



	glBindVertexArray(mVao);
	GLuint vbo = RegisterVertexData((void*)mMesh);
	mShader->registerAttribute("PositionMesh", 3, GL_FLOAT, GL_FALSE, 4* sizeof(float) , 0, 0);

	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndicesNum * sizeof(GLuint), mIndices, GL_STATIC_DRAW);


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


	if (BWScene::getCurrentScene() != 0)
	{
		glm::mat4 projection = BWScene::getCurrentScene()->getPerspectiveMatrix();	
		BWCommon::DebugOutputMatrix(projection);
		glUniformMatrix4fv(glGetUniformLocation(mShader->getProgramID(), "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projection));
	}
	mShader->Unuse();
	glBindVertexArray(0);
	DisplayMesh();
	DisplayIndices();

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

	glDrawElements(GL_QUADS, mIndicesNum, GL_UNSIGNED_INT, 0);
	mShader->Unuse();
	glBindVertexArray(0);
}