#pragma once

#include <QMap>
#include <QVector>
#include <QObject>

struct PWData
{
	QString title;
	QString user_name;
	QString pass_word;
	QString url;
	QString notes;
};

class DataSource : public QObject
{
	Q_OBJECT

public:
	explicit DataSource();
	~DataSource();

public:
	QByteArray exportData() const;

	void importData(const QByteArray &bytes);

public:
	bool deleteFolder(size_t index);

	bool addFolder(const QString &name);

	bool renameFolder(size_t index, const QString &new_name);

	const QVector<QString>& folderList() const;

	bool hasFolder(const QString &name) const;

private:
	QVector<QString> folder_order_;
	QMap<QString, QVector<PWData>> all_records_;
};