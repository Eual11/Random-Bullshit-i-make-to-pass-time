#include <iostream>
#include <array>
#include <vector>
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#define start 0x200
using namespace std;
using namespace sf;
uint16_t fetch(uint16_t &PC);
array <char, 4*1024> ram; //the program memory
uint8_t V[16];//15 general purpose registers and VF flag
uint16_t PC=0x0000;//16 bit program counter
uint16_t I=0x0000; //16 bit index register
vector <uint16_t> stack; //stack for 16bit addresses which is used for call backs
uint8_t nDelayTimer=0x00;
uint8_t nSoundTimer=0x00;
RenderWindow window(VideoMode(480,320), "chip 8");

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
//=======================FONTS========================================
     const unsigned int FONTSET_SIZE = 80;
     uint8_t fontset[FONTSET_SIZE] =
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

for (int i=0; i<80; ++i)
{
     ram[i]=fontset[i];
}
//=======================================================================================

//=========================the screen=================================================////
array <uint8_t,2048> screen={0};

///======================================================

     
//=====================================================================================================
  PC=0x0000;
  cout<<"========"<<endl;
  while (window.isOpen())
  {
     //===================Fetching opcode=================================///
     uint16_t opcode=fetch(PC);


     uint8_t nFirstNibble=(opcode & 0xF000)>>12; //exteracts first nibble
     uint8_t nLastNibble =(opcode &0x000F);  //exteracts the last nibble
     uint8_t nSecondNibble =(opcode & 0x0F00)>>8; //exteracts the second nibble
     uint8_t nThirdNibble =(opcode & 0x00F0)>>4; //exteracts the third nibble
     uint8_t nNN = (nThirdNibble<<4 | nLastNibble); //exteracts the second byte
     uint16_t nNNN=(opcode &0XFFF);//12 bit address
     //================================================================================


     //===============================Decoding the instructions======================================

     switch (nFirstNibble)
     {
          case 0:
          if (opcode==0x00E0)
          {
               screen.fill(0);
               //cout<<"cleared"<<endl;
          }
          else if (opcode == 0x0EE)
          {
               //pop an address from the stack and set the PC to that value
               uint16_t addr=stack.back();
               PC=addr;
               stack.pop_back();
          }
          break;

          case 1:
          //jumps to addresss NNN
                PC=nNNN;
           break;

          case 2:
          //sets the PC go NNN and add that value to the stack;
               PC=nNNN;
               stack.push_back(nNNN);
          break;

          case 3:
          // skips one instruction if VX==nNN
          if (V[nSecondNibble]==nNN)
          {
               PC+=2;
          }
          break;

          case 4:
          //skips one instruction if VX!=nNN
               if (V[nSecondNibble]!=nNN)
               {
                    PC+=2;
               }
               break;

          case 5:
          //skips if VX==VY
               if (V[nSecondNibble]==V[nThirdNibble])
               {
                    PC+=2;
               }
          break;

          case 6:
          //sets the register VX to nn;
               V[nSecondNibble]=nNN;
          break;

          case 7:
          //adds value NN to register vx
          V[nSecondNibble]+=nNN;
          break;

          case 8:
          //logical and arthemetic operations

          switch(nLastNibble)
          {
               case 0:
                         //sets VX to VY
                         V[nSecondNibble]=V[nThirdNibble];
                    break;
               case 1:
                         //VX= VX|VY
                         V[nSecondNibble]=V[nSecondNibble] | V[nThirdNibble];
                         break;
               case 2:
                         //VX=VX&VY
                         V[nSecondNibble]=V[nSecondNibble] & V[nThirdNibble];
                         break;
               case 3:
                         V[nSecondNibble]=V[nSecondNibble] ^ V[nThirdNibble];
                         break;
               case 4:
               {
                         //add instruction
                         uint16_t sum=V[nSecondNibble] + V[nThirdNibble];

                         if (sum >255U)
                         {
                              V[0XF] = 0x01;
                         }
                         else 
                         {
                              V[0xF]=0x00;
                         }

                         V[nSecondNibble]=sum & 0xFF;

                         break;
               }

               case 5:

                         if (V[nSecondNibble] > V[nThirdNibble])
                         {
                              V[0xF]=0x01;
                         }
                         
                         else if (V[nSecondNibble] < V[nThirdNibble])
                         {
                              V[0xF]=0x00;
                         }
                         V[nSecondNibble]-=V[nThirdNibble];
                         break;
               case 7:
                         if (V[nThirdNibble] > V[nSecondNibble])
                         {
                               V[0xF]=0x01;
                         }
                         else if (V[nThirdNibble] < V[nSecondNibble])
                         {
                              V[0xF]=0x00;
                         }

                         V[nSecondNibble]=V[nThirdNibble]-V[nSecondNibble];
                         break;
               case 6:
                     //shifts VX to right one bit
                     V[0xF]= 1 & V[nSecondNibble];
                     V[nSecondNibble] = V[nSecondNibble]>>1;
                     break;

               case 14:
                   V[0xF]= 0x80 & V[nSecondNibble];
                   V[nSecondNibble] = V[nSecondNibble]<<1;
                   break;
                    

          }


          break;

          case 9:
          //skips if VX !=VY
            if (V[nSecondNibble]!=V[nThirdNibble])
               {
                    PC+=2;
               }
          break;

          case 10:
          //sets the index register to NNN
               I=nNNN;
          break;

          case 11:
               //jumps to adresss NNN +V[0]
               PC=V[0]+nNNN;
               break;

          case 12:
          {
               //generates a random binary number and it with vx
               uint8_t e= rand();
               uint8_t nLastByte= opcode &0x00FF;

               V[0]=e & nLastByte;
               break;
          }

          case 13:
          {
               uint8_t nPosX=V[nSecondNibble]%64;
               uint8_t nPosY=V[nThirdNibble]%32;
               int row=nLastNibble;

               for (int i=0; i <row; ++i)
               {
                    uint8_t Byte=ram[I+i];
                    cout<<"\r i just want to sleep forever ";

                    for (int j=0; j<8;++j)
                    {
                         //row+poxy
                         uint8_t screenbit=screen[8*(row+nPosY)+(nPosX+j)];
                         screen[8*(row+nPosY)+(nPosX+j)]=screen[8*(row+nPosY)+(nPosX+j)] | 1;
                         V[0xF]=screenbit & ((Byte & (128>>j))>>(7-j));
                    
                         
                    }
               }

          break;
          
          }

          case 14:
          //
          {cout<<'s';
          break;}

          case 15:

          {//timers go brrr

          switch(nLastNibble)
          {
               case 7:
               //sets Vx to the value of delay timer
                    V[nSecondNibble]=nDelayTimer;
                    break;
               case 5:
               {
               if (opcode & 0xF0FF ==0xF015 ) {
                    //set the delay timer to the value of VX

                    nDelayTimer=V[nSecondNibble];
               }
               else  if ((opcode & 0xF0FF) ==0xF055 )
               {
                    for (int i=0; i<=nSecondNibble; ++i)
                    {
                         ram[i+I]=V[i];
                    }
               }
               else  if ((opcode & 0xF0FF) ==0xF065 )
               {
                    for (int i=0; i<=nSecondNibble; ++i)
                    {
                        V[i]= ram[i+I];
                    }
               }
          }
                    
                    
                    break;
               case 8:
                    //set the sound timer to the value in vx
                    nSoundTimer = V[nSecondNibble];
                    break;
                    
               case 14:
               {
                    //Add to index
                    I+=V[nSecondNibble];
                    if (I>4095U)
                    {
                         V[0xF]=0x01;
                    }
                    break;
               }
               case 10:
               {
               //stops the excecution unless a a key is pressed
                    //PC-=2;
                    //execution = false
                    break;
               }
               case 9:
               {
                    I=V[nSecondNibble];
               }
               case 3:
               {
                    int num=V[nSecondNibble];
                    int i=0;
                    vector <int> nums;
                    while (num>0)
                    {
                         int temp=num%10;
                         nums.insert(nums.begin(),temp);
                         num/=10;

                    }
                    for (int i=0; i<nums.size(); ++i)
                    {
                         ram[I+i]=nums[i];
                    }
                    break;

               }


          }
          }
          
     }

      Event event;
  while(window.pollEvent(event))
  {
     if (event.type==Event::Closed)
     {
          window.close();
     }
  }


for (int i=0; i<screen.size(); i++)
{
     if (screen[i])
     {
          int x=i%64;
          int y=i/32;
          RectangleShape pixel(Vector2f(6,6));

          pixel.setFillColor(Color::White);
          pixel.setPosition(Vector2f(x*6,y*6));
          window.draw(pixel);

     }
}


  window.display();
  window.clear(Color::Blue);


  }
  ///==================================================================================================================================================

    
    
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


