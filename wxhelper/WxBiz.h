#pragma once
#include <iostream>
#include "mongoose.h"
using namespace std;

class WxBiz
{
public:
	WxBiz();
	~WxBiz();
	static string SendMsg(http_message* http_message);
};

