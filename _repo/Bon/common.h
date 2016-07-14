/**
 * @file common.h
 * @brief ���ʂŎg�p���鏬���ȃN���X��`.
 * @author Y.Taira
 * @date 2016/5/7
 */

#pragma once

#include <string>

using namespace std;

/*! @class PathString
    @brief  �p�X���̕ҏW�p�N���X.
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
	 * �p�X�\���v�f.
	 */
	enum	PATH_ELM {
		//! �p�X���v�f(�֋X��̐ݒ�l).
		PATH_BEGIN	= 0,
		DRIVE		= PATH_BEGIN,			/**< �h���C�u����. */  
		DIR			= DRIVE + _MAX_DRIVE ,	/**< �f�B���N�g������. */  
		FILE		= DIR   + _MAX_DIR,		/**< �t�@�C������. */  
		EXT			= FILE  + _MAX_FNAME,	/**< �g���q����. */  
		TOTAL		= EXT   + _MAX_EXT		/**< �p�X���̍ő�T�C�Y. */  
	};

private:

	string	get_path_elm( PATH_ELM pos )
	{
		//�p�X���𕪉�
		char	drive[_MAX_DRIVE];	// �h���C�u��
		char	dir[_MAX_DIR];		// �f�B���N�g����
		char	file[_MAX_FNAME];	// �t�@�C����
		char	ext[_MAX_EXT];		// �g���q

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

	// �p�X�̏�������.
	void	rep_path( PATH_ELM	pos, const char *val )
	{
		//�p�X���𕪉�
		char	drive[_MAX_DRIVE];	// �h���C�u��
		char	dir[_MAX_DIR];		// �f�B���N�g����
		char	file[_MAX_FNAME];	// �t�@�C����
		char	ext[_MAX_EXT];		// �g���q

		_splitpath_s(
			(const char*)str.c_str(),
			drive,	_MAX_DRIVE,
			dir,	_MAX_DIR,
			file,	_MAX_FNAME,
			ext,	_MAX_EXT	);

		// �o�͐�t�H���_��.
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
