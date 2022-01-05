#include <iostream>
#include <list>
#include <map>

using namespace std;


string removeQuotes(string my_str)
{
    my_str.erase(remove(my_str.begin(), my_str.end(), '"'), my_str.end());
    return my_str;
}

// converts string into integer
int toInt(string str)
{
    return stoi((str == "") ? ("-1") : (str));
}

// converts string into long
long toLong(string str)
{
    return atol((str == "") ? ("-1") : (str.c_str()));
}

// converts string into float
float toFloat(string str)
{
    return stof((str == "") ? ("-1") : (str));
}


// breaks down a string into smaller substrings and returns a vector
vector<string> split(string input, char delimeter)
{
     string S, T;  // declare string variables
    stringstream inputString(input); // X is an object of stringstream that references the S string  
    vector<string> tokens;
    // use while loop to check the getline() function condition  
    while (getline(inputString, T, delimeter)) {  
        /* X represents to read the string from stringstream, T use for store the token string and, 
         ' ' whitespace represents to split the string where whitespace is found. */  
        tokens.push_back(T);
    }  
    return tokens;
}


// a class to store the data of a movie
class Movie
{
    public:
        string movie_title = "";
        vector<string> genre;
        int title_year = 0;	
        float imdb_score =  0;	
        string director_name = "";
        int director_facebook_likes = 0;	
        int num_critic_for_reviews = 0;
        int duration = 0;
        string actors[3] = {"", "", ""};
        int actors_facebook_likes[3] = {0,0,0};
        int gross = 0;	
        int num_voted_users = 0;	
        int cast_total_facebook_likes = 0;	
        int facenumber_in_poster = 0;
        vector<string> plot_keywords;
        string movie_imdb_link = "";	
        int num_user_for_reviews = 0;
        string language = "";
        string country = "";
        string content_rating = "";
        double budget = 0;
        float aspect_ratio = 0;
        int movie_facebook_likes = 0;
        string color = "";

    // default constructor for movie
    Movie()
    {

    }

    Movie(string movie_title, string genre, string title_year, string imdb_score ,	
        string director_name, string director_facebook_likes , string num_critic_for_reviews, 
        string duration, string actor_1, string actors_facebook_like_1, string actor_2, 
        string actors_facebook_like_2, string actor_3, string actors_facebook_like_3,
        string gross, string num_voted_users, string cast_total_facebook_likes, 
        string facenumber_in_poster, string plot_keywords, string movie_imdb_link,
        string num_user_for_reviews, string language, string country,
        string content_rating, string budget, string aspect_ratio,
        string movie_facebook_likes, string color)
    {
        this->movie_title = removeQuotes(movie_title);
        this->genre = split(genre, '|');
        this->title_year = toInt(title_year);	
        this->imdb_score =  toFloat(imdb_score);	
        this->director_name = director_name;
        this->director_facebook_likes = toInt(director_facebook_likes);	
        this->num_critic_for_reviews = toInt(num_critic_for_reviews);
        this->duration = toInt(duration);
        this->actors[0] = actor_1;
        this->actors[1] = actor_2;
        this->actors[2] = actor_3;
        this->actors_facebook_likes[0] = toInt(actors_facebook_like_1);
        this->actors_facebook_likes[1] = toInt(actors_facebook_like_2);
        this->actors_facebook_likes[2] = toInt(actors_facebook_like_3);
        this->gross = toInt(gross);	
        this->num_voted_users = toInt(num_voted_users);	
        this->cast_total_facebook_likes = toInt(cast_total_facebook_likes);	
        this->facenumber_in_poster = toInt(facenumber_in_poster);
        this->plot_keywords = split(plot_keywords, '|');
        this->movie_imdb_link = movie_imdb_link;	
        this->num_user_for_reviews = toInt(num_user_for_reviews);
        this->language = language;
        this->country = country;
        this->content_rating = content_rating;
        this->budget = toInt(budget);
        this->aspect_ratio = toFloat(aspect_ratio);
        this->movie_facebook_likes = toInt(movie_facebook_likes);
        this->color = color;
    }

    void print()
    {
        cout<<"\nMovie Title: "<<this->movie_title<<"\n"
            <<"\tRelease Year: "<<this->title_year<<"\n"
            <<"\tBudget: "<<this->budget<<"\n"
            <<"\tRating: "<<this->content_rating<<"\n"
            <<"\tDuration: "<<this->duration<<"\n"
            <<"\tDirector: "<<this->director_name<<"\n"
            <<"\tActors: \n"<<"\t\t1. "<<this->actors[0]<<"\n"
                          <<"\t\t2. "<<this->actors[1]<<"\n"
                          <<"\t\t3. "<<this->actors[2]<<"\n"<<endl;
    }
};


