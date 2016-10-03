/**
 * @file �t�@�C����.h
 * @brief �ȒP�Ȑ���
 * @author �������l
 * @date ���t�i�J�n���H�j
 */
#pragma once

class Logger
{
public:
	Logger(void);
	~Logger(void);
/*
TRACE - printMessages()
DEBUG - This is a DEBUG message
INFO - This is a INFO message
WARN - This is a WARN message
ERROR - This is a ERROR message
FATAL - This is a FATAL message

�� EMERG, FATAL(�V�X�e�����g�p�s��) 
�� ALERT(�������ɍs�����N�����Ȃ���΂Ȃ�Ȃ�) 
�@ CRIT(�댯�ȏ��) 
�@ ERROR(�G���[�̏��) 
�@ WARN(���[�j���O�̏��) 
�@ NOTICE(�ʏ킾���d�v�ȏ��) 
�� INFO(�C���t�H���[�V�������b�Z�[�W) 
�� DEBUG(�f�o�b�O���x���̃��b�Z�[�W) 

*/
private:
	// �t�@�C���o�̓p�����^
	FILE	*fp ;

public:
	//
	bool	debug( LPCTSTR lpszFormat, ... ) ;

	bool	info( LPCTSTR lpszFormat, ... ) ;

	bool	warning( LPCTSTR lpszFormat, ... ) ;

	bool	error( LPCTSTR lpszFormat, ... ) ;

	bool	Dump(							// Hex Dump
				LPCTSTR		lpBuffer ,
				DWORD		dwLen 
			) ;

private:
	BOOL	Write(							// Message
				LPCTSTR		lpszFormat,
				...
			) ;

	DWORD	m_dwDebug ;			// Debug Log
	DWORD	m_dwInfo ;			// Infomation Log
	DWORD	m_dwWarning ;		// Warning Log
	DWORD	m_dwError ;			// Error Log
	DWORD	m_dwWrite ;			// Message
	DWORD	m_dwDump ;			// Dump

	BOOL WriteOut(LPCTSTR lpKind,LPCTSTR lpData, DWORD dwFlags, va_list arg );

	BOOL WriteOut(LPCTSTR lpData, DWORD dwFlags );



	BOOL WriteOut(LPCTSTR lpData );
};



