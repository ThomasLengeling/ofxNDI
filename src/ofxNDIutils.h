/*
	NDI utility functions

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

	16.10.16 - Create file

*/
#pragma once
#ifndef __ofxNDI_
#define __ofxNDI_

#if defined(_WIN32)
#include <windows.h>
#include <intrin.h> // for _movsd
#endif

#if defined(__APPLE__)
#include <x86intrin.h> // for _movsd
#include <stdlib.h>
#include <cstdint>
#include <string.h>
#endif

#include <emmintrin.h> // for SSE2
#include <stdio.h> // for print debugging

namespace ofxNDIutils {

	void CopyImage(const unsigned char *source, unsigned char *dest,
				   unsigned int width, unsigned int height, unsigned int stride,
				   bool bSwapRB = false, bool bInvert = false);
	void memcpy_sse2(void* dst, void* src, size_t Size);
	void rgba_bgra_sse2(void *source, void *dest, unsigned int width, unsigned int height, bool bInvert = false);
	void FlipBuffer(const unsigned char *src, unsigned char *dst, unsigned int width, unsigned int height);
	void YUV422_to_RGBA(const unsigned char * source, unsigned char * dest, unsigned int width, unsigned int height, unsigned int stride);

}


#endif
