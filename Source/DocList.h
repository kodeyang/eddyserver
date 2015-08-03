#include <QtWidgets/QListWidget>


class DocList : public QListWidget
{
	Q_OBJECT

public:
	explicit DocList(QWidget *parent = 0);
	~DocList();
};