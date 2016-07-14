#pragma once

// [MS-EMF].pdf 

namespace emf {

	// 2.1.10 EmrComment Enumeration
	typedef enum
	{
		EMR_COMMENT_WINDOWS_METAFILE = 0x80000001,
		EMR_COMMENT_BEGINGROUP = 0x00000002,
		EMR_COMMENT_ENDGROUP = 0x00000003,
		EMR_COMMENT_MULTIFORMATS = 0x40000004,
		EMR_COMMENT_UNICODE_STRING = 0x00000040,
		EMR_COMMENT_UNICODE_END = 0x00000080
	} EmrComment ;

	// 2.3.11.17 EMR_SETLAYOUT Record
	//   WinGDI.hでは、LAYOUT_RTLとLAYOUT_BITMAPORIENTATIONPRESERVEDは定義済み.
#define	LAYOUT_LTR					0x00000000

	// WinGDI.hでは別名定義(EMR_GDICOMMENT)されているので、仕様の通りに再定義.
#define	EMR_COMMENT					0x00000046

	// 下記レコードタイプは、WinGDI.hでは予約扱いとなっているので再定義.
/*
    EmfRecordTypeDrawEscape              = 105, // EMR_RESERVED_105,
    EmfRecordTypeExtEscape               = 106, // EMR_RESERVED_106,
    EmfRecordTypeStartDoc                = 107, // EMR_RESERVED_107,	<-
    EmfRecordTypeSmallTextOut            = 108, // EMR_RESERVED_108,
    EmfRecordTypeForceUFIMapping         = 109, // EMR_RESERVED_109,
    EmfRecordTypeNamedEscape             = 110, // EMR_RESERVED_110,
    EmfRecordTypeSetLinkedUFIs           = 119, // EMR_RESERVED_119,
    EmfRecordTypeSetTextJustification    = 120, // EMR_RESERVED_120,
*/
#define	EMR_DRAWESCAPE				0x00000069
#define	EMR_EXTESCAPE				0x0000006A
#define	EMR_SMALLTEXTOUT			0x0000006C
#define	EMR_FORCEUFIMAPPING			0x0000006D
#define	EMR_NAMEDESCAPE				0x0000006E
#define	EMR_SETLINKEDUFIS			0x00000077
#define	EMR_SETTEXTJUSTIFICATION	0x00000078

// EmfRecordTypeSmallTextOut (EMR_RESERVED_108)
typedef struct tagEMRSMALLTEXTOUT
{
    EMR     emr;
	LONG	x ;					// x-coordinate of where to place the string.
	LONG	y ;					// y-coordinate of where to place the string.
	DWORD	cChars ;			// number of 16-bit characters in the string. The string is NOT null-terminated.
	DWORD	fuOptions ;
	DWORD	iGraphicsMode ;
	FLOAT	exScale ;
	FLOAT	eyScale ;
	//RECTL	rclBounds ; <- optional 
	// TextString
} EMRSMALLTEXTOUT, *PEMRSMALLTEXTOUT;

// 2.2.27 UniversalFontId Object
typedef struct tagUniversalFontId
{
	DWORD	Checksum ;
	DWORD	Index ;
} UniversalFontId, *PUniversalFontId ;


// EmfRecordTypeForceUFIMapping (EMR_RESERVED_109)
typedef struct tagEMRFORCEUFIMAPPING
{
    EMR     emr;
	UniversalFontId	ufi ;

} EMRFORCEUFIMAPPING, *PEMRFORCEUFIMAPPING;

// EmfRecordTypeSetLinkedUFIs (EMR_RESERVED_119)
typedef struct tagSETLINKEDUFIS
{
    EMR     emr;
	DWORD	uNumLinkedUFI ;
	// ufis
	// Reserved
} SETLINKEDUFIS, *PSETLINKEDUFIS;

}