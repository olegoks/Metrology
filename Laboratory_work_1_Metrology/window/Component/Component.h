#pragma once
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <Windows.h>
#include "WindowStructures.h"

static const uint DEFAULT_WIDTH = 1000;
static const uint DEFAULT_HEIGHT = 500;
static const uint DEFAULT_X = 0;
static const uint DEFAULT_Y = 0;
static const Style DEFAULT_STYLE = NULL;
static const int DEFAULT_CMD_SHOW = SW_SHOWNORMAL;

class Component {
private:
protected:

	unsigned int width_;
	unsigned int height_;
	unsigned int x_;
	unsigned int y_;
	HWND parent_handle_, self_handle_;
	HMENU menu_handle_;
	HINSTANCE app_instance_handle_;
	Style style_;
	int show_state_;


public:

	explicit Component(HWND handle, HINSTANCE app_intance_handle) noexcept:

		x_(DEFAULT_X), y_(DEFAULT_Y), width_(DEFAULT_WIDTH), height_(DEFAULT_HEIGHT),
		self_handle_(handle),style_(DEFAULT_STYLE),show_state_(DEFAULT_CMD_SHOW),
		parent_handle_(NULL), menu_handle_(NULL), app_instance_handle_(app_intance_handle){

	}

	explicit Component(HWND handle, HINSTANCE app_intance_handle, uint width, uint height, uint x, uint y) noexcept :
		x_(x), y_(y), width_(width), height_(height),
		self_handle_(handle), style_(DEFAULT_STYLE), show_state_(DEFAULT_CMD_SHOW),
		parent_handle_(NULL), menu_handle_(NULL), app_instance_handle_(app_intance_handle)
	{
	}

	explicit Component(HINSTANCE app_intance_handle) noexcept :

		x_(DEFAULT_X), y_(DEFAULT_Y), width_(DEFAULT_WIDTH), height_(DEFAULT_HEIGHT),
		self_handle_(NULL), style_(DEFAULT_STYLE), show_state_(DEFAULT_CMD_SHOW),
		parent_handle_(NULL), menu_handle_(NULL), app_instance_handle_(app_intance_handle) {

	}

	inline uint GetHeight()const noexcept { return height_; };
	inline uint GetWidth()const noexcept { return width_; };
	inline uint GetX()const noexcept { return x_; }
	inline uint GetY()const noexcept { return y_; }

};
#endif