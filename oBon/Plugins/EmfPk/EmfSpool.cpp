#include "StdAfx.h"
#include "EmfSpool.h"

EmfSpool::EmfSpool(void)
{
}

EmfSpool::EmfSpool( TCHAR *filename )
{
	count_devmode = 0 ;
	count_emf = 0 ;
	count_emf_text = 0 ;
	fs.open( filename, ios_base::binary );
}
EmfSpool::EmfSpool( char *filename )
{
	count_devmode = 0 ;
	count_emf = 0 ;
	count_emf_text = 0 ;
	fs.open( filename, ios::in | ios::binary );
}
EmfSpool::~EmfSpool(void)
{
}

// EMFSpoolとして妥当なファイルか判断する.
bool	EmfSpool::valid()
{
	return parse( true );
}

// 解析処理.
bool	EmfSpool::parse(
			bool valid			// 検証モード(ON=妥当性検証を行い、解析は行わない,OFF(default)=解析を行う)
		)
{
	cout << "EmfSpool::parse()" << endl ;

	bool	result = false ;
	if( fs.is_open() )
	{
		// ファイルの先頭から解析を行う.
//		fs.seekg( ios_base::beg );
		fs.seekp( ios_base::beg );

		// 解析開始.
		sym	sym(fs,valid);
		result = parse_emf_spool_format(sym) ;

		// 解析可で解析モードの場合に、EMFファイルの解析も行う.
		if( result && !valid )
		{
			// <EMRI_METAFILE_DATA>で保存したEMFファイル名で順次解析.
			for( vector<string>::iterator it = sym.emfs.begin() ; it != sym.emfs.end() ; ++it )
			{
				// EMFファイルの解析.
				Emf	*e = new Emf( *it );
				e->parse();
				delete e ;
			}
		}
	}
	return result ;
}

#include	<wchar.h>
#include <direct.h>
#include <ERRNO.H >



#include	"../../bon/common.h"

// 解析結果出力先環境の作成.
bool	EmfSpool::create_output_env( char *filename )
{
	// 出力先フォルダ名=出力先ファイル名
	PathString	ps(filename);
	ps.rep_ext(NULL);

	struct _stat buf;
//	if( _wstat( out_folder, &buf ) != 0 )
	if( _stat( ps.c_str(), &buf ) != 0 )
	{
		// なければ作る.
		//   なるべく環境異存しないよう作りたいが
		//   突然errnoなど出てくるCの仕組みは、やはり好きではない.
		//   といいつつ、TCHARが出てきた時点で環境依存してる…
		if( errno == ENOENT )
		{
//			_wmkdir( out_folder );
//			wstring	folder( out_folder );
//			this->_out_folder = string( folder.begin(), folder.end() );

			_mkdir( ps.c_str() );
			this->_out_folder = string(ps.c_str());

			this->of.open( out_doc_name().c_str() );
		}
	}
	else
	{
		// あったら出力先として採用.
//		wstring	folder( out_folder );
//		this->_out_folder = string( folder.begin(), folder.end() );
		this->_out_folder = string(ps.c_str());

		this->of.open( out_doc_name().c_str() );
	}

	return true ;
}

/*
	Output Format
	1.EMFSpool format text
	2.  DEVMODE(bin)
	3.  EMF(bin)
	4.  EMF(text/resource)

	create folder.
	./[filename]
	  filename.txt		... 全体の構成
	  devmode_%d.bin	... DEVMODE
	  emf_%d.emf		... EMFファイル
	  emf_%.txt			... EMFファイル解析結果
	  emf_%/
	     resource

    text format:
	  ID:
	    var.
      
*/

// ---------------------------------------------------------------------------
//  The Record Syntax is specified as follows.
// ---------------------------------------------------------------------------

