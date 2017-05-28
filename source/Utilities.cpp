#include "Utilities.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <shlobj.h>

void cutoutDandR(std::string &str)
{
    std::string d("\\x64\\Debug");
    int f = str.find(d);
    if (f != std::string::npos)
    {
        str.replace(f, d.size(), "");
    }

    std::string r("\\x64\\Release");
    f = str.find(r);
    if (f != std::string::npos)
    {
        str.replace(f, r.size(), "");
    }
}

//void Replace(std::string &str, char oc, char nc)
//{
//    std::string::iterator it = str.begin(), it2 = str.end();
//
//    for (; it != it2; ++it)
//    {
//        if (*it == oc)
//            *it = nc;
//    }
//}

std::string getprogrampath = "";
std::string getpersonalpath = "";

std::string GetProgramPath()
{
    if (getprogrampath != "")
    {
        return getprogrampath;
    }

    char path[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, path);

    //GetModuleFileName(NULL, LPWCH(path), MAX_PATH);
    //PathRemoveFileSpec(path);
    getprogrampath = path;
    cutoutDandR(getprogrampath);
    SetCurrentDirectory(getprogrampath.c_str());
    GetCurrentDirectory(MAX_PATH, path);
    //printf("%s\n", path);
    //printf("%s\n", getprogrampath.c_str());
    //Replace(getprogrampath, '\\', '/');

    return getprogrampath;
}

std::string GetPersonalPath(const std::string &folder)
{
    if (getpersonalpath != "")
        return getpersonalpath;

    char localpath[MAX_PATH] = {0};
    SHGetFolderPath(NULL, SHGFP_TYPE_CURRENT | CSIDL_LOCAL_APPDATA, NULL, 0, LPSTR(localpath));
    getpersonalpath = localpath + folder;
    memset(localpath, 0, MAX_PATH);
    memcpy(localpath, getpersonalpath.c_str(), getpersonalpath.size());
    long error = SHCreateDirectoryEx(NULL, LPSTR(localpath), NULL);
    if (error != ERROR_SUCCESS && error != ERROR_ALREADY_EXISTS)
        std::cout << "Failed: error " << error << std::endl;

    memset(localpath, 0, MAX_PATH);
    memcpy(localpath, (getpersonalpath + "Screen Shots/").c_str(), (getpersonalpath + "Screen Shots/").size());
    error = SHCreateDirectoryEx(NULL, LPSTR(localpath), NULL);
    if (error != ERROR_SUCCESS && error != ERROR_ALREADY_EXISTS)
        std::cout << "Failed: error " << error << std::endl;

    memset(localpath, 0, MAX_PATH);
    memcpy(localpath, (getpersonalpath + "Saves/").c_str(), (getpersonalpath + "Saves/").size());
    error = SHCreateDirectoryEx(NULL, LPSTR(localpath), NULL);
    if (error != ERROR_SUCCESS && error != ERROR_ALREADY_EXISTS)
        std::cout << "Failed: error " << error << std::endl;

    return getpersonalpath;
}