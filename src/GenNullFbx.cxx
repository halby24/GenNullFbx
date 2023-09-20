#include <filesystem>
#include "Common.h"
#include "GenNullFbx.h"

static bool gVerbose = true;

int GenNullFbx(const char* pFilePath)
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
        FBXSDK_printf("\n\nFile name is not provided!\n\n");
        return 1;
	}
	else
	{
		FBXSDK_printf("\n\nSave Path: %s\n\n", lFilePath.Buffer());
        
        char* lPath = NULL;
        FbxAnsiToUTF8(lFilePath.Buffer(), lPath, NULL);
        lFilePath = lPath;
	}

    FbxString lName(std::filesystem::path(lFilePath.Buffer()).stem().string().c_str());
    auto lNode = FbxNode::Create(lSdkManager, lName);
    auto lNull = FbxNull::Create(lSdkManager, lName);
    lNode->SetNodeAttribute(lNull);
    lScene->GetRootNode()->AddChild(lNode);

    lResult = SaveScene(lSdkManager, lScene, lFilePath.Buffer());
    if(lResult == false)
    {
        FBXSDK_printf("\n\nAn error occurred while saving the scene...\n");
        DestroySdkObjects(lSdkManager, lResult);
        return 1;
    }

    // Destroy all objects created by the FBX SDK.
    DestroySdkObjects(lSdkManager, lResult);
    return 0;
}
