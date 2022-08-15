#include <iostream>
#include <array>
#include <vector>
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>
#define start 0x200
using namespace std;

uint16_t fetch(uint16_t &PC);
array <char, 4*1024> ram; //the program memory
uint8_t V[16];//15 general purpose registers and VF flag
uint16_t PC=0x0000;//16 bit program counter
uint16_t I=0x0000; //16 bit index register
vector <uint16_t> stack; //stack for 16bit addresses which is used for call backs
uint8_t nDelayTimer=0x00;
uint8_t nSoundTimer=0x00;

int main (void)
{
     char number;
     //setting the ram to zero
     for (auto &val: V) val=0x00; //setting all of the registers to zero
//======================writes the content of rom to ram starting at address 0x200==============//
     ifstream rom;
     rom.open("rom.ch8", ios::binary|ios::ate);
/**
 * 
 * another possible way to load the rom
     std::streampos size=rom.tellg();
     char *buffer = new char [size];
     rom.seekg(0,ios::beg);
     rom.read(buffer,size);
     for (int i=0; i <size;++i)
     {
          ram[start+i]=buffer[i];
          //cout<<to_string(buffer[i])<<endl;
     }*/
     int size=rom.tellg();
     rom.seekg(ios::beg);
     for (int i=0; i<size; ++i)
     {
          char eu;
          rom.get(eu);
          ram[start+i]=eu;
     }
     

     rom.close();
     //delete[] buffer;

    
     
//=====================================================================================================
  PC=0x0006;
  cout<<"========"<<endl;
  while (true)
  {
     //fetch(PC);
     uint16_t opcode=fetch(PC);
     uint8_t nFirstNibble=(opcode & 0xF000)>>12; //exteracts first nibble
     uint8_t nLastNibble =(opcode &0x000F);  //exteracts the last nibble
     uint8_t nSecondNibble =(opcode & 0x0F00)>>8; //exteracts the second nibble
     uint8_t nThirdNibble =(opcode & 0x00F0)>>4; //exteracts the third nibble
     uint8_t nNN = (nThirdNibble<<4 | nLastNibble); //exteracts the second byte
     uint16_t nNNN=(opcode &0XFFF);//12 bit address

     
    
  }
  

    
}
//=============================Fetchs the instructions, returns it and increment the program counter by 2===============//
uint16_t fetch(uint16_t &PC)
{
     uint8_t ophi=ram[start+PC];
     uint8_t oplo=ram[start+PC+1];
     uint16_t opcode = (ophi<<8) | oplo;
     if (PC+2 <= 0x1000)
     {
          PC+=2;
     }
     return opcode;
}
//========================================================================================================================


