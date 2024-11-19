#ifndef PTABLE_H
#define PTABLE_H

#include "bitmap.h"
#include "pcb.h"
#include <unordered_map>

#define MAX_PROCESS 1000

class PTable {
   private:
    Bitmap* bm;
    int psize;
    Semaphore* bmsem;

   public:
    PTable(int size);
    PCB* pcb[MAX_PROCESS];
    std::unordered_map<int, int> physicalPageToPID;
    ~PTable();
    int ExecUpdate(char* name);
    int ExitUpdate(int ec);
    int ExecPUpdate(char* name, int priority);
    int JoinUpdate(int id);
    int GetFreeSlot();
    bool IsExist(int pid);
    void Remove(int pid);
    char* GetFileName(int id);
};

#endif