/**
 * @file ファイル名.h
 * @brief 簡単な説明
 * @author 書いた人
 * @date 日付（開始日？）
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

高 EMERG, FATAL(システムが使用不可) 
↑ ALERT(ただちに行動を起こさなければならない) 
　 CRIT(危険な状態) 
　 ERROR(エラーの状態) 
　 WARN(ワーニングの状態) 
　 NOTICE(通常だが重要な状態) 
↓ INFO(インフォメーションメッセージ) 
低 DEBUG(デバッグレベルのメッセージ) 

*/
private:
	// ファイル出力パラメタ
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