/*
   『[MS-EMFSPOOL].pdf』の表記が、少々理解できない。
     複数ページある時に

		<Header_record>
		<other_records>
			<EMRI_METAFILE_DATA>
			<EMRI_DEVMODE>
		<page_offset_records>	<- *1 (ここで終わりでは？)
			<EMRI_BW_METAFILE_EXT>
		<other_records>			<- ?  (次ページの構成)
			<EMRI_METAFILE_DATA>
			:
	のような構成となっている。
	BNF記法では、上記の*1<page_offset_records>が終端と理解しているが
	実際には続く上に、仕様書の3.Exsampleでも上記の構成で解説されている。

	なので、勝手に下記の解釈として実装している

	オリジナルの仕様
	<emf_spool_format> ::=
		<Header_record>
		[ <EMRI_PS_JOB_DATA_record> ]
		{ <other_records> }
		<page_offset_records>

	実装している内容
	<emf_spool_format> ::=
		<Header_record>
		[ <EMRI_PS_JOB_DATA_record> ]
		{ <other_records> 
		  <page_offset_records> }  <- '}'の位置を変更.

*/
bool	EmfSpool::parse_emf_spool_format( sym &s )
{
//	TRACE("start\n");

	// <Header_record>
	if( s.is(emfspool::EMRI_HEADER) )
	{
		proc_header( s );				// EMRI_HEADER
	}
	else
	{
		return false ;
	}

	// [ <EMRI_PS_JOB_DATA_record> ]
	if( s.is(emfspool::EMRI_PS_JOB_DATA) )
	{ 
		proc_ps_job_data( s );			// EMRI_PS_JOB_DATA
	}

#if 0	// オリジナル仕様.
	// { <other_records> }	
	while( parse_other_records(s) )
	{
		;
	}

	// <page_offset_records>
	if( ! parse_page_offset_records(s) )
	{
		return false ;
	}
#else
	while( !s.eof() )
	{
		// todo
		// なぜか、type=00のケースが発生.



		// { <other_records>	
		if( ! parse_other_records(s) )
		{
			// <page_offset_records> }
			if( ! parse_page_offset_records(s) )
			{
				//return false ;
				// Citrix UPD(XenDesktop)の出力したEMFEpoolでは、<page_offset_records>なしだった.
				//return true ;
			}
		}
	}
#endif

//	TRACE("success!!\n");

	return true ;
}

/*
	2.2.3 Data Records
	<other_records> ::=
		<page_content_records> |
		<font_definition_records> |
		<font_offset_records> |
		<EMRI_DEVMODE_record> |
		<EMRI_PRESTARTPAGE_record>
*/
bool	EmfSpool::parse_other_records( sym &s )
{
	if( parse_page_content_records(s) )
	{
		;
	}
	else if( parse_page_content_records(s) )
	{ 
		;
	}
	else if( parse_font_offset_records(s) )
	{ 
		;
	}
	else if(s.is(emfspool::EMRI_DEVMODE) )
	{ 
		proc_devmode( s );				// EMRI_DEVMODE
	}
	else if(s.is(emfspool::EMRI_PRESTARTPAGE) )
	{ 
		proc_prestartpage( s );			// EMRI_PRESTARTPAGE
	}
	else
	{
		return false ;
	}
	return true ;
}

/*
	2.2.3.1 Page Content Records
	<page_content_records> ::=
		<EMRI_METAFILE_record> |
		<EMRI_FORM_METAFILE_record> |
		<EMRI_BW_METAFILE_record> |
		<EMRI_BW_FORM_METAFILE_record> |
		<EMRI_METAFILE_DATA_record>

EMRI_METAFILE			<4> This record is not written to metafiles by the following implementations:
								Windows 2000
								Windows XP
								Windows Server 2003
								Windows Vista
								Windows Server 2008
								Windows 7
								Windows Server 2008 R2
								Windows 8
								Windows Server 2012
								Windows 8.1
								Windows Server 2012 R2
EMRI_FORM_METAFILE		<5> This record is not written to metafiles by Windows implementations.
EMRI_BW_METAFILE		<6> This record is not written to metafiles by Windows implementations.
EMRI_BW_FORM_METAFILE	<7> This record is not written to metafiles by Windows implementations.
*/
bool	EmfSpool::parse_page_content_records( sym &s )
{
	if( s.is( emfspool::EMRI_METAFILE ) )
	{
		proc_metafile( s );				// EMRI_METAFILE
	}
	else if( s.is( emfspool::EMRI_FORM_METAFILE ) )
	{
		proc_form_metafile( s );		// EMRI_FORM_METAFILE
	}
	else if( s.is( emfspool::EMRI_BW_METAFILE ) )
	{
		proc_bw_metafile( s );			// EMRI_BW_METAFILE
	}
	else if( s.is( emfspool::EMRI_BW_FORM_METAFILE ) )
	{
		proc_bw_form_metafile( s );		// EMRI_BW_FORM_METAFILE
	}
	else if( s.is( emfspool::EMRI_METAFILE_DATA ) )
	{
		proc_metafile_data( s );		// EMRI_METAFILE_DATA
	}
	else
	{
		return false ;
	}
	return true ;
}

