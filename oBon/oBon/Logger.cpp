/**
 * @file �t�@�C����.h
 * @brief �ȒP�Ȑ���
 * @author �������l
 * @date ���t�i�J�n���H�j
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
// ��  �� : ���O�o�͏���
// �֐��� : Debug
// ��  �� : non
// �o  �� : non
// �߂�l : TRUE	����I��
// ��  �l : �f�o�b�O���x�����O�̏o�́B
//----------------------------------------------------------------------------
/**
 * @fn
 * �����Ɋ֐��̐���������
 * @brief �v�����
 * @param (������) �����̐���
 * @param (������) �����̐���
 * @return �߂�l�̐���
 * @sa �Q�Ƃ��ׂ��֐��������΃����N���\���
 * @detail �ڍׂȐ���
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
// ��  �� : ���O�o�͏���
// �֐��� : Info
// ��  �� : non
// �o  �� : non
// �߂�l : TRUE	����I��
// ��  �l : �C���t�H���[�V�������x�����O�̏o��
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
// ��  �� : ���O�o�͏���
// �֐��� : Warning
// ��  �� : non
// �o  �� : non
// �߂�l : TRUE	����I��
// ��  �l : ���[�j���O���x�����O�̏o��
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
// ��  �� : ���O�o�͏���
// �֐��� : Error
// ��  �� : non
// �o  �� : non
// �߂�l : TRUE	����I��
// ��  �l : �G���[���x�����O�̏o��
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
	// �������b�N
//	EnterCriticalSection(&m_csWrite);

	int size = _vscprintf( (const char*)format, argptr );
	if( size )
	{
	}

	// �����J��
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
