#include "stdafx.h"
#include "utils.h"
#include <string>
#include <vector>
using namespace std;

//��һ���ַ���string����ĳ���ַ����зָ�
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

//unicode��CStringתstring
string CStr_to_str(CString cstr)
{
	int buffer_len = cstr.GetLength() * 2 + 2;
	char *buffer = new char[buffer_len];
	WideCharToMultiByte(CP_OEMCP, NULL, cstr, -1, buffer, buffer_len, NULL, FALSE);

	string str = buffer;
	delete []buffer;
	return str;
}

//unicode��stringתCString
CString str_to_CStr(string str)
{
	int buffer_len = str.length() + 1;
	wchar_t *buffer = new wchar_t[buffer_len];
	// Convert headers from ASCII to Unicode.��ASCII ת���� Unicode
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buffer, buffer_len);

	CString cstr = buffer;
	delete []buffer;
	return cstr;
}

//��ȡִ�г���ľ���·��
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

//��ȡ��ǰ���е�Ŀ¼�ļ��� 
string ExtractFileName(const string astrFilePathName)
{
	char drive[_MAX_DRIVE];   //drive���������ţ����һ��ð��(:)
	char dir[_MAX_DIR];       //dir��Ŀ¼·��������β����б�ܣ�����ʹ�á�\��,��/�����߶�ʹ�ã��������ҪĿ¼·�������Դ���NULL
	char fname[_MAX_FNAME];   //fname��������չ�����ļ���
	char ext[_MAX_EXT];       //ext���ļ�����չ����������.��
	_splitpath(astrFilePathName.c_str(),drive,dir,fname,ext);   
	return string(fname) + ext;
}

//��ȡ��ǰ���е�Ŀ¼·�� 
string ExtractFilePath(const string astrFilePathName)
{
	char drive[_MAX_DRIVE];   
	char dir[_MAX_DIR];   
	char fname[_MAX_FNAME];   
	char ext[_MAX_EXT];   
	_splitpath(astrFilePathName.c_str(),drive,dir,fname,ext);   
	return string(drive) + dir;
}

//�ж��ļ����ļ����Ƿ����
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

//�ж��Ƿ���ȷ�����ļ���
BOOL CreateDirectory(string astrDir)
{
	HANDLE lhFile;					// File Handle�ļ����
	WIN32_FIND_DATA	fileinfo;		// File Information Structure�ļ���Ϣ�ṹ
	list<string> loDirList;			// CString Array to hold Directory Structures�ַ�������������Ŀ¼�ṹ
	BOOL lbResult;					// BOOL used to test if Create Directory was successful   BOOL�������Դ���Ŀ¼�Ƿ�ɹ�
	string::size_type lsizePos = 0;	// Counter������
	string lstrTemp = "";			// lstrTempporary CString Object  �ַ�������

	lhFile = FindFirstFile(str_to_CStr(astrDir),&fileinfo);

	// if the file exists and it is a directory ����ļ���������һ��Ŀ¼
	if(fileinfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
	{
		//  Directory Exists close file and returnĿ¼���ڹر��ļ�������
		FindClose(lhFile);
		return FALSE;
	}
	loDirList.clear();

	for(lsizePos = 0; lsizePos < astrDir.length(); lsizePos++ )		// Parse the supplied CString Directory String�����ṩĿ¼�ַ���
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

	// Now lets cycle through the String Array and create each directory in turn ͨ���ַ��������ѭ������ÿ��Ŀ¼
	for(list<string>::iterator lsizePos=loDirList.begin();lsizePos != loDirList.end();lsizePos++)//lsizePos = 1; lsizePos < loDirList.size(); lsizePos++)
	{
		lstrTemp = *lsizePos;//loDirList.at(lsizePos);
		lbResult = CreateDirectory(str_to_CStr(lstrTemp),NULL);

		// If the Directory exists it will return a false   ���Ŀ¼����,��������һ������
		if(lbResult)
			SetFileAttributes(str_to_CStr(lstrTemp),FILE_ATTRIBUTE_NORMAL);
		// If we were successful we set the attributes to normal ����ɹ� ����������Ϊ����
	}
	//  Now lets see if the directory was successfully created  �鿴Ŀ¼�Ƿ񴴽��ɹ�
	lhFile = FindFirstFile(str_to_CStr(astrDir),&fileinfo);

	loDirList.clear();
	if(fileinfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
	{
		//  Directory Exists close file and return   �ر��ļ�������
		FindClose(lhFile);
		return TRUE;
	}
	else
	{
		// For Some reason the Function Failed  Return FALSE  ����ĳ��ԭ����ʧ�ܷ���FALSE 
		FindClose(lhFile);
		return FALSE;
	}
}

//����Ŀ¼��FileName �ж��Ƿ���ʵ�����
bool DirectoryExists(string astrDir)
{
	return PathFileExists(str_to_CStr(astrDir));
}