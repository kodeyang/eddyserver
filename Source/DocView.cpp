#include "DoccView.h"


DoccView::DoccView(QWidget *parent)
	: QTableWidget(parent)
{
	setColumnCount(5);
	QStringList header;
	header << tr("Title") << tr("User Name") << tr("Password") << tr("URL") << tr("Notes");
	setHorizontalHeaderLabels(header);
	this->resizeColumnToContents(0);
}

DoccView::~DoccView()
{

}