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

#include "Application.h"

/**
 * @brief Constructor
 */
Application::Application(int &argc, char **argv) :
    QApplication(argc, argv)
{
    Macaw::DEBUG("[Application] started");

    DatabaseManager *databaseManager = DatabaseManager::instance();

    this->setApplicationName(APP_NAME);
    this->setApplicationVersion(APP_VERSION);
    this->setWindowIcon(QIcon(":/img/logov0_1.png"));
    m_tmdbkey = "6e4cbac7861ad5b847ef8f60489dc04e";
    m_mainWindow = new MainWindow;
    m_fetchMetadata = NULL;
    m_fetchMetadataDialog = NULL;

    connect(databaseManager, SIGNAL(orphanTagDetected(Tag&)),
            this, SLOT(askForOrphanTagDeletion(Tag&)));
    connect(databaseManager, SIGNAL(orphanPeopleDetected(People&)),
            this, SLOT(askForOrphanPeopleDeletion(People&)));
    connect(m_mainWindow, SIGNAL(startFetchingMetadata()),
            this, SLOT(on_startFetchingMetadata()));

    m_mainWindow->show();

    Macaw::DEBUG("[Application] Application initialized");
}

/**
 * @brief Destructor
 */
Application::~Application()
{
    Macaw::DEBUG("[Application] Destructed");
}

/**
 * @brief Slot triggered when DatabaseManager finds an orphan tag.
 * A QMessageBox asks the user if the tag should be delete or not.
 *
 * @param orphanTag concerned by the choice
 */
void Application::askForOrphanTagDeletion(Tag &orphanTag)
{
    DatabaseManager *databaseManager = DatabaseManager::instance();

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText("The tag <b>"+ orphanTag.name() +"</b> is not used in any movie now. ");
    msgBox.setInformativeText("Do you want to delete this tag?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec() == QMessageBox::Yes) {
        databaseManager->deleteTag(orphanTag);
    }
}

/**
 * @brief Slot triggered when DatabaseManager finds an orphan person.
 * A QMessageBox asks the user if the person should be delete or not.
 *
 * @param orphanPeople concerned by the choice
 */
void Application::askForOrphanPeopleDeletion(People &orphanPeople)
{
    DatabaseManager *databaseManager = DatabaseManager::instance();

    QString l_name = orphanPeople.name();

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText("The person <b>" +l_name+ "</b> is not linked to any movie now.");
    msgBox.setInformativeText("Do you want to delete it?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec() == QMessageBox::Yes) {
        databaseManager->deletePeople(orphanPeople);
    }
}

void Application::on_startFetchingMetadata()
{
    Macaw::DEBUG("[Application] startFetchingMetadata called");
    if(m_fetchMetadata == NULL) {
        m_fetchMetadata = new FetchMetadata;
    }

    //m_fetchMetadata->moveToThread(&m_metadataThread);
    //connect(&m_metadataThread, SIGNAL(finished()),
    //        m_fetchMetadata, SLOT(deleteLater()));
    connect(this, SIGNAL(fetchMetadata()),
            m_fetchMetadata, SLOT(startProcess()));
    connect(m_fetchMetadata, SIGNAL(sendFetchMetadataDialog(Movie&, QList<Movie>)),
            this, SLOT(on_sendFetchMetadataDialog(Movie&,QList<Movie>)));
    //     connect(l_fetchMetadata, SIGNAL(&FetchMetadata::resultReady),
     //           this, SLOT(&Controller::handleResults));
    //m_metadataThread.start();
    emit fetchMetadata();
}

void Application::on_sendFetchMetadataDialog(Movie& movie,QList<Movie> accurateList)
{
    Macaw::DEBUG("[Application] on_sendFetchMetadataDialog triggered");

    if(m_fetchMetadataDialog != NULL)
    {
        delete m_fetchMetadataDialog;
    }
    m_fetchMetadataDialog = new FetchMetadataDialog(movie, accurateList);
    connect(m_fetchMetadataDialog, SIGNAL(selectedMovie(Movie)),
            m_fetchMetadata, SLOT(on_selectedMovie(Movie)));
    connect(m_fetchMetadataDialog, SIGNAL(searchMovies(QString)),
            m_fetchMetadata, SLOT(on_searchMovies(QString)));
    connect(m_fetchMetadataDialog, SIGNAL(searchCanceled()),
            m_fetchMetadata, SLOT(on_searchCanceled()));
    connect(m_fetchMetadata, SIGNAL(updateFetchMetadataDialog(QList<Movie>)),
            this, SLOT(on_updateFetchMetadataDialog(QList<Movie>)));
    m_fetchMetadataDialog->show();
}

void Application::on_updateFetchMetadataDialog(QList<Movie> updatedList)
{
    m_fetchMetadataDialog->setMovieList(updatedList);

}
