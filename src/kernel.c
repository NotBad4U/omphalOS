#include "kb.h"
#include "isr.h"
#include "idt.h"

int kmain()
{
    isr_install();

    clearScreen();
    print("Welcome to omphalOS operating system\nPlease enter a command\n");

    while (1)
    {
        print("\n$> ");

        string ch = readStr();
        print(ch);
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
