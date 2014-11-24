#pragma once

// конечный объект команды Client_Socket

class Client_Socket : public CSocket
{
public:
	Client_Socket(FORM_MAIN* f);
	virtual ~Client_Socket();
	void* forma;
	virtual void OnReceive(int nErrorCode);
};


