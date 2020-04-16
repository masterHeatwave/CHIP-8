#include <iostream>
#include <cstring>
#include <fstream>
#if 0

using namespace std;


    // define the keyboard

    unsigned char chip8_fontset[80] =
            {
                    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
                    0x20, 0x60, 0x20, 0x20, 0x70, // 1
                    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
                    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
                    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
                    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
                    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
                    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
                    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
                    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
                    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
                    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
                    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
                    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
                    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
                    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
            };

    interpreter = 0x200; // 0x000 to 0x1FF for the interpreter

    //registers

    I = 0;
    sp = 0;
    sound_timer = 0;
    delay_timer = 0;

    //clear registers, stack and memory

    memset(V, 0, sizeof(V));
    memset(stack, 0, sizeof(stack));
    memset(memory, 0, sizeof(memory));

    draw_flag = false;


 //load fontset from 0 to 80

    for (int i = 0; i < 80; i++)
    {
        memory[i] = chip8_fontset[i];
    }

    //resetting display and keypad

    memset(display, 0, sizeof(display));
    memset(keypad, 0, sizeof(keypad));


#endif

#include <stdint.h>
#include <stdio.h>


uint8_t v[16];
uint16_t sp, pc, I;

uint8_t ram[4096];


int main(int, char**)

{
    printf("masterHeatwave CHiP-8 emulator\n");

    FILE* f;

    // Load the program to RAM


    f = fopen("IBM.ch8", "rb");


    fread(ram + 0x200, 132, 1, f);

    fclose(f);

    //Initialize register state

    pc = 0x200;

    //loop forever

    for (;;)
    {
        //OPCODE fetch from RAM 

        uint16_t opcode=ram[pc] * 256 + ram[pc+1];

        //Move PC to next OPCODE

        pc=pc+2;

        // OPCODE field decoding

        uint16_t nnn=opcode&0xFFF; //**HomeWork Google C Bitwise Operators**

        uint8_t x=(opcode>>8)&0xF;

        uint8_t y=(opcode>>4)&0xF;

        uint8_t kk=opcode&0xFF;
        
        uint8_t K=(opcode>>12)&0xF;

        uint8_t L=(opcode>>0)&0xF; 

        uint8_t k=(opcode>>0)&0xF;

        //OPCODE instruction decoding

        if (opcode==0x00E0)
        {
            printf("CLS\n");
        }
        else if (K==0xA)
        {
            //LD I, nnn
            I=nnn;
        }
        else if (K==0x6)
        {
            //LD Vx, kk
            v[x]=kk;
        }
        else if (K==0xD)
        {
            //DRW Vx, Vy, nibble
            printf("DRW V%X, V%X, %X\n", x,y,k);
        }
        else if (K==0x7)
        {
            //ADD Vx, kk
            v[x]=v[x]+kk;
        }
        else if (K==0x1)
        {
            //JP nnn
            pc=nnn;
        }
        else 
        {
            printf("unknown opcode: %04X\n", opcode);
            getchar();
        }
        

    }
    
}