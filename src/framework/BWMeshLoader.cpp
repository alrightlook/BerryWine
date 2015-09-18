#include "framework/BWMeshLoader.h"
#include "framework/BWFbxMesh.h"
#include "fbxsdk.h"

#ifdef IOS_REF
        #undef  IOS_REF
        #define IOS_REF (*(pManager->GetIOSettings()))
#endif


BWMeshLoader* BWMeshLoader::mInstance = 0;
void DisplayContent(FbxNode* pNode, BWFbxLoader* fbxloader);


BWMeshLoader::BWMeshLoader()
{
}

BWMeshLoader::~BWMeshLoader()
{

}

void InitializeSdkObjects(FbxManager*& pManager, FbxScene*& pScene)
{
    //The first thing to do is to create the FBX Manager which is the object allocator for almost all the classes in the SDK
    pManager = FbxManager::Create();
    if( !pManager )
    {
        FBXSDK_printf("Error: Unable to create FBX Manager!\n");
        exit(1);
    }
        else FBXSDK_printf("Autodesk FBX SDK version %s\n", pManager->GetVersion());

        //Create an IOSettings object. This object holds all import/export settings.
        FbxIOSettings* ios = FbxIOSettings::Create(pManager, IOSROOT);
        pManager->SetIOSettings(ios);

        //Load plugins from the executable directory (optional)
        FbxString lPath = FbxGetApplicationDirectory();
        pManager->LoadPluginsDirectory(lPath.Buffer());

    //Create an FBX scene. This object holds most objects imported/exported from/to files.
    pScene = FbxScene::Create(pManager, "My Scene");
        if( !pScene )
    {
        FBXSDK_printf("Error: Unable to create FBX scene!\n");
        exit(1);
    }
}

