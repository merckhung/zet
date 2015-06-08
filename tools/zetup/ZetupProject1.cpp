//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Test_Page.cpp", Form4);
USEFORM("About.cpp", AboutBox);
USEFORM("Main.cpp", Form1);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->Title = "ZET Setup";
         Application->CreateForm(__classid(TForm1), &Form1);
         Application->CreateForm(__classid(TForm4), &Form4);
         Application->CreateForm(__classid(TAboutBox), &AboutBox);
         Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    catch (...)
    {
         try
         {
             throw Exception("");
         }
         catch (Exception &exception)
         {
             Application->ShowException(&exception);
         }
    }
    return 0;
}
//---------------------------------------------------------------------------
