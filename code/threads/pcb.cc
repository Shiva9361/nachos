#include "synch.h"
#include "pcb.h"
#include <fstream>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

PCB::PCB(int id) {
    cout << "process_id " << id << endl;
    this->processID = kernel->currentThread->processID;
    joinsem = new Semaphore("joinsem", 0);
    exitsem = new Semaphore("exitsem", 0);
    multex = new Semaphore("multex", 1);
}

PCB::~PCB() {
    delete joinsem;
    delete exitsem;
    delete multex;

    if (thread) {
        thread->FreeSpace();
        thread->Finish();
        // delete thread;
    }
    // munmap(swap, 128 * 128);

    delete[] filename;
}

void StartProcess_2(void* pid) {
    int id;
    id = *((int*)pid);
    // Lay fileName cua process id nay
    char* fileName = kernel->pTab->GetFileName(id);

    AddrSpace* space;
    space = new AddrSpace(fileName);

    if (space == NULL) {
        printf("\nPCB::Exec: Can't create AddSpace.");
        return;
    }

    space->Execute();
    // kernel->currentThread->space = space;

    // space->InitRegisters();	// set the initial register values
    // space->RestoreState();	// load page table register

    // kernel->machine->Run();	// jump to the user progam
    ASSERT(FALSE);  // machine->Run never returns;
                    // the address space exits
                    // by doing the syscall "exit"
}

int PCB::Exec(char* filename, int id) {
    // cerr << filename << ' ' << pid << endl;
    multex->P();

    this->thread = new Thread(filename, true);
    if (this->thread == NULL) {
        printf("\nPCB::Exec: Not enough memory!\n");
        multex->V();  // Nha CPU de nhuong CPU cho tien trinh khac
        return -1;    // Tra ve -1 neu that bai
    }

    //  Đặt processID của thread này là id.
    this->thread->processID = id;
    // Đặt parrentID của thread này là processID của thread gọi thực thi Exec
    this->parentID = kernel->currentThread->processID;
    // Gọi thực thi Fork(StartProcess_2,id) => Ta cast thread thành kiểu int,
    // sau đó khi xử ký hàm StartProcess ta cast Thread về đúng kiểu của nó.

    // Không được sử dụng biến id ở đây, vì biến id là biến cục bộ,
    // nên khi hàm này kết thúc thì giá trị của biến này cũng bị xóa
    // Đừng hỏi tôi đã mất bao lâu để nhận ra điều này :)
    this->thread->Fork(StartProcess_2, &this->thread->processID);

    multex->V();
    // Trả về id.
    return id;
}
int PCB::ExecP(char* filename, int id, int priority) {
    // cerr << filename << ' ' << pid << endl;
    multex->P();

    this->thread = new Thread(filename, true, priority);
    if (this->thread == NULL) {
        printf("\nPCB::Exec: Not enough memory!\n");
        multex->V();  // Nha CPU de nhuong CPU cho tien trinh khac
        return -1;    // Tra ve -1 neu that bai
    }

    //  Đặt processID của thread này là id.
    this->thread->processID = id;
    // Đặt parrentID của thread này là processID của thread gọi thực thi Exec
    this->parentID = kernel->currentThread->processID;
    // Gọi thực thi Fork(StartProcess_2,id) => Ta cast thread thành kiểu int,
    // sau đó khi xử ký hàm StartProcess ta cast Thread về đúng kiểu của nó.

    // Không được sử dụng biến id ở đây, vì biến id là biến cục bộ,
    // nên khi hàm này kết thúc thì giá trị của biến này cũng bị xóa
    // Đừng hỏi tôi đã mất bao lâu để nhận ra điều này :)
    this->thread->Fork(StartProcess_2, &this->thread->processID);

    multex->V();
    // Trả về id.
    return id;
}

int PCB::GetID() { return thread->processID; }

int PCB::GetNumWait() { return numwait; }

void PCB::JoinWait() {
    // Gọi joinsem->P() để tiến trình chuyển sang trạng thái block và ngừng lại,
    // chờ JoinRelease để thực hiện tiếp.
    joinsem->P();
}

void PCB::ExitWait() {
    // Gọi exitsem-->V() để tiến trình chuyển sang trạng thái block và ngừng
    // lại, chờ ExitReleaseđể thực hiện tiếp.
    exitsem->P();
}

void PCB::JoinRelease() {
    // Gọi joinsem->V() để giải phóng tiến trình gọi JoinWait().
    joinsem->V();
}

void PCB::ExitRelease() {
    // Gọi exitsem->V() để giải phóng tiến trình đang chờ.
    exitsem->V();
}

void PCB::IncNumWait() {
    multex->P();
    ++numwait;
    multex->V();
}

void PCB::DecNumWait() {
    multex->P();
    if (numwait > 0) --numwait;
    multex->V();
}

void PCB::SetExitCode(int ec) { exitcode = ec; }

int PCB::GetExitCode() { return exitcode; }

void PCB::SetFileName(char* fn) { strcpy(filename, fn); }

char* PCB::GetFileName() {
    // cerr << "get file name" << ' ' << filename << endl;
    return filename;
}

void PCB::WriteToSwap(int physicalPage, unsigned int vpn) {
    // Check if the physical page is valid
    if (!thread) return;
    if (physicalPage < 0) {
        std::cerr << "Invalid physical page" << std::endl;
        return;
    }

    // Calculate the offset in the swap file where the page should be written
    unsigned int offset = vpn * PageSize;  // Assuming PageSize is a constant
    char buffer[50];  // Allocate enough space for the string
    sprintf(buffer, "id_%d", this->thread->processID);  // Format the string
    char* result = strdup(buffer);

    // Check if the swap file pointer is valid
    FILE* swapFile = fopen(result,
                           "r+");  // Open in read/write binary mode
    if (swapFile == NULL) {
        swapFile = fopen(result, "w+");
        fclose(swapFile);
        swapFile = fopen(result, "r+");
    }
    if (swapFile != NULL) {
        fseek(swapFile, offset, SEEK_SET);  // Move to the specified offset
        fwrite(&(kernel->machine->mainMemory[physicalPage * PageSize]), 1,
               PageSize, swapFile);
        fclose(swapFile);
    } else {
        perror("File opening failed");
    }
    thread->space->pageTable[vpn].valid = false;
    swappedPages.insert(vpn);
    std::cerr << "Written physical page " << physicalPage
              << " to swap file at vpn " << vpn << std::endl;
}

void PCB::ReadFromSwap(int physicalPage, unsigned int vpn) {
    // Check if the physical page is valid
    if (physicalPage < 0) {
        std::cerr << "Invalid physical page" << std::endl;
        return;
    }
    char buffer[50];  // Allocate enough space for the string
    sprintf(buffer, "id_%d", this->thread->processID);
    char* result = strdup(buffer);
    // Check if the swap file pointer is valid
    FILE* swapFile = fopen(result, "r+");

    // Calculate the offset in the swap file where the page should be read from
    unsigned int offset = vpn * PageSize;  // Assuming PageSize is a constant
    fseek(swapFile, offset, SEEK_SET);
    // Read the physical page from the swap file at the calculated offset
    fread(&(kernel->machine->mainMemory[physicalPage * PageSize]), 1, PageSize,
          swapFile);
    swappedPages.erase(vpn);
    std::cerr << "Restored physical page " << physicalPage
              << " from swap file at vpn " << vpn << std::endl;
}