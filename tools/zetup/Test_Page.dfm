object Form4: TForm4
  Left = 196
  Top = 570
  AutoScroll = False
  AutoSize = True
  Caption = 'Board Test'
  ClientHeight = 218
  ClientWidth = 154
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 16
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 154
    Height = 218
    TabOrder = 0
    object CheckBox6: TCheckBox
      Left = 19
      Top = 141
      Width = 103
      Height = 20
      Caption = 'LCD Test'
      TabOrder = 0
    end
    object CheckBox1: TCheckBox
      Left = 19
      Top = 13
      Width = 103
      Height = 20
      Caption = 'LED Test'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
    end
    object Button1: TButton
      Left = 19
      Top = 173
      Width = 110
      Height = 33
      Caption = 'Start Test'
      TabOrder = 2
      OnClick = Button1Click
    end
    object CheckBox4: TCheckBox
      Left = 19
      Top = 115
      Width = 103
      Height = 20
      Caption = 'FLASH Test'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object CheckBox3: TCheckBox
      Left = 19
      Top = 90
      Width = 103
      Height = 20
      Caption = 'SRAM Test'
      TabOrder = 4
    end
    object CheckBox5: TCheckBox
      Left = 19
      Top = 64
      Width = 103
      Height = 20
      Caption = 'SDRAM Test '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
    end
    object CheckBox2: TCheckBox
      Left = 19
      Top = 38
      Width = 103
      Height = 20
      Caption = '7 SEG Test'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 6
    end
  end
end
