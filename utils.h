#include <string>
#include <vector>
#include <list>
using namespace std;

int string_split(const string& str,string sep,vector<string>& ret);
string CStr_to_str(CString cstr);
CString str_to_CStr(string str);

void string_trimmed(string &str);
string GetAppExePathName();
string GetAppExePath();
string ExtractFileName(const string astrFilePathName);
string ExtractFilePath(const string astrFilePathName);

BOOL FileExists( LPCTSTR szFile);
BOOL FileExists(string astrFile);
BOOL CreateDirectory(string astrDir);
bool DirectoryExists(string astrDir);