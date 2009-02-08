/******************************************************************************
* FOBS C++ Header File
* Copyright (c) 2004 Omnividea Multimedia S.L
* Coded by José San Pedro Wandelmer
*
*    This file is part of FOBS.
*
*    FOBS is free software; you can redistribute it and/or modify
*    it under the terms of the GNU Lesser General Public License as
*    published by the Free Software Foundation; either version 2.1 
*    of the License, or (at your option) any later version.
*
*    FOBS is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU Lesser General Public License for more details.
*
*    You should have received a copy of the GNU Lesser General Public
*    License along with FOBS; if not, write to the Free Software
*    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
******************************************************************************/

//Forward declaration of ffmpeg structs
struct AVPacket;

class PacketBuffer
{
   class Packet;
   Packet* buffer;

   int index0;
   int indexF;
   int countV;
   
   void dupPacket(AVPacket *pkt, int index);

   public:
   static const int maxPktNumber;
   PacketBuffer();
   ~PacketBuffer();
   int count();
   void clear();
   AVPacket* readNext();
   void deleteNext();
   AVPacket* extractNext();
   bool append(AVPacket* pkt);
   bool prepend(AVPacket *pkt);
   
};