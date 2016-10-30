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
#include "Tree.h"
#include "CLI.h"
#include "Util/IO.h"
#include "Util/EntsFile.h"
//#include "Util/Prime.h"

using namespace std;

int main(int argc, char** argv) {
    
    //**
    //Create a new Ent Hierarchy. Starts off with just a root Ent.
    Tree tree;
    //Make a new EntsFile to handle the tree.
    EntsFile entsFile(&tree);
    //Make a new CLI instance and have it explore the hierarchy.
    CLI cli(&entsFile);
    //Tell the CLI to listen for commands in the console.
    cli.listen();
    //*/

    return 0;
}

