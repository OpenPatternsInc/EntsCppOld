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
#include <algorithm>

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
    return 0;
}


int Ent::connectUncheckedAndPrune(Ent* parent, Ent* child) {
    //Get a copy of the new parent's ancestors.
    unordered_set<Ent*> pAncestors = parent->getAncestors();
    //Get the new child's direct parents.
    vector<Ent*> existingParents = child->getParents();
    //Check if any of child's direct parents are in this set already.
    for (Ent* existingParent : existingParents) {
        //Insert it into the set. second indicates if it was added or not.
        //TODO This assumes that existingParents has 1 of each...
        //Change the lists like parents, children, overlaps, etc. to unordered_set.
        if (!pAncestors.insert(existingParent).second) {
            //It wasn't added, so it must have already been there.
            //That means it's redundant.
            disconnectUnchecked(existingParent, child);
        }
    }
    //Now we do the same thing to see if one of parent's children is a descendent
    //of child already. That info is redundant and implied.
    //Get parent's children
    vector<Ent*> existingChildren = parent->getChildren();
    //And child's descendents.
    unordered_set<Ent*> cDescendents = child->getDescendents();
    //Go through each existing child and see if it's redundant.
    for (Ent* existingChild : existingChildren) {
        //Insert it into the set and see if it actually goes in.
        if (!cDescendents.insert(existingChild).second) {
            //It wasn't added, and so is redundant.
            disconnectUnchecked(parent, existingChild);
        }
    }

    //Now actually connect them up!
    connectUnchecked(parent, child);

    return 0;
}

//TODO add an exception for when this is called and they aren't even related.
int Ent::disconnectUnchecked(Ent* parent, Ent* child) {
    
    auto itP = std::find(parent->children.begin(), parent->children.end(), child);
    if(itP != parent->children.end())
        parent->children.erase(itP);
    
    auto itC = std::find(child->parents.begin(), child->parents.end(), parent);
    if (itC != child->parents.end())
        child->parents.erase(itC);
    
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


const unordered_set<Ent*> Ent::getParentalConflicts(Ent* entPtr) {
    //Create an empty unordered_set. Add any overlaps to it as we go.
    unordered_set<Ent*> overlap;
    //Make sure they aren't the same Ent. Do so by comparing unique names for now.
    if (name == entPtr->getName()) {
        //This shouldn't happen... well... return a set with just this Ent...
        overlap.insert(this);
        return overlap;
    }
    //Get this Ent's ancestors. First make a list to pass.
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


unordered_set<Ent*> Ent::getAncestors() {
    //Create the new list to pass along and collect Ancestors.
    unordered_set<Ent*> list;
    //Now call the recursive function to populate the list.
    getAncestors(&list);
    //Should now be populated.
    return list;
}


void Ent::getAncestors(unordered_set<Ent*>* list, int depth)
{
    //Have to draw the line somewhere. If we're too far down, return and empty set.
    //TODO Call an exception here? Could be useful.
    if (depth > 10) {
        cout << "Warning: Recursion overflow in Ent::getAncestors. Increase limit.\n";
        return;
    }
    //We need to get each parent, add it to the list, and call in recursion.
    for (Ent* parent : parents) {
        list->insert(parent);
        //We need to go deeper...
        parent->getAncestors(list, depth+1);
    }
    //All set.
    return;
}

unordered_set<Ent*> Ent::getDescendents() {
    //Create the list to pass along and populate.
    unordered_set<Ent*> list;
    //Call the recursive function.
    getDescendents(&list);
    //All set.
    return list;
}


void Ent::getDescendents(unordered_set<Ent*>* list, int depth)
{
    //Have to draw the line somewhere. If we're too far down, return and empty set.
    //TODO Call an exception here? Could be useful.
    if (depth > 10) {
        cout << "Warning: Recursion overflow in Ent::getDescendents. Increase limit.\n";
        return;
    }
    //We need to get each parent, add it to the list, and call in recursion.
    for (Ent* child : children) {
        list->insert(child);
        //We need to go deeper...
        child->getDescendents(list, depth+1);
    }
    //All set.
    return;
}

const unordered_set<Ent*> Ent::getSiblings() {
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
    assert(parentPtr != nullptr);
    parents.push_back(parentPtr);
}


void Ent::addChildUnchecked(Ent* childPtr) {
    assert(childPtr != nullptr);
    children.push_back(childPtr);
}