#ifndef APP_H
#define APP_H

#include <string.h>
#include <windows.h>
#include <QShortcut>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <QTime>
#include <QtWidgets/QMainWindow>
#include <vector>
#include <string>
#include "ui_app.h"
#include "../controller/controller.h"


class App : public QWidget
{
//	Q_OBJECT
private:
	//Ui::AppClass ui;
	Controller& __ctrl;
	QTime timeStamp;
	QListWidget* __moviesListWidget;
	QListWidget* __logListWidget;
	QLabel* __labelMoviesNumber;
	QPushButton* __refresh;
	QPushButton* __sortByActorButton;
	QPushButton* __sortByTitleButton;
	QPushButton* __addButton;
	QPushButton* __deleteButton;
	QPushButton* __searchButton;
	QPushButton* __quitButton;
	QLineEdit* __titleLineEdit;
	QLineEdit* __genLineEdit;
	QLineEdit* __releaseYearLineEdit;
	QLineEdit* __mainActorLineEdit;
	QLineEdit* __searchLineEdit;

	void __initComponents();
	void __connectSignalsSlots();
	void __refreshList();
	void __reloadList(const std::vector<Film>& filme);
	void __inLineDetalisEdit(const std::string& title, const std::string& gen, const std::string& releaseYear, const std::string& mainActor);
	void __displayError(const std::string& error);
private slots:
	void __on_addButton_clicked();
	void __on_selectMovieFromList();
	void __on_deleteButton_clicked();
	void __on_searchButton_clicked();
	void __on_quitButton_clicked();

public:
	App(Controller& __ctrl) : __ctrl{ __ctrl } {
		//boot the application here!
		__initComponents();
		__connectSignalsSlots();
		__refreshList();
	}
	~App();
};

#endif // APP_H
