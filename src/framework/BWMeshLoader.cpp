#include "framework/BWMeshLoader.h"
#include "framework/BWFbxMesh.h"
#include "fbxsdk.h"
#include <stdlib.h>
#include <vector>

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
	int j = rootNode->GetChildCount();
	if (rootNode)
	{
		for(int i = 0; i < rootNode->GetChildCount(); i++)
		{
			DisplayContent(rootNode->GetChild(i), fbxloader);
		}
	}
}

void DisplayPolygons(FbxMesh* pMesh, BWFbxMesh* bwMesh)
{
	int indicesSize = 0;
	for(int i = 0; i < pMesh->GetPolygonCount(); i ++)
	{
		indicesSize += pMesh->GetPolygonSize(i);
	}
	FbxVector4* lControlPoints = pMesh->GetControlPoints();

	std::vector<float> data;
	for(int i = 0; i < pMesh->GetControlPointsCount(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			data.push_back(lControlPoints[i][j]);
		}
	}

	bwMesh->setMeshValue(data);

	std::vector<GLuint> indices;
	std::vector<float> vecNormal;
	int index = 0;
	for (int  i = 0; i < pMesh->GetPolygonCount(); i++)
	{
		for(int j= 0; j < pMesh->GetPolygonSize(i); j++)
		{
			indices.push_back(pMesh->GetPolygonVertex(i, j));
			FbxVector4 theNormal;
			pMesh->GetPolygonVertexNormal(i, j, theNormal);
			theNormal.Normalize();
			
			bwMesh->setNormal(theNormal[0]);
			bwMesh->setNormal(theNormal[1]);
			bwMesh->setNormal(theNormal[2]);
			bwMesh->setNormal(theNormal[3]);

			index++;
		}
	}

	bwMesh->setIndiceValue(indices);	
}

