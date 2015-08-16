#include <QSharedPointer>
#include <QAbstractListModel>

class DataSource;

class FolderListModel final : public QAbstractListModel
{
public:
	explicit FolderListModel(QSharedPointer<DataSource> data, QObject *parent = 0);

	~FolderListModel();

	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private Q_SLOTS:
	void refresh();

private:
	QSharedPointer<DataSource> data_source_;
};