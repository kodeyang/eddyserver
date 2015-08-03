#pragma once

#include <QObject>

class DataSource : public QObject
{
	Q_OBJECT

public:
	explicit DataSource();
	~DataSource();
};