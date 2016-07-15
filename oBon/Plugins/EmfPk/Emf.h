/**
 * @file Emf.h
 * @brief �ȒP�Ȑ���
 * @author �������l
 * @date ���t�i�J�n���H�j
 */
#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include    <sstream>
#include    <iomanip>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

#include	<WinGDI.h>		// EMF record types (Microsoft SDK)
#include	"emfspool_def.h"

#pragma warning(disable: 4786) 
#include <map>

using namespace std;
using namespace emf;

// ��Windows SDK ���C���X�g�[������Ă�����ł��邱��!!

class Emf
{
public:
	Emf(void);
	Emf(string &d, string f) : data(d), fnam(f) { init(); }
	Emf(string f) : fnam(f)
	{
		init();

		// fnam -> data ��ǂݍ���.
		ifstream	i(fnam.c_str(), std::ios::in | std::ios::binary) ;

		// �t�@�C���T�C�Y�̎Z�o.
		UINT eofPos = i.seekg(0, fstream::end).tellg();
		i.clear();
		UINT begPos = i.seekg(0, fstream::beg).tellg();
		UINT size = eofPos - begPos;//����-�擪�Ńt�@�C���T�C�Y���v�Z

		// �����o�b�t�@�ɓǂݍ���.
		if( i.is_open() )
		{
			char *p = new char[size];
			i.read( p, size );
			data.append( p, size );
			delete p;
		}
	}
	~Emf(void);

private:
	string	data ;	// �����f�[�^.
	string	fnam ;	// �t�@�C����(FullPath).
	string	_out_folder ;	// �o�͐�t�H���_.
	string	_name ;	// �t�@�C����(file only);

	// �t�@�C���o�͊֘A.
	ofstream	f ;
	int	write_count ;	// �t�@�C�����̏o�͍s.
	int	file_count ;	// �t�@�C���A��.
	int line_count ;	// �t�@�C�����o�͍s.

	int res_count ;		// ���\�[�X��.

	// �֐��e�[�u��.
	typedef map<int, string (Emf::*)(stringstream&)>	func_tbl ;
	func_tbl ft;

public:
	// ���
	bool	parse();

	string	out_res_name()		{	return make_out_name( "_res_"		, ".bmp", res_count ) ;	}
	string	make_out_name( string name, string ext, int &count )
	{
		stringstream	tmp ;
		tmp << _out_folder << "\\" << _name << name << setfill('0') << setw(5) << right << count << ext ;
		count++;
		return tmp.str() ;
	}

private:
	void	init();

	// ��͌��ʂ̏o��.
	bool	writeFile( string data );

	// ���m�̃��R�[�h�^�C�v.
	string	proc_unknown( stringstream &s );

	// 2.3.1 Bitmap Record Types
	string	proc_alphablend( stringstream &s );
	string	proc_bitblt( stringstream &s );
	string	proc_maskblt( stringstream &s );
	string	proc_plgblt( stringstream &s );
	string	proc_setdibitstodevice( stringstream &s );
	string	proc_stretchblt( stringstream &s );
	string	proc_stretchdibits( stringstream &s );
	string	proc_transparentblt( stringstream &s );

	// 2.3.2 clipping record types
	string	proc_excludecliprect( stringstream &s );
	string	proc_extselectcliprgn( stringstream &s );
	string	proc_intersectcliprect( stringstream &s );
	string	proc_offsetcliprgn( stringstream &s );
	string	proc_selectclippath( stringstream &s );
	string	proc_setmetargn( stringstream &s );

	// 2.3.3 Comment record types
	string	proc_comment( stringstream &s );

	// 2.3.4 control record types
	string	proc_eof( stringstream &s );
	string	proc_header( stringstream &s );

	// 2.3.5 drawing record types
	string	proc_anglearc( stringstream &s );
	string	proc_arc( stringstream &s );
	string	proc_arcto( stringstream &s );
	string	proc_chord( stringstream &s );
	string	proc_ellipse( stringstream &s );
	string	proc_extfloodfill( stringstream &s );
	string	proc_exttextouta( stringstream &s );
	string	proc_exttextoutw( stringstream &s );
	string	proc_fillpath( stringstream &s );
	string	proc_fillrgn( stringstream &s );
	string	proc_framergn( stringstream &s );
	string	proc_gradientfill( stringstream &s );
	string	proc_lineto( stringstream &s );
	string	proc_paintrgn( stringstream &s );
	string	proc_pie( stringstream &s );
	string	proc_polybezier( stringstream &s );
	string	proc_polybezier16( stringstream &s );
	string	proc_polybezierto( stringstream &s );
	string	proc_polybezierto16( stringstream &s );
	string	proc_polydraw( stringstream &s );
	string	proc_polydraw16( stringstream &s );
	string	proc_polygon( stringstream &s );
	string	proc_polygon16( stringstream &s );
	string	proc_polyline( stringstream &s );
	string	proc_polyline16( stringstream &s );
	string	proc_polylineto( stringstream &s );
	string	proc_polylineto16( stringstream &s );
	string	proc_polypolygon( stringstream &s );
	string	proc_polypolygon16( stringstream &s );
	string	proc_polypolyline( stringstream &s );
	string	proc_polypolyline16( stringstream &s );
	string	proc_polytextouta( stringstream &s );
	string	proc_polytextoutw( stringstream &s );
	string	proc_rectangle( stringstream &s );
	string	proc_roundrect( stringstream &s );
	string	proc_setpixelv( stringstream &s );
	string	proc_smalltextout( stringstream &s );
	string	proc_strokeandfillpath( stringstream &s );
	string	proc_strokepath( stringstream &s );

