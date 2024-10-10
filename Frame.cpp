#include "Frame.h"
#include <wx/artprov.h>

//�ú궨�崴���¼���
BEGIN_EVENT_TABLE(Frame,wxFrame)
    EVT_MENU(wxID_NEW,Frame::onNew)
    EVT_MENU(wxID_EXIT,Frame::onQuit)
    EVT_TOOL(wxID_HELP,Frame::onHelp)
END_EVENT_TABLE();

Frame::Frame(wxWindow* parent,
    wxWindowID id,
    const wxString& title,
    const wxPoint& pos,
    const wxSize& size,
    long style,
    const wxString& name) :
    wxFrame(parent, id, title, pos, size, style, name)
{
    wxMenuBar* menuBar = new wxMenuBar();
    wxMenu* fileMenu = new wxMenu();

    //wxWidgets default wxMenuItem example
    fileMenu->Append(wxID_NEW);

    //Custom wxMenuItem �Զ���ѡ��
    wxMenuItem* testItem = fileMenu->Append(wxID_ANY, _("&Test\tCtrl+T"));
    Bind(wxEVT_MENU, &Frame::onTest, this, testItem->GetId());

    //Separator �ָ���
    fileMenu->AppendSeparator();

    //Submenu exampke �����˵�
    wxMenu* subMenu = new wxMenu();
    subMenu->Append(wxID_CUT);
    subMenu->Append(wxID_COPY);
    subMenu->Append(wxID_PASTE);
    fileMenu->AppendSubMenu(subMenu, _("SubMenu"));

    fileMenu->AppendSeparator();

    //Create wxMenuItem example ����ѡ����ͼ��
    wxMenuItem* quitItem = new wxMenuItem(fileMenu, wxID_EXIT);
    quitItem->SetBitmap(wxArtProvider::GetBitmap("wxART_QUIT"));

    fileMenu->Append(quitItem);

    menuBar->Append(fileMenu, _("&File"));
    SetMenuBar(menuBar);




    wxToolBar* toolBar = CreateToolBar();

    //Create new tool
    toolBar->AddTool(wxID_NEW, _("New"), wxArtProvider::GetBitmap("wxART_NEW"));

    //Separator
    toolBar->AddSeparator();

    //Create quit tool
    toolBar->AddTool(wxID_EXIT, _("Quit"), wxArtProvider::GetBitmap("wxART_QUIT"));
    
    //����չ�Ŀռ�
    toolBar->AddStretchableSpace();

    //Create help tool
    toolBar->AddTool(wxID_HELP, _("Help"), wxArtProvider::GetBitmap("wxART_HELP"));
    toolBar->SetToolShortHelp(wxID_HELP, _("This is the help button"));
    toolBar->SetToolLongHelp(wxID_HELP, _("This is the long help text"));

    toolBar->Realize();




    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);//wxVERTICAL��ֱ  wxHORIZONTALˮƽ

    //Create first name box
    wxTextCtrl* firstNameBox = new wxTextCtrl(this, wxID_ANY);

    //�ڶ���������ʾ�Ƿ�����   0����������  ��0���������죨wxVERTICAL��/�������죨wxHORIZONTAL)
    //����������flag   wxEXPAND��ʾռ���ռ�
    //���ĸ�������ʾ�߿���(��Ҫ��ǩ��ʾλ�ã�wxALL/wxLEFT/wxRIGHT/wxTOP/wxBUTTOM��
    mainSizer->Add(firstNameBox,1,wxEXPAND | wxALL,10);

    SetSizer(mainSizer);




    const int SIZE = 2;
    wxStatusBar* statusBar = CreateStatusBar(2);
    statusBar->SetStatusText(_("Ready!"));
    statusBar->SetStatusText(_("Hello World"), 1);
    //����ÿ��״̬�Ŀ��
    int widths[SIZE] = { -2,-1 };//������ʾ�ɱ��ȣ�����֪��1�����Ϊ��2����������ʵ�ʿ����wx����
    statusBar->SetStatusWidths(SIZE, widths);
}




//Event handling
void Frame::onNew(wxCommandEvent& event) 
{
    wxMessageBox("Frame::onNew");
    PushStatusText(_("Frame::onNew"));

    wxSleep(5);//ά��5��

    PopStatusText();//����
}

void Frame::onTest(wxCommandEvent& event)
{
    wxMessageBox("Frame::onTest");
}

void Frame::onHelp(wxCommandEvent& event)
{
    wxMessageBox("Frame::onHelp");
}

void Frame::onQuit(wxCommandEvent& event)
{
    wxMessageBox("Frame::onQuit");
    bool veto = Close();
}

void Frame::onClose(wxCloseEvent& event)
{
    wxMessageBox("Frame::onClose");

    if (event.CanVeto())
    {
        int answer = wxMessageBox("Should we close?", _("Confirm?"), wxYES_NO);

        if (answer != wxYES)
        {
            event.Veto();
            return;
        }
    }
    Destroy();
}

Frame::~Frame()
{

}