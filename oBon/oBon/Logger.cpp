/**
 * @file ファイル名.h
 * @brief 簡単な説明
 * @author 書いた人
 * @date 日付（開始日？）
 */

#include "StdAfx.h"
#include "Logger.h"

Logger::Logger(void)
{
}

Logger::~Logger(void)
{
}

//----------------------------------------------------------------------------
// 関  数 : ログ出力処理
// 関数名 : Debug
// 入  力 : non
// 出  力 : non
// 戻り値 : TRUE	正常終了
// 備  考 : デバッグレベルログの出力。
//----------------------------------------------------------------------------
/**
 * @fn
 * ここに関数の説明を書く
 * @brief 要約説明
 * @param (引数名) 引数の説明
 * @param (引数名) 引数の説明
 * @return 戻り値の説明
 * @sa 参照すべき関数を書けばリンクが貼れる
 * @detail 詳細な説明
 */
bool Logger::debug( LPCTSTR lpszFormat, ... )
{
//	if( isDebugEnable() )
	{
		va_list argp;
		va_start(argp, lpszFormat);
		WriteOut( (LPCTSTR)_T("DEBUG"), lpszFormat, m_dwError, argp );
		va_end(argp);
	}

	return TRUE ;
}

//----------------------------------------------------------------------------
// 関  数 : ログ出力処理
// 関数名 : Info
// 入  力 : non
// 出  力 : non
// 戻り値 : TRUE	正常終了
// 備  考 : インフォメーションレベルログの出力
//----------------------------------------------------------------------------
bool Logger::info( LPCTSTR lpszFormat, ... )
{
//	if( isInfoEnable() )
	{
		va_list argp;
		va_start(argp, lpszFormat);
		WriteOut( (LPCTSTR)_T("INFO"), lpszFormat, m_dwError, argp );
		va_end(argp);
	}

	return true ;
}

//----------------------------------------------------------------------------
// 関  数 : ログ出力処理
// 関数名 : Warning
// 入  力 : non
// 出  力 : non
// 戻り値 : TRUE	正常終了
// 備  考 : ワーニングレベルログの出力
//----------------------------------------------------------------------------
bool Logger::warning( LPCTSTR lpszFormat, ... )
{
//	if( isWarningEnable() )
	{
		va_list argp;
		va_start(argp, lpszFormat);
		WriteOut( (LPCTSTR)_T("WARNING"), lpszFormat, m_dwError, argp );
		va_end(argp);
	}

	return true ;
}

//----------------------------------------------------------------------------
// 関  数 : ログ出力処理
// 関数名 : Error
// 入  力 : non
// 出  力 : non
// 戻り値 : TRUE	正常終了
// 備  考 : エラーレベルログの出力
//----------------------------------------------------------------------------
bool Logger::error( LPCTSTR lpszFormat,	...	)
{
//	if( isErrorEnable() )
	{
		va_list argp;
		va_start(argp, lpszFormat);
		WriteOut( (LPCTSTR)_T("ERROR"), lpszFormat, this->m_dwError, argp );
		va_end(argp);
	}

	return true ;
}

BOOL Logger::WriteOut(LPCTSTR lpKind, LPCTSTR format, DWORD dwFlags, va_list argptr  )
{
	// 資源ロック
//	EnterCriticalSection(&m_csWrite);

	int size = _vscprintf( (const char*)format, argptr );
	if( size )
	{
	}

	// 資源開放
//	LeaveCriticalSection(&m_csWrite);

	return TRUE ;
}

BOOL Logger::WriteOut(LPCTSTR lpData, DWORD dwFlags )
{
	return TRUE ;
}

BOOL Logger::WriteOut(LPCTSTR lpData )
{
	SYSTEMTIME	st ;
	GetLocalTime( &st );

	char	*buf = new char [1024/*BUFFER_SIZE*/];
	sprintf( buf, "%04d/%02d/%02d,%02d:%02d:%02d.%03d,%s\n",
					st.wYear,
					st.wMonth,
					st.wDay,
					st.wHour,
					st.wMinute,
					st.wSecond,
					st.wMilliseconds,
					lpData
			);
/*
	if( dwFlags & FILE )
	{
		if( Open() )
		{
			fwrite( buf, strlen(buf), 1, fp );
			fflush(fp);
		}
	}

	if( dwFlags & CONSOLE )
	{
		DWORD	dwWrite = 0;
		if( hStdOut == NULL )
		{
			FreeConsole();
			AllocConsole();

			hStdOut = CreateFile(
						"CONOUT$",
						GENERIC_WRITE,
						0,
						NULL,
						OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL,
						NULL
					);
		}

		WriteFile(hStdOut, buf, lstrlen(buf), &dwWrite, NULL);
	}
*/
	delete [] buf ;

	return TRUE ;
}
