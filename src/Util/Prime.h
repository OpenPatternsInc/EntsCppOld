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

#ifndef PRIME_H
#define PRIME_H

#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

/**
 * This file contains programs to generate prime numbers. These prime numbers will
 * be used to represent the hierarchal location of Ents via factorization.
 * 
 * Still deciding what the best course of action is. Hopefully the prime approach
 * will limit recursive searching and provide O(1) speed for certain actions,
 * with calculations done up-front like testing "are humans fish?" without needing
 * to iterate through the hierarchy which can be relatively "unordered" compared
 * to traditional trees.
 */
class Prime {
    
    /**
     * Vector holding a list of prime numbers from 1 to the nth prime, where
     * n is the size of the vector.
     */
    vector<unsigned int> primes;
    /**
     * Keeps track of which primes have already been given.
     */
    unsigned int nextPrimeIndex;
    /**
     * How many new primes to generate at a time.
     */
    int batchNum;
    
public:
    /**
     * Constructs a Prime class which is only filled with 1.
     */
    Prime();
    /**
     * Destroys the Prime instance and deletes the vector.
     */
    ~Prime();
    /**
     * Generates n more primes to add to the vector. 
     */
    void generateMorePrimes(int n);
    /**
     * Returns the next prime number after currentPrimeIndex.
     */
    unsigned int getNextPrime();
    
    
    
    
};



#endif /* PRIME_H */

