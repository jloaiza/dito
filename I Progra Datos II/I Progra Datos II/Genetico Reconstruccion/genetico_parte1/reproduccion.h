/*
 * reproduccion.h
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

#ifndef REPRODUCCION_H
#define REPRODUCCION_H

#include "individuo.h"
#include "constants.h"

class reproduccion {
	
public:

	recta* _lineas;
	int _numLineas;
    int _probabilidadMutacion;
    int _probabilidadInvertir;

    reproduccion(int pProbabilidadMutacion, int pProbabilidadInvertir);
    individuo* cruce(individuo* pPadre, individuo* pMadre);
    void Mutacion(individuo* pIndividuo);
    void Inversion(individuo* pIndividuo);
    void fitness(individuo* pIndividuo);
    
    void setLineas(recta* plineas, int pNumLineas);

};
#endif
