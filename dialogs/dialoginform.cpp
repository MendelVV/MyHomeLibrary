#include "dialoginform.h"

DialogInForm::DialogInForm(FormPlusData* formP, QWidget *parent) : QDialog(parent)
{
    setModal(true);
    form = formP;
    CellPlusClass* cell;
    cell = form->getCell("butOk");
    connect(cell,SIGNAL(signalPress()),this,SLOT(accept()));
    cell = form->getCell("butCancel");
    connect(cell,SIGNAL(signalPress()),this,SLOT(reject()));
    LayoutToForm* ltf = new LayoutToForm;
    ltf->addFormData(form);
    setLayout(ltf);
}

DialogInForm::~DialogInForm(){
    delete form;
}

void DialogInForm::keyPressEvent(QKeyEvent *e){
    switch (e->key()){
    case Qt::Key_Enter:
        accept();
        break;
    case Qt::Key_Escape:
        reject();
        break;
    default:
        QDialog::keyPressEvent(e);
    }
}
