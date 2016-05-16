#pragma once
#include <QAbstractTableModel>
#include "../domain/Film.h"
#include <vector>
#include <qdebug.h>

class MoviesTableModel : public QAbstractTableModel {
private:
	std::vector<Film> __movies;
public:
	MoviesTableModel(std::vector<Film> movies) : __movies{ movies } {}

	void setMovies(const std::vector<Film>& movies) {
		this->__movies.clear();
		std::copy(movies.begin(), movies.end(), std::back_inserter(this->__movies));
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return __movies.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole || role == Qt::EditRole) {
			Film film = __movies[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(film.getTitle());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(film.getGen());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(std::to_string(film.getReleaseYear()));
			}
			else if (index.column() == 3) {
				return QString::fromStdString(film.getMainActor());
			}
		}
		return QVariant();
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
		if (role == Qt::DisplayRole) {
			if (orientation == Qt::Horizontal) {
				switch (section) {
				case 0: return QString("Title");
				case 1: return QString("Gen");
				case 2: return QString("Release Year");
				case 3: return QString("Main Actor");
				default: return QVariant();
				}
			}
			else if (orientation == Qt::Vertical) {
				return section;
			}

		}
		return QVariant();
	}

	/*
	Qt::ItemFlags flags(const QModelIndex &index) const override {
		if (index.isValid() == false || index.column() == 0) {
			return Qt::ItemIsEnabled;
		}
		return QAbstractItemModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsSelectable;
	}

	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override {
		if (index.isValid() && role == Qt::EditRole) {
			int row = index.row();
			int col = index.column();
			std::string title = index.sibling(row, 0).data().toString().toStdString();
			auto filmIt = std::find_if(__movies.begin(), __movies.end(), [&](const Film& film) {
				return film.getTitle() == title;
			});
			if (filmIt == __movies.end()) {
				return false;
			}
			switch (col) {
			case 1: {
				std::string gen = value.toString().toStdString();
				filmIt->setGen(gen);
				break;
			}
			case 2: {
				int releaseYear = value.toString().toInt();
				filmIt->setReleaseYear(releaseYear);
				break;
			}
			case 3: {
				std::string mainActor = value.toString().toStdString();
				filmIt->setMainActor(mainActor);
				break;
			}
			default: return false;
			}
			emit dataChanged(index, index);
			return true;
		}
		return false;
	}
	*/
};