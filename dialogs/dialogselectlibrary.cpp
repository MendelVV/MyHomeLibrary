#include "dialogselectlibrary.h"

DialogSelectLibrary::DialogSelectLibrary(SettingsBooksClass* setting, QWidget *parent) :
    QDialog(parent)
{
    double x =((double)GetSystemMetrics(SM_CXSCREEN))/100;;
    setModal(true);
    form = new FormPlusData;
    form->readFormPlusData(":/resource/FormSelectLibrary.cfpoq");
    form->getCell("fldLibrary")->setValue(setting->getDbName());
    form->getCell("fldDir")->setValue(setting->getDir());
    connect(form->getCell("butLibrary"),SIGNAL(signalPress()),this,SLOT(slotSelectLibrary()));
    connect(form->getCell("butDir"),SIGNAL(signalPress()),this,SLOT(slotSelectDir()));
    LayoutToForm* ltf = new LayoutToForm;
    ltf->addFormData(form);
    QHBoxLayout* butLayout = new QHBoxLayout;
    QPushButton* butOk = new QPushButton("Ok");
    butOk->setObjectName("ButtonCell");
    butOk->setFixedWidth(6*x);
    connect(butOk,SIGNAL(clicked(bool)),this,SLOT(accept()));
    butLayout->addWidget(butOk);

    QPushButton* butCancel = new QPushButton(tr("Cancel"));
    butCancel->setFixedWidth(6*x);
    butCancel->setObjectName("ButtonCell");
    connect(butCancel,SIGNAL(clicked(bool)),this,SLOT(reject()));
    butLayout->addWidget(butCancel);
    QGridLayout* layout = new QGridLayout;
    layout->addLayout(ltf,0,0);
    layout->addLayout(butLayout,1,0,Qt::AlignHCenter);
    layout->setMargin(x/2);
    setLayout(layout);
    QPalette pal;
    QColor color(234,252,250);//(255,255,185);
    pal.setColor(backgroundRole(),color);
    setPalette(pal);
}

DialogSelectLibrary::~DialogSelectLibrary(){
    delete form;
}

void DialogSelectLibrary::setFormText(){
    form->getCell("lblTitle")->setValue(tr("Select library file and books directory"));
    form->getCell("lblLibrary")->setValue(tr("Library data"));
    form->getCell("lblDir")->setValue(tr("Directory data"));
    form->getCell("butLibrary")->setValue(tr("Select"));
    form->getCell("butDir")->setValue(tr("Select"));
}

void DialogSelectLibrary::slotSelectLibrary(){
    QString str = QFileDialog::getOpenFileName(this,tr("Select library file"),"","");//"Выберите файл библиотеки"
    if (str!=""){
        form->getCell("fldLibrary")->setValue(str);
        form->getCell("fldLibrary")->changeValueWidget();
    }
}

void DialogSelectLibrary::slotSelectDir(){
    QString str = QFileDialog::getExistingDirectory(this,tr("Select books directory "),"",false);//"Выберите директорию с книгами"
    if (str!=""){
        form->getCell("fldDir")->setValue(str);
        form->getCell("fldDir")->changeValueWidget();
    }
}
