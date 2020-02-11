#include "stdafx.h"
#include "WxBiz.h"
#include "EasyLog.h"
#include "Util.h"
#define Offset 0x4DCBF0;

//用于调用微信发送消息call的结构体
struct wxMsg
{
	wchar_t* pMsg;		//微信ID
	int msgLen;			//ID长度
	int buffLen;		//缓冲区长度
};

WxBiz::WxBiz()
{
}


WxBiz::~WxBiz()
{
}

string WxBiz::SendMsg(http_message* http_message)
{
	EasyLog::Write("SendMsg");
	char wxid_c[100], msg_c[200];
	memset(wxid_c, '\0', sizeof(wxid_c));
	memset(msg_c, '\0', sizeof(msg_c));
	mg_get_http_var(&http_message->query_string, "wxid", wxid_c, sizeof(wxid_c));
	mg_get_http_var(&http_message->query_string, "msg", msg_c, sizeof(msg_c));
	string wxid = string(wxid_c, sizeof(wxid_c));
	string msg = string(msg_c, sizeof(msg_c));
	EasyLog::Write("SendMsg");
	if (wxid.empty()) {
		return "{code:-1,msg:'wxid canot be empty'}";
	}
	if (msg.empty()) {
		return "{code:-2,msg:'msg canot be empty'}";
	}
	EasyLog::Write("wxid:"+wxid+" msg:"+msg);
	//拿到发送消息的call的地址
	DWORD dwSendCallAddr = (DWORD)GetModuleHandle(TEXT("WeChatWin.dll")) + Offset;

	//消息内容
	wxMsg text = { 0 };
	text.pMsg = Util::string2wct(msg);
	text.msgLen = wcslen(text.pMsg);
	text.buffLen = wcslen(text.pMsg) * 2;

	//取出微信ID和消息的地址
	char* pWxid = (char*)&wxid_c;
	char* pWxmsg = (char*)&text.pMsg;
	

	//调用微信发送消息call
	__asm {
		//move [ecx+0x28], pWxmsg;
		mov ebx, pWxmsg;
		mov [ecx + 0x28], ebx;
		push ecx;
		push 0xb;
		mov eax, pWxid;
		push eax;
		call dwSendCallAddr;
		add esp, 0xC;
	}
	return "{code:0}";
}
