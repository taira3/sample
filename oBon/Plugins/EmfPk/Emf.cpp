#include "StdAfx.h"

//#include <afx.h>	// コンパイルする為に、一時的に
//#include	<atlconv.h>


#include	<windef.h>
#include "Emf.h"

Emf::Emf(void)
{
}

Emf::~Emf(void)
{
	if( f.is_open() )
	{
		f.close();
	}
}

void Emf::init(void)
{
	file_count = 0 ;
	write_count = 0 ;
	res_count = 0 ;

	// fnam から _out_folder を作成.
	char	drive[_MAX_DRIVE];	// ドライブ名
	char	dir[_MAX_DIR];		// ディレクトリ名
	char	file[_MAX_FNAME];	// ファイル名
	char	ext[_MAX_EXT];		// 拡張子

	_splitpath_s(
		fnam.c_str(),
		drive,	_MAX_DRIVE,
		dir,	_MAX_DIR,
		file,	_MAX_FNAME,
		ext,	_MAX_EXT	);

	// 出力先フォルダ名.
	char	out_folder[_MAX_PATH];
	_makepath_s(
		out_folder,	_MAX_PATH,
		drive,
		dir,
		NULL ,
		NULL );

	_out_folder.append( out_folder );
	_name.append( file );

#define	AddTbl( key, func )  ft.insert(make_pair((key),&Emf::##func ))

	// 2.3.1 Bitmap Record Types
//	ft.insert( make_pair(EMR_ALPHABLEND,				&Emf::proc_alphablend) );
//	ft.insert( make_pair(EMR_BITBLT,					&Emf::proc_bitblt) );
//	ft.insert( make_pair(EMR_MASKBLT,					&Emf::proc_maskblt) );
//	ft.insert( make_pair(EMR_PLGBLT,					&Emf::proc_plgblt) );
//	ft.insert( make_pair(EMR_SETDIBITSTODEVICE,			&Emf::proc_setdibitstodevice) );
//	ft.insert( make_pair(EMR_STRETCHBLT,				&Emf::proc_stretchblt) );
//	ft.insert( make_pair(EMR_STRETCHDIBITS,				&Emf::proc_stretchdibits) );
//	ft.insert( make_pair(EMR_TRANSPARENTBLT,			&Emf::proc_transparentblt) );
	AddTbl( EMR_ALPHABLEND,				proc_alphablend );
	AddTbl( EMR_BITBLT,					proc_bitblt );
	AddTbl( EMR_MASKBLT,				proc_maskblt );
	AddTbl( EMR_PLGBLT,					proc_plgblt );
	AddTbl( EMR_SETDIBITSTODEVICE,		proc_setdibitstodevice );
	AddTbl( EMR_STRETCHBLT,				proc_stretchblt );
	AddTbl( EMR_STRETCHDIBITS,			proc_stretchdibits );
	AddTbl( EMR_TRANSPARENTBLT,			proc_transparentblt );

	// 2.3.2 Clipping record types
	ft.insert( make_pair(EMR_EXCLUDECLIPRECT,			&Emf::proc_excludecliprect) );
	ft.insert( make_pair(EMR_EXTSELECTCLIPRGN,			&Emf::proc_extselectcliprgn) );
	ft.insert( make_pair(EMR_INTERSECTCLIPRECT,			&Emf::proc_intersectcliprect) );
	ft.insert( make_pair(EMR_OFFSETCLIPRGN,				&Emf::proc_offsetcliprgn) );
	ft.insert( make_pair(EMR_SELECTCLIPPATH,			&Emf::proc_selectclippath) );
	ft.insert( make_pair(EMR_SETMETARGN,				&Emf::proc_setmetargn) );

	// 2.3.3 Comment record types
	ft.insert( make_pair(EMR_COMMENT,					&Emf::proc_comment) );
//	ft.insert( make_pair(EMR_COMMENT_EMFPLUS,			&Emf::proc_comment) );
//	ft.insert( make_pair(EMR_COMMENT_EMFSPOOL,			&Emf::proc_comment) );
//	ft.insert( make_pair(EMR_COMMENT_PUBLIC,			&Emf::proc_comment) );

	// 2.3.4 Control record types
	ft.insert( make_pair(EMR_EOF,						&Emf::proc_eof) );
	ft.insert( make_pair(EMR_HEADER,					&Emf::proc_header) );

	// 2.3.5 Drawing record types
	ft.insert( make_pair(EMR_ANGLEARC,					&Emf::proc_anglearc) );
	ft.insert( make_pair(EMR_ARC,						&Emf::proc_arc) );
	ft.insert( make_pair(EMR_ARCTO,						&Emf::proc_arcto) );
	ft.insert( make_pair(EMR_CHORD,						&Emf::proc_chord) );
	ft.insert( make_pair(EMR_ELLIPSE,					&Emf::proc_ellipse) );
	ft.insert( make_pair(EMR_EXTFLOODFILL,				&Emf::proc_extfloodfill) );
	ft.insert( make_pair(EMR_EXTTEXTOUTA,				&Emf::proc_exttextouta) );
	ft.insert( make_pair(EMR_EXTTEXTOUTW,				&Emf::proc_exttextoutw) );
	ft.insert( make_pair(EMR_FILLPATH,					&Emf::proc_fillpath) );
	ft.insert( make_pair(EMR_FILLRGN,					&Emf::proc_fillrgn) );
	ft.insert( make_pair(EMR_FRAMERGN,					&Emf::proc_framergn) );
	ft.insert( make_pair(EMR_GRADIENTFILL,				&Emf::proc_gradientfill) );
	ft.insert( make_pair(EMR_LINETO,					&Emf::proc_lineto) );
	ft.insert( make_pair(EMR_PAINTRGN,					&Emf::proc_paintrgn) );
	ft.insert( make_pair(EMR_PIE,						&Emf::proc_pie) );
	ft.insert( make_pair(EMR_POLYBEZIER,				&Emf::proc_polybezier) );
	ft.insert( make_pair(EMR_POLYBEZIER16,				&Emf::proc_polybezier16) );
	ft.insert( make_pair(EMR_POLYBEZIERTO,				&Emf::proc_polybezierto) );
	ft.insert( make_pair(EMR_POLYBEZIERTO16,			&Emf::proc_polybezierto16) );
	ft.insert( make_pair(EMR_POLYDRAW,					&Emf::proc_polydraw) );
	ft.insert( make_pair(EMR_POLYDRAW16,				&Emf::proc_polydraw16) );
	ft.insert( make_pair(EMR_POLYGON,					&Emf::proc_polygon) );
	ft.insert( make_pair(EMR_POLYGON16,					&Emf::proc_polygon16) );
	ft.insert( make_pair(EMR_POLYLINE,					&Emf::proc_polyline) );
	ft.insert( make_pair(EMR_POLYLINE16,				&Emf::proc_polyline16) );
	ft.insert( make_pair(EMR_POLYLINETO,				&Emf::proc_polylineto) );
	ft.insert( make_pair(EMR_POLYLINETO16,				&Emf::proc_polylineto16) );
	ft.insert( make_pair(EMR_POLYPOLYGON,				&Emf::proc_polypolygon) );
	ft.insert( make_pair(EMR_POLYPOLYGON16,				&Emf::proc_polypolygon16) );
	ft.insert( make_pair(EMR_POLYPOLYLINE,				&Emf::proc_polypolyline) );
	ft.insert( make_pair(EMR_POLYPOLYLINE16,			&Emf::proc_polypolyline16) );
	ft.insert( make_pair(EMR_POLYTEXTOUTA,				&Emf::proc_polytextouta) );
	ft.insert( make_pair(EMR_POLYTEXTOUTW,				&Emf::proc_polytextoutw) );
	ft.insert( make_pair(EMR_RECTANGLE,					&Emf::proc_rectangle) );
	ft.insert( make_pair(EMR_ROUNDRECT,					&Emf::proc_roundrect) );
	ft.insert( make_pair(EMR_SETPIXELV,					&Emf::proc_setpixelv) );
	ft.insert( make_pair(EMR_SMALLTEXTOUT,				&Emf::proc_smalltextout) );
	ft.insert( make_pair(EMR_STROKEANDFILLPATH,			&Emf::proc_strokeandfillpath) );
	ft.insert( make_pair(EMR_STROKEPATH,				&Emf::proc_strokepath) );

	//2.3.6 Escape record types
	ft.insert( make_pair(EMR_DRAWESCAPE,				&Emf::proc_drawescape) );
	ft.insert( make_pair(EMR_EXTESCAPE,					&Emf::proc_extescape) );
	ft.insert( make_pair(EMR_NAMEDESCAPE,				&Emf::proc_namedescape) );

	// 2.3.7 Object creation record types
	ft.insert( make_pair(EMR_CREATEBRUSHINDIRECT,		&Emf::proc_createbrushindirect) );
	ft.insert( make_pair(EMR_CREATECOLORSPACE,			&Emf::proc_createcolorspace) );
	ft.insert( make_pair(EMR_CREATECOLORSPACEW,			&Emf::proc_createcolorspacew) );
	ft.insert( make_pair(EMR_CREATEDIBPATTERNBRUSHPT,	&Emf::proc_createdibpatternbrushpt) );
	ft.insert( make_pair(EMR_CREATEMONOBRUSH,			&Emf::proc_createmonobrush) );
	ft.insert( make_pair(EMR_CREATEPALETTE,				&Emf::proc_createpalette) );
	ft.insert( make_pair(EMR_CREATEPEN,					&Emf::proc_createpen) );
	ft.insert( make_pair(EMR_EXTCREATEFONTINDIRECTW,	&Emf::proc_extcreatefontindirectw) );
	ft.insert( make_pair(EMR_EXTCREATEPEN,				&Emf::proc_extcreatepen) );

	// 2.3.8 Object manipulation record types
	ft.insert( make_pair(EMR_COLORCORRECTPALETTE,		&Emf::proc_colorcorrectpalette) );
	ft.insert( make_pair(EMR_DELETECOLORSPACE,			&Emf::proc_deletecolorspace) );
	ft.insert( make_pair(EMR_DELETEOBJECT,				&Emf::proc_deleteobject) );
	ft.insert( make_pair(EMR_RESIZEPALETTE,				&Emf::proc_resizepalette) );
	ft.insert( make_pair(EMR_SELECTOBJECT,				&Emf::proc_selectobject) );
	ft.insert( make_pair(EMR_SELECTPALETTE,				&Emf::proc_selectpalette) );
	ft.insert( make_pair(EMR_SETCOLORSPACE,				&Emf::proc_setcolorspace) );
	ft.insert( make_pair(EMR_SETPALETTEENTRIES,			&Emf::proc_setpaletteentries) );

	// 2.3.9 OpenGL record types
	ft.insert( make_pair(EMR_GLSBOUNDEDRECORD,			&Emf::proc_glsboundedrecord) );
	ft.insert( make_pair(EMR_GLSRECORD,					&Emf::proc_glsrecord) );

	// 2.3.10 Path bracket record types
	ft.insert( make_pair(EMR_ABORTPATH,					&Emf::proc_abortpath) );
	ft.insert( make_pair(EMR_BEGINPATH,					&Emf::proc_beginpath) );
	ft.insert( make_pair(EMR_CLOSEFIGURE,				&Emf::proc_closefigure) );
	ft.insert( make_pair(EMR_ENDPATH,					&Emf::proc_endpath) );
	ft.insert( make_pair(EMR_FLATTENPATH,				&Emf::proc_flattenpath) );
	ft.insert( make_pair(EMR_WIDENPATH,					&Emf::proc_widenpath) );

	// 2.3.11 State record types
	ft.insert( make_pair(EMR_COLORMATCHTOTARGETW,		&Emf::proc_colormatchtotargetw) );
	ft.insert( make_pair(EMR_FORCEUFIMAPPING,			&Emf::proc_forceufimapping) );
	ft.insert( make_pair(EMR_INVERTRGN,					&Emf::proc_invertrgn) );
	ft.insert( make_pair(EMR_MOVETOEX,					&Emf::proc_movetoex) );
	ft.insert( make_pair(EMR_PIXELFORMAT,				&Emf::proc_pixelformat) );
	ft.insert( make_pair(EMR_REALIZEPALETTE,			&Emf::proc_realizepalette) );
	ft.insert( make_pair(EMR_RESTOREDC,					&Emf::proc_restoredc) );
	ft.insert( make_pair(EMR_SAVEDC,					&Emf::proc_savedc) );
	ft.insert( make_pair(EMR_SCALEVIEWPORTEXTEX,		&Emf::proc_scaleviewportextex) );
	ft.insert( make_pair(EMR_SCALEWINDOWEXTEX,			&Emf::proc_scalewindowextex) );
	ft.insert( make_pair(EMR_SETARCDIRECTION,			&Emf::proc_setarcdirection) );
	ft.insert( make_pair(EMR_SETBKCOLOR,				&Emf::proc_setbkcolor) );
	ft.insert( make_pair(EMR_SETBKMODE,					&Emf::proc_setbkmode) );
	ft.insert( make_pair(EMR_SETBRUSHORGEX,				&Emf::proc_setbrushorgex) );
	ft.insert( make_pair(EMR_SETCOLORADJUSTMENT,		&Emf::proc_setcoloradjustment) );
	ft.insert( make_pair(EMR_SETICMMODE,				&Emf::proc_seticmmode) );
	ft.insert( make_pair(EMR_SETICMPROFILEA,			&Emf::proc_seticmprofilea) );
	ft.insert( make_pair(EMR_SETICMPROFILEW,			&Emf::proc_seticmprofilew) );
	ft.insert( make_pair(EMR_SETLAYOUT,					&Emf::proc_setlayout) );
	ft.insert( make_pair(EMR_SETLINKEDUFIS,				&Emf::proc_setlinkedufis) );
	ft.insert( make_pair(EMR_SETMAPMODE,				&Emf::proc_setmapmode) );
	ft.insert( make_pair(EMR_SETMAPPERFLAGS,			&Emf::proc_setmapperflags) );
	ft.insert( make_pair(EMR_SETMITERLIMIT,				&Emf::proc_setmiterlimit) );
	ft.insert( make_pair(EMR_SETPOLYFILLMODE,			&Emf::proc_setpolyfillmode) );
	ft.insert( make_pair(EMR_SETROP2,					&Emf::proc_setrop2) );
	ft.insert( make_pair(EMR_SETSTRETCHBLTMODE,			&Emf::proc_setstretchbltmode) );
	ft.insert( make_pair(EMR_SETTEXTALIGN,				&Emf::proc_settextalign) );
	ft.insert( make_pair(EMR_SETTEXTCOLOR,				&Emf::proc_settextcolor) );
	ft.insert( make_pair(EMR_SETTEXTJUSTIFICATION,		&Emf::proc_settextjustification) );
	ft.insert( make_pair(EMR_SETVIEWPORTEXTEX,			&Emf::proc_setviewportextex) );
	ft.insert( make_pair(EMR_SETVIEWPORTORGEX,			&Emf::proc_setviewportorgex) );
	ft.insert( make_pair(EMR_SETWINDOWEXTEX,			&Emf::proc_setwindowextex) );
	ft.insert( make_pair(EMR_SETWINDOWORGEX,			&Emf::proc_setwindoworgex) );

	// 2.3.12 Transform record types
	ft.insert( make_pair(EMR_MODIFYWORLDTRANSFORM,		&Emf::proc_modifyworldtransform) );
	ft.insert( make_pair(EMR_SETWORLDTRANSFORM,			&Emf::proc_setworldtransform) );
#undef	AddTbl
}

