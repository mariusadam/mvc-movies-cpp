#include "app.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <string>
#include <iostream>

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

	//adaug list si sub 2 butoane de sort
	//QWidget* widgetMoviesList = new QWidget;
	QHBoxLayout* layoutMoviesList = new QHBoxLayout;
	//widgetMoviesList->setLayout(layoutMoviesList);
	__moviesListWidget = new QListWidget;
	__moviesListWidget->setLayout(layoutMoviesList);
	//layoutMoviesList->addWidget(__moviesListWidget);

	QWidget* widgetMovieListOperations = new QWidget;
	QGridLayout* layoutMoviesListOperations = new QGridLayout;
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
	__titleLineEdit = new QLineEdit;
	formLayoutDetalisMovie->addRow(new QLabel("Title:"), __titleLineEdit);
	__genLineEdit = new QLineEdit;
	formLayoutDetalisMovie->addRow(new QLabel("Gen:"), __genLineEdit);
	__releaseYearLineEdit = new QLineEdit;
	formLayoutDetalisMovie->addRow(new QLabel("Release year:"), __releaseYearLineEdit);
	__mainActorLineEdit = new QLineEdit;
	formLayoutDetalisMovie->addRow(new QLabel("Main actor"), __mainActorLineEdit);
	__addButton = new QPushButton("Add film");
	formLayoutDetalisMovie->addWidget(__addButton);

	QWidget* widgetSearch = new QWidget;
	QFormLayout* formLayoutSearch = new QFormLayout;
	widgetSearch->setLayout(formLayoutSearch);
	__searchLineEdit = new QLineEdit;
	formLayoutSearch->addRow(new QLabel("Search by title"), __searchLineEdit);
	__searchButton = new QPushButton("Search");
	formLayoutSearch->addWidget(__searchButton);

	QWidget* widgetQuit = new QWidget;
	QHBoxLayout* layoutQuit = new QHBoxLayout;
	widgetQuit->setLayout(layoutQuit);
	__quitButton = new QPushButton("Quit");
	layoutQuit->addWidget(__quitButton);

	__logListWidget = new QListWidget;
	QHBoxLayout* layoutLogList = new QHBoxLayout;
	__logListWidget->setLayout(layoutLogList);


	layoutMain->addWidget(__moviesListWidget, 0, 0);
	layoutMain->addWidget(widgetMovieListOperations, 0, 1);
	layoutMain->addWidget(widgetSearch, 1, 0);
	layoutMain->addWidget(widgetDetailsMovie, 2, 0);
	layoutMain->addWidget(__logListWidget, 1, 1, 2, 2);
	layoutMain->addWidget(widgetQuit, 4, 2);
}

void App::__connectSignalsSlots() {
	//cand se emite semnalul clicked de pe buton reincarc list
	QObject::connect(__sortByTitleButton, &QPushButton::clicked, this, [&]() {
		__reloadList(__ctrl.getSortedByTitleAsc());
	});
	QObject::connect(__sortByActorButton, &QPushButton::clicked, this, [&]() {
		__reloadList(__ctrl.getSortedByMainActorAsc());
	});
	QObject::connect(__moviesListWidget, &QListWidget::itemSelectionChanged, this, &App::__on_selectMovieFromList);
	QObject::connect(__addButton, &QPushButton::clicked, this, &App::__on_addButton_clicked);
	QObject::connect(__deleteButton, &QPushButton::clicked, this, &App::__on_deleteButton_clicked);
	QObject::connect(__searchButton, &QPushButton::clicked, this, &App::__on_searchButton_clicked);
	QObject::connect(__quitButton, &QPushButton::clicked, this, &App::__on_quitButton_clicked);
}

void App::__refreshList() {
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
	__moviesListWidget->clear();
	for (const auto& film : films) {
		QString title{ film.getTitle().c_str() };
		QString gen{ film.getGen().c_str() };
		QString releaseYear{ std::to_string(film.getReleaseYear()).c_str() };
		QString mainActor{ film.getMainActor().c_str() };
		__moviesListWidget->addItem(title + " | " + gen + " | " + releaseYear + " | " + mainActor);
	}
}

void App::__inLineDetalisEdit(const std::string& title, const std::string& gen, const std::string& releaseYear, const std::string& mainActor) {
	__titleLineEdit->setText(title.c_str());
	__genLineEdit->setText(gen.c_str());
	__releaseYearLineEdit->setText(releaseYear.c_str());
	__mainActorLineEdit->setText(mainActor.c_str());
}

void App::__on_selectMovieFromList() {
	if (__moviesListWidget->selectedItems().isEmpty()) {
		//nu este nimic selectat, golesc campurile
		__inLineDetalisEdit("", "", "", "");
		return;
	}
	QListWidgetItem* selectedItem = __moviesListWidget->selectedItems().at(0);
	QString movieString = selectedItem->text();
	std::string title = movieString.split(' ', QString::KeepEmptyParts)[0].toStdString();
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
	auto selectedFilms = __moviesListWidget->selectedItems();
	QListWidgetItem* item;
	if (selectedFilms.empty()) {
		__displayError("You have not selected any movie yet");
		return;
	}
	else {
		item = selectedFilms.at(0);
	}
	std::string title = item->text().split(' ', QString::KeepEmptyParts)[0].toStdString();
	try {
		__ctrl.del(title);
	}
	catch (FilmException& ex) {
		errors += ex.getMsg() + "\n";
	}
	__refreshList();

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
		__refreshList();
	}
	catch (FilmException& ex) {
		__displayError(ex.getMsg());
	}
}

void App::__on_quitButton_clicked() {
	qApp->quit();
}

App::~App()
{

}
