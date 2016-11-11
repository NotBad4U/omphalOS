#include "kb.h"
#include "isr.h"
#include "idt.h"
#include "gdt.h"

int kmain()
{
    isrInstall();
    print("OMPHALOS : idt etablished\n");
    initPic();
    print("OMPHALOS : pic etablished\n");
    initGdt();
    print("OMPHALOS : gdt reloaded\n");

    print("Welcome to omphalOS operating system\nPlease enter a command\n");

    while (1)
    {
        print("\n$> ");
        string ch = readStr();

        if(strEql(ch,"cmd"))
        {
            print("\nYou are allready in cmd\n");
        }
        else if(strEql(ch,"clear"))
        {
            clearScreen();
        }
        else
        {
            print("\ncommand not found\n");
        }

        print("\n");
    }
}
