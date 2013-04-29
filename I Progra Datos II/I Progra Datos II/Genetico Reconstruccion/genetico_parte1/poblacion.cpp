/*
 * poblacion.cpp
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
#include "poblacion.h"

/**
 * constructor de la clase poblacion
 * @param pTamñoPob tamaño maximo que alcanzará la poblacion
 * @param pMaxNac cantidad maxima de nacimientos por generacion
 * @param pProbNac con que probabilidad nacen los individuos
 * @param pNewPob true si la poblacion se va a reemplazar completamente 
 * cada vez que se reproduzca la poblacion
 */
poblacion::poblacion(int pTamanoPob, int pMaxNac, short pProbNac, bool pNewPob, reproduccion* pReproduccion) {
	_reproduccion = pReproduccion;
	_poblacion = NULL;
	_reemplazoPoblacion = pNewPob;
    _generacion = 0;
    _tamanoPoblacion = pTamanoPob;
    _seleccionado = -1; 												// no hay nadie seleccionado 
    
    
    if(_reemplazoPoblacion) {
        _maxNacimientos =pTamanoPob;
        _probabilidadNacimientos = 100;
    }
    
    else {
		
		// en caso de que se inserte un valor incorrecto se asume un nacimiento de un 50%
        if(pProbNac > 100 && pProbNac < 0) { _probabilidadNacimientos = 50; } 
        
        else { _probabilidadNacimientos = pProbNac; }
        
        _maxNacimientos = pMaxNac;
	
	}
    
    _contador = 0;
}
	
/**
 * inicializa la poblacion y asigna los primeros individuos (primera 
 * generacion)
 */	
void poblacion::inicializar(){
	srand(time (NULL) );
	
	for (int i=0; i<_tamanoPoblacion;i++) {
		bool* cromosoma = new bool[LARGO];
		
		for (int j=0; j<LARGO; j++) {
			bool bit = rand()%2;
			cromosoma[j] = bit;
		}
		
		individuo* tmp = new individuo(_contador, cromosoma);
		tmp->setSiguiente(_poblacion);
		_poblacion = tmp;
		_contador++;
	}
	_seleccionado = -1;
}

void poblacion::nuevaGeneracion() {
	individuo *nacimientos = NULL;
    int numeroNacimientos=0;
    individuo *padre1 = NULL;
    individuo *padre2 = NULL;
    for(int i=0;i<_maxNacimientos;i++){
		if((rand()%100) < _probabilidadNacimientos){
            padre1 = seleccionNatural();
            _seleccionado = padre1->getID();
            padre2 = seleccionNatural();
            _seleccionado = -1;
            individuo *tmp = _reproduccion->cruce(padre1,padre2);
            tmp->setSiguiente(nacimientos);
            nacimientos = tmp;
            _contador++;
            nacimientos->setID(_contador);
            nacimientos->setGeneracion(_generacion);
            numeroNacimientos++;
        }
    }
    mezclarPoblacion(nacimientos);
    _generacion++;
}
   
int poblacion::getSumaFitness() {
	int fitnessTotal=0;
    individuo *tmp = _poblacion;
    while(tmp != NULL){
        if(tmp->getID() != _seleccionado){
            fitnessTotal = fitnessTotal + (int)tmp->getFitness();
        }
        tmp = tmp->getSiguiente();
    }
    return fitnessTotal;
}   
   
individuo* poblacion::seleccionNatural() {
	int fitnessTotal = getSumaFitness();
    int afortunado = (rand()%fitnessTotal);
    int min = 0;
    int max = 0;
    individuo *tmp = _poblacion;
    while(tmp != NULL) {
		if(tmp->getID()!=this->_seleccionado) {
            max = max+(int)tmp->getFitness();
            if(afortunado < max)
                break;
            min = max;
        }
        tmp = tmp->getSiguiente();
    }
    return tmp;
}

void poblacion::mezclarPoblacion(individuo* pNewGen) {
	individuo *  debilGeneracionActual = MasDebil(_poblacion);
    individuo *  fuerteNuevaGeneracion = MasFuerte(pNewGen);

    while(debilGeneracionActual->getFitness() < fuerteNuevaGeneracion->getFitness()){
        cambiarIndividuos(debilGeneracionActual,fuerteNuevaGeneracion);
        debilGeneracionActual = MasDebil(_poblacion);
        fuerteNuevaGeneracion = MasFuerte(pNewGen);
    }
}

individuo* poblacion::MasFuerte(individuo *pPoblacion) {
	individuo* masFuerte= pPoblacion;
    individuo* tmp = pPoblacion;
    while(tmp != NULL){
        if(masFuerte->getFitness() < tmp->getFitness()) {
            masFuerte = tmp;
        }
        tmp = tmp->getSiguiente();
    }
    return masFuerte;
}

individuo* poblacion::MasDebil(individuo *pPoblacion) {
	individuo* masDebil = pPoblacion;
    individuo* tmp = pPoblacion;
    while(tmp != NULL){
        if(masDebil->getFitness() > tmp->getFitness()) {
            masDebil = tmp;
        }
        tmp = tmp->getSiguiente();
    }
    return masDebil;
}
    
    
// OJO intentar reparar esto...    
void poblacion::cambiarIndividuos(individuo* pIndividuo1, individuo* pIndividuo2) {
	int id = pIndividuo1->getID();
    bool* cromosoma = pIndividuo1->getCromosoma();
    double fitness = pIndividuo1->getFitness();
    int generacion = pIndividuo1->getGeneracion();
    int padre = pIndividuo1->getPadre();
    int madre = pIndividuo1->getMadre();
    pIndividuo1->setFitness(pIndividuo2->getFitness());

    pIndividuo1->setID(pIndividuo2->getID());
    pIndividuo1->setCromosoma(pIndividuo2->getCromosoma());
    pIndividuo1->setGeneracion(pIndividuo2->getGeneracion());
    pIndividuo1->setPadre(pIndividuo2->getPadre());
    pIndividuo1->setMadre(pIndividuo2->getMadre());
    pIndividuo2->setID(id);
    pIndividuo2->setCromosoma(cromosoma);
    pIndividuo2->setFitness(fitness);
    pIndividuo2->setGeneracion(generacion);
    pIndividuo2->setMadre(madre);
    pIndividuo2->setPadre(padre);
}

/**
 * aplica la funcion fitness a cada uno de los individuos de la poblacion
 * @param reproduccion* (puntero a la clase reproduccion), clase donde se
 * encuentra la funcion fitness 
 */
void poblacion::aplicarFitness() {
	individuo* tmp = _poblacion;
    while(tmp != NULL) {
        _reproduccion->fitness(tmp);
        tmp = tmp->getSiguiente();
    }
}

/**
 * imprime en la terminal al mejor individuo de cada generacion
 */
void poblacion::imprimirMejor() {
	individuo * mejor = _poblacion;
    individuo * tmp = _poblacion;
    while(tmp!=NULL){
		if(mejor->getFitness()<tmp->getFitness())
			mejor = tmp;
        tmp = tmp->getSiguiente();
    }
    std::cout << "Mejor individuo: id = " << mejor->getID() << " generacion = " << mejor->getGeneracion() << " fitness = " << mejor->getFitness() << " cromosoma = " << mejor->getCromosoma() << "\n";
}

/**
 * imprime la poblacion total, es decir individuo por individuo
 */
void poblacion::imprimirPoblacion() {
	individuo * tmp = _poblacion;
    while(tmp!=NULL) {
        tmp->imprimir();
        tmp = tmp->getSiguiente();
    }
    //imprimirMejor();
}
