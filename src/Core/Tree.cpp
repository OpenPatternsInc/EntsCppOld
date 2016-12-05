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

#include "Tree.h"

using namespace std;

Tree::Tree(string name): name_(name) {
    //entsFile = new EntsFile(this);
    //Initialize root. Allocated on heap, released in destructor with all other Ents.
    root_ = new Root();
    //Add root to the nameMap.
    entNameMap_.insert({root_->getName(), root_});
    //Useful for debugging to tell the user now when construction is done.
    cout << "New Tree created named \"" << name_ << "\".\n";
}

Tree::~Tree() {
    //We don't need to delete root_ separately because it will be handled
    //in the following loop.

    //Deallocate each Ent in the nameMap.
    for (pair<string, Ent*> i : entNameMap_) {
        delete i.second;
    }
    //Useful for debugging.
    cout << "Tree destructor completed.\n";
}

//TODO implement call here to UI to handle new estranged pairs.
void Tree::addEntToNameMap(Ent* entPtr, Ent* parentPtr) {
    //If no parent is given, make its parent root to prevent orphan Ents.
    if (parentPtr == 0) parentPtr = root_;
    entNameMap_.insert({entPtr->getName(), entPtr});
    //Connect the new ent and its new parent. Adds references for each other.
    Ent::connectUnchecked(parentPtr, entPtr);
}

NewEntStatus Tree::tryToCreateNewEnt(string name) {
    
    Ent* existingEntPtr;
    
    if ((existingEntPtr = getEntPtrByName(name)) == 0) {
        //Name is free, create the new Ent as a dynamic variable.
        Ent* newEnt = new Ent(name);
        //Add it to the nameMap.
        addEntToNameMap(newEnt);
        return SUCCESS;
    } else {
        //name has been taken
        return NAME_TAKEN;
    }
    //Why not...
    return UNDEFINED_ERROR;

}

Ent* Tree::getEntPtrByName(const string name) {
    //Get an iterator wrapping the pair which holds the desired Ent, or the end
    //of the map if not found. Since each pair is unique, it should hold at most one pair.
    EntNameMap::iterator it = entNameMap_.find(name);
    
    if (it != entNameMap_.end()) {
        //Iterator wasn't the "end" of the map iterator, so, we found something.
        return it->second;
    } else {
        //Nothing found, return null pointer.
        return nullptr;
    }
}
