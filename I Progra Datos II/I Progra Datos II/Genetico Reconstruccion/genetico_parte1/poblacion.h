/*
 * poblacion.h
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

//#include <iostream>



#ifndef POBLACION_H
#define POBLACION_H

#include "reproduccion.h"
#include "individuo.h"
#include "constants.h"

class poblacion {

public:
	reproduccion* _reproduccion;
	individuo* _poblacion;
    int _seleccionado, _contador, _tamanoPoblacion, _maxNacimientos, _generacion, _sumaFitness;
    short _probabilidadNacimientos;	
    bool _reemplazoPoblacion;

	poblacion(int pTamanoPob, int pMaxNac, short pProbNac, bool pNewPob, reproduccion* pReproduccion);
	void inicializar();
	void nuevaGeneracion();
	int getSumaFitness();
    void aplicarFitness();
    individuo* seleccionNatural();
    void mezclarPoblacion(individuo* pNewGen);
    individuo* MasFuerte(individuo *pPoblacion);
    individuo* MasDebil(individuo *pPoblacion);
    void cambiarIndividuos(individuo* pIndividuo1, individuo* pIndividuo2);

// - - - - - - - - - - - - - - - Imprimir - - - - - - - - - - - - - - - 
    void imprimirMejor();
    void imprimirPoblacion();
	
};

#endif //POBLACION_H