	//2.3.6 Escape record types
	string	proc_drawescape( stringstream &s );
	string	proc_extescape( stringstream &s );
	string	proc_namedescape( stringstream &s );

	// 2.3.7 object creation record types
	string	proc_createbrushindirect( stringstream &s );
	string	proc_createcolorspace( stringstream &s );
	string	proc_createcolorspacew( stringstream &s );
	string	proc_createdibpatternbrushpt( stringstream &s );
	string	proc_createmonobrush( stringstream &s );
	string	proc_createpalette( stringstream &s );
	string	proc_createpen( stringstream &s );
	string	proc_extcreatefontindirectw( stringstream &s );
	string	proc_extcreatepen( stringstream &s );

	// 2.3.8 object manipulation record types
	string	proc_colorcorrectpalette( stringstream &s );
	string	proc_deletecolorspace( stringstream &s );
	string	proc_deleteobject( stringstream &s );
	string	proc_resizepalette( stringstream &s );
	string	proc_selectobject( stringstream &s );
	string	proc_selectpalette( stringstream &s );
	string	proc_setcolorspace( stringstream &s );
	string	proc_setpaletteentries( stringstream &s );

	// 2.3.9 opengl record types
	string	proc_glsboundedrecord( stringstream &s );
	string	proc_glsrecord( stringstream &s );

	// 2.3.10 path bracket record types
	string	proc_abortpath( stringstream &s );
	string	proc_beginpath( stringstream &s );
	string	proc_closefigure( stringstream &s );
	string	proc_endpath( stringstream &s );
	string	proc_flattenpath( stringstream &s );
	string	proc_widenpath( stringstream &s );

	// 2.3.11 state record types
	string	proc_colormatchtotargetw( stringstream &s );
	string	proc_forceufimapping( stringstream &s );
	string	proc_invertrgn( stringstream &s );
	string	proc_movetoex( stringstream &s );
	string	proc_pixelformat( stringstream &s );
	string	proc_realizepalette( stringstream &s );
	string	proc_restoredc( stringstream &s );
	string	proc_savedc( stringstream &s );
	string	proc_scaleviewportextex( stringstream &s );
	string	proc_scalewindowextex( stringstream &s );
	string	proc_setarcdirection( stringstream &s );
	string	proc_setbkcolor( stringstream &s );
	string	proc_setbkmode( stringstream &s );
	string	proc_setbrushorgex( stringstream &s );
	string	proc_setcoloradjustment( stringstream &s );
	string	proc_seticmmode( stringstream &s );
	string	proc_seticmprofilea( stringstream &s );
	string	proc_seticmprofilew( stringstream &s );
	string	proc_setlayout( stringstream &s );
	string	proc_setlinkedufis( stringstream &s );
	string	proc_setmapmode( stringstream &s );
	string	proc_setmapperflags( stringstream &s );
	string	proc_setmiterlimit( stringstream &s );
	string	proc_setpolyfillmode( stringstream &s );
	string	proc_setrop2( stringstream &s );
	string	proc_setstretchbltmode( stringstream &s );
	string	proc_settextalign( stringstream &s );
	string	proc_settextcolor( stringstream &s );
	string	proc_settextjustification( stringstream &s );
	string	proc_setviewportextex( stringstream &s );
	string	proc_setviewportorgex( stringstream &s );
	string	proc_setwindowextex( stringstream &s );
	string	proc_setwindoworgex( stringstream &s );

	// 2.3.12 transform record types
	string	proc_modifyworldtransform( stringstream &s );
	string	proc_setworldtransform( stringstream &s );

	// 2.2 EMF Objects
	string	format_object( POINTL &pt );
	string	format_object( SIZEL &sz );
	string	format_object( COLORREF &col );
	string	format_object( RECTL &rc );
	string	dump( string data );
	string	dump( char *p, int size );

} ;