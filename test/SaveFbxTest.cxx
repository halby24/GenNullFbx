#include <windows.h>
#include <iostream>
#include "../src/GenNullFbx.h"

int main()
{
    int result = GenNullFbx("test.fbx");
    
    return result;
}