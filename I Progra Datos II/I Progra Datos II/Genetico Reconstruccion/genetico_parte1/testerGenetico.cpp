/*
 * testerGenetico.cpp
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
#include "individuo.h"
#endif

#ifndef REPRODUCCION_H
#include "reproduccion.h"
#endif

#ifndef POBLACION_H
#include "poblacion.h"
#endif

#include <iostream>

int main(int argc, char **argv) {
	reproduccion* tester1_rep = new reproduccion(5,5);
	poblacion* tester1_pob = new poblacion(50,25,50,false, tester1_rep);
	tester1_pob->inicializar();
	
	for (int z=0; z<5; z++) {
		
		tester1_pob->aplicarFitness(tester1_rep);
		tester1_pob->imprimirPoblacion();
		tester1_pob->nuevaGeneracion(tester1_rep);

    }
	
	return 0;
}

