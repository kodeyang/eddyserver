#include <QtWidgets/QListWidget>
#include "DataSource.h"


class CategoryView : public QListWidget
{
public:
	explicit CategoryView(database_ptr db, QWidget *parent = 0);

	~CategoryView();

public Q_SLOTS:
	void categoryDeleted(const size_t index);

	void categoryCreated(const QString &name);

	void categoryModified(const size_t index, const QString &new_name);

private:
	database_ptr database_;
};