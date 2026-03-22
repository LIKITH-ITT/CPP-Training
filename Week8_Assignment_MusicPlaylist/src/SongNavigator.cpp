#include "SongNavigator.h"

SongNavigator::SongNavigator() : playlist_(NULL), currentIndex_(-1)
{}

ErrorCode SongNavigator::setPlaylist(const Playlist* playlist)
{
    if (playlist == NULL)
    {
        return ErrorCode::INVALID_INPUT;
    }
    playlist_ = playlist;
    currentIndex_ = playlist_->isEmpty() ? -1 : 0;
    return ErrorCode::SUCCESS;
}

Song SongNavigator::next()
{
    if (playlist_ == NULL || playlist_->isEmpty())
    {
        return Song();
    }
    currentIndex_ = (currentIndex_ + 1) % static_cast<int>(playlist_->size());
    return playlist_->getSong(currentIndex_);
}

Song SongNavigator::prev()
{
    if (playlist_ == NULL || playlist_->isEmpty())
    {
        return Song();
    }
    currentIndex_ = (currentIndex_ - 1 + playlist_->size()) % playlist_->size();
    return playlist_->getSong(currentIndex_);
}

Song SongNavigator::current() const
{
    if (playlist_ == NULL || currentIndex_ < 0)
    {
        return Song();
    }
    return playlist_->getSong(currentIndex_);
}

bool SongNavigator::hasCurrentSong() const
{
    return playlist_ != NULL && !playlist_->isEmpty() && currentIndex_ >= 0;
}

ErrorCode SongNavigator::reset()
{
    if (playlist_ == NULL)
    {
        return ErrorCode::INVALID_INPUT;
    }
    currentIndex_ = playlist_->isEmpty() ? -1 : 0;
    return ErrorCode::SUCCESS;
}

int SongNavigator::getCurrentIndex() const
{
    return currentIndex_;
}
