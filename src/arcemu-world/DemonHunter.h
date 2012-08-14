#ifndef _DEMONHUNTER_H
#define _DEMONHUNTER_H

class DemonHunter : public Player
{
   public:
     DemonHunter(uint32 guid) : Player(guid) {}

      bool IsDemonHunter() { return true; }
};

#endif