// CTimer.cpp -


#include "main.h"

// define time-counter
#define TICKS GetTickCount() //timeGetTime()


/////////////////////////////////////////////////////////////////////////////////////////////
//// Name: Start()
//// Desc: inicializira timer
/////////////////////////////////////////////////////////////////////////////////////////////
void CTimer::Start()
{
	m_paused = false;
	m_starttime = TICKS;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//// Name: Pause()
//// Desc: 
/////////////////////////////////////////////////////////////////////////////////////////////
void CTimer::Pause()
{
	m_paused = true;
	m_pausestart = TICKS;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//// Name: Unpause()
//// Desc: 
/////////////////////////////////////////////////////////////////////////////////////////////
void CTimer::Unpause()
{
	m_paused = false;
	m_pausetime += TICKS - m_pausestart;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//// Name: Time()
//// Desc: get current ticks
/////////////////////////////////////////////////////////////////////////////////////////////
int CTimer::Time()
{
	int cur_time = TICKS;
	int result = cur_time - m_pausetime;

	if ( m_paused )
		result -= cur_time - m_pausestart;

	return result - m_starttime;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//// Name: Elapsed()
//// Desc: check if time has elapsed
/////////////////////////////////////////////////////////////////////////////////////////////
bool CTimer::Elapsed( int &time_start, int interval )
{
	int cur_time = Time();

	if ( cur_time > time_start + interval )
	{
		time_start = cur_time;
		return true;
	}
	else 
		return false;
}




/////////////////////////////////////////////////////////////////////////////////////////////
//// Name: CFrame()
//// Desc: 
/////////////////////////////////////////////////////////////////////////////////////////////
CGameFrame::CGameFrame()
{
	timer = NULL;
	frametime = lasttime = 0;
	fps = frames = 0;
	motion_frame = 0.0f;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//// Name: CFrame()
//// Desc: construct from timer
/////////////////////////////////////////////////////////////////////////////////////////////
CGameFrame::CGameFrame( CTimer *Timer )
{
	frametime = lasttime = Timer->Time();
	fps = frames = 0;
	motion_frame = 0.0f;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//// Name: Update()
//// Desc: update frame counter
/////////////////////////////////////////////////////////////////////////////////////////////
void CGameFrame::Update()
{
	int now = timer->Time();
	int diff = now - lasttime;
	 
	// get frames per second
	if ( ( now - frametime ) >= 1000 )
	{
		fps = frames;
		frames = 0;
		frametime = now;
	}
	else
		frames++;

	/*diff = ( diff <= 0 ? 1 : diff );
	if ( diff != 0 )
		fps = ( (float)(1000.0 / diff) );*/


	// calculate motion frame
	motion_frame = (float)diff / 1000.0f;

	// save last time-check
	lasttime = now;	
}
	




