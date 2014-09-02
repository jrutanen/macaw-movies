/* Copyright (C) 2014 Movie-Project
 * (Olivier CHURLAUD, Sébastien TOUZÉ)
 *
 * This file is part of Movie-Project.
 *
 * Movie-Project is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Movie-Project is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Movie-Project.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PEOPLE_H
#define PEOPLE_H

#include <QtWidgets>

class People
{
public:
    People();
    int getId() { return m_id; }
    void setId(int id) { m_id = id; }
    QString getLastname() { return m_lastname; }
    void setLastname(QString lastname) { m_lastname = lastname; }
    QString getFirstname() { return m_firstname; }
    void setFirstname(QString firstname) { m_firstname = firstname; }
    QString getRealname() { return m_realname; }
    void setRealname(QString realname) { m_realname = realname; }
    int getBirthday() { return m_birthday; }
    void setBirthday(int birthday) { m_birthday = birthday; }
    QString getBiography() { return m_biography; }
    void setBiography(QString biography) { m_biography = biography; }

private:
    int m_id;
    QString m_lastname;
    QString m_firstname;
    QString m_realname;
    int m_birthday;
    QString m_biography;
};

#endif // PEOPLE_H