#include "app.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QAbstractTableModel>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <string>
#include <iostream>
#include <qdebug.h>
#include "../Model/MoviesTableModel.h"

/*
App::App(QWidget *parent)
: QMainWindow(parent)
{
ui.setupUi(this);
}
*/

void App::__initComponents() {
	QGridLayout* layoutMain = new QGridLayout;
	setLayout(layoutMain);

	this->__widgetMain = new QWidget;
	setCentralWidget(__widgetMain);
	__widgetMain->setLayout(layoutMain);

	//adaug list si sub 2 butoane de sort
	//QWidget* widgetMoviesList = new QWidget;
	QHBoxLayout* layoutMoviesList = new QHBoxLayout;
	//widgetMoviesList->setLayout(layoutMoviesList);
	//__moviesListWidget = new QListWidget;
	//__moviesListWidget->setLayout(layoutMoviesList);
	//layoutMoviesList->addWidget(__moviesListWidget);

	QWidget* widgetMovieListOperations = new QWidget;
	QGridLayout* layoutMoviesListOperations = new QGridLayout;
	this->__sortComboBox = new QComboBox;
	layoutMoviesListOperations->addWidget(this->__sortComboBox);
	widgetMovieListOperations->setLayout(layoutMoviesListOperations);
	__sortByTitleButton = new QPushButton("Sort by title");
	layoutMoviesListOperations->addWidget(__sortByTitleButton);
	__sortByActorButton = new QPushButton("Sort by actor");
	layoutMoviesListOperations->addWidget(__sortByActorButton);
	__deleteButton = new QPushButton("Delete selected");
	layoutMoviesListOperations->addWidget(__deleteButton);


	//form pentru detalii
	QWidget* widgetDetailsMovie = new QWidget;
	QFormLayout* formLayoutDetalisMovie = new QFormLayout;
	widgetDetailsMovie->setLayout(formLayoutDetalisMovie);
	this->__titleLineEdit = new QLineEdit;
	formLayoutDetalisMovie->addRow(new QLabel("Title:"), this->__titleLineEdit);
	this->__genLineEdit = new QLineEdit;
	formLayoutDetalisMovie->addRow(new QLabel("Gen:"), this->__genLineEdit);
	this->__releaseYearLineEdit = new QLineEdit;
	formLayoutDetalisMovie->addRow(new QLabel("Release year:"), this->__releaseYearLineEdit);
	this->__mainActorLineEdit = new QLineEdit;
	formLayoutDetalisMovie->addRow(new QLabel("Main actor"), this->__mainActorLineEdit);
	this->__addButton = new QPushButton("Add film");
	formLayoutDetalisMovie->addWidget(this->__addButton);
	this->__updateButton = new QPushButton("Update film");
	formLayoutDetalisMovie->addWidget(this->__updateButton);


	QWidget* widgetSearchAndGenerate = new QWidget;
	QFormLayout* formLayoutSearchAndGenerate = new QFormLayout;
	widgetSearchAndGenerate->setLayout(formLayoutSearchAndGenerate);
	this->__searchLineEdit = new QLineEdit;
	formLayoutSearchAndGenerate->addRow(new QLabel("Search by title"), this->__searchLineEdit);
	this->__searchButton = new QPushButton("Search");
	formLayoutSearchAndGenerate->addWidget(this->__searchButton);
	this->__generateRandomLineEdit = new QLineEdit;
	formLayoutSearchAndGenerate->addRow(new QLabel("Genereaza random: "), this->__generateRandomLineEdit);
	this->__generateRandomButton = new QPushButton("Generate");
	formLayoutSearchAndGenerate->addWidget(this->__generateRandomButton);
	this->__undoButton = new QPushButton("Undo");
	formLayoutSearchAndGenerate->addWidget(this->__undoButton);

	QWidget* widgetQuit = new QWidget;
	QHBoxLayout* layoutQuit = new QHBoxLayout;
	widgetQuit->setLayout(layoutQuit);
	__quitButton = new QPushButton("Quit");
	layoutQuit->addWidget(__quitButton);

	QWidget* widgetMoviesTable = new QWidget;
	QVBoxLayout* layoutMoviesTable = new QVBoxLayout;
	widgetMoviesTable->setLayout(layoutMoviesTable);
	this->__labelMoviesNumber = new QLabel("Total movies: 0");
	layoutMoviesTable->addWidget(this->__labelMoviesNumber);
	this->__moviesTableView = new QTableView;
	layoutMoviesTable->addWidget(this->__moviesTableView);

	layoutMain->addWidget(widgetMoviesTable, 0, 0, 2, 2);
	layoutMain->addWidget(widgetMovieListOperations, 1, 2);
	layoutMain->addWidget(widgetDetailsMovie, 3, 0);
	layoutMain->addWidget(widgetSearchAndGenerate, 3, 1);
	layoutMain->addWidget(widgetQuit, 5, 2);
}

