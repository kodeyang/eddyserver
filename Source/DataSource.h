#pragma once

#include <QMap>
#include <QVector>
#include <QObject>
#include <QSharedPointer>

struct PassWordData
{
	QString title;
	QString user_name;
	QString pass_word;
	QString url;
	QString notes;
};

typedef QSharedPointer<class DataSource> database_ptr;

class DataSource final : public QObject
{
	Q_OBJECT

public:
	explicit DataSource() = default;
	~DataSource() = default;

public:
	void clear();

	QByteArray exportData() const;

	void importData(const QByteArray &bytes);

public:
	bool hasCategory(const QString &name);

	bool deleteCategory(const size_t index);

	bool createCategory(const QString &name);

	bool modifieCategory(const size_t index, const QString &new_name);

	bool deleteDocument(const size_t category_index, const size_t doc_index);

	bool createDocument(const size_t category_index, const PassWordData &doc);

	bool modifieDocument(const size_t category_index, const size_t doc_index, const PassWordData &doc);

Q_SIGNALS:
	void categoryDeleted(const size_t index);

	void categoryCreated(const QString &name);

	void categoryModified(const size_t index, const QString &new_name);

	void documentDeleted(const size_t category_index, const size_t doc_index);

	void documentCreated(const size_t category_index, const PassWordData &doc);

	void documentModified(const size_t category_index, const size_t doc_index, const PassWordData &doc);

private:
	QVector<QString>						category_order_;
	QMap<QString, QVector<PassWordData>>	all_password_data_;
};