bool	Emf::writeFile( string data )
{
	// ファイル名の決定.
	if( !f.is_open() )
	{
		write_count = 0 ;

		//パス名を分解
		char	drive[_MAX_DRIVE];	// ドライブ名
		char	dir[_MAX_DIR];		// ディレクトリ名
		char	file[_MAX_FNAME];	// ファイル名
		char	ext[_MAX_EXT];		// 拡張子

		_splitpath_s(
			fnam.c_str(),
			drive,	_MAX_DRIVE,
			dir,	_MAX_DIR,
			file,	_MAX_FNAME,
			ext,	_MAX_EXT	);

		if( file_count == 0 )
		{
			line_count = 1 ;
		}

		sprintf_s( file,256, "%s_%03d", file, file_count );
		file_count++;

		// 出力先ファイル名.
		char	out_folder[_MAX_PATH];
		_makepath_s(
			out_folder,	_MAX_PATH,
			drive,
			dir,
			file,
			"csv");

		f.open( out_folder );
		f << "No.,Record,Param" << endl ;
	}

	// データ書き込み.
	f << line_count << "," << data << endl ;
	line_count++; 

	// 巨大なファイルの場合、分割する.
	write_count++ ;
	if( write_count >= 16000 )
	{
		write_count = 0 ;
		f.close();
	}

	return true ;
}

// 解析処理.
bool	Emf::parse()
{
	stringstream	ss(data);

	EMR	h ;
	while( !ss.read((char*)&h, sizeof(EMR)).eof() )
	{
		// レコード毎処理用に、読み込んだヘッダ分だけ戻す.
		long adr = ss.seekg( -(signed)sizeof(EMR), ios_base::cur ).tellg();

		// レコード毎の処理を行う.
		func_tbl::iterator it = ft.find( (int)h.iType );
		writeFile( (it != ft.end()) ? (this->*it->second)(ss) : proc_unknown(ss) );

		// 次のレコードへ移動.
		ss.seekg( adr, ios_base::beg );		// 念のため、レコードの先頭へ戻す.
		ss.seekg( h.nSize, ios_base::cur );	// レコードサイズ分移動.
	}

	return true ;
}

#define	BEGIN_PARAM	",\""
#define	END_PARAM	"\""

//
string	Emf::proc_unknown( stringstream &s )
{
	EMR	rec ;
	s.read( (char*)&rec, sizeof(EMR));

	stringstream	data("proc_unknown",ios_base::ate | ios_base::app | ios_base::out );

	data << BEGIN_PARAM ;
	data << "type=" << rec.iType << ",size" << rec.nSize  ;
	data << END_PARAM ;

	return data.str() ;
}

// --------------------------------------------------------------------------

// 2.3.1 Bitmap Record Types

// 2.3.1.1 EMR_ALPHABLEND Record
string	Emf::proc_alphablend( stringstream &s )
{
	EMRALPHABLEND	rec ;
	s.read( (char*)&rec, sizeof(EMRALPHABLEND));

	stringstream	data("EMR_ALPHABLEND",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) ;
	// TODO

	data << END_PARAM ;

	return data.str() ;
}

