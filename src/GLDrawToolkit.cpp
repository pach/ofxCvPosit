/*
 *  GLDrawToolkit.cpp
 *  opencvCalTry
 *
 *  Created by pach on 06/09/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GLDrawToolkit.h"
#include "ofMain.h"


void GLDrawToolkit::drawAxes() {
	// draw axe Ox
	ofSetColor(0, 255, 0);
	glBegin(GL_LINES);
	glVertex3f(0., 0., 0.);
	glVertex3f(0.1, 0., 0.);
	glEnd();
	// draw axe Oy
	ofSetColor(255, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0., 0., 0.);
	glVertex3f(0., 0.1, 0.);
	glEnd();
	// draw axe Oz
	ofSetColor(0, 0, 255);
	glBegin(GL_LINES);
	glVertex3f(0., 0., 0.);
	glVertex3f(0., 0., 0.1);
	glEnd();
}

void GLDrawToolkit::drawGrid() {
	//draw plan Oxy
	ofSetColor(0, 255, 0);
	for (int i=0 ; i<=10 ; i++)
	{
		glBegin(GL_LINES);
		glVertex3f((float)i/10., 0., 0.);
		glVertex3f((float)i/10., 1., 0.);
		glEnd();
		
		glBegin(GL_LINES);
		glVertex3f(0., (float)i/10., 0.);
		glVertex3f(1., (float)i/10., 0.);
		glEnd();
	}
	// draw plan Oxz
	ofSetColor(255, 0, 0);
	for (int i=0 ; i<=10 ; i++)
	{
		glBegin(GL_LINES);
		glVertex3f((float)i/10., 0., 0.);
		glVertex3f((float)i/10., 0., -1.);
		glEnd();
		
		glBegin(GL_LINES);
		glVertex3f(0., 0., -(float)i/10.);
		glVertex3f(1., 0., -(float)i/10.);
		glEnd();
	}
	// draw plan Oyz
	ofSetColor(0, 0, 255);
	for (int i=0 ; i<=10 ; i++)
	{
		glBegin(GL_LINES);
		glVertex3f(0., (float)i/10., 0.);
		glVertex3f(0., (float)i/10., -1.);
		glEnd();
		
		glBegin(GL_LINES);
		glVertex3f(0., 0., -(float)i/10.);
		glVertex3f(0., 1., -(float)i/10.);
		glEnd();
	}
}

void GLDrawToolkit::drawLineCube(float size) {
	float demi = size/2. ; 
	
	// top
	glBegin(GL_LINE_STRIP);
	glVertex3f(-demi, demi, -demi);
	glVertex3f(demi, demi, -demi);
	glVertex3f(demi, demi, demi);
	glVertex3f(-demi, demi, demi);
	glVertex3f(-demi, demi, -demi);
	glEnd();
	// bottom
	glBegin(GL_LINE_STRIP);
	glVertex3f(-demi, -demi, -demi);
	glVertex3f(demi, -demi, -demi);
	glVertex3f(demi, -demi, demi);
	glVertex3f(-demi, -demi, demi);
	glVertex3f(-demi, -demi, -demi);
	glEnd();
	//front
	glBegin(GL_LINE_STRIP);
	glVertex3f(-demi, demi, -demi);
	glVertex3f(demi, demi, -demi);
	glVertex3f(demi, -demi, -demi);
	glVertex3f(-demi, -demi, -demi);
	glVertex3f(-demi, demi, -demi);
	glEnd();
	//back
	glBegin(GL_LINE_STRIP);
	glVertex3f(-demi, demi, demi);
	glVertex3f(demi, demi, demi);
	glVertex3f(demi, -demi, demi);
	glVertex3f(-demi, -demi, demi);
	glVertex3f(-demi, demi, demi);
	glEnd();
	//left
	glBegin(GL_LINE_STRIP);
	glVertex3f(-demi, demi, -demi);
	glVertex3f(-demi, demi, demi);
	glVertex3f(-demi, -demi, demi);
	glVertex3f(-demi, -demi, -demi);
	glVertex3f(-demi, demi, -demi);
	glEnd();
	//right
	glBegin(GL_LINE_STRIP);
	glVertex3f(demi, demi, -demi);
	glVertex3f(demi, demi, demi);
	glVertex3f(demi, -demi, demi);
	glVertex3f(demi, -demi, -demi);
	glVertex3f(demi, demi, -demi);
	glEnd();
}