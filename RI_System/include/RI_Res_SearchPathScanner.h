//==================================================================
/// RI_Res_SearchPathScanner.h
///
/// Created by Davide Pasca - 2010/1/19
/// See the file "license.txt" that comes with this project for
/// copyright info. 
//==================================================================

#ifndef RI_RES_SEARCHPATHSCANNER_H
#define RI_RES_SEARCHPATHSCANNER_H

//==================================================================
namespace RI
{

//==================================================================
class SearchPathScanner
{
	size_t				mIdx;
	const char			*mpBaseDir;
	const char			*mpAppResDir;
	const DVec<DStr>	*mpSearchPaths;

public:
	SearchPathScanner(
				const char *pBaseDir,
				const char *pAppResDir,
				const DVec<DStr> &searchPaths );

	bool GetNext( std::string &out_path, bool &out_pathIsAbsolute );

private:
	bool getNextNoSPathList( std::string &out_path, bool &out_pathIsAbsolute );
	bool getNextWithSPathList( std::string &out_path, bool &out_pathIsAbsolute );
};


//==================================================================
}

#endif
