/*
	NDI Receiver

	using the NDI SDK to receive frames from the network

	http://NDI.NewTek.com

	Copyright (C) 2016-2017 Lynn Jarvis.

	http://www.spout.zeal.co

	=========================================================================
	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
	=========================================================================

	16.10.16 - common buffer copy utilities
	09.02.17 - Changes for NDI SDK Version 2
				ReceiveImage - remove swap RG flag - now done internally
				RefreshSenders - uint32_t timeout instead of unsigned int
				Remove timer variables - timeouts done in new SDK functions
				FindGetSources - replacement for deprecated NDIlib_find_get_sources
			 - include changes by Harvey Buchan
				CreateReceiver - include colour format option
			 - SetLowBandWidth, Metadata
	17.02.17 - GetNDIversion - NDIlib_version


*/
#pragma once
#ifndef __ofxNDIreceiver__
#define __ofxNDIreceiver__

#if defined(_WIN32)
#include <windows.h>
#include <intrin.h> // for _movsd
#include <gl\GL.h>
#pragma comment(lib, "Winmm.lib") // for timegettime
#endif

#if defined(__APPLE__)
#include <x86intrin.h> // for _movsd
#endif


#include <string>
#include <iostream>
#include <vector>
#include <emmintrin.h> // for SSE2

#include "Processing.NDI.Lib.h" // NDI SDK
#include "ofxNDIutils.h" // buffer copy utilities

// Version 2 NDI
#include <csignal>
#include <cstddef>
#include <cstdio>
#include <atomic>

class ofxNDIreceiver {

public:

	ofxNDIreceiver();
    ~ofxNDIreceiver();

	bool CreateReceiver(int index = -1);
	bool CreateReceiver(NDIlib_recv_color_format_e colorFormat, int index = -1);
	void ReleaseReceiver();
	// bool ReceiveImage(unsigned char *pixels,
	//				  unsigned int &width, unsigned int &height,
	//				  bool bSwapRB = false, bool bInvert = false);
	bool ReceiveImage(unsigned char *pixels,
					  unsigned int &width, unsigned int &height,
					  bool bInvert = false);

	void CreateFinder();
	void ReleaseFinder();
	int  FindSenders();
	// int  RefreshSenders(unsigned int dwTimeout);
	int  RefreshSenders(uint32_t timeout);

	void SetSenderIndex(int index); // Set current sender index in the sender list
	int  GetSenderIndex(); // Get current index in the sender list
	bool GetSenderIndex(char *sendername, int &index); // Get the index of a sender name
	bool GetSenderName(char *sendername, int index = -1); // Get the name of a sender index
	int  GetSenderCount(); // Number of senders
	bool SenderSelected(); // Has the user changed the sender index

	void SetLowBandwidth(bool bLow = true);
	// Metadata
	bool IsMetadata();
	std::string GetMetadataString();

	// Utility
	std::string GetNDIversion();

private:

	const NDIlib_source_t* p_sources;
	uint32_t no_sources;
	NDIlib_send_create_t NDI_send_create_desc;
	NDIlib_find_instance_t pNDI_find;
	NDIlib_recv_instance_t pNDI_recv;
	NDIlib_video_frame_t video_frame;

	unsigned int m_Width, m_Height;
	std::vector<std::string> NDIsenders; // List of sender names
	int nsenders;// Sender count
	int senderIndex; // Current sender index
	bool bNDIinitialized; // Is NDI initialized properly
	bool bSenderSelected; // Sender index has been changed by the user
	NDIlib_recv_bandwidth_e m_bandWidth; // Bandwidth receive option

	unsigned int dwStartTime; // For timing delay
	unsigned int dwElapsedTime;

	// Metadata
	bool m_bMetadata;
	std::string m_metadataString; // XML message format string NULL terminated

	// Replacement function for deprecated NDIlib_find_get_sources
	const NDIlib_source_t* FindGetSources(NDIlib_find_instance_t p_instance,
														  uint32_t* p_no_sources,
														  uint32_t timeout_in_ms);


};


#endif
