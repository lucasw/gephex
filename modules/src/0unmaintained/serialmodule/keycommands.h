/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

/* 
 * Predefined commands that are executed by keys.
 * The commands are subdivided in 8 groups of 10 commands.
 * 
 * The current group is chosen with the keys F1 to F8.
 * The keys 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 then choose the command
 * inside the group.
 */
static const char commands[90][256] =
{
  "g 0",
  "q",
  "v 0",
  "g 0 real 1 0 0 mon 4 3",
  "q real 1 0 0 mon 4 3",
  "v 0 mon 4 3",
  "v 0 blk 3 0 0",
  "v 0 blk 3 1 0",
  "v 0 blk 3 0 1",
  "v 0 blk 3 1 1",
  "real 1 0 0 m 0 mon 4 3 blk 2 1 1",
  "blk 2 1 1",
  "blk 2 1 1 real 1 0 0 mon 0 0 mon 3 0 mon 0 3 mon 3 3",
  "real 1 0 0 sm 1 1 2 2 mon 0 0 mon 3 0 mon 0 3 mon 3 3",
  "real 1 0 0 zl 0 zl 2 blk 2 0 1 blk 2 2 1",
  "real 1 0 0 sm 0 0 2 2 sm 2 2 2 2 blk 2 0 2 blk 2 2 0",
  "real 1 0 0 sm 0 2 2 2 sm 2 0 2 2 blk 2 2 2 blk 2 0 0",
  "real 1 0 0 mon 4 3",
  "real 1 0 0 zl 0 sp 0 zl 3 sp 3",
  "real 1 0 0 zl 0 zl 3 mon 1 2 mon 2 1",
  "bk m 0 mon 4 3",
  "rd m 0 mon 4 3",
  "gn m 0 mon 4 3",
  "bl m 0 mon 4 3",
  "co 50  0 50 m 0 mon 4 3",
  "co 60 60  0 m 0 mon 4 3",
  "co  0 60 60 m 0 mon 4 3",
  "co  0 40 40 m 0 mon 4 3",
  "co 60 40 20 m 0 mon 4 3",
  "co 60 20 40 m 0 mon 4 3",
  "co 30  0 30 m 0 mon 4 3",
  "co 30 30  0 m 0 mon 4 3",
  "co  0 30 30 m 0 mon 4 3",
  "co 30  0  0 m 0 mon 4 3",
  "co  0 30  0 m 0 mon 4 3",
  "co  0  0 30 m 0 mon 4 3",
  "",
  "",
  "",
  "",
  "farbe 1",
  "farsn1 1",
  "farsn2 1",
  "farspi 1",
  "fardal 1",
  "farsmo 1",
  "farbec 1",
  "fasn1c 1",
  "fasn2c 1",
  "faspic 1",
  "specia 1",
  "games 1",
  "fadalc 1",
  "fasmoc 1",
  "bkmon 1",
  "blkmon 1",
  "verl 1",
  "",
  "",
  "",
  "act 1",
  "g 0 pitc 1",
  "v 0 pitc 1",
  "q pitc 1",
  "",
  "",
  "",
  "",
  "",
  "",
  "colon 0 m 0 mon 4 3",
  "colon 1 m 0 mon 4 3",
  "colon 2 m 0 mon 4 3",
  "colon 3 m 0 mon 4 3",
  "colon 3 m 0 mon 4 3",
  "colon 4 m 0 mon 4 3",
  "colon 5 m 0 mon 4 3",
  "colon 6 m 0 mon 4 3",
  "",
  "",
  "",
  ""
};
