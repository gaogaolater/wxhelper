// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "WxBiz.h"
#include "HttpServer.h"

using namespace std;

void InitServer() 
{
	std::string port = "7999";
	auto http_server = std::shared_ptr<HttpServer>(new HttpServer);
	http_server->Init(port);
	// add handler
	http_server->AddHandler("/api/sendtextmessage", WxBiz::SendMsg);
	http_server->Start();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	{
		CreateThread(NULL,0, (LPTHREAD_START_ROUTINE)InitServer, hModule,0,NULL);
	}
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

