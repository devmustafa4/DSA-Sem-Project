#include <iostream>
#include <list>
using namespace std;


// a class to store the data of a movie
class Movie
{
    public:
        string movie_title;
        list<string> genres;
        int title_year;	
        float imdb_score;	
        string director_name;
        int director_facebook_likes;	
        int num_critic_for_reviews;
        int duration;
        string actors[3];
        int actors_facebook_likes[3];
        int gross;	
        int num_voted_users;	
        int cast_total_facebook_likes;	
        int facenumber_in_poster;
        list<string> plot_keywords;
        string movie_imdb_link;	
        int num_user_for_reviews;
        string language;
        string country;
        string content_rating;
        double budget;
        float aspect_ratio;
        int movie_facebook_likes;
        string color;

};
