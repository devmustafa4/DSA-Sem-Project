#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include "movieTrie.cpp"
#include <set>
#include <stack>
#include "trie.cpp"
using namespace std;

// Container for all movies
class MovieCollection
{
    private:
        // data
        OptimizedMovieTrie movies;
        map<string, list<Movie*>> movieDirectors; // stores the references to all directors of the movies
        map<int, list<Movie*>> moviesYearIndex; // stores the references to all movies year wise
        map<float, list<Movie*>> moviesRatingIndex; // stores the references to all movies rating wise
        map<string, list<Movie*>> moviesByGenre; // stores the references to all movies genre wise
        map<string, list<Movie*>> moviesByActors; // stores the references to all movies actor wise

    public:

    //Contructor
    MovieCollection()
    {
        importData("Data//newdataset.csv");
    }

    void importData(string path)
    {
        ifstream myFile;
        myFile.open(path);

        std::ostringstream out; 
        out << myFile.rdbuf();
        string filestring = out.str();


        // string stringinput = "Hello,,kesy,ho,main,to,theek,hoon,hehhe";
        if(myFile.good())
        {
            string line;
            // split the entire dataset into records
            vector<string> data = split(filestring, '\n');
            
            // for every row
            for (auto row: data)
            {
                // split the record into attributes
                vector<string> record = split(row, ',');
                if (record.size() == 28)
                {
                    if (record.at(0).compare("\"movie_title\"") == 0)
                    {
                        continue;
                    }


                    // create a movie node with the values
                    Movie* movieptr = new Movie(record.at(0), record.at(1), record.at(2), record.at(3), record.at(4), record.at(5),
                            record.at(6), record.at(7), record.at(8), record.at(9), record.at(10), record.at(11),
                            record.at(12), record.at(13), record.at(14), record.at(15), record.at(16), record.at(17),
                            record.at(18), record.at(19), record.at(20), record.at(21), record.at(22), record.at(23),
                            record.at(24), record.at(25), record.at(26), record.at(27));

                    // maintaining the trie of movies
                    movies.insert(removeQuotes(record.at(0)), *movieptr);

                    // pushing the list of actors to every actor's profile
                    moviesByActors[movieptr->actors[0]].push_back(movieptr);
                    moviesByActors[movieptr->actors[1]].push_back(movieptr);
                    moviesByActors[movieptr->actors[2]].push_back(movieptr);
                    

                    // maintaing the trie of directors
                    movieDirectors[removeQuotes(movieptr->director_name)].push_back(movieptr);

                    // add the movie to its linked lists and hash maps
                    // maintaining year index list
                    moviesYearIndex[movieptr->getYear()].push_back(movieptr);
                    // maintaing year index list for ratings
                    moviesRatingIndex[movieptr->getRating()].push_back(movieptr);
                    // maintaining genre indexes
                    for (auto genre: movieptr->getGenre())
                    {
                        moviesByGenre[removeQuotes(genre)].push_back(movieptr);
                    }

                }
            }

        }
    }
    // searches a movie in the loaded data and prints the information.
    void SearchMovie(string movieName)
    {
        movies.printChildren(movieName);
    }

    // prints the movies released in a year
    void moviesReleasedInYear(int releaseYear)
    {
        for (auto movie: moviesYearIndex[releaseYear])
        {
            movie->print();
        }
    }

    // prints all the stored movies sorted by year in ascending order
    void moviesListByYearAscending()
    {
        for (auto key_value: moviesYearIndex)
        {
            moviesReleasedInYear(key_value.first);
        }
    }

    // prints all the stored movies sorted by year in descending order
    void moviesListByYearDescending()
    {
        stack<int> stackYear;
        for (auto key_value:moviesYearIndex)
        {
            stackYear.push(key_value.first);  
        }

        while (!stackYear.empty())
        {
            moviesReleasedInYear(stackYear.top());
            stackYear.pop();
        }
    }

    
    // prints the movies released in a year
    void moviesWithRating(float rating)
    {
        for (auto movie: moviesRatingIndex[rating])
        {
            movie->print();
        }
    }

