/* Copyright (C) 2014 Macaw-Movies
 * (Olivier CHURLAUD, Sébastien TOUZÉ)
 *
 * This file is part of Macaw-Movies.
 *
 * Macaw-Movies is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Macaw-Movies is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Macaw-Movies.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PEOPLEDIALOG_H
#define PEOPLEDIALOG_H

#include <QDialog>

#include "Application.h"

#include "Entities/People.h"

namespace Ui {
class PeopleDialog;
}

/**
 * @brief Dialog to edit the metadata of a People
 */
class PeopleDialog : public QDialog
{
Q_OBJECT

public:
    explicit PeopleDialog(int = 0, QWidget *parent = 0);
    explicit PeopleDialog(People people, QWidget *parent = 0);
    ~PeopleDialog();
    void setName(const QString name);
    QString getName() const;
    void setBirthday(const QDate birthday);
    QDate getBirthday() const;
    void setBiography(const QString biography);
    QString getBiography() const;

public slots:
    void on_validationButtons_accepted();

signals:
    void peopleCreated(People);

private slots:
    void on_resetBirthdayBtn_clicked();

private:
    Ui::PeopleDialog *m_ui;
    People m_people;
};

#endif // PEOPLEDIALOG_H
