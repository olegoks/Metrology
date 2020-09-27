#pragma once
#ifndef _COMPONENT_H_
#define _COMPONENT_H_
#include <Windows.h>
#include "WindowStructures.h"
class Component {
private:
protected:

	unsigned int width_;
	unsigned int height_;
	unsigned int x_;
	unsigned int y_;
	HWND handle_;
	HINSTANCE app_intance_handle_;

public:

	explicit Component(HWND handle, HINSTANCE app_intance_handle) noexcept:

		x_(0), y_(0), width_(1000), height_(500),
		handle_(handle),
		app_intance_handle_(app_intance_handle){

	}

	explicit Component(HWND handle, HINSTANCE app_intance_handle, uint width, uint height, uint x, uint y) noexcept :
		x_(x), y_(y), width_(width), height_(height),
		handle_(handle),
		app_intance_handle_(app_intance_handle)
	{
	}

	explicit Component(HINSTANCE app_intance_handle) noexcept :

		x_(0), y_(0), width_(1000), height_(500),
		handle_(NULL),
		app_intance_handle_(app_intance_handle) {

	}

};
#endif