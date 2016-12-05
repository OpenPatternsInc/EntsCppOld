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

#include "EntX.h"

using namespace std;

class EntX;

EntX::EntX() : ent(nullptr) {
    
}

EntX::EntX(const EntX& entX) : ent(entX.ent) {
    
}

EntX::EntX(Ent* entPtr) : ent(entPtr) {
    
}

//TODO Should we deallocate the held Ent on deletion of this object?
//Probably not. EntXs are simply used as a temporary way for subclasses to
//treat an Ent like an object, without the ability to edit it. Therefore,
//the destructor will be called each time an EntX leaves scope.
EntX::~EntX() {
    
}


vector<EntX> EntX::wrap(vector<Ent*>* ents) {
    
    vector<EntX> vec;
    
    for (Ent* ent : *ents)
        vec.push_back(EntX(ent));
    
    return vec;
}


vector<EntX> EntX::wrap(unordered_set<Ent*>* ents) {
    
    vector<EntX> vec;
    
    for (Ent* ent : *ents)
        vec.push_back(EntX(ent));
    
    return vec;
    
    
}

const bool EntX::equals(EntX otherEntX) {

    return ent == otherEntX.ent;
    
}

const bool EntX::isEmpty() {
        return ent == nullptr;
    }