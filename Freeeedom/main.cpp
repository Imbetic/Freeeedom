// Freeeedom.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Engine m_engine;

	if(m_engine.Initialize()){
		m_engine.Run();
	}
	m_engine.Cleanup();

	return 0;
}