void App::__connectSignalsSlots() {
	//cand se emite semnalul clicked de pe buton reincarc list
	QObject::connect(__sortByTitleButton, &QPushButton::clicked, this, [&]() {
		__reloadList(__ctrl.getSortedByTitleAsc());
	});
	QObject::connect(__sortByActorButton, &QPushButton::clicked, this, [&]() {
		__reloadList(__ctrl.getSortedByMainActorAsc());
	});
	//QObject::connect(__moviesListWidget, &QListWidget::itemSelectionChanged, this, &App::__on_selectMovieFromList);
	QObject::connect(__addButton, &QPushButton::clicked, this, &App::__on_addButton_clicked);
	QObject::connect(__updateButton, &QPushButton::clicked, this, &App::__on_updateButton_clicked);
	QObject::connect(__undoButton, &QPushButton::clicked, this, &App::__on_undoButton_clicked);
	QObject::connect(__deleteButton, &QPushButton::clicked, this, &App::__on_deleteButton_clicked);
	QObject::connect(__searchButton, &QPushButton::clicked, this, &App::__on_searchButton_clicked);
	QObject::connect(__quitButton, &QPushButton::clicked, this, &App::__on_quitButton_clicked);
	QObject::connect(__generateRandomButton, &QPushButton::clicked, this, &App::__on_generateRandomButton_clicked);
	QObject::connect(__moviesTableView, &QTableView::clicked, this, &App::__on_selectedTableCell_clicked);
	QObject::connect(__moviesTableModel, &QAbstractTableModel::dataChanged, this, &App::__on_selectedTableCell_clicked);
}

void App::__refreshMainTable() {
	__reloadList(__ctrl.getAll());
}

void App::__on_searchButton_clicked() {
	std::string title = __searchLineEdit->text().toStdString();
	__searchLineEdit->clear();
	try {
		auto result = __ctrl.search(title);
		__reloadList(result);
	}
	catch (FilmException& ex) {
		__displayError(ex.getMsg());
	}

}

void App::__reloadList(const std::vector<Film>& films) {
	/*__moviesListWidget->clear();
	for (const auto& film : films) {
		QString title{ film.getTitle().c_str() };
		QString gen{ film.getGen().c_str() };
		QString releaseYear{ std::to_string(film.getReleaseYear()).c_str() };
		QString mainActor{ film.getMainActor().c_str() };
		__moviesListWidget->addItem(title + " | " + gen + " | " + releaseYear + " | " + mainActor);
	}*/
	std::string tmp = "Total: " + std::to_string(films.size());
	this->__labelMoviesNumber->setText(tmp.c_str());
	this->__moviesTableModel = new MoviesTableModel(films);
	this->__moviesTableView->setModel(this->__moviesTableModel);
	this->__moviesTableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void App::__inLineDetalisEdit(const std::string& title, const std::string& gen, const std::string& releaseYear, const std::string& mainActor) {
	__titleLineEdit->setText(title.c_str());
	__genLineEdit->setText(gen.c_str());
	__releaseYearLineEdit->setText(releaseYear.c_str());
	__mainActorLineEdit->setText(mainActor.c_str());
}

void App::__on_selectedTableCell_clicked(const QModelIndex &index) {
	if (index.isValid() == false) {
		this->__displayError("You have not selected a valid cell!");
	}
	int row = index.row();
	this->__moviesTableView->selectRow(row);
	std::string title = index.sibling(row, 0).data().toString().toStdString();
	try {
		Film film = __ctrl.find(title);
		__inLineDetalisEdit(film.getTitle(), film.getGen(), std::to_string(film.getReleaseYear()), film.getMainActor());
	}
	catch (FilmException& ex) {
		__displayError(ex.getMsg());
	}
}

void App::__on_deleteButton_clicked() {
	std::string errors{ "" };
	QModelIndexList selectedRows = __moviesTableView->selectionModel()->selectedRows();
	for (auto& index : selectedRows)	{
		if (index.isValid() == false) {
			__displayError("You have not selected any movie yet");
			return;
		}
		int row = index.row();
		std::string title = index.sibling(row, 0).data().toString().toStdString();
		try {
			qDebug() << title.c_str() << "\n";
			__ctrl.del(title);
		}
		catch (FilmException& ex) {
			errors += ex.getMsg() + "\n";
		}
	}
	qDebug() << selectedRows.size() << "\n";
	__refreshMainTable();

	if (!errors.empty()) {
		__displayError(errors);
	}
}

void App::__displayError(const std::string& error) {
	QMessageBox::warning(this, "Warning", QString::fromStdString(error));
}

void App::__on_addButton_clicked() {
	try {
		std::string title = __titleLineEdit->text().toStdString();
		std::string gen = __genLineEdit->text().toStdString();
		int releaseYear = __releaseYearLineEdit->text().toInt();
		std::string mainActor = __mainActorLineEdit->text().toStdString();
		__ctrl.add(title, gen, releaseYear, mainActor);
		__refreshMainTable();
	}
	catch (FilmException& ex) {
		__displayError(ex.getMsg());
	}
}

void App::__on_generateRandomButton_clicked() {
	std::string howManyStr = __generateRandomLineEdit->text().toStdString();
	int howMany = atoi(howManyStr.c_str());
	try {
		this->__ctrl.fillRepoRandom(howMany);
		this->__refreshMainTable();
	}
	catch (FilmException& ex) {
		this->__displayError(ex.getMsg());
	}
}

void App::__on_updateButton_clicked() {
	try {
		std::string title = __titleLineEdit->text().toStdString();
		std::string gen = __genLineEdit->text().toStdString();
		int releaseYear = __releaseYearLineEdit->text().toInt();
		std::string mainActor = __mainActorLineEdit->text().toStdString();
		Film film = this->__ctrl.createFilm(title, gen, releaseYear, mainActor);
		__ctrl.update(film);
		__refreshMainTable();
	}
	catch (FilmException& ex) {
		__displayError(ex.getMsg());
	}
}

void App::__on_undoButton_clicked() {
	try {
		this->__ctrl.undo();
		this->__refreshMainTable();
	}
	catch (FilmException& ex) {
		this->__displayError(ex.getMsg());
	}
}

void App::__on_quitButton_clicked() {
	qApp->quit();
}

App::~App()
{

}
