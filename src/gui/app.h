#ifndef APP_H
#define APP_H

#include <string.h>
#include <windows.h>
#include <QShortcut>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <qtablewidget.h>
#include <QComboBox>
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
#include "../Model/MoviesTableModel.h"
#include "../controller/controller.h"


class App : public QMainWindow
{
	Q_OBJECT
private:
	//Ui::AppClass ui;
	Controller& __ctrl;

	QWidget* __widgetMain;
	QTime __timeStamp;
	QTableView* __moviesTableView = new QTableView;
	MoviesTableModel* __moviesTableModel = new MoviesTableModel({});
	QListView* __moviesListView = new QListView;
	QLabel* __labelMoviesNumber;
	QPushButton* __refresh;
	QPushButton* __sortByActorButton;
	QPushButton* __sortByTitleButton;
	QPushButton* __addButton;
	QPushButton* __updateButton;
	QPushButton* __deleteButton;
	QPushButton* __searchButton;
	QPushButton* __quitButton;
	QPushButton* __generateRandomButton;
	QPushButton* __undoButton;
	QComboBox* __sortComboBox;
	QLineEdit* __titleLineEdit;
	QLineEdit* __genLineEdit;
	QLineEdit* __releaseYearLineEdit;
	QLineEdit* __mainActorLineEdit;
	QLineEdit* __searchLineEdit;
	QLineEdit* __generateRandomLineEdit;

	void __initComponents();
	void __connectSignalsSlots();
	void __refreshMainTable();
	void __reloadList(const std::vector<Film>& filme);
	void __inLineDetalisEdit(const std::string& title, const std::string& gen, const std::string& releaseYear, const std::string& mainActor);
	void __displayError(const std::string& error);
	private slots:
	void __on_addButton_clicked();
	void __on_selectedTableCell_clicked(const QModelIndex &index);
	void __on_deleteButton_clicked();
	void __on_searchButton_clicked();
	void __on_quitButton_clicked();
	void __on_generateRandomButton_clicked();
	void __on_updateButton_clicked();
	void __on_undoButton_clicked();

public:
	App(Controller& __ctrl) : __ctrl{ __ctrl } {
		//boot the application here!
		__initComponents();
		__connectSignalsSlots();
		__refreshMainTable();
	}
	~App();
};

#endif // APP_H
