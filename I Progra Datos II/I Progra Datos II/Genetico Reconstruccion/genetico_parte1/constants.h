/*
 * constants.cpp
 * 
 * Copyright 2013 maikol <maikol@maikol-wander-15>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * 
 */


#ifndef CONSTANTS
#define CONSTANTS

#define ADENINA false
#define TIMINA true

#define ANCHO 10
#define LARGO 10

#endif

#ifndef RECTA
#define RECTA
struct recta {
	bool _direccion;
	int _x1, _y1, _x2, _y2;
	int _m, _b;
};
#endif
