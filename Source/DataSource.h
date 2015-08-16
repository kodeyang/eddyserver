﻿#pragma once

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
	enum MessageCode
	{
		CATEGORY_EXISTS,
		CATEGORY_NOT_EXISTS,
	};

public:
	explicit DataSource();
	~DataSource();

public:
	QByteArray exportData() const;

	void importData(const QByteArray &bytes);

public:
	bool deleteCategory(size_t index);

	bool addCategory(const QString &name);

	bool renameCategory(size_t index, const QString &new_name);

	QVector<QString> categorys() const;

	bool hasCategory(const QString &name) const;

private:
	QVector<QString> category_order_;
	QMap<QString, QVector<PWData>> all_records_;
};