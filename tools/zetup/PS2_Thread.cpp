//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "PS2_Thread.h"
#include "Main.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TPS2_REC::TPS2_REC(bool CreateSuspended) : TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall TPS2_REC::Execute()
{
   while(!Terminated) {
      Synchronize(Show_ASCII);
   }
}
//---------------------------------------------------------------------------
void __fastcall TPS2_REC::Show_ASCII()
{
   Form1->USB1.Write_Data(&Get_ASCII,0,1,true);    // Read PS2 Ascii To Text Windows
   Sleep(30);
   Form1->USB1.Read_Data(&Get_ASCII,1);            // Check Get Data is Valid
   if(Get_ASCII!=0x00) Form1->PS2_times++;         // Check Get Data is Byte 1
   if(Form1->PS2_times == 1) Form1->Memo1->Text = Form1->Memo1->Text + (char)Get_ASCII;
   else if(Form1->PS2_times == 2)
   Form1->PS2_times = 0;
   Application->ProcessMessages();
}
//---------------------------------------------------------------------------

