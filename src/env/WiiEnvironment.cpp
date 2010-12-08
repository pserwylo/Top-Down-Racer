/*
 * WiiEnvironment.cpp
 *
 *  Created on: 08/12/2010
 *      Author: pete
 */

#include "env/WiiEnvironment.h"
#include <stdio.h>
#include <stdlib.h>
#include "gccore.h"
#include "wiiuse/wpad.h"


WiiEnvironment::WiiEnvironment()
{

}

WiiEnvironment::~WiiEnvironment()
{

}

/**
 * Taken from the devkitPPC template...
 */
void WiiEnvironment::setup()
{

	// Initialise the video system
	VIDEO_Init();

	// This function initialises the attached controllers
	WPAD_Init();

	// Obtain the preferred video mode from the system
	// This will correspond to the settings in the Wii menu
	rmode = VIDEO_GetPreferredMode(NULL);

	// Allocate memory for the display in the uncached region
	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

	// Initialise the console, required for printf
	console_init(xfb,20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);

	// Set up the video registers with the chosen mode
	VIDEO_Configure(rmode);

	// Tell the video hardware where our display memory is
	VIDEO_SetNextFramebuffer(xfb);

	// Make the display visible
	VIDEO_SetBlack(FALSE);

	// Flush the video register changes to the hardware
	VIDEO_Flush();

	// Wait for Video setup to complete
	VIDEO_WaitVSync();
	if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();

}

/**
 * Returns to the homebrew launcher.
 * Calling this will exit the application.
 */
void WiiEnvironment::tearDown()
{
	exit( 0 );
}
