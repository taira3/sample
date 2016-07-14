/**
 * @file common.h
 * @brief 共通で使用する小さなクラス定義.
 * @author Y.Taira
 * @date 2016/5/7
 */

#pragma once

#include <string>

using namespace std;

/*! @class PathString
    @brief  パス名の編集用クラス.
*/
class PathString {
public:
	PathString():
	  str("")
	  {}

	PathString(const char* val):
	  str(val)
	  {}

	~PathString()	{str.clear();}

	void	add_path( char *v )	{ rep_path(DIR, string(get_path_elm(DIR)+string(v)).c_str() ); }
	void	rep_ext( char *v )	{ rep_path(EXT, v); }
	void	rep_fnam( char *v )	{ rep_path(FILE,v); }

	const char *c_str()	{ return str.c_str(); }	

private:
	string	str;

	/**
	 * @enum PATH_ELM
	 * パス構成要素.
	 */
	enum	PATH_ELM {
		//! パス名要素(便宜上の設定値).
		PATH_BEGIN	= 0,
		DRIVE		= PATH_BEGIN,			/**< ドライブ名称. */  
		DIR			= DRIVE + _MAX_DRIVE ,	/**< ディレクトリ名称. */  
		FILE		= DIR   + _MAX_DIR,		/**< ファイル名称. */  
		EXT			= FILE  + _MAX_FNAME,	/**< 拡張子名称. */  
		TOTAL		= EXT   + _MAX_EXT		/**< パス名の最大サイズ. */  
	};

private:

	string	get_path_elm( PATH_ELM pos )
	{
		//パス名を分解
		char	drive[_MAX_DRIVE];	// ドライブ名
		char	dir[_MAX_DIR];		// ディレクトリ名
		char	file[_MAX_FNAME];	// ファイル名
		char	ext[_MAX_EXT];		// 拡張子

		_splitpath_s(
			(const char*)str.c_str(),
			drive,	_MAX_DRIVE,
			dir,	_MAX_DIR,
			file,	_MAX_FNAME,
			ext,	_MAX_EXT	);

		string	res;
		switch( (int)pos )
		{
		case DRIVE:
			res = string(drive);
			break;
		case DIR:
			res = string(dir);
			break;
		case FILE:
			res = string(file);
			break;
		case EXT:
			res = string(ext);
			break;
		}
		return res ;
	}

	// パスの書き換え.
	void	rep_path( PATH_ELM	pos, const char *val )
	{
		//パス名を分解
		char	drive[_MAX_DRIVE];	// ドライブ名
		char	dir[_MAX_DIR];		// ディレクトリ名
		char	file[_MAX_FNAME];	// ファイル名
		char	ext[_MAX_EXT];		// 拡張子

		_splitpath_s(
			(const char*)str.c_str(),
			drive,	_MAX_DRIVE,
			dir,	_MAX_DIR,
			file,	_MAX_FNAME,
			ext,	_MAX_EXT	);

		// 出力先フォルダ名.
		char	out_folder[_MAX_PATH];
		_makepath_s(
			out_folder,	_MAX_PATH,
			(pos==DRIVE) ? val : drive,
			(pos==DIR)   ? val : dir,
			(pos==FILE)  ? val : file,
			(pos==EXT)   ? val : ext    );

		this->str.clear();
		this->str = string(out_folder);
	};
};
