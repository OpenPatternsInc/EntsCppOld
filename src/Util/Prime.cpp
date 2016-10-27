/*
 * This file is part of the Ents Hierarchy Database Project.
 * Copyright (C) 2016 OpenPatterns Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Prime.h"

using namespace std;

Prime::Prime() {
    
    primes.push_back(1);
    primes.push_back(2);
    primes.push_back(3);
    
}

Prime::~Prime() {
}

void Prime::generateMorePrimes(int n) {
    
    int numSoFar = primes.size();
    
    unsigned int max = primes[numSoFar - 1];
    
    unsigned int candidate = max + 2;
    
    unsigned int added = 0;
    
    while (added < n) {
        for (int p = 1; p < primes.size(); p++) {
            if (candidate % primes[p] == 0)
                break;
            else if (primes[p] * primes[p] > candidate) {
                //found a primeroni!
                cout << "Prime: " << candidate << endl;
                primes.push_back(candidate);
                max = candidate;
                added++;
                break;
            }
        }
        candidate += 2;
    }
    
}

unsigned int Prime::getNextPrime() {
    
    
    
    
}