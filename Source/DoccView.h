#include <QtWidgets/QTableWidget>


class DoccView : public QTableWidget
{
	Q_OBJECT

public:
	explicit DoccView(QWidget *parent = 0);
	~DoccView();
};