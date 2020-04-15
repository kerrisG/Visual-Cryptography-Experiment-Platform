#include "stdafx.h"
#include "utils.h"
#include <string>
#include <vector>
using namespace std;

//对一个字符串string根据某个字符进行分割
int string_split(const string& str,string sep,vector<string>& ret) 
{
    if (str.empty())
    {
        return 0;
    }

    string tmp;
    string::size_type pos_begin = str.find_first_not_of(sep);
    string::size_type comma_pos = 0;

    while (pos_begin != string::npos)
    {
        comma_pos = str.find(sep, pos_begin);
        if (comma_pos != string::npos)
        {
            tmp = str.substr(pos_begin, comma_pos - pos_begin);
            pos_begin = comma_pos + sep.length();
        }
        else
        {
            tmp = str.substr(pos_begin);
            pos_begin = comma_pos;
        }

        if (!tmp.empty())
        {
            ret.push_back(tmp);
            tmp.clear();
        }
    }
    return 0;
}

void string_trimmed(string &str)
{
	int s = 0,e = str.length();
	int str_len = str.length();
	for(int i = 0; i < str_len; i++)
	{
		if(str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')  
			s = i+1;
		else
			break;
	}

	if(s == str_len)
	{
		str = "";
	}
	else
	{
		for(int i = str_len - 1; i >= s; i--)
		{
			if(str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')  
				e = i-1;
			else
				break;
		}	
		str = str.substr(s,e - s + 1);
	}	
}	

//unicode下CString转string
string CStr_to_str(CString cstr)
{
	int buffer_len = cstr.GetLength() * 2 + 2;
	char *buffer = new char[buffer_len];
	WideCharToMultiByte(CP_OEMCP, NULL, cstr, -1, buffer, buffer_len, NULL, FALSE);

	string str = buffer;
	delete []buffer;
	return str;
}

//unicode下string转CString
CString str_to_CStr(string str)
{
	int buffer_len = str.length() + 1;
	wchar_t *buffer = new wchar_t[buffer_len];
	// Convert headers from ASCII to Unicode.从ASCII 转换成 Unicode
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buffer, buffer_len);

	CString cstr = buffer;
	delete []buffer;
	return cstr;
}

//获取执行程序的绝对路径
string GetAppExePathName()
{
	TCHAR lszPath[MAX_PATH] = _T("");
	GetModuleFileName(NULL, lszPath, MAX_PATH);
	return CStr_to_str(lszPath);
}

string GetAppExePath()
{
	string lstrPathName = GetAppExePathName();
	string::size_type liPos = lstrPathName.rfind("\\");
	if(liPos != -1)
	{
		return lstrPathName.substr(0,liPos);
	}

	else
	{
		return lstrPathName;
	}
}

//获取当前运行的目录文件名 
string ExtractFileName(const string astrFilePathName)
{
	char drive[_MAX_DRIVE];   //drive：驱动器号，后跟一个冒号(:)
	char dir[_MAX_DIR];       //dir：目录路径，包括尾部的斜杠，可以使用“\”,“/”或者都使用，如果不需要目录路径，可以传递NULL
	char fname[_MAX_FNAME];   //fname：不带扩展名的文件名
	char ext[_MAX_EXT];       //ext：文件的扩展名，包括“.”
	_splitpath(astrFilePathName.c_str(),drive,dir,fname,ext);   
	return string(fname) + ext;
}

//获取当前运行的目录路径 
string ExtractFilePath(const string astrFilePathName)
{
	char drive[_MAX_DRIVE];   
	char dir[_MAX_DIR];   
	char fname[_MAX_FNAME];   
	char ext[_MAX_EXT];   
	_splitpath(astrFilePathName.c_str(),drive,dir,fname,ext);   
	return string(drive) + dir;
}

//判断文件或文件夹是否存在
BOOL FileExists( LPCTSTR szFile)
{
	OFSTRUCT of;   
	if (OpenFile(CStr_to_str(szFile).c_str(), &of, OF_EXIST) == HFILE_ERROR)
	{
		int liError = GetLastError();
		return   FALSE;
	}
	else
	{
		return   TRUE;
	}
}

BOOL FileExists(string astrFile)
{
	return FileExists(astrFile.c_str());
}

//判断是否正确创建文件夹
BOOL CreateDirectory(string astrDir)
{
	HANDLE lhFile;					// File Handle文件句柄
	WIN32_FIND_DATA	fileinfo;		// File Information Structure文件信息结构
	list<string> loDirList;			// CString Array to hold Directory Structures字符串数组来保存目录结构
	BOOL lbResult;					// BOOL used to test if Create Directory was successful   BOOL用来测试创建目录是否成功
	string::size_type lsizePos = 0;	// Counter计数器
	string lstrTemp = "";			// lstrTempporary CString Object  字符串对象

	lhFile = FindFirstFile(str_to_CStr(astrDir),&fileinfo);

	// if the file exists and it is a directory 如果文件存在且是一个目录
	if(fileinfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
	{
		//  Directory Exists close file and return目录存在关闭文件并返回
		FindClose(lhFile);
		return FALSE;
	}
	loDirList.clear();

	for(lsizePos = 0; lsizePos < astrDir.length(); lsizePos++ )		// Parse the supplied CString Directory String解析提供目录字符串
	{									
		if(astrDir.at(lsizePos) != '\\')		// if the Charachter is not a \ 
		{
			lstrTemp += astrDir.at(lsizePos);	// aastrDir the character to the lstrTempp String
		}
		else
		{
			loDirList.push_back(lstrTemp);		// if the Character is a \ 
			lstrTemp += "\\";					// Now aastrDir the \ to the lstrTempp string
		}
		if(lsizePos == astrDir.length()-1)		// If we reached the end of the String
			loDirList.push_back(lstrTemp);
	}

	// Close the file
	FindClose(lhFile);

	// Now lets cycle through the String Array and create each directory in turn 通过字符串数组和循环创建每个目录
	for(list<string>::iterator lsizePos=loDirList.begin();lsizePos != loDirList.end();lsizePos++)//lsizePos = 1; lsizePos < loDirList.size(); lsizePos++)
	{
		lstrTemp = *lsizePos;//loDirList.at(lsizePos);
		lbResult = CreateDirectory(str_to_CStr(lstrTemp),NULL);

		// If the Directory exists it will return a false   如果目录存在,它将返回一个错误
		if(lbResult)
			SetFileAttributes(str_to_CStr(lstrTemp),FILE_ATTRIBUTE_NORMAL);
		// If we were successful we set the attributes to normal 如果成功 将属性设置为正常
	}
	//  Now lets see if the directory was successfully created  查看目录是否创建成功
	lhFile = FindFirstFile(str_to_CStr(astrDir),&fileinfo);

	loDirList.clear();
	if(fileinfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
	{
		//  Directory Exists close file and return   关闭文件并返回
		FindClose(lhFile);
		return TRUE;
	}
	else
	{
		// For Some reason the Function Failed  Return FALSE  由于某种原因函数失败返回FALSE 
		FindClose(lhFile);
		return FALSE;
	}
}

//返回目录名FileName 判断是否有实体存在
bool DirectoryExists(string astrDir)
{
	return PathFileExists(str_to_CStr(astrDir));
}