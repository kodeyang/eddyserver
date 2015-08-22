#include <QtWidgets/QTableView>


class DocumentTableView : public QTableView
{
public:
	explicit DocumentTableView(QWidget *parent = 0);

	~DocumentTableView();
};