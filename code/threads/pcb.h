#ifndef PCB_H
#define PCB_H
#include <fstream>
#include <set>
#include <unordered_map>
class PCB {
   private:
    Semaphore *joinsem;
    Semaphore *exitsem;
    Semaphore *multex;

    int exitcode;
    int numwait;
    char filename[128];

   public:
    Thread *thread;
    int parentID;
    int processID;
    PCB();
    PCB(int id);
    ~PCB();

    int Exec(char *filename, int pid);
    int ExecP(char *filename, int pid, int priority);
    int GetID();
    int GetNumWait();

    void JoinWait();
    void ExitWait();
    void JoinRelease();
    void ExitRelease();

    void IncNumWait();
    void DecNumWait();

    void SetExitCode(int ec);
    int GetExitCode();

    void SetFileName(char *fn);
    char *GetFileName();
    void WriteToSwap(int physicalPage, unsigned int vpn);
    void ReadFromSwap(int physicalPage, unsigned int vpn);
    std::ofstream file;
    char *swap;
    std::set<unsigned int> swappedPages;
};

#endif
