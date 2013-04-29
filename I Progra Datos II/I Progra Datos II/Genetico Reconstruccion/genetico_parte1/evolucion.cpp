/*
 * evolucion.cpp
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


#ifndef EVOLUCION_H
#define EVOLUCION_H

#include "individuo.h"

class evolucion {

public:
    void calcularFuncionNormal(Individuo * pIndividuo);

};
#endif // EVOLUCION_H


/**
 * aproxima a un individuo a la solucion real, es decir lo convierte en 
 * un individuo mas apto a los demas debido a que es la solucion exacta 
 * a la funcion fitnes
 * @param pIndividuo el individuo que evoluciona y se le asigna el nuevo
 * valor de fitness 
 */
void evolucion::calcularFuncionNormal(individuo * pIndividuo) {
    //int resultado = (int)pow(M_E,(-(1/(pow(150,4)))*(pIndividuo->getCromosoma()-32000)))*1000;
    pIndividuo->setFitness(resultado);
}


// - - - - - - - - - - - - Tester de la clase - - - - - - - - - - - - -

//int main(int argc, char **argv) {
//	return 0;
//}

