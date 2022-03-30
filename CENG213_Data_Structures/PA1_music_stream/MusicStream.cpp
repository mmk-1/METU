#include "MusicStream.h"

#include <iostream>

void MusicStream::addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan)
{
    /* TODO */
    Profile newProfile(email, username, plan);
    this->profiles.insertAtTheEnd(newProfile);
}

void MusicStream::deleteProfile(const std::string &email)
{
    /* TODO */
    Node<Profile> *currProfile = this->profiles.getFirstNode();
    // get profile to be deleted
    while (currProfile->data.getEmail() != email)
    {
        currProfile = currProfile->next;
    }
    // delete from followers list of followings
    LinkedList<Profile *> followerList = currProfile->data.getFollowers();
    if (!followerList.isEmpty())
    {
        Node<Profile *> *follower = followerList.getFirstNode();
        follower->data->unfollowProfile(&(currProfile->data));
        follower = follower->next;
        while (follower != followerList.getFirstNode())
        {
            follower->data->unfollowProfile(&(currProfile->data));
            follower = follower->next;
        }
    }
    // delete from followings list of followers
    LinkedList<Profile *> followingList = currProfile->data.getFollowings();
    if (!followingList.isEmpty())
    {
        Node<Profile *> *following = followingList.getFirstNode();
        currProfile->data.unfollowProfile(following->data);
        following = following->next;
        while (following != followingList.getFirstNode())
        {
            currProfile->data.unfollowProfile(following->data);
            following = following->next;
        }
    }

    // deleting data
    currProfile->data.getFollowers().removeAllNodes();
    currProfile->data.getFollowings().removeAllNodes();
    currProfile->data.getPlaylists().removeAllNodes();
    this->profiles.removeNode(currProfile);
}

void MusicStream::addArtist(const std::string &artistName)
{
    /* TODO */
    Artist newArtist(artistName);
    this->artists.insertAtTheEnd(newArtist);
}

void MusicStream::addAlbum(const std::string &albumName, int artistId)
{
    /* TODO */
    Album newAlbum(albumName);
    // add to albums of musicstream
    this->albums.insertAtTheEnd(newAlbum);
    // add to artist id's album list
    Node<Artist> *currArtist = this->artists.getFirstNode();
    while(currArtist->data.getArtistId() != artistId){
        currArtist=currArtist->next;
    }
    
    currArtist->data.addAlbum(&(this->albums.getNode(newAlbum)->data));
}

void MusicStream::addSong(const std::string &songName, int songDuration, int albumId)
{
    /* TODO */
    Song newSong(songName, songDuration);
    this->songs.insertAtTheEnd(newSong);
    // add to album id's song list
    Node<Album> *currAlbum = this->albums.getFirstNode();
    while (currAlbum->data.getAlbumId() != albumId)
    {
        currAlbum = currAlbum->next;
    }
    currAlbum->data.addSong(&(this->songs.getNode(newSong)->data));
}

void MusicStream::followProfile(const std::string &email1, const std::string &email2)
{
    /* TODO */
    Node<Profile> * currProfile1 = this->profiles.getFirstNode();
    Node<Profile> * currProfile2 = this->profiles.getFirstNode();
    while(currProfile1->data.getEmail() != email1){
        currProfile1=currProfile1->next;
    }
    while(currProfile2->data.getEmail() != email2){
        currProfile2=currProfile2->next;
    }
    currProfile1->data.followProfile(&(currProfile2->data));
}

void MusicStream::unfollowProfile(const std::string &email1, const std::string &email2)
{
    /* TODO */
    Node<Profile> * currProfile1 = this->profiles.getFirstNode();
    Node<Profile> * currProfile2 = this->profiles.getFirstNode();
    while(currProfile1->data.getEmail() != email1){
        currProfile1=currProfile1->next;
    }
    while(currProfile2->data.getEmail() != email2){
        currProfile2=currProfile2->next;
    }
    currProfile1->data.unfollowProfile(&(currProfile2->data));

}

void MusicStream::createPlaylist(const std::string &email, const std::string &playlistName)
{
    /* TODO */
    Node<Profile> * currProfile = this->profiles.getFirstNode();
    while(currProfile->data.getEmail() != email){
        currProfile=currProfile->next;
    }
    currProfile->data.createPlaylist(playlistName);
}

