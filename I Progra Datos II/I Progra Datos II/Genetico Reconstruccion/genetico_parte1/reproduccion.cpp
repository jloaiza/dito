/*
 * reproduccion.cpp
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

#include <iostream>
#include <stdlib.h>

#include "reproduccion.h"


/**
 * constructor de la clase reproduccion
 * @param pProbabilidadMutacion cantidad de mutaciones por generacion
 * @param pProbabilidadInvertir se pueden invertir los bits de un individuo
 */
reproduccion::reproduccion(int pProbabilidadMutacion, int pProbabilidadInvertir) {
	if(pProbabilidadMutacion > 100 || pProbabilidadMutacion < 0)
        _probabilidadMutacion = 5;
    else
        _probabilidadMutacion = pProbabilidadMutacion;

    if(pProbabilidadInvertir > 100 || pProbabilidadInvertir < 0)
        _probabilidadInvertir = 5;
    else
        _probabilidadInvertir = pProbabilidadMutacion;
}


/**
 * funcion encargada de cruzar a dos individuos
 * @param pPadre papa del nuevo individuo
 * @param pMadre mama del nuevo individuo
 * @return nuevo individuo
 * @version 1.0
 */
individuo* reproduccion::cruce(individuo* pPadre, individuo* pMadre) {
	srand(time (NULL) );
	int pos = rand()%LARGO;
	int ind=0;
	
	bool* cromosomahijo = new bool[LARGO];
	bool* cromosomaPadre = pPadre->getCromosoma();
	bool* cromosomaMadre = pMadre->getCromosoma();
	
	while (ind<LARGO) {
		if (ind <= pos) {
			cromosomahijo[ind] = cromosomaPadre[ind];
		}
		else {
			cromosomahijo[ind] = cromosomaMadre[ind];
		}
		ind++;
	}
	individuo* hijo = new individuo(-1, cromosomahijo);
	hijo->setPadre(pPadre->getID());
    hijo->setMadre(pMadre->getID());
}

/**
 * se encarga de introducir una mutacion a cualquier individuo de la 
 * poblacion, la mutacion consiste en modificar un bit de la solucion
 * @param pIndividuo individuo al que vamos a modificar
 */
void reproduccion::Mutacion(individuo* pIndividuo) {
	srand(time (NULL) );
	int pos = rand()%LARGO;
    unsigned short bitMutado = 1;
    bool* cromosoma = pIndividuo->getCromosoma();
    cromosoma[pos] |= bitMutado;
    pIndividuo->setCromosoma(cromosoma);
}
    
/**
 * invierte el cromosoma de un individuo
 * @param pIndividuo individuo al que vamos a modificarle los genes
 */
void reproduccion::Inversion(individuo* pIndividuo){
	bool* cromosoma = pIndividuo->getCromosoma();
	int y=LARGO;
	for (int x=0; x==y; x++){
		bool temp = cromosoma[x];
		cromosoma[x] = cromosoma[y];
		cromosoma[y]= temp;
	}
}

/**
 * funcion que calcula el fitness de cada individuo
 * @param pIndividuo individuo al cual le calcula su funcion fitness 
 */
void reproduccion::fitness(individuo* pIndividuo) {
	int total=0;
	bool* cromosoma = pIndividuo->getCromosoma();
	
	int ind=0;
	while (ind<_numLineas &&_lineas[ind]._direccion) {
		recta temporal = _lineas[ind];
		int x = temporal._x2;
		int yCromosoma = temporal._
		int y = (temporal._m)*(x+1) + temporal._b;
		if (cromosoma[y]==1) {
			total +=10; 
		}
		else {
			total -= 3;
		} 
		ind++;
	}
	pIndividuo->setFitness(total);
}


void reproduccion::setLineas(recta* plineas, int pNumLineas) {
	_lineas = plineas;
	_numLineas = pNumLineas;
}