// 2.3.1.2 EMR_BITBLT Record
string	Emf::proc_bitblt( stringstream &s )
{
	EMRBITBLT	rec ;
	s.read( (char*)&rec, sizeof(EMRBITBLT));

	stringstream	data("EMR_BITBLT",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) << endl ;
	data << "xDest:" << rec.xDest << endl ;
	data << "yDest:" << rec.yDest << endl ;
	data << "cxDest:" << rec.cxDest << endl ;
	data << "cyDest:" << rec.cyDest << endl ;
	data << "BkColorSrc:" <<  format_object( rec.crBkColorSrc ) << endl ;
	data << "ROP:" ;
	switch( rec.dwRop )
	{
	case BLACKNESS:		data << "BLACKNESS" ;		break;
//	case DPSOON:		data << "DPSOON" ;			break;
//	case DPSONA:		data << "DPSONA" ;			break;
//	case PSON:			data << "PSON" ;			break;
//	case SDPONA:		data << "SDPONA" ;			break;
//	case DPON:			data << "DPON" ;			break;
//	case PDSXNON:		data << "PDSXNON" ;			break;
//	case PDSAON:		data << "PDSAON" ;			break;
//	case SDPNAA:		data << "SDPNAA" ;			break;
//	case PDSXON:		data << "PDSXON" ;			break;
//	case DPNA:			data << "DPNA" ;			break;
//	case PSDNAON:		data << "PSDNAON" ;			break;
//	case SPNA:			data << "SPNA" ;			break;
//	case PDSNAON:		data << "PDSNAON" ;			break;
//	case PDSONON:		data << "PDSONON" ;			break;
//	case PN:			data << "PN" ;				break;
//	case PDSONA:		data << "PDSONA" ;			break;
	case NOTSRCERASE:	data << "NOTSRCERASE" ;		break;
//	case SDPXNON:		data << "SDPXNON" ;			break;
//	case SDPAON:		data << "SDPAON" ;			break;
//	case DPSXNON:		data << "DPSXNON" ;			break;
//	case DPSAON:		data << "DPSAON" ;			break;
//	case PSDPSANAXX:	data << "PSDPSANAXX" ;		break;
//	case SSPXDSXAXN:	data << "SSPXDSXAXN" ;		break;
//	case SPXPDXA:		data << "SPXPDXA" ;			break;
//	case SDPSANAXN:		data << "SDPSANAXN" ;		break;
//	case PDSPAOX:		data << "PDSPAOX" ;			break;
//	case SDPSXAXN:		data << "SDPSXAXN" ;		break;
//	case PSDPAOX:		data << "PSDPAOX" ;			break;
//	case DSPDXAXN:		data << "DSPDXAXN" ;		break;
//	case PDSOX:			data << "PDSOX" ;			break;
//	case PDSOAN:		data << "PDSOAN" ;			break;
//	case DPSNAA:		data << "DPSNAA" ;			break;
//	case SDPXON:		data << "SDPXON" ;			break;
//	case DSNA:			data << "DSNA" ;			break;
//	case SPDNAON:		data << "SPDNAON" ;			break;
//	case SPXDSXA:		data << "SPXDSXA" ;			break;
//	case PDSPANAXN:		data << "PDSPANAXN" ;		break;
//	case SDPSAOX:		data << "RGN_AND" ;		break;
//	case SDPSXNOX:		data << "RGN_AND" ;		break;
//	case DPSXA:			data << "RGN_AND" ;		break;
//	case PSDPSAOXXN:	data << "RGN_AND" ;		break;
//	case DPSANA:		data << "RGN_AND" ;		break;
//	case SSPXPDXAXN:	data << "RGN_AND" ;		break;
//	case SPDSOAX:		data << "RGN_AND" ;		break;
//	case PSDNOX:		data << "RGN_AND" ;		break;
//	case PSDPXOX:		data << "RGN_AND" ;		break;
//	case PSDNOAN:		data << "RGN_AND" ;		break;
//	case PSNA:			data << "RGN_AND" ;		break;
//	case SDPNAON:		data << "RGN_AND" ;		break;
//	case SDPSOOX:		data << "RGN_AND" ;		break;
	case NOTSRCCOPY:	data << "NOTSRCCOPY" ;		break;
//	case SPDSAOX:		data << "RGN_AND" ;		break;
//	case SPDSXNOX:		data << "RGN_AND" ;		break;
//	case SDPOX:			data << "RGN_AND" ;		break;
//	case SDPOAN:		data << "RGN_AND" ;		break;
//	case PSDPOAX:		data << "RGN_AND" ;		break;
//	case SPDNOX:		data << "RGN_AND" ;		break;
//	case SPDSXOX:		data << "RGN_AND" ;		break;
//	case SPDNOAN:		data << "RGN_AND" ;		break;
//	case PSX:			data << "RGN_AND" ;		break;
//	case SPDSONOX:		data << "RGN_AND" ;		break;
//	case SPDSNAOX:		data << "RGN_AND" ;		break;
//	case PSAN:			data << "RGN_AND" ;		break;
//	case PSDNAA:		data << "RGN_AND" ;		break;
//	case DPSXON:		data << "RGN_AND" ;		break;
//	case SDXPDXA:		data << "RGN_AND" ;		break;
//	case SPDSANAXN:		data << "RGN_AND" ;		break;
	case SRCERASE:		data << "SRCERASE" ;		break;
//	case DPSNAON:		data << "RGN_AND" ;		break;
//	case DSPDAOX:		data << "RGN_AND" ;		break;
//	case PSDPXAXN:		data << "RGN_AND" ;		break;
//	case SDPXA:			data << "RGN_AND" ;		break;
//	case PDSPDAOXXN:	data << "RGN_AND" ;		break;
//	case DPSDOAX:		data << "RGN_AND" ;		break;
//	case PDSNOX:		data << "RGN_AND" ;		break;
//	case SDPANA:		data << "RGN_AND" ;		break;
//	case SSPXDSXOXN:	data << "RGN_AND" ;		break;
//	case PDSPXOX:		data << "RGN_AND" ;		break;
//	case PDSNOAN:		data << "RGN_AND" ;		break;
//	case PDNA:			data << "RGN_AND" ;		break;
//	case DSPNAON:		data << "RGN_AND" ;		break;
//	case DPSDAOX:		data << "RGN_AND" ;		break;
//	case SPDSXAXN:		data << "RGN_AND" ;		break;
//	case DPSONON:		data << "RGN_AND" ;		break;
	case DSTINVERT:		data << "DSTINVERT" ;		break;
//	case DPSOX:			data << "RGN_AND" ;		break;
//	case DPSOAN:		data << "RGN_AND" ;		break;
//	case PDSPOAX:		data << "RGN_AND" ;		break;
//	case DPSNOX:		data << "RGN_AND" ;		break;
	case PATINVERT:		data << "PATINVERT" ;		break;
//	case DPSDONOX:		data << "RGN_AND" ;		break;
//	case DPSDXOX:		data << "RGN_AND" ;		break;
//	case DPSNOAN:		data << "RGN_AND" ;		break;
//	case DPSDNAOX:		data << "RGN_AND" ;		break;
//	case DPAN:			data << "RGN_AND" ;		break;
//	case PDSXA:			data << "RGN_AND" ;		break;
//	case DSPDSAOXXN:	data << "RGN_AND" ;		break;
//	case DSPDOAX:		data << "RGN_AND" ;		break;
//	case SDPNOX:		data << "RGN_AND" ;		break;
//	case SDPSOAX:		data << "RGN_AND" ;		break;
//	case DSPNOX:		data << "RGN_AND" ;		break;
	case SRCINVERT:		data << "SRCINVERT" ;		break;
//	case SDPSONOX:		data << "RGN_AND" ;		break;
//	case DSPDSONOXXN:	data << "RGN_AND" ;		break;
//	case PDSXXN:		data << "RGN_AND" ;		break;
//	case DPSAX:			data << "RGN_AND" ;		break;
//	case PSDPSOAXXN:	data << "RGN_AND" ;		break;
//	case SDPAX:			data << "RGN_AND" ;		break;
//	case PDSPDOAXXN:	data << "RGN_AND" ;		break;
//	case SDPSNOAX:		data << "RGN_AND" ;		break;
//	case PDXNAN:		data << "RGN_AND" ;		break;
//	case PDSANA:		data << "RGN_AND" ;		break;
//	case SSDXPDXAXN:	data << "RGN_AND" ;		break;
//	case SDPSXOX:		data << "RGN_AND" ;		break;
//	case SDPNOAN:		data << "RGN_AND" ;		break;
//	case DSPDXOX:		data << "RGN_AND" ;		break;
//	case DSPNOAN:		data << "RGN_AND" ;		break;
//	case SDPSNAOX:		data << "RGN_AND" ;		break;
//	case DSAN:			data << "RGN_AND" ;		break;
//	case PDSAX:			data << "RGN_AND" ;		break;
//	case DSPDSOAXXN:	data << "RGN_AND" ;		break;
//	case DPSDNOAX:		data << "RGN_AND" ;		break;
//	case SDPXNAN:		data << "RGN_AND" ;		break;
//	case SPDSNOAX:		data << "RGN_AND" ;		break;
//	case DPSXNAN:		data << "RGN_AND" ;		break;
//	case SPXDSXO:		data << "RGN_AND" ;		break;
//	case DPSAAN:		data << "RGN_AND" ;		break;
//	case DPSAA:			data << "RGN_AND" ;		break;
//	case SPXDSXON:		data << "RGN_AND" ;		break;
//	case DPSXNA:		data << "RGN_AND" ;		break;
//	case SPDSNOAXN:		data << "RGN_AND" ;		break;
//	case SDPXNA:		data << "RGN_AND" ;		break;
//	case PDSPNOAXN:		data << "RGN_AND" ;		break;
//	case DSPDSOAXX:		data << "RGN_AND" ;		break;
//	case PDSAXN:		data << "RGN_AND" ;		break;
	case SRCAND:		data << "SRCAND" ;			break;
//	case SDPSNAOXN:		data << "RGN_AND" ;		break;
//	case DSPNOA:		data << "RGN_AND" ;		break;
//	case DSPDXOXN:		data << "RGN_AND" ;		break;
//	case SDPNOA:		data << "RGN_AND" ;		break;
//	case SDPSXOXN:		data << "RGN_AND" ;		break;
//	case SSDXPDXAX:		data << "RGN_AND" ;		break;
//	case PDSANAN:		data << "RGN_AND" ;		break;
//	case PDSXNA:		data << "RGN_AND" ;		break;
//	case SDPSNOAXN:		data << "RGN_AND" ;		break;
//	case DPSDPOAXX:		data << "RGN_AND" ;		break;
//	case SPDAXN:		data << "RGN_AND" ;		break;
//	case PSDPSOAXX:		data << "RGN_AND" ;		break;
//	case DPSAXN:		data << "RGN_AND" ;		break;
//	case DPSXX:			data << "RGN_AND" ;		break;
//	case PSDPSONOXX:	data << "RGN_AND" ;		break;
//	case SDPSONOXN:		data << "RGN_AND" ;		break;
//	case DSXN:			data << "RGN_AND" ;		break;
//	case DPSNAX:		data << "RGN_AND" ;		break;
//	case SDPSOAXN:		data << "RGN_AND" ;		break;
//	case SPDNAX:		data << "RGN_AND" ;		break;
//	case DSPDOAXN:		data << "RGN_AND" ;		break;
//	case DSPDSAOXX:		data << "RGN_AND" ;		break;
//	case PDSXAN:		data << "RGN_AND" ;		break;
//	case DPA:			data << "RGN_AND" ;		break;
//	case PDSPNAOXN:		data << "RGN_AND" ;		break;
//	case DPSNOA:		data << "RGN_AND" ;		break;
//	case DPSDXOXN:		data << "RGN_AND" ;		break;
//	case PDSPONOXN:		data << "RGN_AND" ;		break;
//	case PDXN:			data << "RGN_AND" ;		break;
//	case DSPNAX:		data << "RGN_AND" ;		break;
//	case PDSPOAXN:		data << "RGN_AND" ;		break;
//	case DPSOA:			data << "RGN_AND" ;		break;
//	case DPSOXN:		data << "RGN_AND" ;		break;
//	case D:				data << "RGN_AND" ;		break;
//	case DPSONO:		data << "RGN_AND" ;		break;
//	case SPDSXAX:		data << "RGN_AND" ;		break;
//	case DPSDAOXN:		data << "RGN_AND" ;		break;
//	case DSPNAO:		data << "RGN_AND" ;		break;
//	case DPNO:			data << "RGN_AND" ;		break;
//	case PDSNOA:		data << "RGN_AND" ;		break;
//	case PDSPXOXN:		data << "RGN_AND" ;		break;
//	case SSPXDSXOX:		data << "RGN_AND" ;		break;
//	case SDPANAN:		data << "RGN_AND" ;		break;
//	case PSDNAX:		data << "RGN_AND" ;		break;
//	case DPSDOAXN:		data << "RGN_AND" ;		break;
//	case DPSDPAOXX:		data << "RGN_AND" ;		break;
//	case SDPXAN:		data << "RGN_AND" ;		break;
//	case PSDPXAX:		data << "RGN_AND" ;		break;
//	case DSPDAOXN:		data << "RGN_AND" ;		break;
//	case DPSNAO:		data << "RGN_AND" ;		break;
	case MERGEPAINT:	data << "MERGEPAINT" ;		break;
//	case SPDSANAX:		data << "RGN_AND" ;		break;
//	case SDXPDXAN:		data << "RGN_AND" ;		break;
//	case DPSXO:			data << "RGN_AND" ;		break;
//	case DPSANO:		data << "RGN_AND" ;		break;
	case MERGECOPY:		data << "MERGECOPY" ;		break;
//	case SPDSNAOXN:		data << "RGN_AND" ;		break;
//	case SPDSONOXN:		data << "RGN_AND" ;		break;
//	case PSXN:			data << "RGN_AND" ;		break;
//	case SPDNOA:		data << "RGN_AND" ;		break;
//	case SPDSXOXN:		data << "RGN_AND" ;		break;
//	case SDPNAX:		data << "RGN_AND" ;		break;
//	case PSDPOAXN:		data << "RGN_AND" ;		break;
//	case SDPOA:			data << "RGN_AND" ;		break;
//	case SPDOXN:		data << "RGN_AND" ;		break;
//	case DPSDXAX:		data << "RGN_AND" ;		break;
//	case SPDSAOXN:		data << "RGN_AND" ;		break;
	case SRCCOPY:		data << "SRCCOPY" ;			break;
//	case SDPONO:		data << "RGN_AND" ;		break;
//	case SDPNAO:		data << "RGN_AND" ;		break;
//	case SPNO:			data << "RGN_AND" ;		break;
//	case PSDNOA:		data << "RGN_AND" ;		break;
//	case PSDPXOXN:		data << "RGN_AND" ;		break;
//	case PDSNAX:		data << "RGN_AND" ;		break;
//	case SPDSOAXN:		data << "RGN_AND" ;		break;
//	case SSPXPDXAX:		data << "RGN_AND" ;		break;
//	case DPSANAN:		data << "RGN_AND" ;		break;
//	case PSDPSAOXX:		data << "RGN_AND" ;		break;
//	case DPSXAN:		data << "RGN_AND" ;		break;
//	case PDSPXAX:		data << "RGN_AND" ;		break;
//	case SDPSAOXN:		data << "RGN_AND" ;		break;
//	case DPSDANAX:		data << "RGN_AND" ;		break;
//	case SPXDSXAN:		data << "RGN_AND" ;		break;
//	case SPDNAO:		data << "RGN_AND" ;		break;
//	case SDNO:			data << "RGN_AND" ;		break;
//	case SDPXO:			data << "RGN_AND" ;		break;
//	case SDPANO:		data << "RGN_AND" ;		break;
//	case PDSOA:			data << "RGN_AND" ;		break;
//	case PDSOXN:		data << "RGN_AND" ;		break;
//	case DSPDXAX:		data << "RGN_AND" ;		break;
//	case PSDPAOXN:		data << "RGN_AND" ;		break;
//	case SDPSXAX:		data << "RGN_AND" ;		break;
//	case PDSPAOXN:		data << "PDSPAOXN" ;		break;
//	case SDPSANAX:		data << "SDPSANAX" ;		break;
//	case SPXPDXAN:		data << "SPXPDXAN" ;		break;
//	case SSPXDSXAX:		data << "SSPXDSXAX" ;		break;
//	case DSPDSANAXXN:	data << "DSPDSANAXXN" ;		break;
//	case DPSAO:			data << "DPSAO" ;			break;
//	case DPSXNO:		data << "DPSXNO" ;			break;
//	case SDPAO:			data << "SDPAO" ;			break;
//	case SDPXNO:		data << "SDPXNO" ;			break;
	case SRCPAINT:		data << "SRCPAINT" ;		break;
//	case SDPNOO:		data << "SDPNOO" ;			break;
	case PATCOPY:		data << "PATCOPY" ;			break;
//	case PDSONO:		data << "PDSONO" ;			break;
//	case PDSNAO:		data << "PDSNAO" ;			break;
//	case PSNO:			data << "PSNO" ;			break;
//	case PSDNAO:		data << "PSDNAO" ;			break;
//	case PDNO:			data << "PDNO" ;			break;
//	case PDSXO:			data << "PDSXO" ;			break;
//	case PDSANO:		data << "PDSANO" ;			break;
//	case PDSAO:			data << "PDSAO" ;			break;
//	case PDSXNO:		data << "PDSXNO" ;			break;
//	case DPO:			data << "DPO" ;				break;
	case PATPAINT:		data << "PATPAINT" ;		break;
//	case PSO:			data << "PSO" ;				break;
//	case PSDNOO:		data << "PSDNOO" ;			break;
//	case DPSOO:			data << "DPSOO" ;			break;
	case WHITENESS:		data << "WHITENESS" ;		break;
	default:			data << "unknown(" << hex << setfill('0') << setw(8) << rec.dwRop ;	break;
	}
	data << END_PARAM ;

	long size = rec.cbBitsSrc + rec.cbBmiSrc ;
	if( size > 0 )
	{
		// Bitmap 保存処理.
	}

	return data.str() ;
}

// 2.3.1.3 EMR_MASKBLT Record
string	Emf::proc_maskblt( stringstream &s )
{
	EMRMASKBLT	rec ;
	s.read( (char*)&rec, sizeof(EMRMASKBLT));

	stringstream	data("EMR_MASKBLT",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) ;
	// TODO

	data << END_PARAM ;

	return data.str() ;
}

// 2.3.1.4 EMR_PLGBLT Record
string	Emf::proc_plgblt( stringstream &s )
{
	EMRPLGBLT	rec ;
	s.read( (char*)&rec, sizeof(EMRPLGBLT));

	stringstream	data("EMR_PLGBLT",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) ;
	// TODO

	data << END_PARAM ;

	return data.str() ;
}

// 2.3.1.5 EMR_SETDIBITSTODEVICE Record
string	Emf::proc_setdibitstodevice( stringstream &s )
{
	EMRSETDIBITSTODEVICE	rec ;
	s.read( (char*)&rec, sizeof(EMRSETDIBITSTODEVICE));

	stringstream	data("EMR_SETDIBITSTODEVICE",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) ;
	// TODO

	data << END_PARAM ;

	return data.str() ;
}

