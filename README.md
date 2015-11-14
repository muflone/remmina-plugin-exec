    Project: Remmina Plugin EXEC 
Description: Remmina protocol plugin to execute an external process.
     Author: Fabio Castelli (Muflone) <muflone@vbsimple.net>
  Copyright: 2011-2016 Fabio Castelli (Muflone)
    License: GPL-2+

     Status: [![Build Status](https://travis-ci.org/muflone/remmina-plugin-exec.svg?branch=master)](https://travis-ci.org/muflone/remmina-plugin-exec)

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

## Install instructions

Download and extract [**Remmina Plugin Builder**](https://github.com/muflone/remmina-plugin-builder/releases/):

    wget -O remmina-plugin-builder.tar.gz https://github.com/muflone/remmina-plugin-builder/archive/1.2.0.0.tar.gz
    tar --extract --verbose --gzip --file remmina-plugin-builder.tar.gz
  
Copy the plugin source files to the **remmina-plugin-to-build** directory:

    cp --recursive remmina-plugin-exec CMakeLists.txt remmina-plugin-builder-1.2.0.0/remmina-plugin-to-build/

Build the plugin using Remmina Plugin Builder:

    cd remmina-plugin-builder-1.2.0.0
    cmake -DCMAKE_INSTALL_PREFIX=/usr .
    make
  
Install the plugin into the Remmina plugins directory (may need sudo or root
access):

    sudo make install

You'll find it in the remmina connection editor.