class OptimizedTrie 
{
    class Node 
    {
        public:
            string identifier;
            Movie* data;
            map<char, Node*> children;
    };

    Node* root = NULL;

    public:

    OptimizedTrie()
    {
        // initialize the root node
        root = new Node();
        root->data = NULL;
        root->identifier = "";
    }

    void insert(string word, Movie data)
    {
        Movie* dataptr = new Movie(data); 
        int i =0;
        // find common substring split, if found 
        // else if identifier length < word then go to next child 
        Node* prev = NULL;
        Node* temp = root;
        while (i<word.length())
        {
            int temp_i = 0;
            while (temp->identifier[temp_i] != '\0')
            {
                if (temp->identifier[temp_i] == word[i])
                {
                    temp_i++;
                    i++;
                }
                else 
                {
                    // non common letter exists at ith index on the word
                    // in this case create a new node and add two childs one to store the previous chain
                    // and one to store the new word

                    // node where common identifier exists exists
                    
                    // a new common node to insert before
                    Node* common_node = new Node();
                    common_node->identifier = temp->identifier.substr(0,temp_i);
                    //changing the identifier of prev node
                    temp->identifier = temp->identifier.substr( temp_i );

                    common_node->children[temp->identifier[0]] = temp;
                    // if the word has some non matching characters
                    if (word[i] != '\0')
                    {
                        // creating separate node to store the new data
                        Node* node2 = new Node();
                        node2->identifier = word.substr(i);
                        node2->data = dataptr;

                        // building the link between node with data and common node
                        common_node->children[word[i]] = node2;

                        // setting the parent of common node
                        prev->children[common_node->identifier[0]] = common_node;
                    }
                    // if the word only consists of matching characters
                    else
                    {
                        common_node->data = dataptr;
                    }
                    return;
                }
            }
            if (temp->children.find(word[i]) == temp->children.end())
            {
                Node* newNode = new Node();
                newNode->identifier = word.substr(i, word.length());
                newNode->data = dataptr;

                temp->children[word[i]] = newNode;
                break;
            }
            else
            {
                prev = temp;
                temp = temp->children[word[i]];
            }
        }
    }



    void search(string word)
    {
        int word_i = 0;
        Node* temp = root;
        
        // if temp is NULL then don't continue
        while(temp != NULL)
        {
            int temp_i = 0;
            // loop through every character in the current node 
            while (temp->identifier[temp_i] != '\0')
            {
                if (temp->identifier[temp_i] == word[word_i])
                {
                    temp_i++;
                    word_i++;
                }
                else
                {
                    cout<<word<<" does not exists"<<endl;
                    return;
                }       
            }

            // if the word at i'th index is last character of word then the word is found
            if (word[word_i] == '\0')
            {
                temp->data->print();
                return;
            }
            // if the word at i'th index is not the last character of word
            // then check if the node has a child at ith index
            if (temp->children.find(word[word_i]) == temp->children.end())
            {
                // if there is no node at ith index then the word does not exists
                cout<<word<<" does not exists"<<endl;          
                return;
            }
            else
                //if there is a node at ith index then search for the remaining word in the node
                temp = temp -> children[word[word_i]];
        }
    }

    // a function to print values of all nodes starting with a given string in the trie
    void printChildren(string prefix)
    {
        // temp is the node that contains the prefix
        Node* temp = root;
        int word_i =0;
       
        // find the node where prefix exists
        while(temp != NULL)
        {
            int temp_i = 0;
            
            // loop through every character in the current node 
            while (temp->identifier[temp_i] != '\0'&&prefix[word_i] != '\0')
            {
                if (temp->identifier[temp_i] == prefix[word_i])
                {
                    temp_i++;
                    word_i++;
                }
                else
                {
                    cout<<prefix<<" does not exists"<<endl;
                    return;
                }       
            }
            
            // if the word at i'th index is last character of word then the word is found
            if (prefix[word_i] == '\0')
            {
                // the node with the prefix has been found now 
                // now we have to print all children of that node
                printChildNodes(temp);
                return;
            }
            // if the word at i'th index is not the last character of word
            // then check if the node has a child at ith index
            if (temp->children.find(prefix[word_i]) == temp->children.end())
            {
                // if there is no node at ith index then the word does not exists
                cout<<prefix<<" does not exists"<<endl;          
                return;
            }
            else
                //if there is a node at ith index then search for the remaining word in the node
                temp = temp -> children[prefix[word_i]];
        }
    }

    void printChildNodes(Node* node)
    {
        // if the node is NULL return
        if (node == NULL)
        {
            cout<<"The given node is NULL"<<endl;
            return;
        }

        if (node->data != NULL)
            node->data->print();
            //    iterating over all value of umap
    
        for (auto itr : node->children)
            printChildNodes(itr.second);
    }

};
