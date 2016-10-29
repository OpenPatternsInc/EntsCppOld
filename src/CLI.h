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

#ifndef CLI_H
#define CLI_H

#include <string>
#include <iostream>
#include <unordered_set>
#include "Ent.h"
#include "Root.h"
#include "Hierarchy.h"
#include "Analyzer.h"

using namespace std;

class CLI {
    /** If set to true, the after the next command is parsed, stop listening
     * and return control to the calling function. */
    bool exiting_;
    /** Points to the current Ent of focus. */
    Ent* focusPtr;
    /** Points to the Hierarchy Currently being explored.*/
    Hierarchy* archPtr;
    /**
    * List the given Ent's children.
    * Do not alter the Ent!
    * @param ent_ptr
    */
    void listChildren(Ent* ent_ptr);
    /**
    * Lists the given Ent's parents.
    * Do not alter the Ent!
    * @param ent_ptr
    */
    void listParents(Ent* ent_ptr);
    
    void listAncestors(Ent* entPtr);
    
    void listDescendents(Ent* entPtr);
    
    
    /**
     * Sees if the given text is a command, and if so, sets the given argument
     * string to the substring after the command.
     * @param command       The command identifier used first.
     * @param text          The full input text.
     * @param argument      Pointer to the string holding the argument.
     * @return 
     */
    const bool isCommand(const string command, const string text, string *argument) {
        
        if (text.find((command + " ")) == 0) {
            //The text started with the command and then a space.
            //Extract the argument and set the string given.
            *argument = text.substr(command.size() + 1);
            return true;
        } else {
            //The text did not start with the given command, so, return false.
            return false;
        }
    }
    
    void analyzeForEstrangedChildren(Ent* entPtr);
    
    void handleEstrangedPairs(vector<EstrangedPair*> *pairs, Ent *parent);
    

public:

    /**
     * Construct a CLI object with the given Hierarchy. We don't give a no-arg
     * constructor because we just want to always initialize a CLI with a
     * Hierarchy anyways.
     * @param arch_ptr
     */
    CLI(Hierarchy* arch_ptr);
    /**
     * Do not deallocate the Hierarchy or the Ent of focus.
     * The user may want to instead open up a GUI or something else.
     * There is no other way to browse Hierarchies yet though.
     */
    ~CLI();
    /**
     * Starts listening for commands in the console. Commands are used to explore
     * and edit the Hierarchy.
     */
    void listen();
    /**
    * Parse the given command and carry out the actions it represents.
    * @param str   Raw string of the command. Doesn't include the "<".
    */
    void parseCommand(string str);
    /**
     * Set the focus of the CLI listener to the given Ent.
     * @param ent_ptr   Points to the new focus.
     */
    void setFocus(Ent* ent_ptr) {
        focusPtr = ent_ptr;
    }
    /**
     * Sets the Hierarchy to explore.
     */
    void setArch(Hierarchy* new_arch_ptr) {
        archPtr = new_arch_ptr;
        focusPtr = new_arch_ptr->getRoot();
        //TODO Tell the user which Hierarchy is now being explored.
    }
    /**
     * Prints the help section to console.
     */
    void printHelp() {
        cout << "Commands with no argument:\n"
                << "\t>f\t\tPrints out current Ent of focus.\n"
                << "\t>p\t\tLists the focus' parents.\n"
                << "\t>c\t\tLists the focus' children.\n"
                << "\t>s\t\tLists the siblings of focus.\n"
                << "\t>e or >exit\tExits command interface.\n"
                << "\t>h\t\tPrints this help section.\n"
                << "\t>b\t\tUsed to bring up an optional breakpoint if desired.\n"
                << "Commands with one argument:\n"
                << "\t>f [Ent name]\tChanges focus to the Ent with the given name.\n"
                << "\t>n [Ent name]\tCreates a new Ent with the given name, if available,\n"
                << "\t\t\tand sets its only parent as root.\n";
        
    }




};



#endif /* CLI_H */

