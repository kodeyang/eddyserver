#include <QtWidgets/QTableWidget>


class DocTableView : public QTableWidget
{
	Q_OBJECT

public:
	explicit DocTableView(QWidget *parent = 0);
	~DocTableView();
};