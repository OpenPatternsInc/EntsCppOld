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

#include <iostream>
#include <vector>

#include "TreeAnalyzer.h"

using namespace std;


/**
 * Analyze a given Ent and determine if it has children which don't reference
 * each other.
 * For now, assume that the hierarchy is logically sound, except for missing
 * information. For instance, assume that if two Ents are directly exclusive, that
 * they aren't also overlapping or in a parent-child relationship. But, perhaps
 * two children of an Ent aren't exclusive or overlapping, and so the user will
 * be queried for that information, because to exhaustively categorize the Ents,
 * it must be either one or the other, or they must be in a parent-child
 * relationship.
 * 
 * @param parent     A pointer to the parent whose children will be analyzed.
 * @return          A pointer to an EstrangedPair variable, or nullptr if none found.
 */
EstrangedPair* TreeAnalyzer::analyzeForEstrangedChildren(Ent *parent) {
   //Get the children of this Ent.
   vector<Ent*>* children = parent->getChildren();
   //How many children are there? (could be a short... whatever...)
   const unsigned int childrenSize = children->size();
   //If their are two or more children, see if they all reference each other.
   if (childrenSize > 1) {
       //Check if all children reference each other.
       //Only need to check each pair once, so we don't need to check the last.
       for (int a = 0; a < childrenSize - 1; a++) {
           //Get the Ent at a.
           Ent* entA = children->at(a);
           //Don't need to check an Ent's relationship to itself.
           for (int b = a + 1; b < childrenSize; b++) {
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
               //Now for the overlaps. Do not free this variable.
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
                   //a and b aren't connected yet, so lets return that pair!
                   return new EstrangedPair(entA, children->at(b));
               }
           } //end b loop
       } //end a loop
   }
   //No pairs were found. Return a null pointer.
   return nullptr;
} //end analyzeForEstrangedChildren()