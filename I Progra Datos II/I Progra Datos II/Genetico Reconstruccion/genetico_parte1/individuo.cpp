/*
 * individuo.cpp
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

#include "individuo.h"


/**
 * Constructor del individuo
 * @param pID numero de identificacion único de cada individuo
 * @param pCromosoma posible solucion de cada individuo
 */
individuo::individuo(int pID, bool* pCromosoma) {
	_cromosoma = pCromosoma;
	_id = pID;
	_siguiente = NULL;
	_madre = -1;
	_padre = -1;
	_generacion = 0;
	_fitness = 0;
}

/**
 * retorna el cromosoma del individuo
 * @return bool* array de genes (posible solucion del individuo)
 */
bool* individuo::getCromosoma() {
	return _cromosoma;
}

/**
 * le asigna un cromosoma al individuo
 * @param pCromosoma nuevo cromosoma para el individuo
 */
void individuo::setCromosoma(bool* pCromosoma) {
	_cromosoma = pCromosoma;
}

/**
 * retorna el id de un individuo
 * @return int con el id del individuo
 */
int individuo::getID() {
	return _id;
}

/**
 * le otorga un nuevo id al individuo
 * @param pID nuevo id del individuo
 */
void individuo::setID(int pID) {
	_id = pID;
}

/**
 * retorna el valor de fitness de un individuo
 * @return double con el valor de fitness
 */
double individuo::getFitness() {
	return _fitness;
}

/**
 * le otorga un valor de fitness al individuo (despues de aplicarle la funcion)
 * @param pFitness nuevo valor de fitness
 */
void individuo::setFitness(double pFitness) {
	_fitness = pFitness;
}

/**
 * establece el apuntador al siguiente individuo en la estructura 
 * interna de la poblacion
 * @param pSiguiente siguiente individuo al que apunta el individuo actual
 */
void individuo::setSiguiente (individuo* pSiguiente) { 
	_siguiente = pSiguiente;
}

/**
 * retorna el siguiente individuo en la estructura interna de la 
 * poblacion
 * @return apuntador al siguiente individuo
 */
individuo* individuo::getSiguiente() {
	return _siguiente;
}

/**
 * establece quien es el padre del individuo actual
 * @param int con el id del padre
 */
void individuo::setPadre(int pPadre) {
	_padre = pPadre;
}

/**
 * retorna el id del padre del individuo actual
 * @return id del padre
 */
int individuo::getPadre() {
	return _padre;
}

/**
 * establece quien es la madre del individuo actual
 * @param int con el id de la madre
 */
void individuo::setMadre(int pMadre) {
	_madre = pMadre;
}

/**
 * retorna el id de la madre del individuo actual
 * @return id de la madre
 */
int individuo::getMadre() {
	return _madre;
}

/**
 * retorna el numero de generacion a la que pertenece el individuo
 * @return int con el numero de generacion
 */
int individuo::getGeneracion() {
	return _generacion;
}

/**
 * establece el numero de generacion a la que pertenece el individuo
 * @param int con la generacion a la que pertence el individuo
 */
void individuo::setGeneracion(int pGeneracion) {
	_generacion = pGeneracion;
}

void individuo::imprimir(){
	std::cout << "Individuo Id:" << _id << "," << "Cromosoma:";
	for (int x=0; x<LARGO; x++) {
		std::cout << _cromosoma[x] << "-";
	}
	std::cout << std::endl;
}
