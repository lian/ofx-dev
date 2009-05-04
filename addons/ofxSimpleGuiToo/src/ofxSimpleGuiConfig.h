/***********************************************************************
 
 Copyright (c) 2008, 2009, Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 * All rights reserved.
 
 based on Todd Vanderlin's ofxSimpleGui API
 http://toddvanderlin.com/
 
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of MSA Visuals nor the names of its contributors 
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE. 
 *
 * ***********************************************************************/ 


#pragma once

#include "ofTypes.h"

class ofxSimpleGuiConfig {
public:	
	ofPoint	gridSize;

	float	buttonHeight;
	float	toggleHeight;
	float	sliderHeight;
	float	sliderTextHeight;
	float	slider2DTextHeight;
	float	titleHeight;
	
	ofPoint padding;
	ofPoint offset;
	ofPoint	slider2DSize;
	
	int	textColor;
	int textOverColor;
	int textBGColor;
	int textBGOverColor;
	
	int fullColor;
	int	fullOverColor;
	int fullActiveColor;
	int emptyColor;
	int borderColor;
	
	ofxSimpleGuiConfig() {

		sliderHeight		= 12;
		sliderTextHeight	= 18;
		titleHeight			= sliderHeight + sliderTextHeight;
		toggleHeight		= titleHeight;
		buttonHeight		= titleHeight;
		slider2DTextHeight	= titleHeight * 1.5;

		
		padding.set			(titleHeight/2, titleHeight/2);
		offset.set			(titleHeight/2, titleHeight/2);
		slider2DSize.set	(titleHeight * 4, titleHeight * 4);
		
		gridSize.x			= titleHeight * 8 + padding.x;		
		gridSize.y			= toggleHeight + padding.y;
		
		textColor			= 0xAAAAAA;
		textOverColor		= 0xFFFFFF;
		textBGColor			= 0x303030;
		textBGOverColor		= 0x707070;
		
		fullColor			= 0x37a9a9;
		fullOverColor		= 0x64b4b4;
		fullActiveColor		= 0xb41818;
		emptyColor			= 0xDCDCDC;		
		
		borderColor			= 0xCCCCCC;
	}
};


extern ofxSimpleGuiConfig defaultSimpleGuiConfig;