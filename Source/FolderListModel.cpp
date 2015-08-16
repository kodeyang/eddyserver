#include "FolderListModel.h"
#include "DataSource.h"


FolderListModel::FolderListModel(QSharedPointer<DataSource> data, QObject *parent)
	: QAbstractListModel(parent)
	, data_source_(data)
{
	QObject::connect(data.data(), &DataSource::refresh, this, &FolderListModel::refresh);
}

FolderListModel::~FolderListModel()
{

}

void FolderListModel::refresh()
{
	endResetModel();
}

int FolderListModel::rowCount(const QModelIndex &parent) const
{
	return data_source_->folderList().size();
}

QVariant FolderListModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}

	if (role == Qt::TextAlignmentRole)
	{
		return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
	}
	else if (role == Qt::DisplayRole)
	{
		return data_source_->folderList()[index.row()];
	}

	return QVariant();
}