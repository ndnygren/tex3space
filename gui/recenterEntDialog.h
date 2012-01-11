#include "../t3_ent.h"
#include <QtGui>
#include <sstream>

#ifndef NN_RECENTERENTDIALOG_H
#define NN_RECENTERENTDIALOG_H


class recenterEntDialog : public QDialog
{
	Q_OBJECT

	private:
	t3_ent::minmax6tuple mm;
	QLabel *xlab, *ylab, *zlab;
	QLineEdit *xoffs, *yoffs, *zoffs;
	QVBoxLayout *vbox;
	QHBoxLayout *hbox;
	QGridLayout *grid;
	QPushButton *CXButton, *CYButton, *CZButton;
	QPushButton *MXXButton, *MXYButton, *MXZButton;
	QPushButton *MNXButton, *MNYButton, *MNZButton;
	QPushButton *accbutton, *decbutton;

	QString dtoqs(double x)
	{
		std::stringstream ss;
		ss << x;
		return QString(ss.str().c_str());
	}

	static double parseD(QString input)
	{
		double x;
		std::stringstream ss(input.toStdString());
		ss >> x;

		return x;
	}

	public slots:
	void centerX() { xoffs->setText(dtoqs((mm.min_x + mm.max_x) / 2)); }
	void centerY() { yoffs->setText(dtoqs((mm.min_y + mm.max_y) / 2)); }
	void centerZ() { zoffs->setText(dtoqs((mm.min_z + mm.max_z) / 2)); }
	void minX() { xoffs->setText(dtoqs(mm.min_x)); }
	void minY() { yoffs->setText(dtoqs(mm.min_y)); }
	void minZ() { zoffs->setText(dtoqs(mm.min_z)); }
	void maxX() { xoffs->setText(dtoqs(mm.max_x)); }
	void maxY() { yoffs->setText(dtoqs(mm.max_y)); }
	void maxZ() { zoffs->setText(dtoqs(mm.max_z)); }

	public:

	double getX() const { return parseD(xoffs->text()); }
	double getY() const { return parseD(yoffs->text()); }
	double getZ() const { return parseD(zoffs->text()); }

	recenterEntDialog(QWidget *par, t3_ent::minmax6tuple mmin) : QDialog(par)
	{
		QValidator *doubleval = new QDoubleValidator(this);
		std::string diatitle = "Re-Center Entity";

		mm = mmin;

		xlab = new QLabel("X Offset:");
		ylab = new QLabel("Y Offset:");
		zlab = new QLabel("Z Offset:");
		
		xoffs = new QLineEdit();
		yoffs = new QLineEdit();
		zoffs = new QLineEdit();

		xoffs->setText("0");
		yoffs->setText("0");
		zoffs->setText("0");

		xoffs->setValidator(doubleval);
		yoffs->setValidator(doubleval);
		zoffs->setValidator(doubleval);

		grid = new QGridLayout();
		vbox = new QVBoxLayout();
		hbox = new QHBoxLayout();

		CXButton = new QPushButton("Center");
		CYButton = new QPushButton("Center");
		CZButton = new QPushButton("Center");

		MXXButton = new QPushButton("Right");
		MXYButton = new QPushButton("Top");
		MXZButton = new QPushButton("Front");

		MNXButton = new QPushButton("Left");
		MNYButton = new QPushButton("Bottom");
		MNZButton = new QPushButton("Back");

		accbutton = new QPushButton("Accept");
		decbutton = new QPushButton("Cancel");

		grid->addWidget(xlab, 0, 0);
		grid->addWidget(ylab, 1, 0);
		grid->addWidget(zlab, 2, 0);
		grid->addWidget(xoffs, 0, 1);
		grid->addWidget(yoffs, 1, 1);
		grid->addWidget(zoffs, 2, 1);
		grid->addWidget(MNXButton, 0, 2);
		grid->addWidget(MNYButton, 1, 2);
		grid->addWidget(MNZButton, 2, 2);
		grid->addWidget(CXButton, 0, 3);
		grid->addWidget(CYButton, 1, 3);
		grid->addWidget(CZButton, 2, 3);
		grid->addWidget(MXXButton, 0, 4);
		grid->addWidget(MXYButton, 1, 4);
		grid->addWidget(MXZButton, 2, 4);

		hbox->addWidget(accbutton);
		hbox->addWidget(decbutton);

		vbox->addLayout(grid);
		vbox->addLayout(hbox);

		connect(accbutton, SIGNAL(clicked()), this, SLOT(accept()));
		connect(decbutton, SIGNAL(clicked()), this, SLOT(reject()));
		connect(MNXButton, SIGNAL(clicked()), this, SLOT(minX()));
		connect(MNYButton, SIGNAL(clicked()), this, SLOT(minY()));
		connect(MNZButton, SIGNAL(clicked()), this, SLOT(minZ()));
		connect(CXButton, SIGNAL(clicked()), this, SLOT(centerX()));
		connect(CYButton, SIGNAL(clicked()), this, SLOT(centerY()));
		connect(CZButton, SIGNAL(clicked()), this, SLOT(centerZ()));
		connect(MXXButton, SIGNAL(clicked()), this, SLOT(maxX()));
		connect(MXYButton, SIGNAL(clicked()), this, SLOT(maxY()));
		connect(MXZButton, SIGNAL(clicked()), this, SLOT(maxZ()));

		setLayout(vbox);
		setWindowTitle(diatitle.c_str());
	}
};


#endif
