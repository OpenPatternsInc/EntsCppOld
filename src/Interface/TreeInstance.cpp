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

#include "TreeInstance.h"
#include "../Core/Tree.h"
#include <iostream>

using namespace std;

class Tree;

TreeInstance::TreeInstance(Tree* givenTree) : tree(givenTree) {
}


TreeInstance::~TreeInstance() {
    
}

TreeInstance::TreeInstance(const TreeInstance& treeInstance)
    : tree(treeInstance.tree) {
    
}

const EntX TreeInstance::getRoot() {
        
    return EntX(tree->getRoot());

}

    
const EntX TreeInstance::getEntByName(const string name) {

    return EntX(tree->getEntPtrByName(name));

}

const bool TreeInstance::isEntNameFree(const string name) {
    
    return tree->getEntPtrByName(name) == nullptr;
    
    
}

void TreeInstance::addEnt(Ent* ent, Ent* givenParent) {
    Ent* parent = tree->getRoot();
    if (givenParent != nullptr)
        parent = givenParent;
    tree->addEntToNameMap(ent, parent);
}

void TreeInstance::addEnt(EntX ent, EntX parent) {
    
    throw EntsInterfaceException();
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
}

void TreeInstance::rename(string newName) {
    tree->setName(newName);
}

const string TreeInstance::getName() {
    return tree->getName();
}

const bool TreeInstance::isEmpty() {
    return tree == nullptr;
}