void MusicStream::deletePlaylist(const std::string &email, int playlistId)
{
    /* TODO */
    Node<Profile> * currProfile = this->profiles.getFirstNode();
    while(currProfile->data.getEmail() != email){
        currProfile=currProfile->next;
    }
    currProfile->data.deletePlaylist(playlistId);
}

void MusicStream::addSongToPlaylist(const std::string &email, int songId, int playlistId)
{
    /* TODO */
    Node<Profile> * currProfile = this->profiles.getFirstNode();
    while(currProfile->data.getEmail() != email){
        currProfile=currProfile->next;
    }
    Node<Song> * currSong = this->songs.getFirstNode();
    while(currSong->data.getSongId() != songId){
        currSong=currSong->next;
    }
    // Song * newSong = &(currSong->data);
    currProfile->data.addSongToPlaylist(&(currSong->data), playlistId);
}

void MusicStream::deleteSongFromPlaylist(const std::string &email, int songId, int playlistId)
{
    /* TODO */
    Node<Profile> * currProfile = this->profiles.getFirstNode();
    while(currProfile->data.getEmail() != email){
        currProfile=currProfile->next;
    }
    Node<Song *> * songNode = currProfile->data.getPlaylist(playlistId)->getSongs().getFirstNode();
    while(songNode->data->getSongId() != songId){
        songNode=songNode->next;
    }
    currProfile->data.getPlaylist(playlistId)->dropSong(songNode->data);
}

LinkedList<Song *> MusicStream::playPlaylist(const std::string &email, Playlist *playlist)
{
    /* TODO */
    Node<Profile> * currProfile = this->profiles.getFirstNode();
    while(currProfile->data.getEmail() != email){
        currProfile=currProfile->next;
    }

    Profile user = currProfile->data;
    if(user.getPlan() == premium){
        return playlist->getSongs();
    }
    LinkedList<Song *> copyPlaylist = playlist->getSongs();
    copyPlaylist.insertAsEveryKthNode(&Song::ADVERTISEMENT_SONG, 2);

    return copyPlaylist;
}

Playlist *MusicStream::getPlaylist(const std::string &email, int playlistId)
{
    /* TODO */
    Node<Profile> * currProfile = this->profiles.getFirstNode();
    while(currProfile->data.getEmail() != email){
        currProfile=currProfile->next;
    }
    return currProfile->data.getPlaylist(playlistId);
}

LinkedList<Playlist *> MusicStream::getSharedPlaylists(const std::string &email)
{
    /* TODO */
    Node<Profile> * currProfile = this->profiles.getFirstNode();
    while(currProfile->data.getEmail() != email){
        currProfile=currProfile->next;
    }
    return currProfile->data.getSharedPlaylists();
}

void MusicStream::shufflePlaylist(const std::string &email, int playlistId, int seed)
{
    /* TODO */
    this->getPlaylist(email, playlistId)->shuffle(seed);
}

void MusicStream::sharePlaylist(const std::string &email, int playlistId)
{
    /* TODO */
    this->getPlaylist(email, playlistId)->setShared(true);
}

void MusicStream::unsharePlaylist(const std::string &email, int playlistId)
{
    /* TODO */
    this->getPlaylist(email, playlistId)->setShared(false);
}

void MusicStream::subscribePremium(const std::string &email)
{
    /* TODO */
    Node<Profile> * currProfile = this->profiles.getFirstNode();
    while(currProfile->data.getEmail() != email){
        currProfile=currProfile->next;
    }
    currProfile->data.setPlan(premium);
}

void MusicStream::unsubscribePremium(const std::string &email)
{
    /* TODO */
    Node<Profile> * currProfile = this->profiles.getFirstNode();
    while(currProfile->data.getEmail() != email){
        currProfile=currProfile->next;
    }
    currProfile->data.setPlan(free_of_charge);
}

void MusicStream::print() const
{
    std::cout << "# Printing the music stream ..." << std::endl;

    std::cout << "# Number of profiles is " << profiles.getSize() << ":" << std::endl;
    profiles.print();

    std::cout << "# Number of artists is " << artists.getSize() << ":" << std::endl;
    artists.print();

    std::cout << "# Number of albums is " << albums.getSize() << ":" << std::endl;
    albums.print();

    std::cout << "# Number of songs is " << songs.getSize() << ":" << std::endl;
    songs.print();

    std::cout << "# Printing is done." << std::endl;
}
