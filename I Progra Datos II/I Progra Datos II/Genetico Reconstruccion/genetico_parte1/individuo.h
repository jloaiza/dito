/*
 * individuo.h
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


#ifndef INDIVIDUO_H
#define INDIVIDUO_H

#include "constants.h"

class individuo {

public:
	bool* _cromosoma;
	int _id, _padre, _madre, _generacion;
	double _fitness;
	individuo* _siguiente;

	individuo(int pID, bool* pCromosoma);

	bool* getCromosoma();
	void setCromosoma(bool* pCromosoma);
	
	int getID();
	void setID(int pID);
	
	double getFitness();
	void setFitness(double pFitness);

	void setSiguiente (individuo* pSiguiente);
	individuo* getSiguiente();
	
	void setPadre(int pPadre);
	int getPadre();
	
	void setMadre(int pMadre);
	int getMadre();

	void setGeneracion(int pGeneracion);
	int  getGeneracion();
	
// - - - - - - - - - - - - - - - Imprimir - - - - - - - - - - - - - - - 
	void imprimir();

};
#endif