// 2.3.1.6 EMR_STRETCHBLT Record
string	Emf::proc_stretchblt( stringstream &s )
{
	EMRSTRETCHBLT	rec ;
	s.read( (char*)&rec, sizeof(EMRSTRETCHBLT));

	stringstream	data("EMR_STRETCHBLT",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) ;
	// TODO

	data << END_PARAM ;

	return data.str() ;
}

// 2.3.1.7 EMR_STRETCHDIBITS Record
string	Emf::proc_stretchdibits( stringstream &s )
{
	EMRSTRETCHDIBITS	rec ;
	s.read( (char*)&rec, sizeof(EMRSTRETCHDIBITS));

	stringstream	data("EMR_STRETCHDIBITS",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) << endl ;
	data << "xSrc:" << rec.xSrc << endl ;
	data << "ySrc:" << rec.ySrc << endl ;
	data << "cxSrc:" << rec.cxSrc << endl ;
	data << "cySrc:" << rec.cySrc << endl ;
	data << "xDest:" << rec.xDest << endl ;
	data << "yDest:" << rec.yDest << endl ;
	data << "cxDest:" << rec.cxDest << endl ;
	data << "cyDest:" << rec.cyDest << endl ;
	data << "ROP:" ;
	switch( rec.dwRop )
	{
	case BLACKNESS:		data << "BLACKNESS" ;		break;
	case NOTSRCERASE:	data << "NOTSRCERASE" ;		break;
	case NOTSRCCOPY:	data << "NOTSRCCOPY" ;		break;
	case SRCERASE:		data << "SRCERASE" ;		break;
	case DSTINVERT:		data << "DSTINVERT" ;		break;
	case PATINVERT:		data << "PATINVERT" ;		break;
	case SRCINVERT:		data << "SRCINVERT" ;		break;
	case SRCAND:		data << "SRCAND" ;			break;
	case MERGEPAINT:	data << "MERGEPAINT" ;		break;
	case MERGECOPY:		data << "MERGECOPY" ;		break;
	case SRCCOPY:		data << "SRCCOPY" ;			break;
	case SRCPAINT:		data << "SRCPAINT" ;		break;
	case PATCOPY:		data << "PATCOPY" ;			break;
	case PATPAINT:		data << "PATPAINT" ;		break;
	case WHITENESS:		data << "WHITENESS" ;		break;
	default:			data << "unknown(" << hex << setfill('0') << setw(8) << rec.dwRop ;	break;
	}

	long size = rec.cbBitsSrc + rec.cbBmiSrc ;
	if( size > 0 )
	{
		// Bitmap 保存処理.
		char *p = new char [ size ] ;
		s.read( (char*)p, size );
		
		BITMAPFILEHEADER	head = {0};
		head.bfType = 0x4D42 ;

		string	fname = out_res_name();
		ofstream	o( fname.c_str(), ios::binary );
		o.write( (char*)&head, sizeof(BITMAPFILEHEADER) );
		o.write( p, size );
		o.close();

		data << endl ;
		data << "Resource:" << fname ;
	}
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.1.8 EMR_TRANSPARENTBLT Record
string	Emf::proc_transparentblt( stringstream &s )
{
	EMRTRANSPARENTBLT	rec ;
	s.read( (char*)&rec, sizeof(EMRTRANSPARENTBLT));

	stringstream	data("EMR_TRANSPARENTBLT",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) ;
	// TODO

	data << END_PARAM ;

	return data.str() ;
}

// 2.3.2 clipping record types

// 2.3.2.1 EMR_EXCLUDECLIPRECT Record
string	Emf::proc_excludecliprect( stringstream &s )
{
	EMREXCLUDECLIPRECT	rec ;
	s.read( (char*)&rec, sizeof(EMREXCLUDECLIPRECT));

	stringstream	data("EMR_EXCLUDECLIPRECT",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclClip ) ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.2.2 EMR_EXTSELECTCLIPRGN Record
string	Emf::proc_extselectcliprgn( stringstream &s )
{
	EMREXTSELECTCLIPRGN	rec ;
	s.read( (char*)&rec, sizeof(EMREXTSELECTCLIPRGN));

	stringstream	data("EMR_EXTSELECTCLIPRGN",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << "Size:" << rec.cbRgnData ;
	// TODO

	data << END_PARAM ;

	return data.str() ;
}

// 2.3.2.3 EMR_INTERSECTCLIPRECT Record
string	Emf::proc_intersectcliprect( stringstream &s )
{
	EMRINTERSECTCLIPRECT	rec ;
	s.read( (char*)&rec, sizeof(EMRINTERSECTCLIPRECT));

	stringstream	data("EMR_INTERSECTCLIPRECT",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclClip ) ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.2.4 EMR_OFFSETCLIPRGN Record
string	Emf::proc_offsetcliprgn( stringstream &s )
{
	EMROFFSETCLIPRGN	rec ;
	s.read( (char*)&rec, sizeof(EMROFFSETCLIPRGN));

	stringstream	data("EMR_OFFSETCLIPRGN",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.ptlOffset ) ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.2.5 EMR_SELECTCLIPPATH Record
string	Emf::proc_selectclippath( stringstream &s )
{
	// 
	EMRSELECTCLIPPATH	rec ;
	s.read( (char*)&rec, sizeof(EMRSELECTCLIPPATH));

	stringstream	data("EMR_SELECTCLIPPATH",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	switch( rec.iMode )
	{
	case RGN_AND:	data << "RGN_AND" ;		break;
	case RGN_OR:	data << "RGN_OR" ;		break;
	case RGN_XOR:	data << "RGN_XOR" ;		break;
	case RGN_DIFF:	data << "RGN_DIFF" ;	break;
	case RGN_COPY:	data << "RGN_COPY" ;	break;
	}
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.2 EMR_SETMETARGN Record
string	Emf::proc_setmetargn( stringstream &s )
{
	// EMRSETMETARGN
	stringstream	data("EMR_SETMETARGN",ios_base::ate | ios_base::app | ios_base::out );

	// no param

	return data.str() ;
}

// 2.3.3 Comment record types

// 2.3.3.1 EMR_COMMENT Record
string	Emf::proc_comment( stringstream &s )
{
    EMRGDICOMMENT   rec;
	s.read( (char*)&rec, sizeof(EMRGDICOMMENT));

	stringstream	data("EMR_COMMENT",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << "Size:" << rec.cbData ;
	// TODO

	data << END_PARAM ;

	return data.str() ;
}

// 2.3.3.2 EMR_COMMENT_EMFPLUS Record
// 2.3.3.3 EMR_COMMENT_EMFSPOOL Record
// 2.3.3.4 EMR_COMMENT_PUBLIC Record Types

// 2.3.4 control record types

// 2.3.4.1 EMR_EOF Record
string	Emf::proc_eof( stringstream &s )
{
	// EMREOF
	stringstream	data("EMR_EOF",ios_base::ate | ios_base::app | ios_base::out );
	return data.str() ;
}

// 2.3.4.2 EMR_HEADER Record Types
string	Emf::proc_header( stringstream &s )
{
    ENHMETAHEADER   rec;          // Inclusive-inclusive bounds in device units
	s.read( (char*)&rec, sizeof(ENHMETAHEADER));

	stringstream	data("EMR_HEADER",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << "Version:" << setbase(16) << setfill('0') << setw(8) << rec.nVersion ;
	data << " Bytes:" << setbase(10) << rec.nBytes << " Records:" << rec.nRecords << endl;
	data << format_object( rec.rclBounds ) << endl ;
	data << "Device:" << format_object( rec.szlDevice ) ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5 drawing record types

// 2.3.5.1 EMR_ANGLEARC Record
string	Emf::proc_anglearc( stringstream &s )
{
	EMRANGLEARC	rec ;
	s.read( (char*)&rec, sizeof(EMRANGLEARC));

	stringstream	data("EMR_ANGLEARC",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.ptlCenter ) ;
	// TODO

	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.2 EMR_ARC Record
string	Emf::proc_arc( stringstream &s )
{
	EMRARC	rec;
	s.read( (char*)&rec, sizeof(EMRARC));

	stringstream	data("EMR_ARC",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBox ) << endl ;
	data << format_object( rec.ptlStart ) << "-" << format_object( rec.ptlEnd ) ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.3 EMR_ARCTO Record
string	Emf::proc_arcto( stringstream &s )
{
	EMRARCTO	rec;
	s.read( (char*)&rec, sizeof(EMRARCTO));

	stringstream	data("EMR_ARCTO",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBox ) << endl ;
	data << format_object( rec.ptlStart ) << "-" << format_object( rec.ptlEnd ) ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.4 EMR_CHORD Record
string	Emf::proc_chord( stringstream &s )
{
	EMRCHORD	rec;
	s.read( (char*)&rec, sizeof(EMRCHORD));

	stringstream	data("EMR_CHORD",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBox ) << endl ;
	data << format_object( rec.ptlStart ) << "-" << format_object( rec.ptlEnd ) ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.5 EMR_ELLIPSE Record
string	Emf::proc_ellipse( stringstream &s )
{
	EMRELLIPSE	rec ;
	s.read( (char*)&rec, sizeof(EMRELLIPSE));

	stringstream	data("EMR_ELLIPSE",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBox ) ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.6 EMR_EXTFLOODFILL Record
string	Emf::proc_extfloodfill( stringstream &s )
{
	EMREXTFLOODFILL	rec ;
	s.read( (char*)&rec, sizeof(EMREXTFLOODFILL));

	stringstream	data("EMR_EXTFLOODFILL",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.ptlStart ) << endl  ;
	data << format_object( rec.crColor ) << endl ;
	switch( rec.iMode )
	{
	case FLOODFILLBORDER:	data << " Mode:FLOODFILLBORDER" ;	break;
	case FLOODFILLSURFACE:	data << " Mode:FLOODFILLSURFACE" ;	break;
	}
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.7 EMR_EXTTEXTOUTA Record
string	Emf::proc_exttextouta( stringstream &s )
{
	// EMREXTTEXTOUTA

	stringstream	data("EMR_EXTTEXTOUTA",ios_base::ate | ios_base::app | ios_base::out );

	// TODO:

	return data.str() ;
}

// 2.3.5.8 EMR_EXTTEXTOUTW Record
string	Emf::proc_exttextoutw( stringstream &s )
{
	EMREXTTEXTOUTW	rec;
	s.read( (char*)&rec, sizeof(EMREXTTEXTOUTW));

	stringstream	data("EMR_EXTTEXTOUTW",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) << endl ;
	data << "GraphicsMode:" ;
	switch( rec.iGraphicsMode )
	{
	case GM_COMPATIBLE:	data << " GM_COMPATIBLE" ;	break;
	case GM_ADVANCED:	data << " GM_ADVANCED" ;	break;
	}
	data << endl ;
	data << "exScale:" << rec.exScale << endl ;
	data << "eyScale:" << rec.eyScale << endl ;

	// string is UTF16-LE
	if( rec.emrtext.nChars > 0 )
	{
		int size = rec.emrtext.nChars ;
		size *=2;

		wstring	name( size+1, NULL );
		s.read( (char*)name.c_str(), size );
//		TRACE("%s\n",CW2A(name.c_str()));
///		data << "Text(" << size << "):" << CW2A(name.c_str()) << endl ;
		data << "Dump:" << dump( (char*)name.c_str(), size );

//		char	*p = new char [ size ];
//		wstring	b(p,size);
//		b = CW2A(b.c_str());
//		s.read( p, size );
//		data << "str:" << dump( p, size );
//		delete [] p ;
		
	}


	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.9 EMR_FILLPATH Record
string	Emf::proc_fillpath( stringstream &s )
{
	EMRFILLPATH	rec;
	s.read( (char*)&rec, sizeof(EMRFILLPATH));

	stringstream	data("EMR_FILLPATH",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.10 EMR_FILLRGN Record
string	Emf::proc_fillrgn( stringstream &s )
{
	EMRFILLRGN	rec;
	s.read( (char*)&rec, sizeof(EMRFILLRGN));

	stringstream	data("EMR_FILLRGN",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) ;
	// TODO

	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.11 EMR_FRAMERGN Record
string	Emf::proc_framergn( stringstream &s )
{
	EMRFRAMERGN	rec;
	s.read( (char*)&rec, sizeof(EMRFRAMERGN));

	stringstream	data("EMR_FRAMERGN",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) ;
	// TODO

	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.12 EMR_GRADIENTFILL Record
string	Emf::proc_gradientfill( stringstream &s )
{
	EMRGRADIENTFILL	rec;
	s.read( (char*)&rec, sizeof(EMRGRADIENTFILL));

	stringstream	data("EMR_GRADIENTFILL",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) ;
	// TODO

	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.13 EMR_LINETO Record
string	Emf::proc_lineto( stringstream &s )
{
	EMRLINETO	rec ;
	s.read( (char*)&rec, sizeof(EMRLINETO));

	stringstream	data("EMR_LINETO",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.ptl ) ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.14 EMR_PAINTRGN Record
string	Emf::proc_paintrgn( stringstream &s )
{
	EMRPAINTRGN	rec;
	s.read( (char*)&rec, sizeof(EMRPAINTRGN));

	stringstream	data("EMR_PAINTRGN",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) << endl;
	data << "Size:" << rec.cbRgnData  ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.15 EMR_PIE Record
string	Emf::proc_pie( stringstream &s )
{
	EMRPIE	rec;
	s.read( (char*)&rec, sizeof(EMRPIE));

	stringstream	data("EMR_PIE",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBox ) << endl;
	data << format_object( rec.ptlStart ) << "-" << format_object( rec.ptlEnd ) ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.16 EMR_POLYBEZIER Record
string	Emf::proc_polybezier( stringstream &s )
{
	EMRPOLYBEZIER	rec;
	s.read( (char*)&rec, sizeof(EMRPOLYBEZIER));

	stringstream	data("EMR_POLYBEZIER",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) << endl;
	data << "Count:" << rec.cptl ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.17 EMR_POLYBEZIER16 Record
string	Emf::proc_polybezier16( stringstream &s )
{
	EMRPOLYBEZIER16	rec;
	s.read( (char*)&rec, sizeof(EMRPOLYBEZIER16));

	stringstream	data("EMR_POLYBEZIER16",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) << endl;
	data << "Count:" << rec.cpts ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.18 EMR_POLYBEZIERTO Record
string	Emf::proc_polybezierto( stringstream &s )
{
	EMRPOLYBEZIERTO	rec;
	s.read( (char*)&rec, sizeof(EMRPOLYBEZIERTO));

	stringstream	data("EMR_POLYBEZIERTO",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) << endl;
	data << "Count:" << rec.cptl ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.19 EMR_POLYBEZIERTO16 Record
string	Emf::proc_polybezierto16( stringstream &s )
{
	EMRPOLYBEZIERTO16	rec;
	s.read( (char*)&rec, sizeof(EMRPOLYBEZIERTO16));

	stringstream	data("EMR_POLYBEZIERTO16",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) << endl;
	data << "Count:" << rec.cpts ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.20 EMR_POLYDRAW Record
string	Emf::proc_polydraw( stringstream &s )
{
	EMRPOLYDRAW	rec;
	s.read( (char*)&rec, sizeof(EMRPOLYDRAW));

	stringstream	data("EMR_POLYDRAW",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) << endl;
	data << "Count:" << rec.cptl ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.21 EMR_POLYDRAW16 Record
string	Emf::proc_polydraw16( stringstream &s )
{
	EMRPOLYDRAW16	rec;
	s.read( (char*)&rec, sizeof(EMRPOLYDRAW16));

	stringstream	data("EMR_POLYDRAW16",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) << endl;
	data << "Count:" << rec.cpts ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.22 EMR_POLYGON Record
string	Emf::proc_polygon( stringstream &s )
{
	EMRPOLYGON	rec;
	s.read( (char*)&rec, sizeof(EMRPOLYGON));

	stringstream	data("EMR_POLYGON",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) << endl;
	data << "Count:" << rec.cptl ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.23 EMR_POLYGON16 Record
string	Emf::proc_polygon16( stringstream &s )
{
	EMRPOLYGON16	rec;
	s.read( (char*)&rec, sizeof(EMRPOLYGON16));

	stringstream	data("EMR_POLYGON16",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) << endl;
	data << "Count:" << rec.cpts ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.24 EMR_POLYLINE Record
string	Emf::proc_polyline( stringstream &s )
{
	EMRPOLYLINE	rec;
	s.read( (char*)&rec, sizeof(EMRPOLYLINE));

	stringstream	data("EMR_POLYLINE",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) << endl;
	data << "Count:" << rec.cptl ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.25 EMR_POLYLINE16 Record
string	Emf::proc_polyline16( stringstream &s )
{
	EMRPOLYLINE16	rec;
	s.read( (char*)&rec, sizeof(EMRPOLYLINE16));

	stringstream	data("EMR_POLYLINE16",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) << endl;
	data << "Count:" << rec.cpts ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.26 EMR_POLYLINETO Record
string	Emf::proc_polylineto( stringstream &s )
{
	EMRPOLYLINETO	rec;
	s.read( (char*)&rec, sizeof(EMRPOLYLINETO));

	stringstream	data("EMR_POLYLINETO",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) << endl;
	data << "Count:" << rec.cptl ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.27 EMR_POLYLINETO16 Record
string	Emf::proc_polylineto16( stringstream &s )
{
	EMRPOLYLINETO16	rec;
	s.read( (char*)&rec, sizeof(EMRPOLYLINETO16));

	stringstream	data("EMR_POLYLINETO16",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) << endl;
	data << "Count:" << rec.cpts ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.28 EMR_POLYPOLYGON Record
string	Emf::proc_polypolygon( stringstream &s )
{
	EMRPOLYPOLYGON	rec;
	s.read( (char*)&rec, sizeof(EMRPOLYPOLYGON));

	stringstream	data("EMR_POLYPOLYGON",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) << endl;
	data << "TotalPolygons:" << rec.nPolys ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.29 EMR_POLYPOLYGON16 Record
string	Emf::proc_polypolygon16( stringstream &s )
{
	EMRPOLYPOLYGON16	rec;
	s.read( (char*)&rec, sizeof(EMRPOLYPOLYGON16));

	stringstream	data("EMR_POLYPOLYGON16",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) << endl;
	data << "TotalPolygons:" << rec.nPolys ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.30 EMR_POLYPOLYLINE Record
string	Emf::proc_polypolyline( stringstream &s )
{
	EMRPOLYPOLYLINE	rec;
	s.read( (char*)&rec, sizeof(EMRPOLYPOLYLINE));

	stringstream	data("EMR_POLYPOLYLINE",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) << endl ;
	data << "TotalPolyLines:" << rec.nPolys ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.31 EMR_POLYPOLYLINE16 Record
string	Emf::proc_polypolyline16( stringstream &s )
{
	EMRPOLYPOLYLINE16	rec;
	s.read( (char*)&rec, sizeof(EMRPOLYPOLYLINE16));

	stringstream	data("EMR_POLYPOLYLINE16",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) << endl;
	data << "TotalPolyLines:" << rec.nPolys ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.32 EMR_POLYTEXTOUTA Record
string	Emf::proc_polytextouta( stringstream &s )
{
	EMRPOLYTEXTOUTA  rec;
	s.read( (char*)&rec, sizeof(EMRPOLYTEXTOUTA));

	stringstream	data("EMR_POLYTEXTOUTA",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) ; 
	// TODO

	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.33 EMR_POLYTEXTOUTW Record
string	Emf::proc_polytextoutw( stringstream &s )
{
	EMRPOLYTEXTOUTW  rec;
	s.read( (char*)&rec, sizeof(EMRPOLYTEXTOUTW));

	stringstream	data("EMR_POLYTEXTOUTW",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) ;
	// TODO

	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.34 EMR_RECTANGLE Record
string	Emf::proc_rectangle( stringstream &s )
{
	EMRRECTANGLE  rec;
	s.read( (char*)&rec, sizeof(EMRRECTANGLE));

	stringstream	data("EMR_RECTANGLE",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBox ) ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.35 EMR_ROUNDRECT Record
string	Emf::proc_roundrect( stringstream &s )
{
	EMRROUNDRECT  rec;
	s.read( (char*)&rec, sizeof(EMRROUNDRECT));

	stringstream	data("EMR_ROUNDRECT",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBox ) << endl;
	data << format_object( rec.szlCorner ) ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.36 EMR_SETPIXELV Record
string	Emf::proc_setpixelv( stringstream &s )
{
	EMRSETPIXELV  rec;
	s.read( (char*)&rec, sizeof(EMRSETPIXELV));

	stringstream	data("EMR_SETPIXELV",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.ptlPixel ) << endl ;
	data << format_object( rec.crColor ) ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.37 EMR_SMALLTEXTOUT Record
string	Emf::proc_smalltextout( stringstream &s )
{
	EMRSMALLTEXTOUT  rec;	// EMR_RESERVED_108 で未定義なので、自前で定義.
	s.read( (char*)&rec, sizeof(EMRSMALLTEXTOUT));

	stringstream	data("EMR_SMALLTEXTOUT",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;

//	data << format_object( rec.rclBounds ) << endl ;
	data << "GraphicsMode:" ;
	switch( rec.iGraphicsMode )
	{
	case GM_COMPATIBLE:	data << " GM_COMPATIBLE" ;	break;
	case GM_ADVANCED:	data << " GM_ADVANCED" ;	break;
	}
	data << endl ;
	data << "exScale:" << rec.exScale << endl ;
	data << "eyScale:" << rec.eyScale << endl ;

	// fuOptions
	/*
ETO_OPAQUE = 0x00000002,
ETO_CLIPPED = 0x00000004,
ETO_GLYPH_INDEX = 0x00000010,
ETO_RTLREADING = 0x00000080,
ETO_NO_RECT = 0x00000100,
ETO_SMALL_CHARS = 0x00000200,
ETO_NUMERICSLOCAL = 0x00000400,
ETO_NUMERICSLATIN = 0x00000800,
ETO_IGNORELANGUAGE = 0x00001000,
ETO_PDY = 0x00002000,
ETO_REVERSE_INDEX_MAP = 0x00010000
*/

	// string is UTF16-LE
	if( rec.cChars > 0 )
	{
		int size = rec.cChars ;


		string	name( size+1, NULL );
		s.read( (char*)name.c_str(), size );
//		TRACE("%s\n",name.c_str());
		data << "Text(" << size << "):" << name.c_str() << endl ;
		data << "Dump:" << dump( (char*)name.c_str(), size ); 

/*

		wstring	name( size+1, NULL );
		s.read( (char*)name.c_str(), size );
		TRACE("%s\n",CW2A(name.c_str()));
		data << "Text(" << size << "):" << CW2A(name.c_str()) << endl ;
//		data << "Dump:" << dump( string(CW2A(name.c_str()))); 
		data << "Dump:" << dump( (char*)name.c_str(), size ); 
*/
//		char	*p = new char [ size ];
//		wstring	b(p,size);
//		b = CW2A(b.c_str());
//		s.read( p, size );
//		data << "str:" << dump( p, size );
//		delete [] p ;
		
	}
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.38 EMR_STROKEANDFILLPATH Record
string	Emf::proc_strokeandfillpath( stringstream &s )
{
	EMRSTROKEANDFILLPATH	rec ;
	s.read( (char*)&rec, sizeof(EMRSTROKEANDFILLPATH));

	stringstream	data("EMR_STROKEANDFILLPATH",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds );
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.5.39 EMR_STROKEPATH Record
string	Emf::proc_strokepath( stringstream &s )
{
	EMRSTROKEPATH	rec ;
	s.read( (char*)&rec, sizeof(EMRSTROKEPATH));

	stringstream	data("EMR_STROKEPATH",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds );
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.6 Escape record types

// 2.3.6.1 EMR_DRAWESCAPE Record
string	Emf::proc_drawescape( stringstream &s )
{
	// EMRDRAWESCAPE
	stringstream	data("EMR_DRAWESCAPE",ios_base::ate | ios_base::app | ios_base::out );
	return data.str() ;
}

// 2.3.6.2 EMR_EXTESCAPE Record
string	Emf::proc_extescape( stringstream &s )
{
	EMREXTESCAPE	rec ;
	s.read( (char*)&rec, sizeof(EMREXTESCAPE));

	stringstream	data("EMR_EXTESCAPE",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << "Esc:" ;
	switch( rec.cbEscData )
	{
	case EMR_COMMENT_WINDOWS_METAFILE:		data << "EMR_COMMENT_WINDOWS_METAFILE" ;	break;
	case EMR_COMMENT_BEGINGROUP:			data << "EMR_COMMENT_BEGINGROUP" ;			break;
	case EMR_COMMENT_ENDGROUP:				data << "EMR_COMMENT_ENDGROUP" ;			break;
	case EMR_COMMENT_MULTIFORMATS:			data << "EMR_COMMENT_MULTIFORMATS" ;		break;
	case EMR_COMMENT_UNICODE_STRING:		data << "EMR_COMMENT_UNICODE_STRING" ;		break;
	case EMR_COMMENT_UNICODE_END:			data << "EMR_COMMENT_UNICODE_END" ;			break;
	default:		data << hex << setfill('0') << setw(8) << rec.cbEscData ;			break;
	}
	data << " Size:" << rec.cbEscData ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.6.3 EMR_NAMEDESCAPE Record
string	Emf::proc_namedescape( stringstream &s )
{
	// EMRNAMEDESCAPE
	stringstream	data("EMR_NAMEDESCAPE",ios_base::ate | ios_base::app | ios_base::out );
	return data.str() ;
}

// 2.3.7 object creation record types
//   @@TODO:パラメタが多いので、後回し.

// 2.3.7.1 EMR_CREATEBRUSHINDIRECT Record
string	Emf::proc_createbrushindirect( stringstream &s )
{
	// EMRCREATEBRUSHINDIRECT
	stringstream	data("EMR_CREATEBRUSHINDIRECT",ios_base::ate | ios_base::app | ios_base::out );
	return data.str() ;
}

// 2.3.7.2 EMR_CREATECOLORSPACE Record
string	Emf::proc_createcolorspace( stringstream &s )
{
	// EMRCREATECOLORSPACE
	stringstream	data("EMR_CREATECOLORSPACE",ios_base::ate | ios_base::app | ios_base::out );
	return data.str() ;
}

// 2.3.7.3 EMR_CREATECOLORSPACEW Record
string	Emf::proc_createcolorspacew( stringstream &s )
{
	// EMRCREATECOLORSPACE
	stringstream	data("EMR_CREATECOLORSPACEW",ios_base::ate | ios_base::app | ios_base::out );
	return data.str() ;
}

// 2.3.7.4 EMR_CREATEDIBPATTERNBRUSHPT Record
string	Emf::proc_createdibpatternbrushpt( stringstream &s )
{
	// EMRCREATEDIBPATTERNBRUSHPT
	stringstream	data("EMR_CREATEDIBPATTERNBRUSHPT",ios_base::ate | ios_base::app | ios_base::out );
	return data.str() ;
}

// 2.3.7.5 EMR_CREATEMONOBRUSH Record
string	Emf::proc_createmonobrush( stringstream &s )
{
	// EMRCREATEMONOBRUSH

	stringstream	data("EMR_CREATEMONOBRUSH",ios_base::ate | ios_base::app | ios_base::out );

	return data.str() ;
}

// 2.3.7.6 EMR_CREATEPALETTE Record
string	Emf::proc_createpalette( stringstream &s )
{
	stringstream	data("EMR_CREATEPALETTE",ios_base::ate | ios_base::app | ios_base::out );

	// EMRCREATEPALETTE
	// 省略.

	return data.str() ;
}

// 2.3.7.7 EMR_CREATEPEN Record
string	Emf::proc_createpen( stringstream &s )
{
	EMRCREATEPEN	rec ;
	s.read( (char*)&rec, sizeof(EMRCREATEPEN));

	stringstream	data("EMR_CREATEPEN",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	switch( rec.lopn.lopnStyle )
	{
//	case PS_COSMETIC:		data << "PS_COSMETIC" ;			break;
//	case PS_ENDCAP_ROUND:	data << "PS_ENDCAP_ROUND" ;		break;
//	case PS_JOIN_ROUND:		data << "PS_JOIN_ROUND" ;		break;
	case PS_SOLID:			data << "PS_SOLID" ;			break;
	case PS_DASH:			data << "PS_DASH" ;				break;
	case PS_DOT:			data << "PS_DOT" ;				break;
	case PS_DASHDOT:		data << "PS_DASHDOT" ;			break;
	case PS_DASHDOTDOT:		data << "PS_DASHDOTDOT" ;		break;
	case NULL_PEN:			data << "NULL_PEn" ;			break;
	case PS_NULL:			data << "PS_NULL" ;				break;
	case PS_INSIDEFRAME:	data << "PS_INSIDEFRAME" ;		break;
	case PS_USERSTYLE:		data << "PS_USERSTYLE" ;		break;
//	case PS_ALTERNATE:		data << "PS_ALTERNATE" ;		break;
	case PS_ENDCAP_SQUARE:	data << "PS_ENDCAP_SQUARE" ;	break;
	case PS_ENDCAP_FLAT:	data << "PS_ENDCAP_FLAT" ;		break;
	case PS_JOIN_BEVEL:		data << "PS_JOIN_BEVEL" ;		break;
	case PS_JOIN_MITER:		data << "PS_JOIN_MITER" ;		break;
	case PS_GEOMETRIC:		data << "PS_GEOMETRIC" ;		break;
	}
	data << " Width:" << rec.lopn.lopnWidth.x ;
	data << format_object( rec.lopn.lopnColor ) ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.7.8 EMR_EXTCREATEFONTINDIRECTW Record
string	Emf::proc_extcreatefontindirectw( stringstream &s )
{
	EMREXTCREATEFONTINDIRECTW	rec ;
	s.read( (char*)&rec, sizeof(EMREXTCREATEFONTINDIRECTW));

	stringstream	data("EMR_EXTCREATEFONTINDIRECTW",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << "Index:" << rec.ihFont << "(TODO)";
	// 省略.

	data << END_PARAM ;

	return data.str() ;
}

// 2.3.7.9 EMR_EXTCREATEPEN Record
string	Emf::proc_extcreatepen( stringstream &s )
{
	EMREXTCREATEPEN	rec ;
	s.read( (char*)&rec, sizeof(EMREXTCREATEPEN));

	stringstream	data("EMR_EXTCREATEPEN",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << "Index:" << rec.ihPen ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.8 object manipulation record types

// 2.3.8.1 EMR_COLORCORRECTPALETTE Record
string	Emf::proc_colorcorrectpalette( stringstream &s )
{
	EMRCOLORCORRECTPALETTE	rec ;
	s.read( (char*)&rec, sizeof(EMRCOLORCORRECTPALETTE));

	stringstream	data("EMR_COLORCORRECTPALETTE",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << "Index:" << rec.ihPalette ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.8.2 EMR_DELETECOLORSPACE Record
string	Emf::proc_deletecolorspace( stringstream &s )
{
	EMRDELETECOLORSPACE	rec ;
	s.read( (char*)&rec, sizeof(EMRDELETECOLORSPACE));

	stringstream	data("EMR_DELETECOLORSPACE",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << "Index:" << rec.ihCS ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.8.3 EMR_DELETEOBJECT Record
string	Emf::proc_deleteobject( stringstream &s )
{
	EMRDELETEOBJECT	rec ;
	s.read( (char*)&rec, sizeof(EMRDELETEOBJECT));

	stringstream	data("EMR_DELETEOBJECT",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	switch( rec.ihObject )
	{
	case WHITE_BRUSH:			data << "WHITE_BRUSh" ;			break;
	case LTGRAY_BRUSH:			data << "LTGRAY_BRUSh" ;		break;
	case GRAY_BRUSH:			data << "GRAY_BRUSh" ;			break;
	case DKGRAY_BRUSH:			data << "DKGRAY_BRUSh" ;		break;
	case BLACK_BRUSH:			data << "BLACK_BRUSh" ;			break;
	case NULL_BRUSH:			data << "NULL_BRUSh" ;			break;
	case WHITE_PEN:				data << "WHITE_PEn" ;			break;
	case BLACK_PEN:				data << "BLACK_PEn" ;			break;
	case NULL_PEN:				data << "NULL_PEn" ;			break;
	case OEM_FIXED_FONT:		data << "OEM_FIXED_FONt" ;		break;
	case ANSI_FIXED_FONT:		data << "ANSI_FIXED_FONt" ;		break;
	case ANSI_VAR_FONT:			data << "ANSI_VAR_FONt" ;		break;
	case SYSTEM_FONT:			data << "SYSTEM_FONt" ;			break;
	case DEVICE_DEFAULT_FONT:	data << "DEVICE_DEFAULT_FONt" ;	break;
	case DEFAULT_PALETTE:		data << "DEFAULT_PALETTe" ;		break;
	case SYSTEM_FIXED_FONT:		data << "SYSTEM_FIXED_FONt" ;	break;
	case DEFAULT_GUI_FONT:		data << "DEFAULT_GUI_FONt" ;	break;
	case DC_BRUSH:				data << "DC_BRUSh" ;			break;
	case DC_PEN:				data << "DC_PEn" ;				break;
		// EMF仕様の定義.
	case 0x80000000:			data << "WHITE_BRUSH" ;			break;
	case 0x80000001:			data << "LTGRAY_BRUSH" ;		break;
	case 0x80000002:			data << "GRAY_BRUSH" ;			break;
	case 0x80000003:			data << "DKGRAY_BRUSH" ;		break;
	case 0x80000004:			data << "BLACK_BRUSH" ;			break;
	case 0x80000005:			data << "NULL_BRUSH" ;			break;
	case 0x80000006:			data << "WHITE_PEN" ;			break;
	case 0x80000007:			data << "BLACK_PEN" ;			break;
	case 0x80000008:			data << "NULL_PEN" ;			break;
	case 0x8000000A:			data << "OEM_FIXED_FONT" ;		break;
	case 0x8000000B:			data << "ANSI_FIXED_FONT" ;		break;
	case 0x8000000C:			data << "ANSI_VAR_FONT" ;		break;
	case 0x8000000D:			data << "SYSTEM_FONT" ;			break;
	case 0x8000000E:			data << "DEVICE_DEFAULT_FONT" ;	break;
	case 0x8000000F:			data << "DEFAULT_PALETTE" ;		break;
	case 0x80000010:			data << "SYSTEM_FIXED_FONT" ;	break;
	case 0x80000011:			data << "DEFAULT_GUI_FONT" ;	break;
	case 0x80000012:			data << "DC_BRUSH" ;			break;
	case 0x80000013:			data << "DC_PEN" ;				break;
	default:					data << "unknown:" << setbase(16) << setfill('0') << setw(8) << rec.ihObject ;	break;
	}
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.8.4 EMR_RESIZEPALETTE Record
string	Emf::proc_resizepalette( stringstream &s )
{
	EMRRESIZEPALETTE	rec ;
	s.read( (char*)&rec, sizeof(EMRRESIZEPALETTE));

	stringstream	data("EMR_RESIZEPALETTE",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << "Index:" << rec.ihPal ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.8.5 EMR_SELECTOBJECT Record
string	Emf::proc_selectobject( stringstream &s )
{
	EMRSELECTOBJECT	rec ;
	s.read( (char*)&rec, sizeof(EMRSELECTOBJECT));

	stringstream	data("EMR_SELECTOBJECT",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	switch( rec.ihObject )
	{
	case WHITE_BRUSH:			data << "WHITE_BRUSh" ;			break;
	case LTGRAY_BRUSH:			data << "LTGRAY_BRUSh" ;		break;
	case GRAY_BRUSH:			data << "GRAY_BRUSh" ;			break;
	case DKGRAY_BRUSH:			data << "DKGRAY_BRUSh" ;		break;
	case BLACK_BRUSH:			data << "BLACK_BRUSh" ;			break;
	case NULL_BRUSH:			data << "NULL_BRUSh" ;			break;
	case WHITE_PEN:				data << "WHITE_PEn" ;			break;
	case BLACK_PEN:				data << "BLACK_PEn" ;			break;
	case NULL_PEN:				data << "NULL_PEn" ;			break;
	case OEM_FIXED_FONT:		data << "OEM_FIXED_FONt" ;		break;
	case ANSI_FIXED_FONT:		data << "ANSI_FIXED_FONt" ;		break;
	case ANSI_VAR_FONT:			data << "ANSI_VAR_FONt" ;		break;
	case SYSTEM_FONT:			data << "SYSTEM_FONt" ;			break;
	case DEVICE_DEFAULT_FONT:	data << "DEVICE_DEFAULT_FONt" ;	break;
	case DEFAULT_PALETTE:		data << "DEFAULT_PALETTe" ;		break;
	case SYSTEM_FIXED_FONT:		data << "SYSTEM_FIXED_FONt" ;	break;
	case DEFAULT_GUI_FONT:		data << "DEFAULT_GUI_FONt" ;	break;
	case DC_BRUSH:				data << "DC_BRUSh" ;			break;
	case DC_PEN:				data << "DC_PEn" ;				break;
		// EMF仕様の定義.
	case 0x80000000:			data << "WHITE_BRUSH" ;			break;
	case 0x80000001:			data << "LTGRAY_BRUSH" ;		break;
	case 0x80000002:			data << "GRAY_BRUSH" ;			break;
	case 0x80000003:			data << "DKGRAY_BRUSH" ;		break;
	case 0x80000004:			data << "BLACK_BRUSH" ;			break;
	case 0x80000005:			data << "NULL_BRUSH" ;			break;
	case 0x80000006:			data << "WHITE_PEN" ;			break;
	case 0x80000007:			data << "BLACK_PEN" ;			break;
	case 0x80000008:			data << "NULL_PEN" ;			break;
	case 0x8000000A:			data << "OEM_FIXED_FONT" ;		break;
	case 0x8000000B:			data << "ANSI_FIXED_FONT" ;		break;
	case 0x8000000C:			data << "ANSI_VAR_FONT" ;		break;
	case 0x8000000D:			data << "SYSTEM_FONT" ;			break;
	case 0x8000000E:			data << "DEVICE_DEFAULT_FONT" ;	break;
	case 0x8000000F:			data << "DEFAULT_PALETTE" ;		break;
	case 0x80000010:			data << "SYSTEM_FIXED_FONT" ;	break;
	case 0x80000011:			data << "DEFAULT_GUI_FONT" ;	break;
	case 0x80000012:			data << "DC_BRUSH" ;			break;
	case 0x80000013:			data << "DC_PEN" ;				break;
	default:					data << "unknown:" << setbase(16) << setfill('0') << setw(8) << rec.ihObject ;	break;
	}
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.8.6 EMR_SELECTPALETTE Record
string	Emf::proc_selectpalette( stringstream &s )
{
	EMRSELECTPALETTE	rec ;
	s.read( (char*)&rec, sizeof(EMRSELECTPALETTE));

	stringstream	data("EMR_SELECTPALETTE",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << "Index:" << rec.ihPal ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.8.7 EMR_SETCOLORSPACE Record
string	Emf::proc_setcolorspace( stringstream &s )
{
	EMRSETCOLORSPACE	rec ;
	s.read( (char*)&rec, sizeof(EMRSETCOLORSPACE));

	stringstream	data("EMR_SETCOLORSPACE",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << "Index:" << rec.ihCS ;
	data << END_PARAM ;
	return data.str() ;
}

// 2.3.8.8 EMR_SETPALETTEENTRIES Record
string	Emf::proc_setpaletteentries( stringstream &s )
{
	EMRSETPALETTEENTRIES   rec;
	s.read( (char*)&rec, sizeof(EMRSETPALETTEENTRIES));

	stringstream	data("EMR_SETPALETTEENTRIES",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << "EntryNum:" << rec.cEntries ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.9 opengl record types

// 2.3.9.1 EMR_GLSBOUNDEDRECORD Record
string	Emf::proc_glsboundedrecord( stringstream &s )
{
	EMRGLSBOUNDEDRECORD	rec ;
	s.read( (char*)&rec, sizeof(EMRGLSBOUNDEDRECORD));

	stringstream	data("EMR_GLSBOUNDEDRECORD",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) << endl;
	data << "Size:" << rec.cbData ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.9.2 EMR_GLSRECORD Record
string	Emf::proc_glsrecord( stringstream &s )
{
	EMRGLSRECORD	rec ;
	s.read( (char*)&rec, sizeof(EMRGLSRECORD));

	stringstream	data("EMR_GLSRECORD",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << "Size:" << rec.cbData ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.10 path bracket record types
string	Emf::proc_abortpath( stringstream &s )
{
	stringstream	data("EMR_ABORTPATH",ios_base::ate | ios_base::app | ios_base::out );
	return data.str() ;
}
string	Emf::proc_beginpath( stringstream &s )
{
	stringstream	data("EMR_BEGINPATH",ios_base::ate | ios_base::app | ios_base::out );
	return data.str() ;
}
string	Emf::proc_closefigure( stringstream &s )
{
	stringstream	data("EMR_CLOSEFIGURE",ios_base::ate | ios_base::app | ios_base::out );
	return data.str() ;
}
string	Emf::proc_endpath( stringstream &s )
{
	stringstream	data("EMR_ENDPATH",ios_base::ate | ios_base::app | ios_base::out );
	return data.str() ;
}
string	Emf::proc_flattenpath( stringstream &s )
{
	stringstream	data("EMR_FLATTENPATH",ios_base::ate | ios_base::app | ios_base::out );
	return data.str() ;
}
string	Emf::proc_widenpath( stringstream &s )
{
	stringstream	data("EMR_WIDENPATH",ios_base::ate | ios_base::app | ios_base::out );
	return data.str() ;
}

// 2.3.11 state record types

// 2.3.11.1 EMR_COLORMATCHTOTARGETW Record
string	Emf::proc_colormatchtotargetw( stringstream &s )
{
	EMRCOLORMATCHTOTARGET	rec ;
	s.read( (char*)&rec, sizeof(EMRCOLORMATCHTOTARGET));

	stringstream	data("EMR_COLORMATCHTOTARGETW",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << "Action:" << rec.dwAction ;
	// TODO

	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11.2 EMR_FORCEUFIMAPPING Record
string	Emf::proc_forceufimapping( stringstream &s )
{
	EMRFORCEUFIMAPPING	rec ;
	s.read( (char*)&rec, sizeof(EMRFORCEUFIMAPPING));

	stringstream	data("EMR_FORCEUFIMAPPING",ios_base::ate | ios_base::app | ios_base::out );

	// TODO
	/*
	data << BEGIN_PARAM ;

	ULONG	tmp ;
	s.read( (char*)&tmp, sizeof(ULONG));
	data << "Action:" << tmp ;

	// 省略.

	data << END_PARAM ;
	*/

	return data.str() ;
}

// 2.3.11.3 EMR_INVERTRGN Record
string	Emf::proc_invertrgn( stringstream &s )
{
	EMRINVERTRGN	rec ;
	s.read( (char*)&rec, sizeof(EMRINVERTRGN));

	stringstream	data("EMR_INVERTRGN",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.rclBounds ) << endl;
	data << "Size:" << rec.cbRgnData ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11.4 EMR_MOVETOEX Record
string	Emf::proc_movetoex( stringstream &s )
{
	// 
	EMRMOVETOEX	rec ;
	s.read( (char*)&rec, sizeof(EMRMOVETOEX));

	stringstream	data("EMR_MOVETOEX",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.ptl ) ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11.5 EMR_PIXELFORMAT Record
string	Emf::proc_pixelformat( stringstream &s )
{
	EMRPIXELFORMAT	rec ;
	s.read( (char*)&rec, sizeof(EMRPIXELFORMAT));

	stringstream	data("EMR_PIXELFORMAT",ios_base::ate | ios_base::app | ios_base::out );

	// TODO.

	return data.str() ;
}

// 2.3.11 EMR_REALIZEPALETTE Record
string	Emf::proc_realizepalette( stringstream &s )
{
	// EMRREALIZEPALETTE <- ?

	stringstream	data("EMR_REALIZEPALETTE",ios_base::ate | ios_base::app | ios_base::out );

	return data.str() ;
}

// 2.3.11.6 EMR_RESTOREDC Record
string	Emf::proc_restoredc( stringstream &s )
{
	EMRRESTOREDC    rec;
	s.read( (char*)&rec, sizeof(EMRRESTOREDC));

	stringstream	data("EMR_RESTOREDC",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << "State:" << rec.iRelative ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11 (=2.3.11.6 EMR_RESTOREDC) EMR_SAVEDC Record
string	Emf::proc_savedc( stringstream &s )
{
	EMRRESTOREDC    rec;	// EMRSAVEDC  <- ?
	s.read( (char*)&rec, sizeof(EMRRESTOREDC));

	stringstream	data("EMR_SAVEDC",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << "State:" << rec.iRelative ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11.7 EMR_SCALEVIEWPORTEXTEX Record
string	Emf::proc_scaleviewportextex( stringstream &s )
{
	EMRSCALEVIEWPORTEXTEX    rec;
	s.read( (char*)&rec, sizeof(EMRSCALEVIEWPORTEXTEX));

	stringstream	data("EMR_SCALEVIEWPORTEXTEX",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << "xNum:" << rec.xNum << " xDenom:" << rec.xDenom << " yNum:" << rec.yNum << " yDenom:" << rec.yDenom ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11.8 EMR_SCALEWINDOWEXTEX Record
string	Emf::proc_scalewindowextex( stringstream &s )
{
	// 
	EMRSCALEWINDOWEXTEX    rec;
	s.read( (char*)&rec, sizeof(EMRSCALEWINDOWEXTEX));

	stringstream	data("EMR_SCALEWINDOWEXTEX",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << "xNum:" << rec.xNum << " xDenom:" << rec.xDenom << " yNum:" << rec.yNum << " yDenom:" << rec.yDenom ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11.9 EMR_SETARCDIRECTION Record
string	Emf::proc_setarcdirection( stringstream &s )
{
	EMRSETARCDIRECTION	rec ;
	s.read( (char*)&rec, sizeof(EMRSETARCDIRECTION));

	stringstream	data("EMR_SETARCDIRECTION",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	switch( rec.iArcDirection )
	{
	case AD_COUNTERCLOCKWISE:	data << "AD_COUNTERCLOCKWISE" ;		break;
	case AD_CLOCKWISE:			data << "AD_CLOCKWISE" ;			break;
	}
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11.10 EMR_SETBKCOLOR Record
string	Emf::proc_setbkcolor( stringstream &s )
{
	EMRSETBKCOLOR	rec ;
	s.read( (char*)&rec, sizeof(EMRSETBKCOLOR));

	stringstream	data("EMR_SETBKCOLOR",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.crColor ) ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11.11 EMR_SETBKMODE Record
string	Emf::proc_setbkmode( stringstream &s )
{
	EMRSETBKMODE	rec ;
	s.read( (char*)&rec, sizeof(EMRSETBKMODE));

	stringstream	data("EMR_SETBKMODE",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	switch( rec.iMode )
	{
	case TRANSPARENT:	data << "TRANSPARENT" ;		break;
	case OPAQUE:		data << "OPAQUE" ;			break;
	}
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11.12 EMR_SETBRUSHORGEX Record
string	Emf::proc_setbrushorgex( stringstream &s )
{
	EMRSETBRUSHORGEX	rec ;
	s.read( (char*)&rec, sizeof(EMRSETBRUSHORGEX));

	stringstream	data("EMR_SETBRUSHORGEX",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.ptlOrigin ) ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11.13 EMR_SETCOLORADJUSTMENT Record
string	Emf::proc_setcoloradjustment( stringstream &s )
{
	EMRSETCOLORADJUSTMENT	rec ;
	s.read( (char*)&rec, sizeof(EMRSETCOLORADJUSTMENT));

	stringstream	data("EMR_SETCOLORADJUSTMENT",ios_base::ate | ios_base::app | ios_base::out );
	// 省略.

	return data.str() ;
}

// 2.3.11.14 EMR_SETICMMODE Record
string	Emf::proc_seticmmode( stringstream &s )
{
	EMRSETICMMODE	rec ;
	s.read( (char*)&rec, sizeof(EMRSETICMMODE));

	stringstream	data("EMR_SETICMMODE",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	switch( rec.iMode )
	{
	case ICM_OFF:				data << "ICM_OFF" ;				break;
	case ICM_ON:				data << "ICM_ON" ;				break;
	case ICM_QUERY:				data << "ICM_QUERY" ;			break;
	case ICM_DONE_OUTSIDEDC:	data << "ICM_DONE_OUTSIDEDC" ;	break;
	}
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11.15 EMR_SETICMPROFILEA Record
string	Emf::proc_seticmprofilea( stringstream &s )
{
	// EMRSETICMPROFILEA

	stringstream	data("EMR_SETICMPROFILEA",ios_base::ate | ios_base::app | ios_base::out );

	return data.str() ;
}

// 2.3.11.16 EMR_SETICMPROFILEW Record
string	Emf::proc_seticmprofilew( stringstream &s )
{
	// EMRSETICMPROFILEW

	// TODO:
	
	stringstream	data("EMR_SETICMPROFILEW",ios_base::ate | ios_base::app | ios_base::out );

	return data.str() ;
}

// 2.3.11.17 EMR_SETLAYOUT Record
string	Emf::proc_setlayout( stringstream &s )
{
	EMRSETLAYOUT	rec ;
	s.read( (char*)&rec, sizeof(EMRSETLAYOUT));

	stringstream	data("EMR_SETLAYOUT",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	switch( rec.iMode )
	{
	case LAYOUT_LTR:		data << "LAYOUT_LTR" ;		break;
	case LAYOUT_RTL:		data << "LAYOUT_RTL" ;		break;
	case LAYOUT_BITMAPORIENTATIONPRESERVED:	data << "LAYOUT_BITMAPORIENTATIONPRESERVED" ;	break;
	}
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11.18 EMR_SETLINKEDUFIS Record
string	Emf::proc_setlinkedufis( stringstream &s )
{
	SETLINKEDUFIS	rec ;
	s.read( (char*)&rec, sizeof(SETLINKEDUFIS));

	stringstream	data("EMR_SETLINKEDUFIS",ios_base::ate | ios_base::app | ios_base::out );

	// TODO
	/*
	data << BEGIN_PARAM ;

	ULONG	tmp ;
	s.read( (char*)&tmp, sizeof(ULONG));

	switch( tmp )
	{
	case LAYOUT_LTR:		data << "LAYOUT_LTR" ;		break;
	case LAYOUT_RTL:		data << "LAYOUT_RTL" ;		break;
	case LAYOUT_BITMAPORIENTATIONPRESERVED:	data << "LAYOUT_BITMAPORIENTATIONPRESERVED" ;	break;
	}

	data << END_PARAM ;
	*/

	return data.str() ;
}

// 2.3.11.19 EMR_SETMAPMODE Record
string	Emf::proc_setmapmode( stringstream &s )
{
	EMRSETMAPMODE	rec ;
	s.read( (char*)&rec, sizeof(EMRSETMAPMODE));

	stringstream	data("EMR_SETMAPMODE",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	switch( rec.iMode )
	{
	case MM_TEXT:			data << "MM_TEXT" ;			break;
	case MM_LOMETRIC:		data << "MM_LOMETRIC" ;		break;
	case MM_HIMETRIC:		data << "MM_HIMETRIC" ;		break;
	case MM_LOENGLISH:		data << "MM_LOENGLISH" ;	break;
	case MM_HIENGLISH:		data << "MM_HIENGLISH" ;	break;
	case MM_TWIPS:			data << "MM_TWIPS" ;		break;
	case MM_ISOTROPIC:		data << "MM_ISOTROPIC" ;	break;
	case MM_ANISOTROPIC:	data << "MM_ANISOTROPIC" ;	break;
	}
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11.20 EMR_SETMAPPERFLAGS Record
string	Emf::proc_setmapperflags( stringstream &s )
{
	EMRSETMAPPERFLAGS	rec ;
	s.read( (char*)&rec, sizeof(EMRSETMAPPERFLAGS));

	stringstream	data("EMR_SETMAPPERFLAGS",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << "Flag:" << rec.dwFlags ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11.21 EMR_SETMITERLIMIT Record
string	Emf::proc_setmiterlimit( stringstream &s )
{
	EMRSETMITERLIMIT	rec ;
	s.read( (char*)&rec, sizeof(EMRSETMITERLIMIT));

	stringstream	data("EMR_SETMITERLIMIT",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << "MiterLimit:" << rec.eMiterLimit ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11.22 EMR_SETPOLYFILLMODE Record
string	Emf::proc_setpolyfillmode( stringstream &s )
{
	EMRSETPOLYFILLMODE	rec ;
	s.read( (char*)&rec, sizeof(EMRSETPOLYFILLMODE));

	stringstream	data("EMR_SETPOLYFILLMODE",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	switch( rec.iMode )
	{
	case R2_BLACK:			data << "R2_BLACK" ;		break;
	case R2_NOTMERGEPEN:	data << "R2_NOTMERGEPEN" ;	break;
	case R2_MASKNOTPEN:		data << "R2_MASKNOTPEN" ;	break;
	case R2_NOTCOPYPEN:		data << "R2_NOTCOPYPEN" ;	break;
	case R2_MASKPENNOT:		data << "R2_MASKPENNOT" ;	break;
	case R2_NOT:			data << "R2_NOT" ;			break;
	case R2_XORPEN:			data << "R2_XORPEN" ;		break;
	case R2_MASKPEN:		data << "R2_MASKPEN" ;		break;
	case R2_NOTXORPEN:		data << "R2_NOTXORPEN" ;	break;
	case R2_NOP:			data << "R2_NOP" ;			break;
	case R2_MERGENOTPEN:	data << "R2_MERGENOTPEN" ;	break;
	case R2_COPYPEN:		data << "R2_COPYPEN" ;		break;
	case R2_MERGEPENNOT:	data << "R2_MERGEPENNOT" ;	break;
	case R2_MERGEPEN:		data << "R2_MERGEPEN" ;		break;
	case R2_WHITE:			data << "R2_WHITE" ;		break;
	}
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11.23 EMR_SETROP2 Record
string	Emf::proc_setrop2( stringstream &s )
{
	EMRSETROP2	rec ;
	s.read( (char*)&rec, sizeof(EMRSETROP2));

	stringstream	data("EMR_SETROP2",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	switch( rec.iMode )
	{
	case R2_BLACK:			data << "R2_BLACK" ;		break;
	case R2_NOTMERGEPEN:	data << "R2_NOTMERGEPEN" ;	break;
	case R2_MASKNOTPEN:		data << "R2_MASKNOTPEN" ;	break;
	case R2_NOTCOPYPEN:		data << "R2_NOTCOPYPEN" ;	break;
	case R2_MASKPENNOT:		data << "R2_MASKPENNOT" ;	break;
	case R2_NOT:			data << "R2_NOT" ;			break;
	case R2_XORPEN:			data << "R2_XORPEN" ;		break;
	case R2_MASKPEN:		data << "R2_MASKPEN" ;		break;
	case R2_NOTXORPEN:		data << "R2_NOTXORPEN" ;	break;
	case R2_NOP:			data << "R2_NOP" ;			break;
	case R2_MERGENOTPEN:	data << "R2_MERGENOTPEN" ;	break;
	case R2_COPYPEN:		data << "R2_COPYPEN" ;		break;
	case R2_MERGEPENNOT:	data << "R2_MERGEPENNOT" ;	break;
	case R2_MERGEPEN:		data << "R2_MERGEPEN" ;		break;
	case R2_WHITE:			data << "R2_WHITE" ;		break;
	}
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11.24 EMR_SETSTRETCHBLTMODE Record
string	Emf::proc_setstretchbltmode( stringstream &s )
{
	EMRSETSTRETCHBLTMODE	rec ;
	s.read( (char*)&rec, sizeof(EMRSETSTRETCHBLTMODE));

	stringstream	data("EMR_SETSTRETCHBLTMODE",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	switch( rec.iMode )
	{
	case STRETCH_ANDSCANS:		data << "STRETCH_ANDSCANS" ;	break;
	case STRETCH_ORSCANS:		data << "STRETCH_ORSCANS" ;		break;
	case STRETCH_DELETESCANS:	data << "STRETCH_DELETESCANS" ;	break;
	case STRETCH_HALFTONE:		data << "STRETCH_HALFTONE" ;	break;
	}
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11.25 EMR_SETTEXTALIGN Record
string	Emf::proc_settextalign( stringstream &s )
{
	EMRSETTEXTALIGN	rec ;
	s.read( (char*)&rec, sizeof(EMRSETTEXTALIGN));

	stringstream	data("EMR_SETTEXTALIGN",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	switch( rec.iMode )
	{
//	case TA_NOUPDATECP:		data << "TA_NOUPDATECP" ;	break;
//	case TA_LEFT:			data << "TA_LEFT" ;			break;
	case TA_TOP:			data << "TA_TOP" ;			break;
	case TA_UPDATECP:		data << "TA_UPDATECP" ;		break;
	case TA_RIGHT:			data << "TA_RIGHT" ;		break;
	case TA_CENTER:			data << "TA_CENTER" ;		break;
	case TA_BOTTOM:			data << "TA_BOTTOM" ;		break;
	case TA_BASELINE:		data << "TA_BASELINE" ;		break;
	case TA_RTLREADING:		data << "TA_RTLREADING" ;	break;
	}
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11.26 EMR_SETTEXTCOLOR Record
string	Emf::proc_settextcolor( stringstream &s )
{
	EMRSETTEXTCOLOR	rec ;
	s.read( (char*)&rec, sizeof(EMRSETTEXTCOLOR));

	stringstream	data("EMR_SETTEXTCOLOR",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.crColor ) ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11.27 EMR_SETTEXTJUSTIFICATION Record
string	Emf::proc_settextjustification( stringstream &s )
{
	stringstream	data("EMR_SETTEXTJUSTIFICATION",ios_base::ate | ios_base::app | ios_base::out );

	// TODO
/*
	data << BEGIN_PARAM ;

	COLORREF	col ;
	s.read( (char*)&col, sizeof(COLORREF));
	data << "RGB(" ;
	data << setbase(16) << setfill('0') << setw(2) << (int)GetRValue(col) << "," << (int)GetGValue(col) << "," << (int)GetBValue(col) << ")" ;

	data << END_PARAM ;
*/

	return data.str() ;
}

// 2.3.11.28 EMR_SETVIEWPORTEXTEX Record
string	Emf::proc_setviewportextex( stringstream &s )
{
	EMRSETVIEWPORTEXTEX	rec ;
	s.read( (char*)&rec, sizeof(EMRSETVIEWPORTEXTEX));

	stringstream	data("EMR_SETVIEWPORTEXTEX",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.szlExtent ) ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11.29 EMR_SETVIEWPORTORGEX Record
string	Emf::proc_setviewportorgex( stringstream &s )
{
	EMRSETVIEWPORTORGEX	rec ;
	s.read( (char*)&rec, sizeof(EMRSETVIEWPORTORGEX));

	stringstream	data("EMR_SETVIEWPORTORGEX",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.ptlOrigin ) ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11.30 EMR_SETWINDOWEXTEX Record
string	Emf::proc_setwindowextex( stringstream &s )
{
	EMRSETWINDOWEXTEX	rec ;
	s.read( (char*)&rec, sizeof(EMRSETWINDOWEXTEX));

	stringstream	data("EMR_SETWINDOWEXTEX",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.szlExtent ) ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.11.31 EMR_SETWINDOWORGEX Record
string	Emf::proc_setwindoworgex( stringstream &s )
{
	EMRSETWINDOWORGEX	rec ;
	s.read( (char*)&rec, sizeof(EMRSETWINDOWORGEX));

	stringstream	data("EMR_SETWINDOWORGEX",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	data << format_object( rec.ptlOrigin ) ;
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.12 transform record types

// 2.3.12.1 EMR_MODIFYWORLDTRANSFORM Record
string	Emf::proc_modifyworldtransform( stringstream &s )
{
	EMRMODIFYWORLDTRANSFORM	rec ;
	s.read( (char*)&rec, sizeof(EMRMODIFYWORLDTRANSFORM));

	stringstream	data("EMR_MODIFYWORLDTRANSFORM",ios_base::ate | ios_base::app | ios_base::out );
	data << BEGIN_PARAM ;
	switch( rec.iMode )
	{
	case MWT_IDENTITY:		data << "MWT_IDENTITY" ;		break;
	case MWT_LEFTMULTIPLY:	data << "MWT_LEFTMULTIPLY" ;	break;
	case MWT_RIGHTMULTIPLY:	data << "MWT_RIGHTMULTIPLY" ;	break;
	case 0x04: // MWT_SET:
	default:				data << "MWT_SET" ;				break;
	}
	data << END_PARAM ;

	return data.str() ;
}

// 2.3.12.2 EMR_SETWORLDTRANSFORM Record
string	Emf::proc_setworldtransform( stringstream &s )
{
	stringstream	data("EMR_SETWORLDTRANSFORM,",ios_base::ate | ios_base::app | ios_base::out );

	//EMRSETWORLDTRANSFORM
//	emf::XForm	form ;
//	s.read( (char*)&form, sizeof(emf::XForm));

	return data.str() ;
}

#undef	BEGIN_PARAM
#undef	END_PARAM

// 2.2 EMF Objects
//   を扱い易くする為の補助関数群.
//   EMF Object は殆ど<WinGdi.h>に定義されている.
string	Emf::format_object( POINTL &pt )
{
	stringstream	data( ios_base::ate | ios_base::app | ios_base::out );
	data << "X:" << pt.x << " Y:" << pt.y ;
	return data.str() ;
}

string	Emf::format_object( SIZEL &sz )
{
	stringstream	data( ios_base::ate | ios_base::app | ios_base::out );
	data << "CX:" << sz.cx << " CY:" << sz.cy ;
	return data.str() ;
}

string	Emf::format_object( COLORREF &col )
{
	stringstream	data( ios_base::ate | ios_base::app | ios_base::out );
	data << "RGB(" ;
	data << setbase(16) << setfill('0') << setw(2) << (int)GetRValue(col) << "," << (int)GetGValue(col) << "," << (int)GetBValue(col) << ")" ;
	return data.str() ;
}

string	Emf::format_object( RECTL &rc )
{
	stringstream	data( ios_base::ate | ios_base::app | ios_base::out );
	data << "(" << rc.left << ", " << rc.top << ", " << rc.right << ", " << rc.bottom << ") " ;
	return data.str() ;
}

string Emf::dump( string str )
{
	stringstream	data( ios_base::ate | ios_base::app | ios_base::out );
	data.clear();
	for( string::iterator it = str.begin() ; it != str.end() ; ++it )
	{
		data << setw(2) << setfill('0') << hex << uppercase << (int)(unsigned char)*it << " " ;
	}
	return data.str() ;
}
string Emf::dump( char *str, int size )
{
	stringstream	data( ios_base::ate | ios_base::app | ios_base::out );
	for( int i = 0 ; i < size ; i++ )
	{
		data << setw(2) << setfill('0') << hex << uppercase << (int)(unsigned char)str[i] << " " ;
	}
	return data.str() ;
}