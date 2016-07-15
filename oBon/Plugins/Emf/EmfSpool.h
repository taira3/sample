#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include    <sstream>

//#include    <iostream>
//#include    <sstream>
#include    <iomanip>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

#include	"emfspool_def.h"
#include	"Emf.h"

#pragma warning(disable: 4786) 
#include <vector>

using namespace std;

// [MS-EMFSPOOL] - v20140502

// 2.2.2 Header Record
struct	_Header_Record {
	DWORD	dwVersion ;
	DWORD	cjSize ;
	DWORD	dpszDocName ;
	DWORD	dpszOutput ;
//extraDataDocName (variable)
//extraDataOutputDevice (variable)
} ;

typedef struct _Common_Header {
	DWORD	ulID ;		// = RecordType.
	DWORD	cjSize ;

	_Common_Header() :
		ulID(0),
		cjSize(0)
		{
		}

} Common_header ;

class EmfSpool
{
public:
	EmfSpool(void);
	EmfSpool( TCHAR *filename );	// ファイル指定.
	EmfSpool( char *filename );	// ファイル指定.

	~EmfSpool(void);

public:
	// 妥当性の判断.
	bool	valid();

	// 解析
	bool	parse( bool valid = false );

	// 出力先環境の構築.
//	bool	create_output_env( TCHAR *filename ) ;
	bool	create_output_env( char *filename ) ;

	// 出力ファイル名.
	string	out_doc_name()			{	return _out_folder + "\\" + "result.txt" ; }
	string	out_emf_name()			{	return make_out_name( "\\emf_"		, ".emf", count_emf ) ;			}
	string	out_devmode_name()		{	return make_out_name( "\\devmode_"	, ".bin", count_devmode ) ;		}
	string	out_emf_text_name()		{	return make_out_name( "\\emf_"		, ".txt", count_emf_text ) ;	}
	string	make_out_name( string name, string ext, int &count )
	{
		stringstream	tmp ;
		tmp << _out_folder << name << setfill('0') << setw(5) << right << count << ext ;
		count++;
		return tmp.str() ;
	}
	string	get_outfolder()	{ return _out_folder ; }

private:
//	ifstream	fs;
	fstream	fs;
	ofstream	of;

	string		_out_folder;
	int			count_devmode ;
	int			count_emf;
	int			count_emf_text;

	// コンテキスト.
	class	sym {
	public:
//		sym( ifstream &_f, bool _valid = false ) :
		sym( fstream &_f, bool _valid = false ) :
			f(_f), 
			valid(_valid)
		{
//			f.seekg( ios_base::beg );	// これが無いと、引数で渡す側が事前に先頭へseekしても先頭を指さなかった(なぜ？).
			f.seekp( ios_base::beg );	// これが無いと、引数で渡す側が事前に先頭へseekしても先頭を指さなかった(なぜ？).
			cur = f.tellg();
			init_read();
		}
		~sym() {}

	private:
//		ifstream		&f ;
		fstream		&f ;
		Common_header	ch ;		
		bool			valid ;		// 検証モード.
//		ifstream::pos_type cur ;	// 現在の解析データ位置(ヘッダ先頭).
		fstream::pos_type cur ;	// 現在の解析データ位置(ヘッダ先頭).

	public:
		vector <string>	emfs ;		// 出力したemfファイル名.


	public:
		int		top_adr()						{ return cur ; }
		// ヘッダの取得.
		Common_header	&get_header()			{	return ch;	}

		bool	init_read()
		{
//			f.seekg( cur );
			f.seekp( cur );
			f.read( (char*)&ch, sizeof(ch) );
			return eof();
		}

		// 次レコードへ移動(ヘッダのみ、データの空読みが無駄っぽいが安全の為).
		bool	next()
		{
//			f.seekg( cur );
			f.seekp( cur );
			if( ! is(emfspool::EMRI_HEADER) )
			{
//				f.seekg( (long)sizeof(ch), ios_base::cur );
				f.seekp( (long)sizeof(ch), ios_base::cur );
			}
//			f.seekg( (long)size(), ios_base::cur );
			f.seekp( (long)size(), ios_base::cur );
			cur = f.tellg();
			f.read( (char*)&ch, sizeof(ch) );
			if( eof() )
				OutputDebugString( L"End of file\n");
			return eof();
		}

		// データ終了か問い合わせ.
		bool	eof()							{	return f.eof() || !f.is_open();	}

		// レコードタイプの問い合わせ.
		bool	is( emfspool::RecordType t )	{	return (ch.ulID == t) ;	}

		// 検証時のレコードのスキップ.(解析時はskipしない->読み出して解析処理を行うので).
		bool	skip()
		{
			if( this->valid )
			{
				dispId();		// for debug.
				next();
				return true ;
			}
			return false ;
		}

		// レコード内のデータを返す.
		//   巨大なデータサイズの場合にstringで返して大丈夫なのか不安なところ.
		string get()
		{
			// ...なんかダサい処理.
			char	*p = new char[size()] ;
//			f.seekg( cur );
			f.seekp( cur );
			if( ! is(emfspool::EMRI_HEADER) )
			{
//				f.seekg( (long)sizeof(ch), ios_base::cur );
				f.seekp( (long)sizeof(ch), ios_base::cur );
			}
			f.read( p, size());
			string	ret( p, size() );
			delete p ;
			return ret;
		}

		// データ部のサイズを取得.
		DWORD	size()							{	return  this->ch.cjSize ;	}

