#pragma once

#define IPLIGIN_EXPORTS

#ifdef IPLIGIN_EXPORTS
#define IPLIGIN_API __declspec(dllexport)
#else
#define IPLIGIN_API __declspec(dllimport)
#endif

#include	<string>
using namespace std;

//class IPLIGIN_API IPlugin {
class IPlugin {
public:
    virtual ~IPlugin() {}

	// Plugin‚Ìƒo[ƒWƒ‡ƒ“.
	virtual int version() = 0;
//	virtual bool Validate() = 0;

	// ˆ—‚Å‚«‚é‚©.
	virtual bool entry( const char *target_file ) = 0 ;

	// ‘Ã“–«ŒŸØ.
	virtual bool validate() = 0 ;

	// •ªÍ.
	virtual bool analyze() = 0 ;

//	virtual bool LoadScene(const char *file_name) = 0;
//	virtual void SetViewportSize(int w, int h) = 0;
//	virtual void SetCameraPosition(double x, double y, double z) = 0;
//	virtual void SetLookAt(double x, double y, double z) = 0;
//	virtual void Render() = 0;
};

//#define	CREATEI	 IPlugin *(*)(void)
typedef IPlugin *(*CREATEI)(void); 
typedef void (*POII)(IPlugin *); 