void DisplayMaterial(FbxGeometry* pGeometry, BWFbxMesh* bwMesh)
{
    int lMaterialCount = 0;
    FbxNode* lNode = NULL;
    if(pGeometry){
        lNode = pGeometry->GetNode();
        if(lNode)
            lMaterialCount = lNode->GetMaterialCount();    
    }

    if (lMaterialCount > 0)
    {
        FbxPropertyT<FbxDouble3> lKFbxDouble3;
        FbxPropertyT<FbxDouble> lKFbxDouble1;
        FbxColor theColor;

        for (int lCount = 0; lCount < lMaterialCount; lCount ++)
        {
			FbxSurfaceMaterial *lMaterial = lNode->GetMaterial(lCount);
			
			//Get the implementation to see if it's a hardware shader.
            const FbxImplementation* lImplementation = GetImplementation(lMaterial, FBXSDK_IMPLEMENTATION_HLSL);
            FbxString lImplemenationType = "HLSL";
            if(!lImplementation)
            {
                lImplementation = GetImplementation(lMaterial, FBXSDK_IMPLEMENTATION_CGFX);
                lImplemenationType = "CGFX";
            }
            if(lImplementation)
            {
                //Now we have a hardware shader, let's read it
                FBXSDK_printf("            Hardware Shader Type: %s\n", lImplemenationType.Buffer());
                const FbxBindingTable* lRootTable = lImplementation->GetRootTable();
                FbxString lFileName = lRootTable->DescAbsoluteURL.Get();
                FbxString lTechniqueName = lRootTable->DescTAG.Get(); 


                const FbxBindingTable* lTable = lImplementation->GetRootTable();
                size_t lEntryNum = lTable->GetEntryCount();

                for(int i=0;i <(int)lEntryNum; ++i)
                {
                    const FbxBindingTableEntry& lEntry = lTable->GetEntry(i);
                    const char* lEntrySrcType = lEntry.GetEntryType(true); 
                    FbxProperty lFbxProp;


                    FbxString lTest = lEntry.GetSource();
                    FBXSDK_printf("            Entry: %s\n", lTest.Buffer());


                    if ( strcmp( FbxPropertyEntryView::sEntryType, lEntrySrcType ) == 0 )
                    {   
                        lFbxProp = lMaterial->FindPropertyHierarchical(lEntry.GetSource()); 
                        if(!lFbxProp.IsValid())
                        {
                            lFbxProp = lMaterial->RootProperty.FindHierarchical(lEntry.GetSource());
                        }


                    }
                    else if( strcmp( FbxConstantEntryView::sEntryType, lEntrySrcType ) == 0 )
                    {
                        lFbxProp = lImplementation->GetConstants().FindHierarchical(lEntry.GetSource());
                    }
                    if(lFbxProp.IsValid())
                    {
                        if( lFbxProp.GetSrcObjectCount<FbxTexture>() > 0 )
                        {
                            //do what you want with the textures
                            for(int j=0; j<lFbxProp.GetSrcObjectCount<FbxFileTexture>(); ++j)
                            {
                                FbxFileTexture *lTex = lFbxProp.GetSrcObject<FbxFileTexture>(j);
                                FBXSDK_printf("           File Texture: %s\n", lTex->GetFileName());
                            }
                            for(int j=0; j<lFbxProp.GetSrcObjectCount<FbxLayeredTexture>(); ++j)
                            {
                                FbxLayeredTexture *lTex = lFbxProp.GetSrcObject<FbxLayeredTexture>(j);
                                FBXSDK_printf("        Layered Texture: %s\n", lTex->GetName());
                            }
                            for(int j=0; j<lFbxProp.GetSrcObjectCount<FbxProceduralTexture>(); ++j)
                            {
                                FbxProceduralTexture *lTex = lFbxProp.GetSrcObject<FbxProceduralTexture>(j);
                                FBXSDK_printf("     Procedural Texture: %s\n", lTex->GetName());
                            }
                        }
                        else
                        {
                            FbxDataType lFbxType = lFbxProp.GetPropertyDataType();
                            FbxString blah = lFbxType.GetName();
                            if(FbxBoolDT == lFbxType)
                            {
                                //DisplayBool("                Bool: ", lFbxProp.Get<FbxBool>() );
                            }
                            else if ( FbxIntDT == lFbxType ||  FbxEnumDT  == lFbxType )
                            {
                                //DisplayInt("                Int: ", lFbxProp.Get<FbxInt>());
                            }
                            else if ( FbxFloatDT == lFbxType)
                            {
                                //DisplayDouble("                Float: ", lFbxProp.Get<FbxFloat>());

                            }
                            else if ( FbxDoubleDT == lFbxType)
                            {
                                //DisplayDouble("                Double: ", lFbxProp.Get<FbxDouble>());
                            }
                            else if ( FbxStringDT == lFbxType
                                ||  FbxUrlDT  == lFbxType
                                ||  FbxXRefUrlDT  == lFbxType )
                            {
                                //DisplayString("                String: ", lFbxProp.Get<FbxString>().Buffer());
                            }
                            else if ( FbxDouble2DT == lFbxType)
                            {
                                FbxDouble2 lDouble2 = lFbxProp.Get<FbxDouble2>();
                                FbxVector2 lVect;
                                lVect[0] = lDouble2[0];
                                lVect[1] = lDouble2[1];

                                //Display2DVector("                2D vector: ", lVect);
                            }
                            else if ( FbxDouble3DT == lFbxType || FbxColor3DT == lFbxType)
                            {
                                FbxDouble3 lDouble3 = lFbxProp.Get<FbxDouble3>();


                                FbxVector4 lVect;
                                lVect[0] = lDouble3[0];
                                lVect[1] = lDouble3[1];
                                lVect[2] = lDouble3[2];
                                //Display3DVector("                3D vector: ", lVect);
                            }

                            else if ( FbxDouble4DT == lFbxType || FbxColor4DT == lFbxType)
                            {
                                FbxDouble4 lDouble4 = lFbxProp.Get<FbxDouble4>();
                                FbxVector4 lVect;
                                lVect[0] = lDouble4[0];
                                lVect[1] = lDouble4[1];
                                lVect[2] = lDouble4[2];
                                lVect[3] = lDouble4[3];
                                //Display4DVector("                4D vector: ", lVect);
                            }
                            else if ( FbxDouble4x4DT == lFbxType)
                            {
                                FbxDouble4x4 lDouble44 = lFbxProp.Get<FbxDouble4x4>();
                                for(int j=0; j<4; ++j)
                                {

                                    FbxVector4 lVect;
                                    lVect[0] = lDouble44[j][0];
                                    lVect[1] = lDouble44[j][1];
                                    lVect[2] = lDouble44[j][2];
                                    lVect[3] = lDouble44[j][3];
                                    //Display4DVector("                4x4D vector: ", lVect);
                                }

                            }
                        }

                    }   
                }
            }
            else if (lMaterial->GetClassId().Is(FbxSurfacePhong::ClassId))
            {
                // We found a Phong material.  Display its properties.

				// Display the Ambient Color
                lKFbxDouble3 =((FbxSurfacePhong *) lMaterial)->Ambient;
                theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);
				std::vector<float> vecAmbient;
				vecAmbient.push_back(theColor[0]);
				vecAmbient.push_back(theColor[1]);
				vecAmbient.push_back(theColor[2]);

				bwMesh->setMaterialAmbient(vecAmbient);

				std::cout<<"The Ambient color is "<< theColor[0] <<" " << theColor[1]<< " " <<theColor[2]<<std::endl;
                //DisplayColor("            Ambient: ", theColor);

                // Display the Diffuse Color


                lKFbxDouble3 =((FbxSurfacePhong *) lMaterial)->Diffuse;
                theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);

				std::vector<float> vecDiffuse;
				vecDiffuse.push_back(theColor[0]);
				vecDiffuse.push_back(theColor[1]);
				vecDiffuse.push_back(theColor[2]);
				
				bwMesh->setMaterialDiffuse(vecDiffuse);

				std::cout<<"The Diffuse color is "<< theColor[0]<<" "<<theColor[1]<<" "<<theColor[2]<<std::endl;

                // Display the Specular Color (unique to Phong materials)
                lKFbxDouble3 =((FbxSurfacePhong *) lMaterial)->Specular;
                theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);

				std::vector<float> vecSpecular;
				vecSpecular.push_back(theColor[0]);
				vecSpecular.push_back(theColor[1]);
				vecSpecular.push_back(theColor[2]);

				bwMesh->setMaterialSpecular(vecSpecular);

				std::cout<<"The Specular color is " <<theColor[0]<<" "<<theColor[1]<<" "<<theColor[2]<<std::endl;
                

                // Display the Emissive Color
                lKFbxDouble3 =((FbxSurfacePhong *) lMaterial)->Emissive;
                theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);
                std::cout<<"The Emissive color is " <<theColor[0]<< " " <<theColor[1]<<" "<<theColor[2]<<std::endl;

                //Opacity is Transparency factor now
                lKFbxDouble1 =((FbxSurfacePhong *) lMaterial)->TransparencyFactor;
				std::cout<<"Opacity:" << 1.0 - lKFbxDouble1.Get()<<std::endl;

                // Display the Shininess
                lKFbxDouble1 =((FbxSurfacePhong *) lMaterial)->Shininess;
				std::cout<<"Shininess:" << lKFbxDouble1.Get()<<std::endl;

				bwMesh->setMaterialShininess(lKFbxDouble1.Get());

                // Display the Reflectivity
                lKFbxDouble1 =((FbxSurfacePhong *) lMaterial)->ReflectionFactor;
				std::cout<<"Reflectitvity:" <<lKFbxDouble1.Get()<<std::endl;
            }
            else if(lMaterial->GetClassId().Is(FbxSurfaceLambert::ClassId) )
            {
                // We found a Lambert material. Display its properties.
                // Display the Ambient Color
                lKFbxDouble3=((FbxSurfaceLambert *)lMaterial)->Ambient;
                theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);
                //DisplayColor("            Ambient: ", theColor);

                // Display the Diffuse Color
                lKFbxDouble3 =((FbxSurfaceLambert *)lMaterial)->Diffuse;
                theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);
                //DisplayColor("            Diffuse: ", theColor);

                // Display the Emissive
                lKFbxDouble3 =((FbxSurfaceLambert *)lMaterial)->Emissive;
                theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);
                //DisplayColor("            Emissive: ", theColor);

                // Display the Opacity
                lKFbxDouble1 =((FbxSurfaceLambert *)lMaterial)->TransparencyFactor;
                //DisplayDouble("            Opacity: ", 1.0-lKFbxDouble1.Get());
            }
            else
			{
				std::cout<<"Unknown type of Material"<<std::endl;
			}
                //DisplayString("Unknown type of Material");

            FbxPropertyT<FbxString> lString;
            lString = lMaterial->ShadingModel;
            //DisplayString("            Shading Model: ", lString.Get().Buffer());
            //DisplayString("");
        }
    }
}

void DisplayMesh(FbxNode* pNode,BWFbxLoader* fbxloader)
{
    FbxMesh* lMesh = (FbxMesh*) pNode->GetNodeAttribute ();
	std::cout<<"The node mesh name is " << lMesh->GetName()<<std::endl;
	BWFbxMesh* bwMesh = new BWFbxMesh(lMesh->GetName());
	DisplayPolygons(lMesh, bwMesh);
    //DisplayMetaDataConnections(lMesh);
    //DisplayControlsPoints(lMesh);
    
    //DisplayMaterialMapping(lMesh);
    DisplayMaterial(lMesh, bwMesh);
    //DisplayTexture(lMesh);
    //DisplayMaterialConnections(lMesh);
    //DisplayLink(lMesh);
    //DisplayShape(lMesh);
    //    
    //DisplayCache(lMesh);

	fbxloader->mMeshes.push_back(bwMesh);
}

void DisplayLight(FbxNode* pNode)
{
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
            DisplayLight(pNode);
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