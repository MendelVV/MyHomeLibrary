#include "dialogcreatelibrary.h"

DialogCreateLibrary::DialogCreateLibrary(QWidget *parent) : QDialog(parent)
{
    setModal(true);
    setWindowTitle("Нет данных!");
    form = new FormPlusData;
    form->readFormPlusData(":/resource/FormDialogCreateLibrary.cfpoq");
    CellPlusClass* cell;
    cell = form->getCell("butNewLibrary");
    connect(cell,SIGNAL(signalPress()),this,SLOT(accept()));

    cell = form->getCell("butNotNewLibrary");
    connect(cell,SIGNAL(signalPress()),this,SLOT(reject()));

    LayoutToForm* ltf = new LayoutToForm;
    ltf->addFormData(form);
    setLayout(ltf);
}

