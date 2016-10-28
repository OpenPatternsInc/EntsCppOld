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

#ifndef ANALYZER_H
#define ANALYZER_H

#include <iostream>
#include "Ent.h"

using namespace std;

class EstrangedPair {
    
protected:
    Ent *entA, *entB;
public:
    EstrangedPair(Ent* entX, Ent* entY) : entA(entX), entB(entY) {}
    
    Ent* getA() { return entA; }
    Ent* getB() { return entB; }
    
};

class Analyzer {
    
public:
    
    /**
     * Analyze a given Ent and determine if action is needed to organize it
     * within the hierarchy.
     * For now, assume that the hierarchy is logically sound, except for missing
     * information. For instance, assume that if two Ents are exclusive, that
     * they aren't also overlapping. But, perhaps two children of an Ent aren't
     * exclusive or overlapping, and so the user will be queried for that
     * information, because to exhaustively categorize the Ents, it must be either
     * one or the other, or they must be in a parent-child relationship.
     * @param ent
     * @return 
     */
    static vector<EstrangedPair*>* analyzeForEstrangedPairs(Ent* ent) {
        //If we find any pairs of children which don't reference each other,
        //add that pair to this vector.
        vector<EstrangedPair*>* estrangedPairs = new vector<EstrangedPair*>;
        //Get the children of this Ent.
        vector<Ent*>* children = ent->getChildren();
        //How many children are there? (could be a short... whatever...)
        const unsigned int num = children->size();
        //If their are two or more children, see if they all reference each other.
        if (num > 1) {
            //Check if all children reference each other.
            //Only need to check each pair once, so we don't need to check the last.
            for (int a = 0; a < num - 1; a++) {
                //Get the Ent at a.
                Ent* entA = children->at(a);
                //Don't need to check an Ent's relationship to itself.
                for (int b = a + 1; b < num; b++) {
                    //A must either be exclusive to or overlap b.
                    //If neither, then the user needs to take an action.
                    bool connected = false;
                    //Get a's exclusives and search those first.
                    vector<Ent*>* exclusives = entA->getExclusives();
                    //See if b is one of them. See if the pointers are equal.
                    for (Ent* current : *exclusives) {
                        if (current == children->at(b)) {
                            //OK, so a is exclusive to b.
                            connected = true;
                            break;
                        }
                    } //end looping through exclusives
                    if (connected)
                        continue;
                    //now for the overlaps
                    vector<Ent*>* overlaps = entA->getOverlaps();
                    //see if b is one of them.
                    for (Ent* current : *overlaps) {
                        if (current == children->at(b)) {
                            //OK, so a overlaps with b.
                            connected = true;
                            break;
                        }
                    } //end overlaps loop
                    //Here, we've checked if a either overlaps or excludes b,
                    //so, if connected isn't true yet, then it is neither.
                    if (!connected) {
                        //a and b aren't connected yet, so lets record that
                        estrangedPairs->push_back(new EstrangedPair(entA, children->at(b)));
                    }
                    
                } //end b loop
            } //end a loop
        }
        //Return the vector.
        return estrangedPairs;
    }
    
    
    
    
};



#endif /* ANALYZER_H */