/*
	2.2.3.2 Page Offset Records
	<page_offset_records> ::=
		<EMRI_METAFILE_EXT_record> |
		<EMRI_BW_METAFILE_EXT_record>
*/
bool	EmfSpool::parse_page_offset_records( sym &s )
{
	if( s.is( emfspool::EMRI_METAFILE_EXT ) )
	{
		proc_metafile_ext( s );			// EMRI_METAFILE_EXT
	}
	else if( s.is( emfspool::EMRI_BW_METAFILE_EXT ) )
	{
		proc_bw_metafile_ext( s );		// EMRI_BW_METAFILE_EXT
	}
	else
	{
		return false ;
	}
	return true ;
}

/*
	2.2.3.3 Font Definition Records
	<font_definition_records> ::=
		<EMRI_ENGINE_FONT_record> |
		<EMRI_TYPE1_FONT_record> |
		<EMRI_DESIGNVECTOR_record> |
		<EMRI_SUBSET_FONT_record> |
		<EMRI_DELTA_FONT_record>

2.2.3.3.2 EMRI_TYPE1_FONT Record <8>
2.2.3.3.3 EMRI_DESIGNVECTOR Record <9>
*/
bool	EmfSpool::parse_font_definition_records( sym &s )
{
	if( s.is( emfspool::EMRI_ENGINE_FONT ) )
	{
		proc_engine_font( s );			// EMRI_ENGINE_FONT
	}
	else if( s.is( emfspool::EMRI_TYPE1_FONT ) )
	{
		proc_type1_font( s );			// EMRI_TYPE1_FONT
	}
	else if( s.is( emfspool::EMRI_DESIGNVECTOR ) )
	{
		proc_designvector( s );			// EMRI_DESIGNVECTOR
	}
	else if( s.is( emfspool::EMRI_SUBSET_FONT ) )
	{
		proc_subset_font( s );			// EMRI_SUBSET_FONT
	}
	else if( s.is( emfspool::EMRI_DELTA_FONT ) )
	{
		proc_delta_font( s );			// EMRI_DELTA_FONT
	}
	else
	{
		return false ;
	}
	return true ;
}

/*
	2.2.3.3.1 EMRI_ENGINE_FONT Record
	<font_offset_records> ::=
		<EMRI_ENGINE_FONT_EXT_record> |
		<EMRI_TYPE1_FONT_EXT_record> |
		<EMRI_DESIGNVECTOR_EXT_record> |
		<EMRI_SUBSET_FONT_OFFSET_record> |  <- <EMRI_SUBSET_FONT_EXT>の間違い?
		<EMRI_DELTA_FONT_EXT_record> |
		<EMRI_EMBED_FONT_EXT_record>
*/
bool	EmfSpool::parse_font_offset_records( sym &s )
{
	if( s.is( emfspool::EMRI_ENGINE_FONT_EXT ) )
	{
		proc_engine_font_ext( s );		// EMRI_ENGINE_FONT_EXT
	}
	else if( s.is( emfspool::EMRI_TYPE1_FONT_EXT ) )
	{
		proc_type1_font_ext( s );		// EMRI_TYPE1_FONT_EXT
	}
	else if( s.is( emfspool::EMRI_DESIGNVECTOR_EXT ) )
	{
		proc_designvector_ext( s );		// EMRI_DESIGNVECTOR_EXT
	}
//	else if( s.is( emfspool::EMRI_SUBSET_FONT_OFFSET ) )
//	{
//	}
	else if( s.is( emfspool::EMRI_DELTA_FONT_EXT ) )
	{
		proc_delta_font_ext( s );		// EMRI_DELTA_FONT_EXT
	}
	else if( s.is( emfspool::EMRI_EMBED_FONT_EXT ) )
	{
		proc_embed_font_ext( s );		// EMRI_EMBED_FONT_EXT
	}
//
	else if( s.is( emfspool::EMRI_SUBSET_FONT_EXT ) )
	{
		// Citrix UPD で出力していた
		proc_embed_font_ext( s );		// 仮の処理. 
	}
//
	else
	{
		return false ;
	}
	return true ;
}

// ---------------------------------------------------------------------------
// EMFSPOOL Records analyze.
// ---------------------------------------------------------------------------

