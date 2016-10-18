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
#include "Ent.h"
#include "Root.h"
#include "Hierarchy.h"

using namespace std;

class CLI
{
    
public:
    
    CLI();
    ~CLI();
    
    void listen();
    
    void parse(string str);
    
    inline void setFocus(Ent* ent_ptr) { m_focus_ptr = ent_ptr; }
    
    inline void setArch(Hierarchy* new_arch_ptr)
    {
        m_arch_ptr = new_arch_ptr;
        m_focus_ptr = new_arch_ptr->getRoot();
    }
    
    
private:
    
    bool m_exiting;
    
    Ent* m_focus_ptr;
    
    Hierarchy* m_arch_ptr;
    
    
    
    
    
};



#endif /* CLI_H */

