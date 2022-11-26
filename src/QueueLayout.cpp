#include <QueueLayout.h>
#include <iostream>
#include "SongQueueItemWidget.h"

QueueLayout::QueueLayout(QWidget *parent)
    : QVBoxLayout(parent)
{

}

void QueueLayout::addSong(const std::shared_ptr<Song>& song, bool noSignal)
{
    addWidget(new SongQueueItemWidget(song, this->parentWidget()));
    std::cout << "Added song " << song->getName().toStdString() << " to queue, " << count() << "songs in queue" << std::endl;
    connect(dynamic_cast<SongQueueItemWidget*>(itemAt(count() - 1)->widget())->getRemoveButton().get(), &QPushButton::clicked, this, &QueueLayout::removeSong);
    update();
    if(!noSignal){
        updatedSignal();
    }
}

void QueueLayout::removeSong()
{
    removeWidget(dynamic_cast<QPushButton*>(sender())->parentWidget());
    dynamic_cast<QPushButton*>(sender())->parentWidget()->deleteLater();
    update();
    updatedSignal();
}

int32_t QueueLayout::count() const {
    return QBoxLayout::count();
}

std::shared_ptr<Song> QueueLayout::getNextSong() {
    std::shared_ptr<Song> song = dynamic_cast<SongQueueItemWidget*>(itemAt(0)->widget())->getSong();
    QBoxLayout::takeAt(0)->widget()->deleteLater();
    update();
    updatedSignal();
    return song;
}

