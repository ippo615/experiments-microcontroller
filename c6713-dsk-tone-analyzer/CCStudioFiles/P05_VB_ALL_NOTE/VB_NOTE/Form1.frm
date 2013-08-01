VERSION 5.00
Begin VB.Form Form1 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "DSK Note Receiver"
   ClientHeight    =   5355
   ClientLeft      =   4935
   ClientTop       =   3810
   ClientWidth     =   9105
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5355
   ScaleWidth      =   9105
   Begin VB.CommandButton btDisconnect 
      Caption         =   "Disconnect"
      Enabled         =   0   'False
      Height          =   375
      Left            =   7800
      TabIndex        =   8
      Top             =   2880
      Width           =   1215
   End
   Begin VB.Timer Timer1 
      Interval        =   30
      Left            =   240
      Top             =   240
   End
   Begin VB.TextBox outputArea 
      BeginProperty Font 
         Name            =   "Lucida Console"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   3615
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   7
      Top             =   120
      Width           =   7575
   End
   Begin VB.TextBox tbStatus 
      BeginProperty Font 
         Name            =   "Lucida Console"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1455
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   6
      Text            =   "Form1.frx":0000
      Top             =   3840
      Width           =   8895
   End
   Begin VB.CommandButton btConnect 
      Caption         =   "Connect"
      Height          =   375
      Left            =   7800
      TabIndex        =   5
      Top             =   3360
      Width           =   1215
   End
   Begin VB.CommandButton btListRefresh 
      Caption         =   "Refresh"
      Height          =   375
      Left            =   7800
      TabIndex        =   4
      Top             =   2280
      Width           =   1215
   End
   Begin VB.ListBox list_Processors 
      Height          =   780
      IntegralHeight  =   0   'False
      Left            =   7800
      TabIndex        =   1
      Top             =   1440
      Width           =   1215
   End
   Begin VB.ListBox list_Boards 
      Height          =   780
      IntegralHeight  =   0   'False
      Left            =   7800
      TabIndex        =   0
      Top             =   360
      Width           =   1215
   End
   Begin VB.Label lblListProc 
      Alignment       =   2  'Center
      Caption         =   "Processor:"
      Height          =   255
      Left            =   7800
      TabIndex        =   3
      Top             =   1200
      Width           =   1215
   End
   Begin VB.Label lblListBoards 
      Alignment       =   2  'Center
      Caption         =   "Board:"
      Height          =   255
      Left            =   7800
      TabIndex        =   2
      Top             =   120
      Width           =   1215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'''''''''''''''''''''''''''''''''''''''''''''Utility Variables
Public connected As Integer                 '1 if RTDX channel has been opened
Public lastMsg As String                    'for debugging purposes

'''''''''''''''''''''''''''''''''''''''''''''Needed for RTDX/CCStudio setup
Private CCSetup As Object                   'Used To Access CCStudio functions
Private Boards As Object                    'List of Available boards
Private Board As Object                     'Board
Private Processors As Object                'List of available processors
Private Processor As Object                 'Processor
Public CurrentSelectedBoard As String       'The name of the board
Public CurrentSelectedProcessor As String   'Which processor on the board
Dim rtdx As Object                          'Acutal RTDX object

