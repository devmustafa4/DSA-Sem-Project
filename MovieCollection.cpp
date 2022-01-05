#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include "movieTrie.cpp"

// Container for all movies
class MovieCollection
{
    public:
    OptimizedTrie movies;
    //Contructor
    MovieCollection()
    {
        importData("Data//test_data.csv");
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
                if (record.size() != 28)
                    cout<<"Invalid record found ignoring"<<endl;
                else
                {
                    if (record.at(0).compare("\"movie_title\"") == 0)
                    {
                        continue;
                    }
                    Movie movie(record.at(0), record.at(1), record.at(2), record.at(3), record.at(4), record.at(5),
                            record.at(6), record.at(7), record.at(8), record.at(9), record.at(10), record.at(11),
                            record.at(12), record.at(13), record.at(14), record.at(15), record.at(16), record.at(17),
                            record.at(18), record.at(19), record.at(20), record.at(21), record.at(22), record.at(23),
                            record.at(24), record.at(25), record.at(26), record.at(27));
                    movies.insert(removeQuotes(record.at(0)), movie);

                    // add the movie to its linked lists and hash maps
                }
            }

        }
    }
    // searches a movie in the loaded data and prints the information.
    void SearchMovie(string movieName)
    {
        movies.printChildren(movieName);
    }
};


int main()
{
    MovieCollection movieslist;
    movieslist.movies.printChildren("Brave");
    return 0;
}