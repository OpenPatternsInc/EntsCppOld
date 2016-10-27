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

#include "Hierarchy.h"

using namespace std;

Hierarchy::Hierarchy() {
    //Initialize root. Allocate on heap, released in destructor with all other Ents.
    root_ = new Root();
    //Add root to the map.
    entNameMap_.insert({root_->getName(), root_});
    //Useful for debugging to tell the user now when construction is done.
    cout << "New Hierarchy created.\n";
}

Hierarchy::~Hierarchy(void) {
    //We don't need to delete root_ separately because it will be handled
    //in the following loop.

    //Deallocate each Ent in the nameMap.
    for (pair<string, Ent*> i : entNameMap_) {
        delete i.second;
    }
    //Useful for debugging.
    cout << "Hierarchy destructor completed.\n";
}


void Hierarchy::addEntToNameMap(Ent* entPtr, Ent* parentPtr) {
    //If no parent is given, make its parent root to preven orphan Ents.
    if (parentPtr == 0) parentPtr = root_;
    entNameMap_.insert({entPtr->getName(), entPtr});
    //Connect the new ent and its new parent. Adds references for each other.
    Ent::connect(parentPtr, entPtr);
}

NewEntStatus Hierarchy::tryToCreateNewEnt(string name) {
    
    Ent* existingEntPtr;
    
    if ((existingEntPtr = getEntPtrByName(name)) == 0) {
        //name is free, create the new Ent as a dynamic variable.
        //TODO remember to delete this variable from memory when appropriate.
        Ent* newEnt = new Ent(name);
        addEntToNameMap(newEnt);
        return SUCCESS;
    } else {
        //name has been taken
        return NAME_TAKEN;
    }
    //Why not...
    return UNDEFINED_ERROR;

}

Ent* Hierarchy::getEntPtrByName(const string name) {
    //Get an iterator wrapping the pair which holds the desired Ent, or the end
    //of the map if not found. Since each pair is unique, it should hold at most one pair.
    EntNameMap::iterator it = entNameMap_.find(name);
    
    if (it != entNameMap_.end()) {
        //Iterator wasn't the "end" of the map iterator, so, we found something.
        return it->second;
    } else {
        //Nothing found, return 0 pointer.
        return 0;
    }
}