'''''''''''''''''''''''''''''''''''''''''''''RTDX OLE API Status Return codes
Const SUCCESS = &H0                         'Method call succussful
Const FAIL = &H80004005                     'Method call failure
Const ENoDataAvailable = &H8003001E         'No data is currently available
Const EEndOfLogFile = &H80030002            'End of log file
'Utility function to output debugging messages to lower text area
Private Sub LogMessage(message As String)
    If lastMsg <> message Then
        tbStatus.SelStart = Len(tbStatus.Text)
        tbStatus.SelText = message & vbNewLine
        lastMsg = message
    End If
End Sub
'Utility function that takes the value read from the board, converts it into
'useful text and displays it to the user
'The program on the board was designed to send 0 through 8 to represent
'different notes and -1 when it could not make a decision
'This converts those integers to a more meaningful string
Private Sub ProcessData(ReadVal As Long)
    Dim NOTES() As Variant
    NOTES() = Array("C0", "C_0", "D0", "D_0", "E0", "F0", "F_0", "G0", "G_0", "A0", "A_0", "B0", "C1", "C_1", "D1", "D_1", "E1", "F1", "F_1", "G1", "G_1", "A1", "A_1", "B1", "C2", "C_2", "D2", "D_2", "E2", "F2", "F_2", "G2", "G_2", "A2", "A_2", "B2", "C3", "C_3", "D3", "D_3", "E3", "F3", "F_3", "G3", "G_3", "A3", "A_3", "B3", "C4", "C_4", "D4", "D_4", "E4", "F4", "F_4", "G4", "G_4", "A4", "A_4", "B4", "C5", "C_5", "D5", "D_5", "E5", "F5", "F_5", "G5", "G_5", "A5", "A_5", "B5", "C6", "C_6", "D6", "D_6", "E6", "F6", "F_6", "G6", "G_6", "A6", "A_6", "B6", "C7", "C_7", "D7", "D_7", "E7", "F7", "F_7", "G7", "G_7", "A7", "A_7", "B7", "C8", "C_8", "D8", "D_8")
    If ReadVal = -1 Then
        outputArea.SelStart = Len(outputArea.Text)
        outputArea.SelText = "-"
    End If
    If ReadVal > -1 Then
        outputArea.SelStart = Len(outputArea.Text)
        outputArea.SelText = NOTES(ReadVal) & ","
    End If
End Sub
'When the program starts
Private Sub Form_Load()
    connected = 0 'state that we don't have an RTDX channel open
    If (GetAvailableBoards) Then       ' Get Available Boards and Processors
        list_Boards.Selected(0) = True ' Set the selected board to 0
    End If
End Sub
'When the program ends
Private Sub Form_Unload(Cancel As Integer)
    If connected = 1 Then       'If we have the RTDX channel open
        DisconnectFromBoard     'Close the RTDX channel
    End If
    Set CCSetup = Nothing       'Cleanup
    Set Boards = Nothing        'Cleanup
    Set Board = Nothing         'Cleanup
    Set Processors = Nothing    'Cleanup
    Set Processor = Nothing     'Cleanup
End Sub
'Function to update the list of boards that can be connected to
Private Function GetAvailableBoards() As Boolean
    Dim status As Long
    Dim BoardName As String
    
    ' Initialize Lists
    list_Boards.Clear
    list_Processors.Clear
    
    ' Instantiate the Code Composer Setup SystemSetup coclass and obtain a
    ' pointer to the ISystemSetup interface
    Set CCSetup = CreateObject("CodeComposerSetup.SystemSetup")
    
    ' Get a pointer to the IBoards interface
    status = CCSetup.GetBoards(Boards)
    
    ' Loop through the available boards, get the names of the boards,
    ' and add the board names to the boards list control
    For Each Board In Boards
        ' Get the board name
        status = Board.GetName(BoardName)
        
        ' Append board name to the board list
        list_Boards.AddItem (BoardName)
    Next
    
    ' return True
    GetAvailableBoards = True

End Function

'Function to update the list of processors which can be used
Private Function GetAvailableProcessors(SelectedBoardName As String) As Boolean

    Dim status As Long
    Dim ProcessorName As String
    
    ' Get a pointer to the IBoard interface for the selected
    ' board
    status = CCSetup.GetBoardByName(SelectedBoardName, Board)
    
    
    ' Get a pointer to the IProcessors interface
    status = Board.GetProcessors(Processors)
    
    ' Loop through the available processors, get the names of the
    ' processors, and add the processors to the processors list
    ' control
    For Each Processor In Processors
        ' Get the processor name
        status = Processor.GetName(ProcessorName)
        
        ' Append processor name to the processor list
        list_Processors.AddItem (ProcessorName)
    Next
    
    ' Return True
    GetAvailableProcessors = True

End Function
'When the "connect" button is clicked
Private Sub btConnect_Click()
    If connected = 1 Then       'If we have the RTDX channel open
        DisconnectFromBoard     'Close the RTDX channel
    End If
    ConnectToBoard              'Open the RTDX channel
    btConnect.Enabled = False   'Disable the "connect" button
    btDisconnect.Enabled = True 'Enable the "disconnect" button
End Sub
'When the "disconnect" button is clicked
Private Sub btDisconnect_Click()
    DisconnectFromBoard          'Close the RTDX channel
    btDisconnect.Enabled = False 'Disable the "disconnect" button
    btConnect.Enabled = True     'Enable the "connect" button
End Sub

Private Sub btListRefresh_Click()
    ' Get Available Boards and Processors
    If (GetAvailableBoards) Then
        ' Set the selected board to 0
        list_Boards.Selected(0) = True
    End If
End Sub
'When a board is selected
Private Sub list_Boards_Click()
    ' Clear processor list
    list_Processors.Clear
    ' Get current selected board
    CurrentSelectedBoard = list_Boards.List(list_Boards.ListIndex)
    ' Get available processors for that board
    If (GetAvailableProcessors(CurrentSelectedBoard)) Then
        ' Set the selected processor to 0
        list_Processors.Selected(0) = True
    End If
End Sub
'When a processor is selected
Private Sub list_Processors_Click()
    ' Get current selected processor
    CurrentSelectedProcessor = list_Processors.List(list_Processors.ListIndex)
End Sub
'Function which tries to open the RTDX channel on the selected board/processor
Private Sub ConnectToBoard()
    LogMessage "Info  - Attempting to connect to board " & CurrentSelectedBoard
    LogMessage "Info  - Attempting to connect to processor " & CurrentSelectedProcessor
    Dim status As Long
    ' Get application objects
    Set rtdx = CreateObject("RTDX")
    
    status = rtdx.SetProcessor(CurrentSelectedBoard, CurrentSelectedProcessor)
    If (status <> SUCCESS) Then
        LogMessage "Error - Set Processor failed"
        Exit Sub
    End If
                        
    'open target's input channel
    '"ochan" must agree with RTDX_CreateOutputChannel(ochan);
    'from target source code
    status = rtdx.Open("ochan", "R")
    Select Case status
    Case Is = SUCCESS
        connected = 1
        LogMessage "Info  - Opened RTDX channel for reading"
    Case Is = FAIL
        LogMessage "Error - Unable to open channel for RTDX communications"
        Exit Sub
    Case Else
        LogMessage "Info  - Unknown return value from openning RTDX channel"
        Exit Sub
    End Select
End Sub
'Function which tries to close the RTDX channel on the selected board/processor
Private Sub DisconnectFromBoard()
    Dim status As Long
    ' close target's input channel
    status = rtdx.Close()
    Select Case status
        Case Is = SUCCESS
            LogMessage "Info  - Successfully closed RTDX channel"
        Case Is = FAIL
            LogMessage "Error - Unable to close RTDX channel"
        Case Else
            LogMessage "Info  - Unknown return value from closing RTDX channel"
    End Select
    connected = 0
    Set rtdx = Nothing                     ' kill RTDX OLE object
End Sub
'Function to check for new RTDX data every XX milliseconds
Private Sub Timer1_Timer()
    'Dim ReadValue As Variant
    Dim ReadValue As Long 'rtdx.ReadI4(ReadValue)
    'Dim ReadValue As Int  'rtdx.ReadI2(ReadValue)
    'Dim ReadValue As Single 'rtdx.ReadF4(ReadValue)
    'Dim ReadValue As Double  'rtdx.ReadF8(ReadValue)
    Dim status As Long
    If connected = 1 Then
        'status = rtdx.ReadSAI2(ReadValue)
        'status = rtdx.ReadSAF4(ReadValue)
        'Do
            status = rtdx.ReadI4(ReadValue)
            'status = rtdx.ReadF8(ReadValue)
            Select Case status
                Case Is = SUCCESS
                    ProcessData ReadValue
                    'LogMessage "Data: " & ReadValue
                Case Is = FAIL
                    LogMessage "Error - Reading data failed " & ReadValue
                Case Is = ENoDataAvailable
                    LogMessage "Error - No data available"
                Case Is = EEndOfLogFile
                    LogMessage "Info  - Reached end of log file"
                Case Else
                    LogMessage "Error - Unknown error reading RTDX channel - " & ReadValue
            End Select
        'Loop Until status = EEndOfLogFile
    End If
End Sub