		// ---- for debug.
		// 
		void	dispId()
		{
			DWORD	id = ch.ulID ;
			char a[20];
			sprintf_s( a, 20, "id=%0x\n",id);
			OutputDebugStringA(a);
#if 0
			TRACE("%08x:",id);
			switch( id )
			{
			case emfspool::EMRI_METAFILE:			TRACE("EMRI_METAFILE\n");			break;
			case emfspool::EMRI_ENGINE_FONT:		TRACE("EMRI_ENGINE_FONT\n");		break;
			case emfspool::EMRI_DEVMODE:			TRACE("EMRI_DEVMODE\n");			break;
			case emfspool::EMRI_TYPE1_FONT:			TRACE("EMRI_TYPE1_FONT\n");			break;
			case emfspool::EMRI_PRESTARTPAGE:		TRACE("EMRI_PRESTARTPAGE\n");		break;
			case emfspool::EMRI_DESIGNVECTOR:		TRACE("EMRI_DESIGNVECTOR\n");		break;
			case emfspool::EMRI_SUBSET_FONT:		TRACE("EMRI_SUBSET_FONT\n");		break;
			case emfspool::EMRI_DELTA_FONT:			TRACE("EMRI_DELTA_FONT\n");			break;
			case emfspool::EMRI_FORM_METAFILE:		TRACE("EMRI_FORM_METAFILE\n");		break;
			case emfspool::EMRI_BW_METAFILE:		TRACE("EMRI_BW_METAFILE\n");		break;
			case emfspool::EMRI_BW_FORM_METAFILE:	TRACE("EMRI_BW_FORM_METAFILE\n");	break;
			case emfspool::EMRI_METAFILE_DATA:		TRACE("EMRI_METAFILE_DATA\n");		break;
			case emfspool::EMRI_METAFILE_EXT:		TRACE("EMRI_METAFILE_EXT\n");		break;
			case emfspool::EMRI_BW_METAFILE_EXT:	TRACE("EMRI_BW_METAFILE_EXT\n");	break;
			case emfspool::EMRI_ENGINE_FONT_EXT:	TRACE("EMRI_ENGINE_FONT_EXT\n");	break;
			case emfspool::EMRI_TYPE1_FONT_EXT:		TRACE("EMRI_TYPE1_FONT_EXT\n");		break;
			case emfspool::EMRI_DESIGNVECTOR_EXT:	TRACE("EMRI_DESIGNVECTOR_EXT\n");	break;
			case emfspool::EMRI_SUBSET_FONT_EXT:	TRACE("EMRI_SUBSET_FONT_EXT\n");	break;
			case emfspool::EMRI_DELTA_FONT_EXT:		TRACE("EMRI_DELTA_FONT_EXT\n");		break;
			case emfspool::EMRI_PS_JOB_DATA:		TRACE("EMRI_PS_JOB_DATA\n");		break;
			case emfspool::EMRI_EMBED_FONT_EXT:		TRACE("EMRI_EMBED_FONT_EXT\n");		break;
			case emfspool::EMRI_HEADER:				TRACE("EMRI_HEADER\n");				break;
			default:								TRACE("other\n");					break;
			}
#endif
		}
	};

public:

	// 文法チェックと解析.
	bool	parse_emf_spool_format( sym &s );
	bool	parse_other_records( sym &s );
	bool	parse_page_content_records( sym &s );
	bool	parse_page_offset_records( sym &s );
	bool	parse_font_definition_records( sym &s );
	bool	parse_font_offset_records( sym &s );

	// 各レコードの処理.
	bool	proc_header( sym &s );				// EMRI_HEADER
	bool	proc_ps_job_data( sym &s );			// EMRI_PS_JOB_DATA
	bool	proc_devmode( sym &s );				// EMRI_DEVMODE
	bool	proc_prestartpage( sym &s );		// EMRI_PRESTARTPAGE
	bool	proc_metafile( sym &s );			// EMRI_METAFILE
	bool	proc_form_metafile( sym &s );		// EMRI_FORM_METAFILE
	bool	proc_bw_metafile( sym &s );			// EMRI_BW_METAFILE
	bool	proc_bw_form_metafile( sym &s );	// EMRI_BW_FORM_METAFILE
	bool	proc_metafile_data( sym &s );		// EMRI_METAFILE_DATA
	bool	proc_metafile_ext( sym &s );		// EMRI_METAFILE_EXT
	bool	proc_bw_metafile_ext( sym &s );		// EMRI_BW_METAFILE_EXT
	bool	proc_engine_font( sym &s );			// EMRI_ENGINE_FONT
	bool	proc_type1_font( sym &s );			// EMRI_TYPE1_FONT
	bool	proc_designvector( sym &s );		// EMRI_DESIGNVECTOR
	bool	proc_subset_font( sym &s );			// EMRI_SUBSET_FONT
	bool	proc_delta_font( sym &s );			// EMRI_DELTA_FONT
	bool	proc_engine_font_ext( sym &s );		// EMRI_ENGINE_FONT_EXT
	bool	proc_type1_font_ext( sym &s );		// EMRI_TYPE1_FONT_EXT
	bool	proc_designvector_ext( sym &s );	// EMRI_DESIGNVECTOR_EXT
	bool	proc_delta_font_ext( sym &s );		// EMRI_DELTA_FONT_EXT
	bool	proc_embed_font_ext( sym &s );		// EMRI_EMBED_FONT_EXT

};
