#include <filesystem>
#include "Common.h"
#include "GenNullFbx.h"

static bool gVerbose = true;

int GenNullFbx(char* pFilePath)
{
    FbxManager* lSdkManager = NULL;
    FbxScene* lScene = NULL;
    bool lResult;

    // Prepare the FBX SDK.
    InitializeSdkObjects(lSdkManager, lScene);

    // The example can take a FBX file as an argument.
	FbxString lFilePath(pFilePath);

	if( lFilePath.IsEmpty() )
	{
        lResult = false;
        FBXSDK_printf("\n\nUsage: ImportScene <FBX file name>\n\n");
	}
	else
	{
		FBXSDK_printf("\n\nSave Path: %s\n\n", lFilePath.Buffer());
        
        char* lPath = NULL;
        FbxAnsiToUTF8(lFilePath.Buffer(), lPath, NULL);
        lFilePath = lPath;
	}

    auto lName = std::filesystem::path(lFilePath.Buffer()).stem().string().c_str();
    auto lNode = FbxNode::Create(lSdkManager, lName);
    lNode->SetNodeAttribute(FbxNull::Create(lSdkManager, lName));
    lScene->GetRootNode()->AddChild(lNode);

    lResult = SaveScene(lSdkManager, lScene, lFilePath.Buffer());
    if(lResult == false)
    {
        FBXSDK_printf("\n\nAn error occurred while saving the scene...\n");
        DestroySdkObjects(lSdkManager, lResult);
        return 0;
    }

    // Destroy all objects created by the FBX SDK.
    DestroySdkObjects(lSdkManager, lResult);

    return 0;
}
