#include "MovieCollection.cpp"

int main()
{
    MovieCollection movieslist;

    while(true)
    {

        cout<<"1. Search profile of an actor" <<endl;
        cout<<"2. Search co-actors of an actor" <<endl;
        cout<<"3. Search unique co-actors and print them" <<endl;
        cout<<"4. Print choice movieList2 of all co-actors of the co-actor of an actor" <<endl;
        cout<<"5. Checks whether A and B are co-actors" <<endl;
        cout<<"6. Search director" <<endl;
        cout<<"7. Directors who have directed movies of choice certain genre" <<endl;
        cout<<"8. Search choice movie" <<endl;
        cout<<"9. Search movies released in choice given year" <<endl;
        cout<<"10. Print movies year-wise (both increasing & decreasing order)" <<endl;
        cout<<"11. Search movies based on genre" <<endl;
        cout<<"12. Print movies rating-wise" <<endl;
        cout<<"13. Print movies of choice certain genre rating-wise" <<endl;
        cout<<endl<<"Please select an option: ";
        int choice=1;
        string input="";
        string input1="";

        cin >> choice;
        switch(choice)
        {
            case 1:
                cout<<endl<<"Input Actor Name: ";
                cin.ignore();
                getline(cin, input);
                movieslist.getActorProfile(input);
                break;
            case 2:
                cout<<endl<<"Input Actor Name: ";
                cin.ignore();
                getline(cin, input);
                movieslist.printCoActorsOfActor(input);
                break;
            case 3:
                cout<<endl<<"Input Actor Name: ";
                cin.ignore();
                getline(cin, input);
                movieslist.printUniqueCoActors(input);
                break;
            case 4:
                cout<<endl<<"Inout Actor Name: ";
                cin.ignore();
                getline(cin, input);
                movieslist.printCoActorsofCoActorsofActor(input);
                break;
            case 5:
                cout<<endl<<"Input Actor Names.";
                cin.ignore();
                cout<<endl<<"1st Actor: ";
                getline(cin, input);
                cout<<endl<<"2nd Actor: ";
                getline(cin, input1);
                if(movieslist.checkCoActors(input, input1))
                    cout<<input<<" and "<<input1<<" are co-actors."<<endl;
                else
                    cout<<input<<" and "<<input1<<" are not co-actors."<<endl;
                break;
            case 6:
                cout<<endl<<"Input director name: ";
                cin.ignore();
                getline(cin, input);
                movieslist.moviesByDirector(input);
                break;
            case 7:
                cout<<endl<<"Input genre: ";
                cin.ignore();
                getline(cin, input);
                movieslist.getDirectorsOfGenre(input);
                break;
            case 8:
                cout<<endl<<"Input movie name: ";
                cin.ignore();
                getline(cin, input);
                movieslist.SearchMovie(input);
                break;
            case 9:
                cout<<endl<<"Input year: ";
                int year;
                cin >> year;
                movieslist.moviesReleasedInYear(year);
                break;
            case 10:
                cout<<endl<<"List of movies in ascending order"<<endl;
                movieslist.moviesListByYearAscending();
                cout<<endl<<"List of movies in descending order"<<endl;
                movieslist.moviesListByYearDescending();
                break;
            case 11:
                cout<<endl<<"Input genre: ";
                cin.ignore();
                getline(cin, input);
                movieslist.moviesListByGenre(input);
                break;
            case 12:
                cout<<endl<<"List of movies from highest to lowest rating: "<<endl;
                movieslist.moviesListByRatingDescending();
                break;
            case 13:
                cout<<endl<<"Input genre: ";
                cin.ignore();
                getline(cin, input);
                movieslist.moviesListByGenre(input);
                break;
        }
      system("pause");
    }

    // task 1
    // movieslist.getActorProfile("Wes Studi");
    // task 2
    // movieslist.printCoActorsOfActor("Wes Studi");
    // task 3
    // movieslist.printUniqueCoActors("Wes Studi");
    // task 4
    // movieslist.printCoActorsofCoActorsofActor("Wes Studi");
    // task 5
    // string actorA = "Wes Studi";
    // string actorB = "Christian Bale";
    // if(movieslist.checkCoActors(actorA, actorB))
    //     cout<<actorA<<" and "<<actorB<<" are co-actors."<<endl;
    // else
    //     cout<<actorA<<" and "<<actorB<<" are not co-actors."<<endl;
    // task 6
    // movieslist.moviesByDirector("James Cameron");
    // task 7
    // movieslist.getDirectorsOfGenre("Action");
    // task 8
    // movieslist.SearchMovie("X-Men");
    // task 9
    // movieslist.moviesReleasedInYear(2006);
    // movieslist.moviesReleasedInYear(2005);
    // task 10 a
    // movieslist.moviesListByYearAscending();
    // task 10 b
    // movieslist.moviesListByYearDescending();
    // task 11
    // movieslist.moviesListByGenre("Action");
    // task 12
    // movieslist.moviesListByRatingDescending();
    // task 13
    // same as task 11
    return 0;
}