// EMRI_HEADER
bool	EmfSpool::proc_header( sym &s )
{
	if( !s.skip() )
	{
		// EMRI_HEADER だけ、sizeがレコード全体なので処理が他と異なる.
		stringstream	data( s.get(),std::ios::in|std::ios::binary );

		_Header_Record	hr;
		data.read( (char*)&hr , sizeof(_Header_Record));

		// EMFファイルの判断(暫定)
		//   仕様では、この値は固定.
		if( hr.dwVersion != 0x00010000 )
		{
//			TRACE("This is not EMF!\n");
			return false ;
		}

		of << "EMRI_HEADER\n" ;
		of << "\taddr   : " << setbase(16) << setfill('0') << setw(8) << s.top_adr() << endl;
		of << "\tsize   : " << setbase(16) << setfill('0') << setw(8) << s.size() << endl;

		// ドキュメント名.
		if( hr.dpszDocName )
		{
			long	term_doc = hr.dpszOutput ? hr.dpszOutput : s.size();
			long	size_doc = term_doc - hr.dpszDocName;

			wstring	name( term_doc+1, NULL );
			data.seekg( (long)hr.dpszDocName, ios_base::beg );
			data.read( (char*)name.c_str(), term_doc );

///			of << "\tdocument : " << CW2A(name.c_str()) << endl;
		}

		// 出力先デバイス.
		if( hr.dpszOutput )
		{
			long	size_output = s.size() - hr.dpszOutput ;

			wstring	name( size_output+1, NULL );
			data.seekg( (long)hr.dpszOutput, ios_base::beg );
			data.read( (char*)name.c_str(), size_output );

///			of << "\toutput   : " << CW2A(name.c_str()) << endl;
		}
		of << endl;

		s.next();
	}

	return true ;
}

// EMRI_PS_JOB_DATA
bool	EmfSpool::proc_ps_job_data( sym &s )
{
	if( !s.skip() )
	{

		s.next();
	}
	return true ;
}

// 2.2.3.5 EMRI_DEVMODE Record
bool	EmfSpool::proc_devmode( sym &s )
{
	if( !s.skip() )
	{
		// とりあえず、DEVMODEを切り出してファイル出力.
		string	fname = out_devmode_name().c_str() ;
		ofstream	o( fname.c_str(), ios::binary );
		o << s.get() ;
		o.close();

		of << "EMRI_DEVMODE\n" ;
		of << "\taddr   : " << setbase(16) << setfill('0') << setw(8) << s.top_adr() << endl;
		of << "\tsize   : " << setbase(16) << setfill('0') << setw(8) << s.size() << endl;
		of << "\tfile   : " << fname << endl ;
		of << endl;

		s.next();
	}
	return true ;
}

// EMRI_PRESTARTPAGE
bool	EmfSpool::proc_prestartpage( sym &s )
{
	if( !s.skip() )
	{

		s.next();
	}
	return true ;
}

// EMRI_METAFILE
bool	EmfSpool::proc_metafile( sym &s )
{
	if( !s.skip() )
	{
		// This record is not written to metafiles by the following implementations:
		//		Windows 2000
		//		Windows XP
		//		Windows Server 2003
		//		Windows Vista
		//		Windows Server 2008
		//		Windows 7
		//		Windows Server 2008 R2
		//		Windows 8
		//		Windows Server 2012
		//		Windows 8.1
		//		Windows Server 2012 R2
		s.next();
	}
	return true ;
}

// EMRI_FORM_METAFILE
bool	EmfSpool::proc_form_metafile( sym &s )
{
	if( !s.skip() )
	{
		// EMRI_FORM_METAFILE	<5> This record is not written to metafiles by Windows implementations.
		s.next();
	}
	return true ;
}

// EMRI_BW_METAFILE
bool	EmfSpool::proc_bw_metafile( sym &s )
{
	if( !s.skip() )
	{
		// EMRI_BW_METAFILE	<6> This record is not written to metafiles by Windows implementations.
		s.next();
	}
	return true ;
}

// EMRI_BW_FORM_METAFILE
bool	EmfSpool::proc_bw_form_metafile( sym &s )
{
	if( !s.skip() )
	{
		// EMRI_BW_FORM_METAFILE <7> This record is not written to metafiles by Windows implementations.
		s.next();
	}
	return true ;
}

// 2.2.3.1 Page Content Records
// EMRI_METAFILE_DATA
bool	EmfSpool::proc_metafile_data( sym &s )
{
	if( !s.skip() )
	{
		// EMFを切り出してファイル出力.
		//   TODO:巨大なファイルの場合、ちょっと遅いので要改善.
		string	fname = out_emf_name().c_str() ;
		ofstream	o( fname.c_str(), ios::binary );
		o << s.get() ;
		o.close();

		of << "EMRI_METAFILE_DATA\n" ;
		of << "\taddr   : " << setbase(16) << setfill('0') << setw(8) << s.top_adr() << endl;
		of << "\tsize   : " << setbase(16) << setfill('0') << setw(8) << s.size() << endl;
		of << "\tfile   : " << fname << endl ;
		of << endl;

		// EMFファイル名の保存.
		s.emfs.push_back( fname );

		// EMFファイルの解析.
//		Emf	*e = new Emf(s.get(),fname);
//		e->parse();
//		delete e ;

		s.next();
	}
	return true ;
}
		
