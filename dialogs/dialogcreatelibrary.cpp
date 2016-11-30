#include "dialogcreatelibrary.h"

DialogCreateLibrary::DialogCreateLibrary(QWidget *parent) : QDialog(parent)
{
    setModal(true);
    setWindowTitle(tr("No data!"));//"Нет данных!"
    form = new FormPlusData;
    form->readFormPlusData(":/resource/FormDialogCreateLibrary.cfpoq");
    setFormText();
    CellPlusClass* cell;
    cell = form->getCell("butNewLibrary");
    connect(cell,SIGNAL(signalPress()),this,SLOT(accept()));

    cell = form->getCell("butNotNewLibrary");
    connect(cell,SIGNAL(signalPress()),this,SLOT(reject()));

    LayoutToForm* ltf = new LayoutToForm;
    ltf->addFormData(form);
    setLayout(ltf);
}

void DialogCreateLibrary::setFormText(){
    form->getCell("lblText")->setValue(tr("Select action to continue"));
    form->getCell("butNewLibrary")->setValue(tr("Create new library"));
    form->getCell("butNotNewLibrary")->setValue(tr("Not create and continue"));
}
