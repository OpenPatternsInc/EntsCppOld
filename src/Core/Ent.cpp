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

#include "Ent.h"
#include <string>

using namespace std;

Ent::Ent() {
}

Ent::Ent(string name) : name(name) {
    //Useful in debugging, and generally good info for the CLI user.
    cout << "An Ent has been created with the name \"" << name << "\".\n";
}

Ent::~Ent() {
    //Deallocate the vectors. No need to deallocate what they point to.
    //delete parents_;
    //delete children_;
    //Useful for debugging.
    cout << "Ent \"" << getName() << "\" has been destroyed.\n";
}


int Ent::connectUnchecked(Ent* parent, Ent* child) {
    //Add references to the vectors holding the lists.
    parent->addChildUnchecked(child);
    child->addParentUnchecked(parent);

    cout << parent->getName() << " is now a parent of " << child->getName()
            << ".\n";

    return 0;
}


int Ent::connectUncheckedAndPrune(Ent* parent, Ent* child) {
    //Get the new parent's ancestors.
    unordered_set<Ent*> pAncestors = parent->getAncestors();
    //Get a pointer to the child's parents.
    vector<Ent*> existingParents = child->getParents();
    //Check if any of child's direct parents are in this set already.
    for (Ent* existingParent : existingParents) {
        //Insert it into the set. second indicates if it was added or not.
        if (!pAncestors.insert(existingParent).second) {
            //It wasn't added, so it must have already been there.
            disconnectUnchecked(existingParent, child);
            //TODO Should we break here?
        }
    }

    //Now actually connect them up!
    connectUnchecked(parent, child);

    //TODO Implement an analogous pruning algorithm for the child's descendents?

    return 0;
}

int Ent::disconnectUnchecked(Ent* parent, Ent* child) {
    //Get the parent's children.
    vector<Ent*> children = parent->getChildren();
    //Find child in the vector and remove it.
    for (vector<Ent*>::iterator it = children.begin(); it != children.end(); it++) {
        if (*it == child) {
            children.erase(it);
            //There should be only one, so break early.
            break;
        }
    }
    //Now get the child's parents.
    vector<Ent*> parents = child->getParents();
    //Find parent in the vector and remove it.
    for (vector<Ent*>::iterator it = parents.begin(); it != parents.end(); it++) {
        if (*it == parent) {
            parents.erase(it);
            //There should be only one, so break early.
            break;
        }
    }
    //No need to free the vectors, they are owned by the Ents themselves.
}

int Ent::setOverlap(Ent* a, Ent* b) {
    a->addOverlaps(b);
    b->addOverlaps(a);

    return 0;
}

int Ent::setExclusive(Ent* a, Ent* b) {
    a->addExclusive(b);
    b->addExclusive(a);

    return 0;
}


unordered_set<Ent*> Ent::canBeParentOf(Ent* entPtr) {
    //Create an empty unordered_set. Add any overlaps to it as we go.
    unordered_set<Ent*> overlap;
    //Make sure they aren't the same Ent. Do so by comparing unique names for now.
    if (name == entPtr->getName()) {
        //This shouldn't happen... well... return a set with just this Ent...
        overlap.insert(this);
        return overlap;
    }
    //Get this Ent's ancestors.
    unordered_set<Ent*> setA = getAncestors();
    //Add this Ent to the list, it counts.
    setA.insert(this);
    //Get the given Ent's descendents.
    unordered_set<Ent*> setB = entPtr->getDescendents();
    //Add the supplied Ent to the list as well.
    setB.insert(entPtr);
    //Find the smaller of the two sets. Ancestors should be smaller on average?
    if (setA.size() > setB.size()) {
        unordered_set<Ent*> temp = setA;
        setA = setB;
        setB = temp;
    }
    //Now setA is smaller, or they are equal, so, insert it into setB.
    //If the size of setB doesn't change after an Ent pointer is added,
    //then that Ent pointer was already there, and so is a overlap.
    for (Ent* ent : setA) {
        //Try to insert this ent into setB. If it doesn't work, we found overlap.
        if (!setB.insert(ent).second)
            overlap.insert(ent);
    }
    //Return what we've found. If the set is empty, then it can be the parent. 
    return overlap;
}


unordered_set<Ent*> Ent::getAncestors(unsigned short depth) {
    //List for this iteration of the recursion.
    unordered_set<Ent*> localList;
    //Have to draw the line somewhere. If we're too far down, return and empty set.
    if (depth > 50) return localList;
    //If there are no parents, the recursion will just stop.
    for (Ent* parent : parents) {
        localList.insert(parent);
        //get the parents of the parent
        unordered_set<Ent*> grandparents = parent->getAncestors(depth + 1);
        //add them to this list
        for (auto g : grandparents)
            localList.insert(g);
    }
    //now return the localList for this iteration of the recursion.
    return localList;
}


unordered_set<Ent*> Ent::getDescendents(unsigned short depth) {
    //List for this iteration of the recursion.
    unordered_set<Ent*> localList;
    //Make sure we don't blow up the universe. If we're too far in, just stop.
    if (depth > 50) return localList;
    //If there are no parents, the recursion will just stop.
    for (Ent* child : children) {
        localList.insert(child);
        //get the parents of the parent
        unordered_set<Ent*> grandchildren = child->getDescendents(depth + 1);
        //add them to this list
        for (auto g : grandchildren)
            localList.insert(g);
    }
    //now return the localList for this iteration of the recursion.
    return localList;
}

unordered_set<Ent*> Ent::getSiblings() {
    //Create an empty unordered_set to fill up.
    unordered_set<Ent*> siblings;
    //Go through each parent.
    for (Ent* parent : parents) {
        for (Ent* sibling : parent->children) {
            siblings.insert(sibling);
        }
    }
    //ok, we've filled the list. But we need to remove this Ent.
    siblings.erase(this);
    //now send a pointer of it back.
    return siblings;
}


void Ent::addParentUnchecked(Ent* parentPtr) {
    assert(parentPtr != 0);
    parents.push_back(parentPtr);
}