// EMRI_METAFILE_EXT
bool	EmfSpool::proc_metafile_ext( sym &s )
{
	if( !s.skip() )
	{
		of << "EMRI_METAFILE_EXT\n" ;
		of << "\taddr   : " << setbase(16) << setfill('0') << setw(8) << s.top_adr() << endl;
		of << "\tsize   : " << setbase(16) << setfill('0') << setw(8) << s.size() << endl;

		stringstream	data( s.get() );

		DWORD	offset_hi;
		DWORD	offset_lo;

		data.read( (char*)&offset_lo, sizeof(DWORD));
		data.read( (char*)&offset_hi, sizeof(DWORD));

		of << "\toffset : " << setbase(16) << setfill('0')
							<< setw(8) << offset_hi 
							<< setw(8) << offset_lo << endl ;
		of << endl;

		s.next();
	}
	return true ;
}

// EMRI_BW_METAFILE_EXT
bool	EmfSpool::proc_bw_metafile_ext( sym &s )
{
	if( !s.skip() )
	{
		of << "EMRI_BW_METAFILE_EXT\n" ;
		of << "\taddr   : " << setbase(16) << setfill('0') << setw(8) << s.top_adr() << endl;
		of << "\tsize   : " << setbase(16) << setfill('0') << setw(8) << s.size() << endl;

		stringstream	data( s.get() );

		DWORD	offset_hi;
		DWORD	offset_lo;

		data.read( (char*)&offset_lo, sizeof(DWORD));
		data.read( (char*)&offset_hi, sizeof(DWORD));

		of << "\toffset : " << setbase(16) << setfill('0')
							<< setw(8) << offset_hi 
							<< setw(8) << offset_lo << endl ;
		of << endl;

		s.next();
	}
	return true ;
}
		
// EMRI_ENGINE_FONT
bool	EmfSpool::proc_engine_font( sym &s )
{
	if( !s.skip() )
	{
		of << "EMRI_ENGINE_FONT\n" ;

		s.next();
	}
	return true ;
}
		
// EMRI_TYPE1_FONT
bool	EmfSpool::proc_type1_font( sym &s )
{
	if( !s.skip() )
	{
		// Windows NT 4.0: This is set to a nonzero value.
		s.next();
	}
	return true ;
}
		
// EMRI_DESIGNVECTOR
bool	EmfSpool::proc_designvector( sym &s )
{
	if( !s.skip() )
	{
		// This record is written to metafiles by Windows 2000 implementations only.
		s.next();
	}
	return true ;
}
		
// EMRI_SUBSET_FONT
bool	EmfSpool::proc_subset_font( sym &s )
{
	if( !s.skip() )
	{
		of << "EMRI_SUBSET_FONT\n" ;

		s.next();
	}
	return true ;
}
		
// EMRI_DELTA_FONT
bool	EmfSpool::proc_delta_font( sym &s )
{
	if( !s.skip() )
	{
		of << "EMRI_DELTA_FONT\n" ;

		s.next();
	}
	return true ;
}
		
// EMRI_ENGINE_FONT_EXT
bool	EmfSpool::proc_engine_font_ext( sym &s )
{
	if( !s.skip() )
	{
		of << "EMRI_ENGINE_FONT_EXT\n" ;

		s.next();
	}
	return true ;
}
		
// EMRI_TYPE1_FONT_EXT
bool	EmfSpool::proc_type1_font_ext( sym &s )
{
	if( !s.skip() )
	{
		of << "EMRI_TYPE1_FONT_EXT\n" ;

		s.next();
	}
	return true ;
}
		
// EMRI_DESIGNVECTOR_EXT
bool	EmfSpool::proc_designvector_ext( sym &s )
{
	if( !s.skip() )
	{
		of << "EMRI_DESIGNVECTOR_EXT\n" ;

		s.next();
	}
	return true ;
}
	
// EMRI_DELTA_FONT_EXT
bool	EmfSpool::proc_delta_font_ext( sym &s )
{
	if( !s.skip() )
	{
		of << "EMRI_DELTA_FONT_EXT\n" ;

		s.next();
	}
	return true ;
}
		
// EMRI_EMBED_FONT_EXT
bool	EmfSpool::proc_embed_font_ext( sym &s )
{
	if( !s.skip() )
	{
		of << "EMRI_EMBED_FONT_EXT\n" ;

		s.next();
	}
	return true ;
}