    // prints all the stored movies sorted by rating
    void moviesListByRatingDescending()
    {
        stack<float> stackRating;
        for (auto key_value:moviesRatingIndex)
        {
            stackRating.push(key_value.first);  
        }

        while (!stackRating.empty())
        {
            moviesWithRating(stackRating.top());
            stackRating.pop();
        }
    }
    // lists all movies in the given genre
    void moviesListByGenre(string genre)
    {
        for (auto movie : moviesByGenre[genre])
        {
            movie->print();
        }
    }
    // prints the  names of all movies directed by director
    void moviesByDirector(string director)
    {
        for (auto movie: movieDirectors[director])
        {
            cout<<"\t"<<movie->movie_title<<endl;
        }
    }

    // prints all directors who have directed movies of a genre
    void getDirectorsOfGenre(string action)
    {
        set<string> directors;
        for (auto movie: moviesByGenre[action])
        {
            directors.insert(movie->director_name);
        }
        
        for (auto director: directors)
        {
            cout<<director<<endl;
        }
    }

    // prints the profile of an actor
    void getActorProfile(string actor)
    {
        // display the actors info if he exists in the list
        if (moviesByActors.find(actor) == moviesByActors.end())
        {
            cout<<"Actor does not exists"<<endl;
        }
        else
        {
                cout<<"\n"<<actor<<" acted in acted in  "<<moviesByActors[actor].size()<<" movies"<<endl;
                cout<<"Title of Movies: "<<endl;
                for (auto movie: moviesByActors[actor])
                {
                    cout<<"\t"<<movie->movie_title<<movie->title_year<<"\n";
                }
        }
    }

    // searches and prints the co actors of the actor with movie titles
    void printCoActorsOfActor(string actor)
    {
        // display the actors info if he exists in the list
        if (moviesByActors.find(actor) == moviesByActors.end())
        {
            cout<<"Actor does not exists"<<endl;
        }
        else
        {
                cout<<"\n"<<actor<<": "<<endl;
                for (auto movie: moviesByActors[actor])
                {
                    cout<<"\t"<<movie->movie_title<<movie->title_year<<"\n";
                    cout<<"\t\tCo-Actors:"<<endl<<"\t";
                    for (auto i : movie->actors)
                    {
                        if (i.compare(actor) != 0) // if the actor is not equal to 0 then print it
                            cout<<"\t"<<i;
                    }
                    cout<<endl;
                }
        }
    }

    void printUniqueCoActors(string actor)
    {
        set<string> co_actors;
        // display the actors info if he exists in the list
        if (moviesByActors.find(actor) == moviesByActors.end())
        {
            cout<<"Actor does not exists"<<endl;
        }
        else
        {      
            cout<<"The unique co actors of "<<actor<<" are:"<<endl;
            // save all actors name in a set 
            for (auto movie :moviesByActors[actor])
            {
                for (auto movieActor: movie->actors)
                {
                    if (movieActor.compare(actor) != 0) // if the actor is not equal to movieactor then print it
                        co_actors.insert(movieActor);
                }
            }
            // print all names in the set
            for (auto coactor: co_actors)
            {
                cout<<"\t"<<coactor<<endl;
            }
        }
    }

    // prints all the co actors of co actors of the actor
    void printCoActorsofCoActorsofActor(string actor)
    {
        // display the actors info if he exists in the list
        if (moviesByActors.find(actor) == moviesByActors.end())
        {
            cout<<"Actor does not exists"<<endl;
        }
        else
        {      
            cout<<"The unique co actors of co actors of  "<<actor<<" are:"<<endl;
            // save all actors name in a set 
            for (auto movie :moviesByActors[actor])
            {
                for (auto movieActor: movie->actors)
                {
                    // if the actor is not equal to movieactor then print it
                    if (movieActor.compare(actor) != 0) 
                        printUniqueCoActors(movieActor);
                }
            }
        }
    }

    // returns true if the actors are co actors
    bool checkCoActors(string actorA, string actorB)
    {
        // display the actors info if he exists in the list
        if (moviesByActors.find(actorA) == moviesByActors.end())
        {
            cout<<"Actor does not exists"<<endl;
        }
        else
        {
            // save all actors name in a set 
            for (auto movie :moviesByActors[actorA])
            {
                for (auto movieActor: movie->actors)
                {
                    // if the actor is not equal to movieactor then print it
                    if (movieActor.compare(actorB) != 0) 
                        return true;
                }
            }
        }
        return false;
    }
};
