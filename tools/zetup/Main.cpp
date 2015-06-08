// --------------------------------------------------------------------
// --------------------------------------------------------------------
// Major Functions:	CII Starter Kit USB API Borland C++ Builder Code
//   V1.1 :| Donna Polehn      :| 04/06/10  :| Added SD Card Function
// --------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Main.h"
#include "About.h"
#include "PS2_Thread.h"
#include "Test_Page.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FTD2XX.lib"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
{
    Form1->DoubleBuffered   = true;
    USB_is_Open             = false;
    PS2_times               = 0;
    ToolBar1->Buttons[0]->Enabled = true;
    ToolBar1->Buttons[1]->Enabled = false;
    ToolBar1->Buttons[0]->Style = tbsButton	;
    ToolBar1->Buttons[1]->Style = tbsButton	;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
    BuildDevList(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BuildDevList(TObject *Sender)
{
    if(USB1.GetDeviceList()) {
        DevComboBox1->Items = USB1.DeviceList;
        if(DevComboBox1->Items->Count) {
            DevComboBox1->ItemIndex = 0;
            USB1.DevNum = DevComboBox1->ItemIndex;
        }
    }
    else {
        DevComboBox1->Clear();
        DevComboBox1->Text = "Select Device";
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DevComboBox1Change(TObject *Sender)
{
    USB1.DevNum = DevComboBox1->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::OpenUSBPort1Click(TObject *Sender)
{
    USB1.Select_Device(USB1.DevNum);
    if(USB1.Open_Device()) {
        USB_is_Open = true;
        USB1.Reset_Device(USB1.DevNum);
        PS2_REC = new TPS2_REC(true);
        PS2_REC->Resume();
        Show_All_Button(true);    // Enable All Button

        ToolBar1->Buttons[0]->Enabled = false;
        ToolBar1->Buttons[1]->Enabled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Close_USB_Port()
{
    if(USB_is_Open)   {
        PS2_REC->Terminate();
        USB1.Close_Device();       // Close USB Port
        Show_All_Button(false);
        USB_is_Open = false;

        ToolBar1->Buttons[0]->Enabled = true;
        ToolBar1->Buttons[1]->Enabled = false;
        ToolBar1->Update();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Exit1Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CloseUSBPort1Click(TObject *Sender)
{
    Close_USB_Port();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
    Close_USB_Port();  // Close Control Panel and Close USB JTAG Port
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Show_All_Button(bool Show)
{
   // Enable / Disable All Button
   Button1->Enabled=Show;
   Button2->Enabled=Show;
   Button3->Enabled=Show;
   Button4->Enabled=Show;
   Button5->Enabled=Show;
   Button6->Enabled=Show;
   Button7->Enabled=Show;
   Button8->Enabled=Show;
   Button9->Enabled=Show;
   Button10->Enabled=Show;
   Button11->Enabled=Show;
   Button12->Enabled=Show;
   Button13->Enabled=Show;
   Button14->Enabled=Show;
   Button15->Enabled=Show;
   Button16->Enabled=Show;
   Button17->Enabled=Show;
   Button18->Enabled=Show;
   CopyToSDCardButton1->Enabled=Show;
   CopyFromSDCardButton1->Enabled=Show;
   Default_IMG->Enabled=Show;
   Cursor_EN->Enabled=Show;
   ScrollBar1->Enabled=Show;
   ScrollBar2->Enabled=Show;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
    if(CheckBox1->Checked) iWR_Length->ReadOnly=true;    //  if( Flash Write Size == File Length )
    else                   iWR_Length->ReadOnly=false;   // Disable iWR_Length Text Field
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox2Click(TObject *Sender)
{
    if(CheckBox2->Checked) {             //  if( Flash Read Size = Entrie Flash )
        iRD_Length->Text="400000";       // Show iRD_Length = 4 MByte
        iRD_Length->ReadOnly=true;       // And Disable iRD_Length Text Field
    }
    else {
        iRD_Length->Text="0";
        iRD_Length->ReadOnly=false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::About1Click(TObject *Sender)
{
   AboutBox->Visible=true;        // Show About Form
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Help1Click(TObject *Sender)
{
    ShowMessage("You are beyond help");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button8Click(TObject *Sender)
{
   Memo1->Clear();  // Clear PS2 Text Windows
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button14Click(TObject *Sender)
{
    Form4->Visible = true;   // Board Test
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TabSheet1Show(TObject *Sender)
{
    if(USB_is_Open) {
        USB1.Reset_Device(USB1.DevNum);
        PS2_REC->Resume();         //  Enable PS2_REC Thread
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TabSheet2Show(TObject *Sender)
{
    if(USB_is_Open) {             // Disable PS2_REC Thread
        PS2_REC->Suspend();       // Disable PS2_REC Thread
        USB1.Reset_Device(USB1.DevNum);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
    char x[8];
    x[0] = WRITE;
    x[1] = LED;               // Send LED Value To FPGA
    x[2] = 0x00;
    x[3] = (char(DR9->Checked)<<1)+(char(DR8->Checked));
    x[4] = (char(DR7->Checked)<<7)+(char(DR6->Checked)<<6)+(char(DR5->Checked)<<5)+(char(DR4->Checked)<<4)+
           (char(DR3->Checked)<<3)+(char(DR2->Checked)<<2)+(char(DR1->Checked)<<1)+(char(DR0->Checked));
    x[5] = 0x00;
    x[6] = (char(D8->Checked)<<7)+(char(D7->Checked)<<6)+(char(D6->Checked)<<5)+(char(D5->Checked)<<4)+
           (char(D4->Checked)<<3)+(char(D3->Checked)<<2)+(char(D2->Checked)<<1)+(char(D1->Checked));
    x[7] = DISPLAY;
    PS2_REC->Suspend();
    USB1.Reset_Device(0);
    USB1.Write_Data(x,8,0,true);
    PS2_REC->Resume();
    Button1Click(this);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
    char x[8];
    x[0] = WRITE;        // Flash Random Write
    x[1] = FLASH;
    x[2] = char(HexToInt(oFL_ADDR->Text)>>16);
    x[3] = char(HexToInt(oFL_ADDR->Text)>>8);
    x[4] = char(HexToInt(oFL_ADDR->Text));
    x[5] = 0xFF;
    x[6] = char(HexToInt(oFL_DATA->Text));
    x[7] = NORMAL;
    USB1.Reset_Device(0);
    USB1.Write_Data(x,8,0,true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
    char x[8];
    //-----------------------------------
    // T-Rex TXD Output Select to FLASH
    x[0] = SETUP;
    x[1] = SET_REG;
    x[2] = 0x12;
    x[3] = 0x34;
    x[4] = 0x56;
    x[5] = 0x00;
    x[6] = FLASH;
    x[7] = OUTSEL;
    USB1.Reset_Device(0);
    USB1.Write_Data(x,8,0,true);
    Sleep(10);
    //-----------------------------------
    // Send Flash Address To FPGA
    x[0] = READ;                             // Flash Random Read
    x[1] = FLASH;
    x[2] = char(HexToInt(oFL_ADDR->Text)>>16);
    x[3] = char(HexToInt(oFL_ADDR->Text)>>8);
    x[4] = char(HexToInt(oFL_ADDR->Text));
    x[5] = 0xFF;
    x[6] = 0x00;
    x[7] = NORMAL;
    USB1.Write_Data(x,8,1,true);
    Sleep(10);
    USB1.Read_Data(x,1);      // Flash Random Read
    iFL_DATA->Text=IntToHex((unsigned char)x[0],2);  // Show Get Value To Text Filed
    //-----------------------------------
    // T-Rex TXD Output Select to PS2
    x[0] = SETUP;
    x[1] = SET_REG;
    x[2] = 0x12;
    x[3] = 0x34;
    x[4] = 0x56;
    x[5] = 0x00;
    x[6] = PS2;
    x[7] = OUTSEL;
    USB1.Reset_Device(0);
    USB1.Write_Data(x,8,0,true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
    Screen->Cursor=crHourGlass;     // Erase Flash
    Panel1->Visible=true;           // Show Busy Panel
    Show_All_Button(false);         // Disable All Button
    ProgressBar1->Max = 400;        // Set ProgressBar
    char x[8];
    int wait = 0;
    x[0] = ERASE;                  // Send Erase Command To FPGA
    x[1] = FLASH;
    x[2] = 0x00;
    x[3] = 0x00;
    x[4] = 0x00;
    x[5] = 0xFF;
    x[6] = 0x00;
    x[7] = NORMAL;
    USB1.Reset_Device(0);
     USB1.Write_Data(x,8,0,true);
    USB1.Write_Data(x,8,0,true);
    USB1.Write_Data(x,8,0,true);
    for(int i = 0; i < 400; i++) {        // Wait 40 Sec.....
        Process_Label->Caption=IntToStr(i*100/400) + " %";    // Display Process %
        ProgressBar1->Position = i;
        Application->ProcessMessages();
        Sleep(100);                   // Waitting
    }
    Form1->iFL_DATA->Text = "00";
    while((HexToInt(Form1->iFL_DATA->Text)!= 255) && wait < 600) {    // Max Wait 60 Sec...
        Form1->Button4Click(this);
        Application->ProcessMessages();
        Sleep(100);
        wait++;
    }
    if(wait == 600)
    ShowMessage("FLASH Erase TimeOut!!");
    Form1->iFL_DATA->Text = "00";
    Panel1->Visible = false;             // Close Busy Panel
    Show_All_Button(true);             // Enable All Button
    Screen->Cursor=crArrow;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button6Click(TObject *Sender)
{
   if(OpenDialog1->Execute()) {           // Write File To Flash
      char x[8];
      int File_Length,File_Type;
      int ADDR=HexToInt(iWR_ADDR->Text);
      Screen->Cursor=crHourGlass;
      Panel1->Visible=true;            // Show Busy Panel
      Show_All_Button(false);          // Disable All Button
      x[0]=WRITE;
      x[1]=FLASH;           // Send Flash Write Command To FPGA
      x[5]=0xFF;
      x[7]=NORMAL;
      USB1.Reset_Device(0);
      if(Select_File(OpenDialog1->FileName)==1) {   // Check File Type and Open File
         File_AscToHex(OpenDialog1->FileName,"123.tmp",1);
         Sleep(100);
         file1=fopen("123.tmp","rb");
      }
      else file1=fopen(OpenDialog1->FileName.c_str(),"rb");
      fseek(file1,0,SEEK_END);     // Set File ptr To File End
      if(CheckBox1->Checked) {      // Set Transport Length
         File_Length=ftell(file1);       // Check File Length
         iWR_Length->Text=IntToHex(File_Length,6);   // Show File Length To Text Field
      }
      else File_Length=HexToInt(iWR_Length->Text);
      ProgressBar1->Max=File_Length;     // Set ProgressBar
      fseek(file1,0,SEEK_SET);           // Set File ptr To File Start
      // Read File Data To Temp Memory
      unsigned char* a=(unsigned char*)VirtualAlloc(NULL,File_Length,MEM_COMMIT,PAGE_READWRITE);
      fread(a,sizeof(char),File_Length,file1);
      for(int i=0;i<File_Length;i++) {    // Transport File To Flash
         Process_Label->Caption=IntToStr(i*100/File_Length)+" %"; // Display Process %
         ProgressBar1->Position=i;
         Application->ProcessMessages();
         x[2]=char(ADDR>>16);         // Send Data and Address
         x[3]=char(ADDR>>8);
         x[4]=char(ADDR);
         x[5]=0xFF;
         x[6]=a[i];
         if(i%MAX_TOTAL_PACKET==MAX_TOTAL_PACKET-1)
         USB1.Reset_Device(0);
         if(i<File_Length-1)
         USB1.Write_Data(x,8,0,false);
         else
         USB1.Write_Data(x,8,0,true);
         // Inc Address
         ADDR++;
      }
      USB1.Reset_Device(0);
      fclose(file1);           // Close File
      if(FileExists("123.tmp")) DeleteFile("123.tmp");   // Delete Temp File
      Panel1->Visible=false;        // Close Busy Panel
      Show_All_Button(true);     // Enable All Button
      VirtualFree(a,0,MEM_RELEASE);    // Free Temp Memory
      Screen->Cursor=crArrow;
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button7Click(TObject *Sender)
{
   if(SaveDialog1->Execute())  {       // Load Flash Content to File
      char x[8];
      int DATA_Read=0;
      int Queue;
      int Flash_Length;
      int ADDR=HexToInt(iRD_ADDR->Text);
      Screen->Cursor=crHourGlass;
      Panel1->Visible=true;          // Show Busy Panel
      Show_All_Button(false);        // Disable All Button
      //-----------------------------------
      // T-Rex TXD Output Select to FLASH
      x[0] = SETUP;
      x[1] = SET_REG;
      x[2] = 0x12;
      x[3] = 0x34;
      x[4] = 0x56;
      x[5] = 0x00;
      x[6] = FLASH;;
      x[7] = OUTSEL;
      USB1.Reset_Device(0);
      USB1.Write_Data(x,8,0,true);
      Sleep(10);
      //-----------------------------------
      // Send Flash Read Command To FPGA
      x[0] = READ;
      x[1] = FLASH;
      x[5] = 0xFF;
      x[6] = 0x00;
      x[7]=NORMAL;
      if(CheckBox2->Checked) {        // Set Transport Length
         Flash_Length=1048576*4;      // Set Transport Length = Flash Size = 4Mbyte
         iRD_Length->Text=IntToHex(Flash_Length,6);     // Show Transport Length To Text Field
      }
      else Flash_Length=HexToInt(iRD_Length->Text);
      unsigned char* a=(unsigned char*)VirtualAlloc(NULL,Flash_Length+MAX_RXD_PACKET,MEM_COMMIT,PAGE_READWRITE);
      ProgressBar1->Max=Flash_Length;   // Set ProgressBar
      for(int i=0;i<Flash_Length;i++)  {     // Transport Flash Data To File
         Process_Label->Caption=IntToStr(i*100/Flash_Length)+" %";  // Display Process %
         ProgressBar1->Position=i;
         Application->ProcessMessages();
         x[2]=char(ADDR>>16);       // Send Address
         x[3]=char(ADDR>>8);
         x[4]=char(ADDR);
         if(i%ALMOST_FULL_SIZE==ALMOST_FULL_SIZE-1)
         USB1.Write_Data(x,8,1,true);
         else if(i==Flash_Length-1)
         USB1.Write_Data(x,8,1,true);
         else
         USB1.Write_Data(x,8,1,false);
         if(i%MAX_RXD_PACKET==MAX_RXD_PACKET-1) {
            USB1.Read_Data(&a[DATA_Read],MAX_RXD_PACKET);  // Flash Seq. Read
            DATA_Read+=MAX_RXD_PACKET;
            USB1.Reset_Device(0);
         }
         ADDR++;        // Increment Address
      }
      USB1.Write_Data(x,0,8,true);
      Sleep(100);                       // Wait a short time to get Data Form USB JTAG
      Queue=USB1.Number_Of_Queue_Data();
      USB1.Read_Data(&a[DATA_Read],Queue);
      if(Select_File(SaveDialog1->FileName)==1) {  // Check File and Write File
         file2=fopen("123.tmp","w+b");
         fwrite(a,sizeof(char),Flash_Length,file2);
         fclose(file2);
         Sleep(100);
         File_HexToAsc("123.tmp",SaveDialog1->FileName,1);
      }
      else {
         file2=fopen(SaveDialog1->FileName.c_str(),"w+b");
         fwrite(a,sizeof(char),Flash_Length,file2);
         fclose(file2);
      }
      Sleep(100);
      VirtualFree(a,0,MEM_RELEASE);
      
      if(FileExists("123.tmp")) DeleteFile("123.tmp"); // Delete Temp File
      //-----------------------------------
      // T-Rex TXD Output Select to PS2
      x[0] = SETUP;
      x[1] = SET_REG;
      x[2] = 0x12;
      x[3] = 0x34;
      x[4] = 0x56;
      x[5] = 0x00;
      x[6] = PS2;
      x[7] = OUTSEL;
      USB1.Reset_Device(0);
      USB1.Write_Data(x,8,0,true);
      //-----------------------------------
      Panel1->Visible=false;   // Close Busy Panel
      Show_All_Button(true);     // Enable All Button
      Screen->Cursor=crArrow;
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button9Click(TObject *Sender)
{
    char x[8];
    x[0] = WRITE;
    x[1] = SDRAM;    // dram Random Write
    x[2] = char(HexToInt(oSDR_ADDR->Text)>>16);
    x[3] = char(HexToInt(oSDR_ADDR->Text)>>8);
    x[4] = char(HexToInt(oSDR_ADDR->Text));
    x[5] = char(HexToInt(oSDR_DATA->Text)>>8);
    x[6] = char(HexToInt(oSDR_DATA->Text));
    x[7] = NORMAL;
    USB1.Reset_Device(0);
    USB1.Write_Data(x,8,0,true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button10Click(TObject *Sender)
{
    char x[8];
    x[0] = SETUP;           // T-Rex TXD Output Select to SDRAM
    x[1] = SET_REG;
    x[2] = 0x12;
    x[3] = 0x34;
    x[4] = 0x56;
    x[5] = 0x00;
    x[6] = SDRAM;          // Sdram Random Read
    x[7] = OUTSEL;
    USB1.Reset_Device(0);
    USB1.Write_Data(x,8,0,true);
    Sleep(10);
    //-----------------------------------
    x[0] = READ;
    x[1] = SDRAM;      // Send SDRAM Address To FPGA
    x[2] = char(HexToInt(oSDR_ADDR->Text)>>16);
    x[3] = char(HexToInt(oSDR_ADDR->Text)>>8);
    x[4] = char(HexToInt(oSDR_ADDR->Text));
    x[5] = 0x00;
    x[6] = 0x00;
    x[7] = NORMAL;
    USB1.Write_Data(x,8,2,true);
    Sleep(10);
    USB1.Read_Data(x,2);     // Sdram Random Read
    iSDR_DATA->Text=IntToHex((unsigned char)x[0]+(unsigned char)x[1]*256,4); // Show Get Value To Text Filed
    //-----------------------------------
    x[0] = SETUP;            // T-Rex TXD Output Select to PS2
    x[1] = SET_REG;
    x[2] = 0x12;
    x[3] = 0x34;
    x[4] = 0x56;
    x[5] = 0x00;
    x[6] = PS2;
    x[7]=OUTSEL;
    USB1.Reset_Device(0);
    USB1.Write_Data(x,8,0,true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button11Click(TObject *Sender)
{
   if(OpenDialog2->Execute()) {   // Write File To Sdram
      char x[8];
      int File_Length;
      int ADDR=HexToInt(iSDR_SWR_ADDR->Text);
      Screen->Cursor=crHourGlass;
      Panel1->Visible=true;        // Show Busy Panel
      Show_All_Button(false);       // Disable All Button
      x[0]=WRITE;
      x[1]=SDRAM;             // Send Sdram Write Command To FPGA
      x[7]=NORMAL;
      USB1.Reset_Device(0);
      if(Select_File(OpenDialog2->FileName)==1) {   // Check File Type and Open File
         File_AscToHex(OpenDialog2->FileName,"123.tmp",2);
         Sleep(100);
         file1=fopen("123.tmp","rb");
      }
      else file1=fopen(OpenDialog2->FileName.c_str(),"rb");
      fseek(file1,0,SEEK_END);    // Set File ptr To File End
      if(CheckBox3->Checked) {     // Set Transport Length
         File_Length=ftell(file1);        // Check File Length
         iSDR_SWR_Length->Text=IntToHex(File_Length,6); // Show File Length To Text Field
      }
      else
      File_Length=HexToInt(iSDR_SWR_Length->Text);
      ProgressBar1->Max=File_Length;       // Set ProgressBar
      fseek(file1,0,SEEK_SET);   // Set File ptr To File Start and Read File Data To Temp Memory
      unsigned char* a=(unsigned char*)VirtualAlloc(NULL,File_Length+1,MEM_COMMIT,PAGE_READWRITE);
      fread(a,sizeof(char),File_Length,file1);
      for(int i=0;i<File_Length;i+=2) {  // Transport File To Sdram
         Process_Label->Caption=IntToStr(i*100/File_Length)+" %";  // Display Process %
         ProgressBar1->Position=i;
         Application->ProcessMessages();
         x[2]=char(ADDR>>16);          // Send Data and Address
         x[3]=char(ADDR>>8);
         x[4]=char(ADDR);
         x[5]=a[i+1];
         x[6]=a[i];
         if(i%MAX_TOTAL_PACKET==MAX_TOTAL_PACKET-2)
         USB1.Reset_Device(0);
         if(i<File_Length-2)
         USB1.Write_Data(x,8,0,false);
         else
         USB1.Write_Data(x,8,0,true);
         ADDR++;                 // Inc Address
      }
      USB1.Reset_Device(0);
      fclose(file1);        // Close File
      Panel1->Visible=false;    // Close Busy Panel
      Show_All_Button(true);    // Enable All Button
      VirtualFree(a,0,MEM_RELEASE);   // Free Temp Memory
      Screen->Cursor=crArrow;
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button12Click(TObject *Sender)
{
   int t1,t2;
   
   if(SaveDialog2->Execute()) {    // Load Sdram Content to File
      char x[8];
      int Sdram_Length;
      int DATA_Read=0;
      int Queue;
      int ADDR=HexToInt(iSDR_SRD_ADDR->Text);
      Screen->Cursor=crHourGlass;
      Panel1->Visible=true;     // Show Busy Panel
      Show_All_Button(false);   // Disable All Button
      //-----------------------------------
      x[0] = SETUP;
      x[1] = SET_REG;            // T-Rex TXD Output Select to SDRAM
      x[2] = 0x12;
      x[3] = 0x34;
      x[4] = 0x56;
      x[5] = 0x00;
      x[6] = SDRAM;;
      x[7] = OUTSEL;
      USB1.Reset_Device(0);
      USB1.Write_Data(x,8,0,true);
      Sleep(10);
      //-----------------------------------
      x[0] = READ;
      x[1] = SDRAM;         // Send Sdram Read Command To FPGA
      x[5] = 0x00;
      x[6] = 0x00;
      x[7] = NORMAL;
      if(CheckBox4->Checked) {      // Set Transport Length
         Sdram_Length=8388608;     // Set Transport Length = Sdram Size = 8Mbyte
         iSDR_SRD_Length->Text=IntToHex(Sdram_Length,6);   // Show Transport Length To Text Field
      }
      else Sdram_Length=HexToInt(iSDR_SRD_Length->Text);
      unsigned char* a=(unsigned char*)VirtualAlloc(NULL,Sdram_Length+MAX_RXD_PACKET,MEM_COMMIT,PAGE_READWRITE);
      ProgressBar1->Max=Sdram_Length;       // Set ProgressBar
      for(int i=0;i<Sdram_Length;i+=2) {       // Transport Sdram Data To File
         Process_Label->Caption=IntToStr(i*100/Sdram_Length)+" %";          // Display Process %
         ProgressBar1->Position=i;
         Application->ProcessMessages();
         x[2]=char(ADDR>>16);          // Send Address
         x[3]=char(ADDR>>8);
         x[4]=char(ADDR);
         if(i%ALMOST_FULL_SIZE==ALMOST_FULL_SIZE-2)
         USB1.Write_Data(x,8,2,true);
         else if(i==Sdram_Length-2) USB1.Write_Data(x,8,2,true);
         else                       USB1.Write_Data(x,8,2,false);
         if(i%MAX_RXD_PACKET==MAX_RXD_PACKET-2) {
            USB1.Read_Data(&a[DATA_Read],MAX_RXD_PACKET);     // Sdram Seq. Read
            DATA_Read+=MAX_RXD_PACKET;
            USB1.Reset_Device(0);
         }
         ADDR++;          // Inc Address
      }
      USB1.Write_Data(x,0,8,true);       // Wait a short time to get Data Form USB JTAG
      Sleep(100);
      Queue=USB1.Number_Of_Queue_Data();
      USB1.Read_Data(&a[DATA_Read],Queue);
      if(Select_File(SaveDialog2->FileName)==1) {       // Check File and Write File
         file2=fopen("123.tmp","w+b");
         fwrite(a,sizeof(char),Sdram_Length,file2);
         fclose(file2);
         Sleep(100);
         File_HexToAsc("123.tmp",SaveDialog2->FileName,2);
      }
      else {
         file2=fopen(SaveDialog2->FileName.c_str(),"w+b");
         fwrite(a,sizeof(char),Sdram_Length,file2);
         fclose(file2);
      }
      Sleep(100);
      VirtualFree(a,0,MEM_RELEASE);
      if(FileExists("123.tmp")) DeleteFile("123.tmp");      // Delete Temp File
      //-----------------------------------
      x[0] = SETUP;                     // T-Rex TXD Output Select to PS2
      x[1] = SET_REG;
      x[2] = 0x12;
      x[3] = 0x34;
      x[4] = 0x56;
      x[5] = 0x00;
      x[6] = PS2;
      x[7] = OUTSEL;
      USB1.Reset_Device(0);
      USB1.Write_Data(x,8,0,true);
      //-----------------------------------
      Panel1->Visible=false;    // Close Busy Panel
      Show_All_Button(true);    // Enable All Button
      Screen->Cursor=crArrow;
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button13Click(TObject *Sender)
{
    char x[8];
    x[0] = WRITE;        // ToDo : Send External IO Value To FPGA
    x[1] = EXTIO;
    x[2] = 0x12;
    x[3] = 0x34;
    x[4] = 0x56;
    x[5] = 0x00;
    x[6] = 0x00;
    x[7] = NORMAL;
    USB1.Write_Data(x,8,0,true);
    x[0] = SETUP;                  // Send Sdram Multiplexer To FPGA
    x[1] = SDRSEL;
    x[6] = char(Sdram_Multi->ItemIndex);
    x[7] = OUTSEL;
    USB1.Write_Data(x,8,0,true);
    x[0] = SETUP;
    x[1] = FLSEL;                    // Send Flash Multiplexer To FPGA
    x[6] = char(Flash_Multi->ItemIndex);
    x[7] = OUTSEL;
    USB1.Write_Data(x,8,0,true);
    x[0] = SETUP;
    x[1] = SRSEL;                   // Send SRAM Multiplexer To FPGA
    x[6] = char(Sram_Multi->ItemIndex);
    x[7] = OUTSEL;
    USB1.Write_Data(x,8,0,true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button16Click(TObject *Sender)
{
    char x[8];
    x[0] = WRITE;
    x[1] = SRAM;            // SRAM Random Write
    x[2] = char(HexToInt(oSR_ADDR->Text)>>16);
    x[3] = char(HexToInt(oSR_ADDR->Text)>>8);
    x[4] = char(HexToInt(oSR_ADDR->Text));
    x[5] = char(HexToInt(oSR_DATA->Text)>>8);
    x[6] = char(HexToInt(oSR_DATA->Text));
    x[7] = NORMAL;
    USB1.Reset_Device(0);
    USB1.Write_Data(x,8,0,true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button17Click(TObject *Sender)
{
    char x[8];
    //-----------------------------------
    x[0] = SETUP;
    x[1] = SET_REG;            // T-Rex TXD Output Select to SRAM
    x[2] = 0x12;
    x[3] = 0x34;
    x[4] = 0x56;
    x[5] = 0x00;
    x[6] = SRAM;
    x[7] = OUTSEL;
    USB1.Reset_Device(0);
    USB1.Write_Data(x,8,0,true);
    Sleep(10);
    //-----------------------------------
    x[0] = READ;         // Send SRAM Address To FPGA
    x[1] = SRAM;        // SRAM Random Read
    x[2] = char(HexToInt(oSR_ADDR->Text)>>16);
    x[3] = char(HexToInt(oSR_ADDR->Text)>>8);
    x[4] = char(HexToInt(oSR_ADDR->Text));
    x[5] = 0x00;
    x[6] = 0x00;
    x[7] = NORMAL;
    USB1.Write_Data(x,8,2,true);
    Sleep(10);
    USB1.Read_Data(x,2);      // SRAM Random Read  &Show Get Value To Text Filed
    iSR_DATA->Text=IntToHex((unsigned char)x[0]+(unsigned char)x[1]*256,4);
    //-----------------------------------
    x[0] = SETUP;                // T-Rex TXD Output Select to PS2
    x[1] = SET_REG;
    x[2] = 0x12;
    x[3] = 0x34;
    x[4] = 0x56;
    x[5] = 0x00;
    x[6] = PS2;
    x[7] = OUTSEL;
    USB1.Reset_Device(0);
    USB1.Write_Data(x,8,0,true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox5Click(TObject *Sender)
{
    if(CheckBox5->Checked) iSR_SWR_Length->ReadOnly = true;  // if Sram Write Size == File Length
    else                   iSR_SWR_Length->ReadOnly = false; // Disable iSR_SWR_Length Text Field
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox6Click(TObject *Sender)
{
    if(CheckBox6->Checked) {               // if( Sram Read Size = Entrie Sram )
       iSR_SRD_Length->Text = "80000";       // Show iSR_SRD_Length = 512 KByte
       iSR_SRD_Length->ReadOnly = true;      // And Disable iSR_SRD_Length Text Field
    }
    else {
       iSR_SRD_Length->Text = "0";
       iSR_SRD_Length->ReadOnly = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button15Click(TObject *Sender)
{
   if(OpenDialog3->Execute()) {
      char x[8];
      int File_Length;
      int ADDR=HexToInt(iSR_SWR_ADDR->Text);
      Screen->Cursor=crHourGlass;
      Panel1->Visible=true;        // Show Busy Panel
      Show_All_Button(false);       // Disable All Button
      x[0]=WRITE;                // Write File To Sram
      x[1]=SRAM;                 // Send Sram Write Command To FPGA
      x[7]=NORMAL;
      USB1.Reset_Device(0);
      if(Select_File(OpenDialog3->FileName)==1) { // Check File Type and Open File
         File_AscToHex(OpenDialog3->FileName,"123.tmp",2);
         Sleep(100);
         file1=fopen("123.tmp","rb");
      }
      else file1=fopen(OpenDialog3->FileName.c_str(),"rb");
      fseek(file1,0,SEEK_END);     // Set File ptr To File End
      if(CheckBox5->Checked) {     // Set Transport Length
         File_Length=ftell(file1);     // Check File Length
         iSR_SWR_Length->Text=IntToHex(File_Length,6);  // Show File Length To Text Field
      }
      else File_Length=HexToInt(iSR_SWR_Length->Text);
      ProgressBar1->Max=File_Length;       // Set ProgressBar
      fseek(file1,0,SEEK_SET);             // Set File ptr To File Start & Read File Data To Temp Memory
      unsigned char* a=(unsigned char*)VirtualAlloc(NULL,File_Length+1,MEM_COMMIT,PAGE_READWRITE);
      fread(a,sizeof(char),File_Length,file1);
      for(int i=0;i<File_Length;i+=2) {      // Transport File To Sram
         Process_Label->Caption=IntToStr(i*100/File_Length)+" %";   // Display Process %
         ProgressBar1->Position=i;
         Application->ProcessMessages();
         x[2]=char(ADDR>>16);            // Send Data and Address
         x[3]=char(ADDR>>8);
         x[4]=char(ADDR);
         x[5]=a[i+1];
         x[6]=a[i];
         if(i%MAX_TOTAL_PACKET==MAX_TOTAL_PACKET-2)
         USB1.Reset_Device(0);
         if(i<File_Length-2) USB1.Write_Data(x,8,0,false);
         else                USB1.Write_Data(x,8,0,true);
         ADDR++;                 // Inc Address
      }
      USB1.Reset_Device(0);
      fclose(file1);              // Close File
      Panel1->Visible=false;      // Close Busy Panel
      Show_All_Button(true);      // Enable All Button
      VirtualFree(a,0,MEM_RELEASE);  // Free Temp Memory
      Screen->Cursor=crArrow;
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button18Click(TObject *Sender)
{
   if(SaveDialog3->Execute()) {        // Load Sram Content to File
      char x[8];
      int Sram_Length;
      int DATA_Read=0;
      int Queue;
      int ADDR=HexToInt(iSR_SRD_ADDR->Text);
      Screen->Cursor=crHourGlass;
      Panel1->Visible = true;     // Show Busy Panel
      Show_All_Button(false);     // Disable All Button
      //-----------------------------------
      x[0] = SETUP;          // T-Rex TXD Output Select to SRAM
      x[1] = SET_REG;
      x[2] = 0x12;
      x[3] = 0x34;
      x[4] = 0x56;
      x[5] = 0x00;
      x[6] = SRAM;;
      x[7] = OUTSEL;
      USB1.Reset_Device(0);
      USB1.Write_Data(x,8,0,true);
      Sleep(10);
      //-----------------------------------
      x[0] = READ;
      x[1] = SRAM;             // Send Sram Read Command To FPGA
      x[5] = 0x00;
      x[6] = 0x00;
      x[7] = NORMAL;
      if(CheckBox6->Checked) {    // Set Transport Length
         Sram_Length=524288;       // Set Transport Length = Sram Size = 512KByte
         iSR_SRD_Length->Text=IntToHex(Sram_Length,6);  // Show Transport Length To Text Field
      }
      else
      Sram_Length=HexToInt(iSR_SRD_Length->Text);
      unsigned char* a=(unsigned char*)VirtualAlloc(NULL,Sram_Length+MAX_RXD_PACKET,MEM_COMMIT,PAGE_READWRITE);
      ProgressBar1->Max=Sram_Length;      // Set ProgressBar
      for(int i = 0; i < Sram_Length; i += 2) {   // Transport Sram Data To File
         Process_Label->Caption=IntToStr(i*100/Sram_Length)+" %"; // Display Process %
         ProgressBar1->Position=i;
         Application->ProcessMessages();
         x[2] = char(ADDR>>16);     // Send Address
         x[3] = char(ADDR>>8);
         x[4] = char(ADDR);
         if(i%ALMOST_FULL_SIZE==ALMOST_FULL_SIZE-2)
         USB1.Write_Data(x,8,2,true);
         else if(i==Sram_Length-2)  USB1.Write_Data(x,8,2,true);
         else                       USB1.Write_Data(x,8,2,false);
         if(i%MAX_RXD_PACKET==MAX_RXD_PACKET-2) {
            USB1.Read_Data(&a[DATA_Read],MAX_RXD_PACKET);   // Sram Seq. Read
            DATA_Read+=MAX_RXD_PACKET;
            USB1.Reset_Device(0);
         }
         ADDR++;                  // Inc Address
      }
      USB1.Write_Data(x,0,8,true);        // Wait a short time to get Data Form USB JTAG
      Sleep(100);
      Queue=USB1.Number_Of_Queue_Data();
      USB1.Read_Data(&a[DATA_Read],Queue);
      if(Select_File(SaveDialog3->FileName)==1) {        // Check File and Write File
         file2=fopen("123.tmp","w+b");
         fwrite(a,sizeof(char),Sram_Length,file2);
         fclose(file2);
         Sleep(100);
         File_HexToAsc("123.tmp",SaveDialog3->FileName,2);
      }
      else {
         file2=fopen(SaveDialog3->FileName.c_str(),"w+b");
         fwrite(a,sizeof(char),Sram_Length,file2);
         fclose(file2);
      }
      Sleep(100);
      VirtualFree(a,0,MEM_RELEASE);
      if(FileExists("123.tmp")) DeleteFile("123.tmp");     // Delete Temp File
      //-----------------------------------
      x[0] = SETUP;          // T-Rex TXD Output Select to PS2
      x[1] = SET_REG;
      x[2] = 0x12;
      x[3] = 0x34;
      x[4] = 0x56;
      x[5] = 0x00;
      x[6] = PS2;
      x[7] = OUTSEL;
      USB1.Reset_Device(0);
      USB1.Write_Data(x,8,0,true);
      //-----------------------------------
      Panel1->Visible = false;         // Close Busy Panel
      Show_All_Button(true);           // Enable All Button
      Screen->Cursor=crArrow;
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ScrollBar2Change(TObject *Sender)
{
    Cur_Y->Caption=IntToStr(ScrollBar2->Position);
    char x[8];
    x[0] = WRITE;
    x[1] = VGA;        // Send VGA Value To FPGA
    x[2] = 0x00;
    x[3] = 0x00;
    x[7] = DISPLAY;
    PS2_REC->Suspend();
    USB1.Reset_Device(0);
    x[4] = 0x01;
    x[5] = char(ScrollBar1->Position/256);
    x[6] = char(ScrollBar1->Position%256);
    USB1.Write_Data(x,8,0,true);
    x[4] = 0x02;
    x[5] = char(ScrollBar2->Position/256);
    x[6] = char(ScrollBar2->Position%256);
    USB1.Write_Data(x,8,0,true);
    PS2_REC->Resume();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ScrollBar1Change(TObject *Sender)
{
    Cur_X->Caption=IntToStr(ScrollBar1->Position);
    char x[8];
    x[0] = WRITE;           // Send VGA Value To FPGA
    x[1] = VGA;
    x[2] = 0x00;
    x[3] = 0x00;
    x[7] = DISPLAY;
    PS2_REC->Suspend();
    USB1.Reset_Device(0);
    x[4] = 0x01;
    x[5] = char(ScrollBar1->Position/256);
    x[6] = char(ScrollBar1->Position%256);
    USB1.Write_Data(x,8,0,true);
    x[4] = 0x02;
    x[5] = char(ScrollBar2->Position/256);
    x[6] = char(ScrollBar2->Position%256);
    USB1.Write_Data(x,8,0,true);
    PS2_REC->Resume();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Default_IMGClick(TObject *Sender)
{
    char x[8];
    x[0] = WRITE;       // Send VGA Value To FPGA
    x[1] = VGA;
    x[2] = 0x00;
    x[3] = 0x00;
    x[4] = 0x00;
    x[5] = 0x00;
    x[6] = (char(!Default_IMG->Checked)<<1)+char(Cursor_EN->Checked);
    x[7] = DISPLAY;
    PS2_REC->Suspend();
    USB1.Reset_Device(0);
    USB1.Write_Data(x,8,0,true);
    PS2_REC->Resume();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Cursor_ENClick(TObject *Sender)
{
    char x[8];
    x[0] = WRITE;
    x[1] = VGA;        // Send VGA Value To FPGA
    x[2] = 0x00;
    x[3] = 0x00;
    x[4] = 0x00;
    x[5] = 0x00;
    x[6] = (char(!Default_IMG->Checked)<<1)+char(Cursor_EN->Checked);
    x[7] = DISPLAY;
    PS2_REC->Suspend();
    USB1.Reset_Device(0);
    USB1.Write_Data(x,8,0,true);
    x[4] = 0x03;
    x[5] = 0x00;
    x[6] = 0x00;
    USB1.Write_Data(x,8,0,true);
    x[4] = 0x04;
    x[5] = char(1023/256);
    x[6] = char(1023%256);
    USB1.Write_Data(x,8,0,true);
    x[4] = 0x05;
    x[5] = 0x00;
    x[6] = 0x00;
    USB1.Write_Data(x,8,0,true);
    PS2_REC->Resume();
}
//---------------------------------------------------------------------------
int __fastcall TForm1::Select_File(String File_Name)
{
    int i;
    int File_Type;
    String Sub_Name;
    for(i=File_Name.Length()-3;i<=File_Name.Length();i++)
    Sub_Name=Sub_Name+File_Name[i];
    if(Sub_Name==".hex" || Sub_Name==".HEX")
    File_Type=1;
    else
    File_Type=0;
    return File_Type;
}
//---------------------------------------------------------------------------
int __fastcall TForm1::AscToHex(unsigned char a)
{
    int Out_Hex;
    if(a>=0x30 && a<=0x39) Out_Hex=a-0x30;
    else if(a>=0x41 && a<=0x46) Out_Hex=a-0x40+9;
    else if(a>=0x61 && a<=0x66) Out_Hex=a-0x60+9;
    else if( (a==0x20) || (a==0x09) || (a==0x0A) || (a==0x0D) ) Out_Hex=100;
    else Out_Hex=200;
    return Out_Hex;
}
//---------------------------------------------------------------------------
int __fastcall TForm1::File_AscToHex(String File_Input,String File_Output,int File_Type)
{
    unsigned int File_Length;
    unsigned int tmp=0;
    unsigned int i,j,k;
    unsigned char *hex08;
    unsigned short *hex16;
    unsigned int *hex32;

    file1=fopen(File_Input.c_str(),"rb");
    file2=fopen(File_Output.c_str(),"w+b");
    fseek(file1,0,SEEK_END);
    File_Length=ftell(file1);
    fseek(file1,0,SEEK_SET);
    unsigned char* a=(unsigned char*)VirtualAlloc(NULL,File_Length+1,MEM_COMMIT,PAGE_READWRITE);
    hex08=a;
    hex16=(unsigned short*)a;
    hex32=(unsigned int*)a;
    fread(a,sizeof(char),File_Length,file1);
    j=0;
    k=0;
    for(i=0;i<File_Length;i++) {
       if(AscToHex(a[i])==200 && File_Type!=0) {
          ShowMessage("Invalid Character Detected!!");
          fclose(file1);
          VirtualFree(a,0,MEM_RELEASE);
          return 0;
       }
       else if(AscToHex(a[i])==100)  {
          /*
          if(k!=0) {
             if(File_Type==1) hex08[j]=tmp;
             else if(File_Type==2) hex16[j]=tmp;
             else if(File_Type==3) hex32[j]=tmp;
             tmp=0;
             j++;
          }
          k=0;
          */
       }
       else  {
          tmp=(tmp<<4)+AscToHex(a[i]);
          if(k==1 && File_Type==1)  {
              hex08[j]=tmp;
             tmp=0;
             j++;
             k=0;
          }
          else if(k==3 && File_Type==2)  {
             hex16[j]=tmp;
             tmp=0;
             j++;
             k=0;
          }
          else if(k==7 && File_Type==3) {
             hex32[j]=tmp;
             tmp=0;
             j++;
             k=0;
         }
          else  k++;
       }
    }
    if(k!=0) {
       if(File_Type==1) hex08[j]=tmp;
       else if(File_Type==2)  hex16[j]=tmp;
       else if(File_Type==3)  hex32[j]=tmp;
       tmp=0;
       j++;
       k=0;
    }
    if(File_Type==1) fwrite(hex08,sizeof(char),j,file2);
    else if(File_Type==2)  fwrite(hex16,sizeof(short),j,file2);
    else if(File_Type==3)  fwrite(hex32,sizeof(int),j,file2);
    fclose(file1);
    fclose(file2);
    VirtualFree(a,0,MEM_RELEASE);
    return 1;
}
//---------------------------------------------------------------------------
int __fastcall TForm1::File_HexToAsc(String File_Input,String File_Output,int File_Type)
{
    unsigned int File_Length;
    unsigned int i;
    String   tmp;

    file1=fopen(File_Input.c_str(),"rb");
    file2=fopen(File_Output.c_str(),"w+");
    fseek(file1,0,SEEK_END);
    File_Length=ftell(file1);
    fseek(file1,0,SEEK_SET);
    unsigned char* a=(unsigned char*)VirtualAlloc(NULL,File_Length+16,MEM_COMMIT,PAGE_READWRITE);
    fread(a,sizeof(char),File_Length,file1);
    i=0;
    while(i<File_Length) {
       if(File_Type==1)  {
          tmp=IntToHex(a[i],2)+"\n";
          fputs(tmp.c_str(),file2);
          i++;
       }
       else if(File_Type==2) {
          tmp=IntToHex((a[i+1]<<8)+a[i],4)+"\n";
          fputs(tmp.c_str(),file2);
          i+=2;
       }
       else if(File_Type==3) {
          tmp=IntToHex((a[i+3]<<24)+(a[i+2]<<16)+(a[i+1]<<8)+a[i],8)+"\n";
          fputs(tmp.c_str(),file2);
          i+=4;
       }
    }
    fclose(file1);
    fclose(file2);
    VirtualFree(a,0,MEM_RELEASE);
    return 1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    char x[8];
    x[0] = WRITE;
    x[1] = SEG7;      // Send 7-SEG Value To FPGA
    x[2] = 0x00;
    x[3] = 0x00;
    x[4] = 0x00;
    x[5] = (DIG_4->ItemIndex<<4)+DIG_3->ItemIndex;
    x[6] = (DIG_2->ItemIndex<<4)+DIG_1->ItemIndex;
    x[7] = DISPLAY;
    PS2_REC->Suspend();
    USB1.Reset_Device(0);
    USB1.Write_Data(x,8,0,true);
    PS2_REC->Resume();
}
//---------------------------------------------------------------------------
int __fastcall TForm1::HexToInt(AnsiString strHex)
{
  return StrToInt64("0x"+strHex);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox4Click(TObject *Sender)
{
   if(CheckBox4->Checked) {                //  if( Sdram Read Size = Entrie Sdram )
      iSDR_SRD_Length->Text = "800000";    // Show iSDR_SRD_Length = 8 MByte
      iSDR_SRD_Length->ReadOnly = true;    // And Disable iSDR_SRD_Length Text Field
   }
   else {
      iSDR_SRD_Length->Text = "0";
      iSDR_SRD_Length->ReadOnly = false;
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox3Click(TObject *Sender)
{
   if(CheckBox3->Checked) iSDR_SWR_Length->ReadOnly = true;    // if Sdram Write Size == File Length )
   else                   iSDR_SWR_Length->ReadOnly = false;   // Disable iSDR_SWR_Length Text Field
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CopyToSDCardButton1Click(TObject *Sender)
{
   if(OpenDialog4->Execute()) {           // Write File To Flash
      char x[8];
      int File_Length,File_Type;
      int ADDR=HexToInt(iWR_ADDR->Text);
      Screen->Cursor = crHourGlass;
      Panel1->Visible = true;            // Show Busy Panel
      Show_All_Button(false);            // Disable All Button
      x[0]=WRITE;
      x[1]=SDCARD;           // Send Flash Write Command To FPGA
      x[5]=0xFF;
      x[7]=NORMAL;
      USB1.Reset_Device(0);
      if(Select_File(OpenDialog4->FileName) == 1) {   // Check File Type and Open File
         File_AscToHex(OpenDialog1->FileName,"c123.img", 1);
         Sleep(100);
         file1=fopen("c123.tmp","rb");
      }
      else file1 = fopen(OpenDialog1->FileName.c_str(), "rb");
      fseek(file1,0,SEEK_END);     // Set File ptr To File End
      if(CheckBox1->Checked) {          // Set Transport Length
         File_Length = ftell(file1);       // Check File Length
         iWR_Length->Text = IntToHex(File_Length, 6);   // Show File Length To Text Field
      }
      else File_Length = HexToInt(iWR_Length->Text);
      ProgressBar1->Max = File_Length;     // Set ProgressBar
      fseek(file1,0,SEEK_SET);             // Set File ptr To File Start and Read File Data To Temp Memory
      unsigned char* a=(unsigned char*)VirtualAlloc(NULL,File_Length,MEM_COMMIT,PAGE_READWRITE);
      fread(a,sizeof(char),File_Length,file1);
      for(int i=0; i < File_Length; i++) {    // Transport File To Flash
         Process_Label->Caption=IntToStr(i*100/File_Length)+" %"; // Display Process %
         ProgressBar1->Position = i;
         Application->ProcessMessages();
         x[2] = char(ADDR>>16);         // Send Data and Address
         x[3] = char(ADDR>>8);
         x[4] = char(ADDR);
         x[5] = 0xFF;
         x[6] = a[i];
         if(i%MAX_TOTAL_PACKET==MAX_TOTAL_PACKET-1) USB1.Reset_Device(0);
         if(i<File_Length-1) USB1.Write_Data(x,8,0,false);
         else                USB1.Write_Data(x,8,0,true);
         ADDR++;    // Inc Address
      }
      USB1.Reset_Device(0);
      fclose(file1);           // Close File
      if(FileExists("c123.tmp")) DeleteFile("123.tmp");   // Delete Temp File
      Panel1->Visible = false;        // Close Busy Panel
      Show_All_Button(true);          // Enable All Button
      VirtualFree(a,0,MEM_RELEASE);    // Free Temp Memory
      Screen->Cursor = crArrow;
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ConfigControllerButton1Click(TObject *Sender)
{
    if(USB_is_Open) CloseUSBPort1->Click();
    Application->ProcessMessages();
    ShellExecute(NULL,NULL,"quartus_pgm","-cUSB-Blaster -mJTAG --o=P;DE1_Zetup.sof",NULL,SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ConfigKotkuButton1Click(TObject *Sender)
{
    if(USB_is_Open) CloseUSBPort1->Click();
    Application->ProcessMessages();
    ShellExecute(NULL,NULL,"quartus_pgm","-cUSB-Blaster -mJTAG --o=P;Kotku.sof",NULL,SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------
bool __fastcall TForm1::AutoOpenUSB(TObject *Sender)
{
    if(!USB_is_Open) {
        USB1.Select_Device(USB1.DevNum);
        if(USB1.Open_Device()) {
            USB_is_Open = true;
            USB1.Reset_Device(USB1.DevNum);
            Show_All_Button(true);    // Enable All Button
            ToolBar1->Buttons[0]->Enabled = false;
            ToolBar1->Buttons[1]->Enabled = true;
        }
        else {
           ShowMessage("Could not open the USB, try Open Menu");
           return(false);
        }
    }
    return(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EraseFlashButton1Click(TObject *Sender)
{
    if(AutoOpenUSB(Sender)) {
        Button3->Click();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LoadBiosButton1Click(TObject *Sender)
{
    if(AutoOpenUSB(Sender)) {
        CheckBox1->Checked = true;
        iWR_ADDR->Text     = "0";
        OpenDialog1->DefaultExt = "rom";
        Button6->Click();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LoadAtoFlashButton1Click(TObject *Sender)
{
    if(AutoOpenUSB(Sender)) {
        CheckBox1->Checked = true;
        iWR_ADDR->Text     = "200000";
        OpenDialog1->DefaultExt = "img";
        Button6->Click();
    }
}
//---------------------------------------------------------------------------
















