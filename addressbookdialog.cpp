#include "addressbookdialog.h"
#include "ui_addressbookdialog.h"

#include "addresstablemodel.h"
#include "editaddressdialog.h"

#include <QSortFilterProxyModel>

AddressBookDialog::AddressBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddressBookDialog),
    model(0)
{
    ui->setupUi(this);

    model = new AddressTableModel(this);
    setModel(model);
}

AddressBookDialog::~AddressBookDialog()
{
    delete ui;
}

void AddressBookDialog::setModel(AddressTableModel *model)
{
    /* Receive filter */
    QSortFilterProxyModel *receive_model = new QSortFilterProxyModel(this);
    receive_model->setSourceModel(model);
    receive_model->setDynamicSortFilter(true);
    receive_model->setFilterRole(Qt::UserRole);
    receive_model->setFilterKeyColumn(AddressTableModel::Type);
    receive_model->setFilterFixedString(AddressTableModel::Receive);
    ui->receiveTableView->setModel(receive_model);

    /* Send filter */
    QSortFilterProxyModel *send_model = new QSortFilterProxyModel(this);
    send_model->setSourceModel(model);
    send_model->setDynamicSortFilter(true);
    send_model->setFilterRole(Qt::UserRole);
    send_model->setFilterKeyColumn(AddressTableModel::Type);
    send_model->setFilterFixedString(AddressTableModel::Send);
    ui->sendTableView->setModel(send_model);

    /* Set column widths */
    ui->receiveTableView->horizontalHeader()->resizeSection(
            AddressTableModel::Address, 320);
    ui->receiveTableView->horizontalHeader()->setResizeMode(
            AddressTableModel::Label, QHeaderView::Stretch);
    ui->sendTableView->horizontalHeader()->resizeSection(
            AddressTableModel::Address, 320);
    ui->sendTableView->horizontalHeader()->setResizeMode(
            AddressTableModel::Label, QHeaderView::Stretch);

    /* Hide "Type" column in both views as it is only used for filtering */
    ui->receiveTableView->setColumnHidden(AddressTableModel::Type, true);
    ui->sendTableView->setColumnHidden(AddressTableModel::Type, true);
}

void AddressBookDialog::setTab(int tab)
{
    ui->tabWidget->setCurrentIndex(tab);
}

void AddressBookDialog::on_OKButton_clicked()
{
    accept();
}

void AddressBookDialog::on_copyToClipboard_clicked()
{
   /* Copy currently selected address to clipboard */
}

void AddressBookDialog::on_editButton_clicked()
{
    /* Double click should trigger edit button */
    EditAddressDialog dlg;
    dlg.exec();
}

void AddressBookDialog::on_newAddressButton_clicked()
{
    EditAddressDialog dlg;
    dlg.exec();
}