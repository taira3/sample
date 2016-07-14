#pragma once

#include <stdarg.h>

class DebugLog
{
public:
	DebugLog(void)
	{
		output_status[_CONSOLE] = false ;
		level_[_CONSOLE] = FATAL_LOG ;
	}

	~DebugLog(void)
	{
	}

	// DEBUG�@���@INFO�@���@WARN�@���@ERROR�@���@FATAL
	enum	LOGLEVEL
	{
		NON_LOG		,	//   �o�͂��Ȃ�.
						// ��.
		DEBUG_LOG	,	//  
		INFO_LOG	,
		WARN_LOG	,
		ERROR_LOG	,
		FATAL_LOG	
						// ��.
	};
	typedef	enum LOGLEVEL	eLogLevel ;

	enum	OUTPUT
	{
		_LOGFILE	,		// �t�@�C���o��.
		_DEBUGWIN,		// �f�o�b�O�E�B���h�E
		_CONSOLE	,		// �W���o��.
		_OUTPUT_MAX
	};
	typedef enum OUTPUT		eOutput ;

	// �o�͐�̐ݒ�.
	void	setOutput();
	void	setOutputConsole()
	{
		if( level_[_CONSOLE] != NON_LOG )
		{
			if( !output_status[_CONSOLE] )
			{
				output_status[_CONSOLE] = true ;
				//�R���\�[�����쐬���C�W�����o�͂Ɋ��蓖�Ă�
				::AllocConsole();
				freopen_s(&console,"CONOUT$","w",stdout);
				//freopen("CONIN$", "r", stdin);
			}
		}
	}

	void	dispose()
	{
		if( level_[_CONSOLE] != NON_LOG )
		{
			fclose(console);
			::FreeConsole();
		}
	}

	// �o�̓��x���̐ݒ�.
	void	setLogLevel( eLogLevel v )	{ level = v ; } 
	void	setLogDebug()	{ level = DEBUG_LOG; }
	void	setLogInfo()	{ level = INFO_LOG; }
	void	setLogWarn()	{ level = WARN_LOG; }
	void	setLogError()	{ level = ERROR_LOG; }
	void	setLogFatal()	{ level = FATAL_LOG; }

	// �o��
	void	Debug(const char * format, ...)	{ if( level <= DEBUG_LOG )	{	va_list va;	va_start(va, format);	log(format, va);	va_end(va);	}	}
	void	Info(const char * format, ...)	{ if( level <= INFO_LOG )	{	va_list va;	va_start(va, format);	log(format, va);	va_end(va);	}	}
	void	Warn(const char * format, ...)	{ if( level <= WARN_LOG )	{	va_list va;	va_start(va, format);	log(format, va);	va_end(va);	}	}
	void	Error(const char * format, ...)	{ if( level <= ERROR_LOG )	{	va_list va;	va_start(va, format);	log(format, va);	va_end(va);	}	}
	void	Fatal(const char * format, ...)	{ if( level <= FATAL_LOG )	{	va_list va;	va_start(va, format);	log(format, va);	va_end(va);	}	}

	void	log(const char* format, va_list va)
	{
		char sMessage[256];
		vsprintf_s(sMessage,256,format, va);
		OutputDebugStringA( sMessage );
	}

private:
	eLogLevel	level ;
	eLogLevel	level_[_OUTPUT_MAX] ;
	bool		output_status[_OUTPUT_MAX];
	FILE	*console ;

};