bool LoadScene(FbxManager* pManager, FbxDocument* pScene, const char* pFilename)
{
    int lFileMajor, lFileMinor, lFileRevision;
    int lSDKMajor,  lSDKMinor,  lSDKRevision;
    //int lFileFormat = -1;
    int i, lAnimStackCount;
    bool lStatus;
    char lPassword[1024];

    // Get the file version number generate by the FBX SDK.
    FbxManager::GetFileFormatVersion(lSDKMajor, lSDKMinor, lSDKRevision);

    // Create an importer.
    FbxImporter* lImporter = FbxImporter::Create(pManager,"");

    // Initialize the importer by providing a filename.
    const bool lImportStatus = lImporter->Initialize(pFilename, -1, pManager->GetIOSettings());
    lImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);

    if( !lImportStatus )
    {
        FbxString error = lImporter->GetStatus().GetErrorString();
        FBXSDK_printf("Call to FbxImporter::Initialize() failed.\n");
        FBXSDK_printf("Error returned: %s\n\n", error.Buffer());

        if (lImporter->GetStatus().GetCode() == FbxStatus::eInvalidFileVersion)
        {
            FBXSDK_printf("FBX file format version for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);
            FBXSDK_printf("FBX file format version for file '%s' is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);
        }

        return false;
    }

    FBXSDK_printf("FBX file format version for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);

    if (lImporter->IsFBX())
    {
        FBXSDK_printf("FBX file format version for file '%s' is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);

        // From this point, it is possible to access animation stack information without
        // the expense of loading the entire file.

        FBXSDK_printf("Animation Stack Information\n");

        lAnimStackCount = lImporter->GetAnimStackCount();

        FBXSDK_printf("    Number of Animation Stacks: %d\n", lAnimStackCount);
        FBXSDK_printf("    Current Animation Stack: \"%s\"\n", lImporter->GetActiveAnimStackName().Buffer());
        FBXSDK_printf("\n");

        for(i = 0; i < lAnimStackCount; i++)
        {
            FbxTakeInfo* lTakeInfo = lImporter->GetTakeInfo(i);

            FBXSDK_printf("    Animation Stack %d\n", i);
            FBXSDK_printf("         Name: \"%s\"\n", lTakeInfo->mName.Buffer());
            FBXSDK_printf("         Description: \"%s\"\n", lTakeInfo->mDescription.Buffer());

            // Change the value of the import name if the animation stack should be imported 
            // under a different name.
            FBXSDK_printf("         Import Name: \"%s\"\n", lTakeInfo->mImportName.Buffer());

            // Set the value of the import state to false if the animation stack should be not
            // be imported. 
            FBXSDK_printf("         Import State: %s\n", lTakeInfo->mSelect ? "true" : "false");
            FBXSDK_printf("\n");
        }

        // Set the import states. By default, the import states are always set to 
        // true. The code below shows how to change these states.
        IOS_REF.SetBoolProp(IMP_FBX_MATERIAL,        true);
        IOS_REF.SetBoolProp(IMP_FBX_TEXTURE,         true);
        IOS_REF.SetBoolProp(IMP_FBX_LINK,            true);
        IOS_REF.SetBoolProp(IMP_FBX_SHAPE,           true);
        IOS_REF.SetBoolProp(IMP_FBX_GOBO,            true);
        IOS_REF.SetBoolProp(IMP_FBX_ANIMATION,       true);
        IOS_REF.SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
    }

    // Import the scene.
    lStatus = lImporter->Import(pScene);

    if(lStatus == false && lImporter->GetStatus().GetCode() == FbxStatus::ePasswordError)
    {
        FBXSDK_printf("Please enter password: ");

        lPassword[0] = '\0';

        FBXSDK_CRT_SECURE_NO_WARNING_BEGIN
        scanf("%s", lPassword);
        FBXSDK_CRT_SECURE_NO_WARNING_END

        FbxString lString(lPassword);

        IOS_REF.SetStringProp(IMP_FBX_PASSWORD,      lString);
        IOS_REF.SetBoolProp(IMP_FBX_PASSWORD_ENABLE, true);

        lStatus = lImporter->Import(pScene);

        if(lStatus == false && lImporter->GetStatus().GetCode() == FbxStatus::ePasswordError)
        {
            FBXSDK_printf("\nPassword is wrong, import aborted.\n");
        }
    }

    // Destroy the importer.
    lImporter->Destroy();

    return lStatus;
}

void DestroySdkObjects(FbxManager* pManager, bool pExitStatus)
{
    //Delete the FBX Manager. All the objects that have been allocated using the FBX Manager and that haven't been explicitly destroyed are also automatically destroyed.
    if( pManager ) pManager->Destroy();
        if( pExitStatus ) FBXSDK_printf("Program Success!\n");
}

void BWMeshLoader::LoadFBXScene(const char* filename, BWFbxLoader* fbxloader)
{
	FbxManager* fbxMgr;
	FbxScene* bwScene;
	
	InitializeSdkObjects(fbxMgr, bwScene);
	bool lResult = LoadScene(fbxMgr, bwScene, filename);

	FbxNode* rootNode = bwScene->GetRootNode();
	if (rootNode)
	{
		for(int i = 0; i < rootNode->GetChildCount(); i++)
		{
			DisplayContent(rootNode->GetChild(i), fbxloader);
		}
	}


}

void DisplayPolygons(FbxMesh* pMesh, BWFbxLoader* fbxloader)
{
	
	int indicesSize = 0;
	for(int i = 0; i < pMesh->GetPolygonCount(); i ++)
	{
		indicesSize += pMesh->GetPolygonSize(i);
	}
	std::cout<<"indicesSize is " << indicesSize<<std::endl;

	FbxVector4* lControlPoints = pMesh->GetControlPoints();

	std::cout<<"Point count is " << pMesh->GetControlPointsCount()<<std::endl;

	BWFbxMesh* bwMesh = new BWFbxMesh(pMesh->GetName(), pMesh->GetControlPointsCount() * 4, indicesSize);

	for(int i = 0; i < pMesh->GetPolygonCount(); i++)
	{
		for (int j = 0; j <= 4; j++)
		{
			bwMesh->setMeshValue(i*4+j, lControlPoints[i][j]);
		}
	}
	
	int index = 0;
	for (int  i = 0; i < pMesh->GetPolygonCount(); i++)
	{
		for(int j= 0; j < pMesh->GetPolygonSize(i); j++)
		{
			bwMesh->setIndiceValue(index, pMesh->GetPolygonVertex(i, j));
			index++;
		}
	}
	fbxloader->mMeshes.push_back(bwMesh);

}



void DisplayMesh(FbxNode* pNode,BWFbxLoader* fbxloader)
{
    FbxMesh* lMesh = (FbxMesh*) pNode->GetNodeAttribute ();
	std::cout<<"The node mesh name is " << lMesh->GetName()<<std::endl;
    //DisplayString("Mesh Name: ", (char *) pNode->GetName());
    //DisplayMetaDataConnections(lMesh);
    //DisplayControlsPoints(lMesh);
    DisplayPolygons(lMesh, fbxloader);
    //DisplayMaterialMapping(lMesh);
    //DisplayMaterial(lMesh);
    //DisplayTexture(lMesh);
    //DisplayMaterialConnections(lMesh);
    //DisplayLink(lMesh);
    //DisplayShape(lMesh);
    //    
    //DisplayCache(lMesh);
}



void DisplayContent(FbxNode* pNode, BWFbxLoader* fbxloader)
{
    FbxNodeAttribute::EType lAttributeType;
    int i;

    if(pNode->GetNodeAttribute() == NULL)
    {
        FBXSDK_printf("NULL Node Attribute\n\n");
    }
    else
    {
        lAttributeType = (pNode->GetNodeAttribute()->GetAttributeType());

        switch (lAttributeType)
        {
            default:
                break;
        case FbxNodeAttribute::eMarker:  
            //DisplayMarker(pNode);
            break;

        case FbxNodeAttribute::eSkeleton:  
            //DisplaySkeleton(pNode);
            break;

        case FbxNodeAttribute::eMesh:      
            DisplayMesh(pNode,  fbxloader);
            break;

        case FbxNodeAttribute::eNurbs:      
            //DisplayNurb(pNode);
            break;

        case FbxNodeAttribute::ePatch:     
            //DisplayPatch(pNode);
            break;

        case FbxNodeAttribute::eCamera:    
            //DisplayCamera(pNode);
			std::cout<<"This is a camera"<<std::endl;
            break;

        case FbxNodeAttribute::eLight:     
            //DisplayLight(pNode);
			std::cout<<"This is a light"<<std::endl;
            break;

        case FbxNodeAttribute::eLODGroup:
            //DisplayLodGroup(pNode);
            break;
        }   
    }

    /*DisplayUserProperties(pNode);
    DisplayTarget(pNode);
    DisplayPivotsAndLimits(pNode);
    DisplayTransformPropagation(pNode);
    DisplayGeometricTransform(pNode);*/

    for(i = 0; i < pNode->GetChildCount(); i++)
    {
        DisplayContent(pNode->GetChild(i), fbxloader);
    }
}

BWMeshLoader* BWMeshLoader::getInstance()
{
	if(mInstance == 0)
	{
		mInstance = new BWMeshLoader();
	}
	return mInstance;
}

void BWMeshLoader::Debug(const char* content)
{
	std::cout<<content<<std::endl;
}