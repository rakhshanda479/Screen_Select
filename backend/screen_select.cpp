#include<iostream>
#include <ctime>
#include <cstdlib>
#include<string>
using namespace std;
class movie 
{
    string title;
    string genre;
    string type;
    string releasedYear;
    string director;
    int rating;
public:
    movie(string t, string g, string typ, string year, string d, int rate) : title(t), genre(g), type(typ), releasedYear(year), director(d), rating(rate) {}
    movie() :rating(0)
    {    }
    string getTitle() {
        return title;
    }
    string getGenre() {
        return genre;
    }
    string getType() {
        return type;
    }
    string getReleasedYear() {
        return releasedYear;
    }
    string getDirector() {
        return director;
    }
    int getRating() {
        return rating;
    }
    void printmoviedetail()
    {
        cout << "*******Movie Details********* " << endl;
        cout << "Title: " << this->title << endl;
        cout << "Genre: " << this->genre << endl;
        cout << "Type: " << this->type << endl;
        cout << "Released Year: " << this->releasedYear << endl;
        cout << "Director: " << this->director << endl;
        cout << "Rating: " << this->rating << endl;
        cout << "*****************************"<<endl;
    }
};
class node
{
public:
    node* left;
    node* right;
    movie* data; // Add a pointer to movie data in each node
    node() : left(NULL), right(NULL), data(NULL) {}
};
class Result
{
public:
    movie** movies;
    int size;
    Result()
    {

    }
    Result(int capacity) : size(0) {
        movies = new movie * [capacity];
    }
    ~Result() {
        delete[] movies;
    }
    void addMovie(movie* m) {
        movies[size++] = m;
    }
};
class kdtree
{
public:
    node* root;
    kdtree() : root(NULL) {}
    // Recursive function to delete the entire tree
    void destroyTree(node* root) 
    {
        if (root == NULL) 
        {
            return;
        }
        // Recursively delete left and right subtrees
        destroyTree(root->left);
        destroyTree(root->right);

        // Delete the current node
        delete root;
    }
    ~kdtree() {
        // Call a recursive function to delete the entire tree
        destroyTree(root);
    }
    // Function to clear the tree and reset root to NULL
    void clear() {
        destroyTree(root);
        root = NULL;
    }
    //***************insertion**********//
    //Function to insert a movie into the KD tree(1D)
    node* insert1D(node* root, movie* data, int depth, int searchtype)
    {
        if (root == NULL)
        {
            node* newNode = new node;
            newNode->data = data;
            return newNode;
        }
        // Determine the current dimension based on depth
        int currentDim = depth % 1;
        // Compare based on the current dimension
        switch (searchtype)
        {
        case 1: // Compare based on "genre" dimension
            if (data->getGenre() < root->data->getGenre()) {
                root->left = insert1D(root->left, data, depth + 1, searchtype);
            }
            else {
                root->right = insert1D(root->right, data, depth + 1, searchtype);
            }
            break;

        case 2: // Compare based on "type" dimension
            if (data->getType() < root->data->getType()) {
                root->left = insert1D(root->left, data, depth + 1, searchtype);
            }
            else {
                root->right = insert1D(root->right, data, depth + 1, searchtype);
            }
            break;

        case 3: // Compare based on "releasedYear" dimension
            if (data->getReleasedYear() < root->data->getReleasedYear()) {
                root->left = insert1D(root->left, data, depth + 1, searchtype);
            }
            else {
                root->right = insert1D(root->right, data, depth + 1, searchtype);
            }
            break;
        default:
        // Handle unexpected searchtype
        break;    
        }
        return root;
    }
    // Function to insert a movie into the KD tree
    node* insertInKd1D(movie* data, int searchtype)
    {
        root = insert1D(root, data, 0, searchtype);
        return root;
    }
    // Function to insert a movie into the KD tree (2D)
    node* insert2D(node* root, movie* data, int depth, int searchtype)
    {
        if (root == NULL)
        {
            node* newNode = new node;
            newNode->data = data;
            return newNode;
        }
        // Alternate between dimensions (genre and type)
        int currentDim = depth % 2;
        switch (searchtype)
        {
        case 1: // Compare based on "genre" and "type" dimensions
            if (currentDim == 0)
            { // Compare based on "genre"
                if (data->getGenre() < root->data->getGenre()) {
                    root->left = insert2D(root->left, data, depth + 1, searchtype);
                }
                else {
                    root->right = insert2D(root->right, data, depth + 1, searchtype);
                }
            }
            else
            { // Compare based on "type"
                if (data->getType() < root->data->getType()) {
                    root->left = insert2D(root->left, data, depth + 1, searchtype);
                }
                else {
                    root->right = insert2D(root->right, data, depth + 1, searchtype);
                }
            }
            break;
        case 2:
            if (currentDim == 0) // Compare based on "genre" dimension
            {
                if (data->getGenre() < root->data->getGenre()) {
                    root->left = insert2D(root->left, data, depth + 1, searchtype);
                }
                else {
                    root->right = insert2D(root->right, data, depth + 1, searchtype);
                }
            }
            else // Compare based on "releasedYear" dimension
            {
                if (data->getReleasedYear() < root->data->getReleasedYear()) {
                    root->left = insert2D(root->left, data, depth + 1, searchtype);
                }
                else {
                    root->right = insert2D(root->right, data, depth + 1, searchtype);
                }
            }
            break;
        case 3:
            if (currentDim == 0)
            {
                // Compare based on the "type" dimension
                if (data->getType() < root->data->getType()) {
                    root->left = insert2D(root->left, data, depth + 1, searchtype);
                }
                else {
                    root->right = insert2D(root->right, data, depth + 1, searchtype);
                }
            }
            else
            {
                // Compare based on the "releasedYear" dimension
                if (data->getReleasedYear() < root->data->getReleasedYear()) {
                    root->left = insert2D(root->left, data, depth + 1, searchtype);
                }
                else {
                    root->right = insert2D(root->right, data, depth + 1, searchtype);
                }
            }
            break;
        default:
        // Handle unexpected searchtype
        break;    
        }
        return root;
    }
    // Function to insert a movie into the KD tree (2D)
    node* insertInKd2D(movie* data, int searchtype)
    {
        root = insert2D(root, data, 0, searchtype);
        return root;
    }
    // Function to insert a movie into the KD tree (3D)
node* insert3D(node* root, movie* data, int depth)
{
    if (root == NULL) {
        node* newNode = new node;
        newNode->data = data;
        return newNode;
    }

    // Determine the current dimension based on depth
    int currentDim = depth % 3;  // Considering three dimensions (genre, type, year)

    // Compare based on the current dimension
    if (currentDim == 0) {
        // Compare based on the "genre" dimension
        if (data->getGenre() < root->data->getGenre()) {
            root->left = insert3D(root->left, data, depth + 1);
        }
        else {
            root->right = insert3D(root->right, data, depth + 1);
        }
    }
    else if (currentDim == 1) {
        // Compare based on the "type" dimension
        if (data->getType() < root->data->getType()) {
            root->left = insert3D(root->left, data, depth + 1);
        }
        else {
            root->right = insert3D(root->right, data, depth + 1);
        }
    }
    else {
        // Compare based on the "releasedYear" dimension
        if (data->getReleasedYear() < root->data->getReleasedYear()) {
            root->left = insert3D(root->left, data, depth + 1);
        }
        else {
            root->right = insert3D(root->right, data, depth + 1);
        }
    }

    return root;
}

// Function to insert a movie into the KD tree (3D)
node* insertInKd3D(movie* data)
{
    root = insert3D(root, data, 0);
    return root;
}

    /////****************searching**************/////    
    //search by genre or type or year 
private:
    void searchin1D(node* root, const string& target,int depth, Result& result, int searchType)
    {
    	
        if (root == NULL)
        {
            return;
        }
        switch (searchType)
        {
        case 1:  // Search by genre
            if (target < root->data->getGenre()) {
                searchin1D(root->left, target, depth + 1, result, searchType);
            }
            else if (target > root->data->getGenre()) {
                searchin1D(root->right, target, depth + 1, result, searchType);
            }
            else {
                result.addMovie(root->data);
                searchin1D(root->left, target, depth + 1, result, searchType);
                searchin1D(root->right, target, depth + 1, result, searchType);
            }
            break;

        case 2:  // Search by released year
            if (target < root->data->getReleasedYear()) {
                searchin1D(root->left, target, depth + 1, result, searchType);
            }
            else if (target > root->data->getReleasedYear()) {
                searchin1D(root->right, target, depth + 1, result, searchType);
            }
            else {
                result.addMovie(root->data);
                searchin1D(root->left, target, depth + 1, result, searchType);
                searchin1D(root->right, target, depth + 1, result, searchType);
            }
            break;

        case 3:  // Search by type
            if (target < root->data->getType()) {
                searchin1D(root->left, target, depth + 1, result, searchType);
            }
            else if (target > root->data->getType()) {
                searchin1D(root->right, target, depth + 1, result, searchType);
            }
            else {
                result.addMovie(root->data);
                searchin1D(root->left, target, depth + 1, result, searchType);
                searchin1D(root->right, target, depth + 1, result, searchType);
            }
            break;
        default:
        // Handle unexpected searchtype
        break;    
        }
    }
public:
    // Function for recommending movies based on user input
    Result recommendMovies1D(int searchType, const string& userInput)
    {
        Result result(100);  // Assuming a maximum of 40 movies
        searchin1D(root, userInput, 0, result, searchType);
        return result;
    }
private:
    void searchin2D(node* root, string targetstring1, string targetstring2, int depth, Result& result, int searchType)
    {
        if (root == NULL) {
            return;
        }

        // Alternate between dimensions (genre and type)
        int currentDim = depth % 2;
        switch (searchType)
        {
            //on basis of genre and type
        case 1:
            if (currentDim == 0) { // Compare based on "genre"
                if (targetstring1 < root->data->getGenre()) {
                    searchin2D(root->left, targetstring1, targetstring2, depth + 1, result, searchType);
                }
                else if (targetstring1 > root->data->getGenre()) {
                    searchin2D(root->right, targetstring1, targetstring2, depth + 1, result, searchType);
                }
                else { // "genre" matches
                 // Check if "type" also matches
                    if (searchType == 1 && targetstring2 == root->data->getType()) {
                        result.addMovie(root->data);
                    }

                    // Continue searching in both subtrees (left and right)
                    searchin2D(root->left, targetstring1, targetstring2, depth + 1, result, searchType);
                    searchin2D(root->right, targetstring1, targetstring2, depth + 1, result, searchType);
                }
            }
            else { // Compare based on "type"
                if (targetstring2 < root->data->getType()) {
                    searchin2D(root->left, targetstring1, targetstring2, depth + 1, result, searchType);
                }
                else if (targetstring2 > root->data->getType()) {
                    searchin2D(root->right, targetstring1, targetstring2, depth + 1, result, searchType);
                }
                else { // "type" matches
                 // Check if "genre" also matches
                    if (searchType == 0 && targetstring1 == root->data->getGenre()) {
                        result.addMovie(root->data);
                    }

                    // Continue searching in both subtrees (left and right)
                    searchin2D(root->left, targetstring1, targetstring2, depth + 1, result, searchType);
                    searchin2D(root->right, targetstring1, targetstring2, depth + 1, result, searchType);
                }
            }
            break;
            //on basis of genre and year
        case 2:
            if (currentDim == 0) { // Compare based on "genre"
                if (targetstring1 < root->data->getGenre()) {
                    searchin2D(root->left, targetstring1, targetstring2, depth + 1, result, searchType);
                }
                else if (targetstring1 > root->data->getGenre()) {
                    searchin2D(root->right, targetstring1, targetstring2, depth + 1, result, searchType);
                }
                else { // "genre" matches
                 // Check if "year" also matches
                    if (targetstring2 == root->data->getReleasedYear()) {
                        result.addMovie(root->data);
                    }

                    // Continue searching in both subtrees (left and right)
                    searchin2D(root->left, targetstring1, targetstring2, depth + 1, result, searchType);
                    searchin2D(root->right, targetstring1, targetstring2, depth + 1, result, searchType);
                }
            }
            else { // Compare based on "releasedYear"
                if (targetstring2 < root->data->getReleasedYear()) {
                    searchin2D(root->left, targetstring1, targetstring2, depth + 1, result, searchType);
                }
                else if (targetstring2 > root->data->getReleasedYear()) {
                    searchin2D(root->right, targetstring1, targetstring2, depth + 1, result, searchType);
                }
                else { // "year" matches
                 // Check if "genre" also matches
                    if (targetstring1 == root->data->getGenre()) {
                        result.addMovie(root->data);
                    }

                    // Continue searching in both subtrees (left and right)
                    searchin2D(root->left, targetstring1, targetstring2, depth + 1, result, searchType);
                    searchin2D(root->right, targetstring1, targetstring2, depth + 1, result, searchType);
                }
            }
            break;
            //on the basis of year and type 
        case 3:
            if (currentDim == 0) {
                if (targetstring1 == root->data->getType()) {
                    if (targetstring2 == root->data->getReleasedYear()) {
                        result.addMovie(root->data);
                    }
                    searchin2D(root->left, targetstring1, targetstring2, depth + 1, result, searchType);
                    searchin2D(root->right, targetstring1, targetstring2, depth + 1, result, searchType);
                }
                else if (targetstring1 == root->data->getType()) {
                    searchin2D(root->left, targetstring1, targetstring2, depth + 1, result, searchType);
                }
                else {
                    searchin2D(root->right, targetstring1, targetstring2, depth + 1, result, searchType);
                }
            }
            else {
                if (targetstring2.compare(root->data->getReleasedYear()) == 0) {
                    if (targetstring1 == root->data->getType()) {
                        result.addMovie(root->data);
                    }
                    searchin2D(root->left, targetstring1, targetstring2, depth + 1, result, searchType);
                    searchin2D(root->right, targetstring1, targetstring2, depth + 1, result, searchType);
                }
                else if (targetstring1 == root->data->getReleasedYear()) {
                    searchin2D(root->left, targetstring1, targetstring2, depth + 1, result, searchType);
                }
                else {
                    searchin2D(root->right, targetstring1, targetstring2, depth + 1, result, searchType);
                }
            }
            break;
        default:
        // Handle unexpected searchtype
        break;    
        }
    }
public: 
    // Function for recommending movies based on user input
    Result recommendMovies2D(string str1, string str2, int choice)
    {
        Result result(100); // Assuming a maximum of 20 movies
       // Start the search from the root of the KD tree
        searchin2D(root, str1, str2, 0, result, choice);
        
        return result;
    }
private:
void searchin3D(node* root, string targetGenre, string targetType, string targetYear, int depth, Result& result)
{
    if (root == NULL) {
        return;
    }

    // Determine the current dimension based on depth
    int currentDim = depth % 3;  // Considering three dimensions (genre, type, year)

    // Traverse the tree based on three dimensions
    if (currentDim == 0) {
        // Check conditions based on targetGenre, targetType, and targetYear
        if ((targetGenre < root->data->getGenre()) ||
            (targetGenre == root->data->getGenre() && targetType < root->data->getType()) ||
            (targetGenre == root->data->getGenre() && targetType == root->data->getType() && targetYear < root->data->getReleasedYear())) {
            // Continue searching based on genre, type, and year conditions
            searchin3D(root->left, targetGenre, targetType, targetYear, depth + 1, result);
        }
        else {
            // Continue searching in the right subtree
            searchin3D(root->right, targetGenre, targetType, targetYear, depth + 1, result);
        }
    }
    else {
        // Continue searching in both subtrees (left and right)
        searchin3D(root->left, targetGenre, targetType, targetYear, depth + 1, result);
        searchin3D(root->right, targetGenre, targetType, targetYear, depth + 1, result);
    }
}

public:
Result recommendMoviesin3D(string userGenre, string userType, string userYear)
{
    Result result(100); // Adjust the capacity based on your needs
    // Start the search from the root of the KD tree
    searchin3D(root, userGenre, userType, userYear, 0, result);
    return result;
}

    ////maximum rating 
    void getTopRatedMovies(node* root, int depth, Result& result)
    {
        if (root == NULL) {
            return;
        }
        // Determine the current dimension based on depth
        int currentDim = depth % 4;  // Considering all dimensions (genre, type, year, rating)
        // Traverse the tree based on all dimensions
        if (currentDim == 0) {
            // Continue searching in both subtrees (left and right)
            getTopRatedMovies(root->left, depth + 1, result);
            getTopRatedMovies(root->right, depth + 1, result);
        }
        else {
            // Add the current movie to the result
            result.addMovie(root->data);
            // Continue searching in both subtrees (left and right)
            getTopRatedMovies(root->left, depth + 1, result);
            getTopRatedMovies(root->right, depth + 1, result);
        }
    }
    void printTopRatedMovies(node* root)
    {
        Result result(100); // Adjust the capacity based on your needs
        getTopRatedMovies(root, 0, result);

        cout << "*****Top 5 highest-rated movies*****" << endl;
        for (int i = 1; i <= min(result.size, 5); ++i) {
            cout << i << ". " << result.movies[i]->getTitle() << "  Rating: " << result.movies[i]->getRating()  << endl;
        }
        cout<<"***************************************"<<endl;
    }
};
int findmax4(int a, int b, int c, int d)
{
    int max = a;
    if (b > max)
    {
        max = b;
    }
    if (c > max)
    {
        max = c;
    }
    if (d > max)
    {
        max = d;
    }
    return max;
}
int findmax2(int a, int b)
{
    int max = a;
    if (b > max)
    {
        max = b;
    }
    return max;
}
int findmax6(int a, int b, int c, int d, int e, int f)
{
    int max = a;
    if (b > max)
    {
        max = b;
    }
    if (c > max)
    {
        max = c;
    }
    if (d > max)
    {
        max = d;
    }
    if (e > max)
    {
        max = e;
    }
    if (f > max)
    {
        max = f;
    }
    return max;
}
class user
{
    string name;
    string password;
    movie* history[100];
    int historySize;
    string key;
    string email;
    kdtree ob;

public:
    user() : historySize(0){}
    void setName(const string& newName) {
        name = newName;
    }
    void setKey(const string& newKey) {
        key = newKey;
    }

    string getKey() const {
        return key;
    }
    string getName() const {
        return name;
    }
    void setEmail(const string& mail) {
        email = mail;
    }
    string getEmail() const {
        return email;
    }
    void setPassword(const string& newPassword) {
        password = newPassword;
    }
    string getPassword()
    {
        return password;
    }
    void addToHistory(movie* obj) {
        if (historySize < 100) {
            history[historySize++] = obj;
        }
    }
    int getHistorySize() const {
        return historySize;
    }

    // Function to recommend movies based on the user's preferred genre from history
    Result recommendMovies(int choice) 
    {
            Result recmovies;
            switch (choice)
            {
            case 1:
            {
                string mostFrequentGenre;
                int maxcount;
                int actioncount = 0, comedycount = 0, fantasycount = 0, Thrillercount = 0;
                // Count occurrences of each genre in the user's history
                for (int i = 0; i < historySize; ++i)
                {
                    if (history[i]->getGenre() == "Action")
                    {
                        actioncount++;
                    }
                    else if (history[i]->getGenre() == "Fantasy")
                    {
                        fantasycount++;
                    }
                    else if (history[i]->getGenre() == "Comedy")
                    {
                        comedycount++;
                    }
                    else if (history[i]->getGenre() == "Thriller")
                    {
                        Thrillercount++;
                    }
                }
                maxcount = findmax4(actioncount, comedycount, fantasycount, Thrillercount);
                if (maxcount == actioncount)
                {
                    mostFrequentGenre = "Action";
                }
                else if (maxcount == comedycount)
                {
                    mostFrequentGenre = "Comedy";
                }
                else if (maxcount == fantasycount)
                {
                    mostFrequentGenre = "Fantasy";
                }
                else if (maxcount == Thrillercount)
                {
                    mostFrequentGenre = "Thriller";
                }
                recmovies = ob.recommendMovies1D(1, mostFrequentGenre);
                break;
            }
            case 2:
            {
                string mostFrequentType;
                int maxcount = 0;
                int hollywoodcount = 0, bollywoodcount = 0;
                for (int i = 0; i < historySize; ++i)
                {
                    if (history[i]->getType() == "Hollywood")
                    {
                        hollywoodcount++;
                    }
                    else
                    {
                        bollywoodcount++;
                    }
                }
                maxcount = findmax2(hollywoodcount, bollywoodcount);
                if (maxcount == hollywoodcount)
                {
                    mostFrequentType = "Hollywood";
                }
                else if (maxcount == bollywoodcount)
                {
                    mostFrequentType = "Bollywood";
                }
                recmovies = ob.recommendMovies1D(2, mostFrequentType);
                break;
            }
            case 3:
            {
                string mostFrequentYear;
                int maxcount = 0;
                int count2017 = 0, count2018 = 0, count2019 = 0, count2020 = 0, count2021 = 0, count2022 = 0;
                for (int i = 0; i < historySize; ++i)
                {
                    if (history[i]->getReleasedYear() == "2017")
                    {
                        count2017++;
                    }
                    else if (history[i]->getReleasedYear() == "2018")
                    {
                        count2018++;
                    }
                    else if (history[i]->getReleasedYear() == "2019")
                    {
                        count2019++;
                    }
                    else if (history[i]->getReleasedYear() == "2020")
                    {
                        count2020++;
                    }
                    else if (history[i]->getReleasedYear() == "2021")
                    {
                        count2021++;
                    }
                    else if (history[i]->getReleasedYear() == "2022")
                    {
                        count2022++;
                    }
                }
                maxcount = findmax6(count2017, count2018, count2019, count2020, count2021, count2022);
                if (maxcount == count2017)
                {
                    mostFrequentYear = "2017";
                }
                else if (maxcount == count2018)
                {
                    mostFrequentYear = "2018";
                }
                else if (maxcount == count2019)
                {
                    mostFrequentYear = "2019";
                }
                else if (maxcount == count2020)
                {
                    mostFrequentYear = "2020";
                }
                else if (maxcount == count2021)
                {
                    mostFrequentYear = "2021";
                }
                else if (maxcount == count2022)
                {
                    mostFrequentYear = "2022";
                }
                recmovies = ob.recommendMovies1D(3, mostFrequentYear);
                break;
            }
            }
            return recmovies;
    }
};
bool login(user& obj)
{
    bool loginOrNot = 0;
        string name;
        string password;
        bool flag = 0;
        while (flag != 1)
        {
            system("cls");
            cout << endl << "**************login page*******************" << endl;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter password: ";
            cin >> password;
            if (name == obj.getName())
            {
                if (password == obj.getPassword())
                {
                    cout << "****login successfully*****" << endl;
                    flag = 1;
                    loginOrNot = 1;
                }
                else
                {
                    cout << "!!!Wrong Password!!!" << endl;
                    int c;
                    cout << "1. Login again" << endl << "2. Forgot my password and want to change " << endl << "3. Exit" << endl;
                    cin >> c;
                    if (c == 1)
                    {
                        cout << "Please try to Login again with your correct password" << endl;
                    }
                    else
                    {
                        if (c == 2)
                        {
                            string key;
                            cout << "Enter the key that we assign you at the time of registeration: " << endl;
                            cin >> key;
                            if (key == obj.getKey())
                            {
                                cout << "Enter new password: ";
                                cin >> password;
                                obj.setPassword(password);
                                cout << "your password has been changed" << endl;
                                cout << "Now please try login with your correct password" << endl;
                            }
                            else
                            {
                                cout << "!!!Wrong key!!!" << endl;
                                cout << "You can't login without the key kindly try to find the key in your gmail" << endl;
                                cout << "Note: We want to provide a secured and saved system to the user and it is our security" << endl;
                                cout << "concern that the user who forgot his password can only access his account by using " << endl;
                                cout << "key so for the recovery of account try to contact us through the provided contact details" << endl;
                                cout << "RMRmovierecommendation@gmail.com" << endl;
                                flag = 1;
                            }
                        }
                        else
                        {
                            flag = 1;
                        }
                    }
                }
            }
            else
            {
                cout << "!!!Wrong name!!!" << endl;
                int c;
                cout << "1. Login again" << endl << "2. Forgot my name and want to change" << endl << "3. Exit" << endl;
                cin >> c;
                if (c == 1)
                {
                    cout << "Please try to Login again with your correct name" << endl;
                }
                else
                {
                    if (c == 2)
                    {
                        cout << "Enter your name you want to set: " << endl;
                        cin >> name;
                        obj.setName(name);
                        cout << "Name saved succesfully now please login again with your correct name";
                    }
                    else
                    {
                        flag = 1;
                    }
                }
            }
        }
        return loginOrNot;
 }
string generateKey(int length)
{
        string key;
        for (int i = 0; i < length; ++i)
        {
            // Generate a random ASCII value within the range [40, 126]
            char randomChar = 40 + rand() % 94;
            key += randomChar;
        }
        return key;
}
void Register(user& obj)
{
        system("cls");
        cout << "***************Registration***************" << endl;
        string name;
        string password;
        string key;
        string email;
        cout << "Enter Name: ";
        cin >> name;
        obj.setName(name);
        cout << "Enter Password: ";
        cin >> password;
        obj.setPassword(password);
        cout << "Enter Email: ";
        cin >> email;
        obj.setEmail(email);
        key = generateKey(5); //key will be of fixed length (5)
        obj.setKey(key);
        cout << "Providing you a key which you have saved somewhere in case you will forget your" << endl;
        cout << "password this will be the only option to reset your password.Also we will also send you this key by email" << endl;
        cout << "Key: " << obj.getKey();
        cout << endl << "************Registered successfully************" << endl;
}
void givefeedback()
{
        int feedback;
        cout << "********Feedback**********" << endl;
        cout << "Your feedback will be taken into consideration and your respone will highly appreciated" << endl;
        cout << "Select from the following options: " << endl;
        cout << "1. Efficiency of Movie recommendation system is Excellent" << endl;
        cout << "2. Efficiency of Movie recommendation system is Good" << endl;
        cout << "3. Efficiency of Movie recommendation system is Average" << endl;
        cout << "4. Efficiency of Movie recommendation system is Worst" << endl;
        cin >> feedback;
        if(feedback>=1&&feedback<=4)
        {
        	cout << "Thank you" << endl;
		}
		else
		{
			cout<<"!!!!Wrong input!!!"<<endl;
		}
}
node* insertobjects(int dimension, int a, kdtree& tree)
{
        movie* obj1=new movie("Avengers infinity war", "Action", "Hollywood", "2018", "Anthny Russo", 9);
        movie* obj2=new movie("Wonder Woman", "Action", "Hollywood", "2017", "Patty Jenkins", 8);
        movie* obj3=new movie("Captain Marvel", "Action", "Hollywood", "2019", "Ryan Fleck", 7);
        movie* obj4=new movie("Dead pool", "Action", "Hollywood", "2018", "David Leitch", 8);
        movie* obj5=new movie("Venom", "Action", "Hollywood", "2018", "Ruben Fleischer", 9);
        movie* obj6=new movie("Bahubali", "Action", "Bollywood", "2017", "S.S Rajamouli", 10);
        movie* obj7=new movie("The Ghazi Attack", "Action", "Bollywood", "2017", "Francis Ford Coppola", 10);
        movie* obj8=new movie("Point man", "Action", "Bollywood", "2018", "Amar Kaushik", 8);
        movie* obj9=new movie("The Surgical Strike", "Action", "Bollywood", "2019", "Aditya Dhar", 10);
        movie* obj10=new movie("Hotel mumbai", "Action", "Bollywood", "2020", "David Prior", 8);
        movie* obj11=new movie("Jumanji Welcome to the jungle", "Comedy", "Hollywood", "2017", "Jake Kasdan", 8);
        movie* obj12=new movie("Coco", "Comedy", "Hollywood", "1942", "Michael Curtiz", 9);
        movie* obj13=new movie("Jojo Rabbit", "Comedy", "Hollywood", "2019", "Taika Waititi", 7);
        movie* obj14=new movie("Dont Look up", "Comedy", "Hollywood", "2021", "Adam McKay", 9);
        movie* obj15=new movie("Frozen", "Comedy", "Hollywood", "2019", "Chris Buck", 8);
        movie* obj16=new movie("102 not out", "Comedy", "Bollywood", "2018", "Umesh Shukla", 10);
        movie* obj17=new movie("Joly LLB 2", "Comedy", "Bollywood", "2017", "subhash kapoor", 10);
        movie* obj18=new movie("Bhediya", "Comedy", "Bollywood", "2022", "Steven Spielberg", 6);
        movie* obj19=new movie("Jug jug jiyo", "Comedy", "Bollywood", "2022", "Raj mehta", 8);
        movie* obj20=new movie("Simba", "Comedy", "Bollywood", "2018", "Victor Fleming", 4);
        movie* obj21=new movie("split", "Thriller", "Hollywood", "2017", "John Rusk", 5);
        movie* obj22=new movie("Joker", "Thriller", "Hollywood", "2019", "Carolina Jimenez", 9);
        movie* obj23=new movie("Parasite", "Thriller", "Hollywood", "2019", "Boon joon-ho", 7);
        movie* obj24=new movie("Bird Box", "Thriller", "Hollywood", "2018", "Susane bier", 5);
        movie* obj25=new movie("Tenet", "Thriller", "Hollywood", "2020", "Christopher Nolan", 6);
        movie* obj26=new movie("Jawan", "Thriller", "Bollywood", "2022", "Atle", 4);
        movie* obj27=new movie("Knives out", "Thriller", "Bollywood", "2019", "Rian jhonson", 7);
        movie* obj28=new movie("Arya", "Thriller", "Bollywood", "2020", "Ram madhvani", 5);
        movie* obj29=new movie("Ek tha tiger", "Thriller", "Bollywood", "2019", "kabir khan", 6);
        movie* obj30=new movie("Sultan", "Thriller", "Bollywood", "2018", "Ali Abbas zafar", 8);
        movie* obj31=new movie("Rebel Moon", "Fantasy", "Hollywood", "2022", "Zack Synder", 9);
        movie* obj32=new movie("Barbie", "Fantasy", "Hollywood", "2021", "Greta Gerwig", 9);
        movie* obj33=new movie("Downsizing", "Fantasy", "Hollywood", "2017", "Alexander Payne", 7);
        movie* obj34=new movie("The little mermaid", "Fantasy", "Hollywood", "2018", "Rob Marshall", 10);
        movie* obj35=new movie("The grinch", "Fantasy", "Bollywood", "2018", "Yarrow Cheney", 6);
        movie* obj36=new movie("Eternals", "Fantasy", "Bollywood", "2021", "Chloe Zhao", 7);
        movie* obj37=new movie("the last voyage", "Fantasy", "Hollywood", "2022", "Andre Ovredal", 8);
        movie* obj38=new movie("inside out", "Fantansy", "Bollywood", "2017", "pete docter", 7);
        movie* obj39=new movie("finding nemo", "Fantasy", "Bollywood", "2019", "Andrew Stanton", 8);
        movie* obj40=new movie("Ratatouille", "Fantasy", "Hollywood", "2018", "Brad Bied", 5);
        node* root;
        if (dimension == 1)
        {
        	tree.clear();
            root = tree.insertInKd1D(obj1, a);
            root = tree.insertInKd1D(obj2, a);
            root = tree.insertInKd1D(obj3, a);
            root = tree.insertInKd1D(obj4, a);
            root = tree.insertInKd1D(obj5, a);
            root = tree.insertInKd1D(obj6, a);
            root = tree.insertInKd1D(obj7, a);
            root = tree.insertInKd1D(obj8, a);
            root = tree.insertInKd1D(obj9, a);
            root = tree.insertInKd1D(obj10, a);
            root = tree.insertInKd1D(obj11, a);
            root = tree.insertInKd1D(obj12, a);
            root = tree.insertInKd1D(obj13, a);
            root = tree.insertInKd1D(obj14, a);
            root = tree.insertInKd1D(obj15, a);
            root = tree.insertInKd1D(obj16, a);
            root = tree.insertInKd1D(obj17, a);
            root = tree.insertInKd1D(obj18, a);
            root = tree.insertInKd1D(obj19, a);
            root = tree.insertInKd1D(obj20, a);
            root = tree.insertInKd1D(obj21, a);
            root = tree.insertInKd1D(obj22, a);
            root = tree.insertInKd1D(obj23, a);
            root = tree.insertInKd1D(obj24, a);
            root = tree.insertInKd1D(obj25, a);
            root = tree.insertInKd1D(obj26, a);
            root = tree.insertInKd1D(obj27, a);
            root = tree.insertInKd1D(obj28, a);
            root = tree.insertInKd1D(obj29, a);
            root = tree.insertInKd1D(obj30, a);
            root = tree.insertInKd1D(obj31, a);
            root = tree.insertInKd1D(obj32, a);
            root = tree.insertInKd1D(obj33, a);
            root = tree.insertInKd1D(obj34, a);
            root = tree.insertInKd1D(obj35, a);
            root = tree.insertInKd1D(obj36, a);
            root = tree.insertInKd1D(obj37, a);
            root = tree.insertInKd1D(obj38, a);
            root = tree.insertInKd1D(obj39, a);
            root = tree.insertInKd1D(obj40, a);
            return root;
        }
        else if (dimension == 2)
        {
        	tree.clear();
            root = tree.insertInKd2D(obj1, a);
            root = tree.insertInKd2D(obj2, a);
            root = tree.insertInKd2D(obj3, a);
            root = tree.insertInKd2D(obj4, a);
            root = tree.insertInKd2D(obj5, a);
            root = tree.insertInKd2D(obj6, a);
            root = tree.insertInKd2D(obj7, a);
            root = tree.insertInKd2D(obj8, a);
            root = tree.insertInKd2D(obj9, a);
            root = tree.insertInKd2D(obj10, a);
            root = tree.insertInKd2D(obj11, a);
            root = tree.insertInKd2D(obj12, a);
            root = tree.insertInKd2D(obj13, a);
            root = tree.insertInKd2D(obj14, a);
            root = tree.insertInKd2D(obj15, a);
            root = tree.insertInKd2D(obj16, a);
            root = tree.insertInKd2D(obj17, a);
            root = tree.insertInKd2D(obj18, a);
            root = tree.insertInKd2D(obj19, a);
            root = tree.insertInKd2D(obj20, a);
            root = tree.insertInKd2D(obj21, a);
            root = tree.insertInKd2D(obj22, a);
            root = tree.insertInKd2D(obj23, a);
            root = tree.insertInKd2D(obj24, a);
            root = tree.insertInKd2D(obj25, a);
            root = tree.insertInKd2D(obj26, a);
            root = tree.insertInKd2D(obj27, a);
            root = tree.insertInKd2D(obj28, a);
            root = tree.insertInKd2D(obj29, a);
            root = tree.insertInKd2D(obj30, a);
            root = tree.insertInKd2D(obj31, a);
            root = tree.insertInKd2D(obj32, a);
            root = tree.insertInKd2D(obj33, a);
            root = tree.insertInKd2D(obj34, a);
            root = tree.insertInKd2D(obj35, a);
            root = tree.insertInKd2D(obj36, a);
            root = tree.insertInKd2D(obj37, a);
            root = tree.insertInKd2D(obj38, a);
            root = tree.insertInKd2D(obj39, a);
            root = tree.insertInKd2D(obj40, a);
            return root;
        }
        else if (dimension == 4)
        {
        	tree.clear();
            root = tree.insertInKd3D(obj1);
root = tree.insertInKd3D(obj2);
root = tree.insertInKd3D(obj3);
root = tree.insertInKd3D(obj4);
root = tree.insertInKd3D(obj5);
root = tree.insertInKd3D(obj6);
root = tree.insertInKd3D(obj7);
root = tree.insertInKd3D(obj8);
root = tree.insertInKd3D(obj9);
root = tree.insertInKd3D(obj10);
root = tree.insertInKd3D(obj11);
root = tree.insertInKd3D(obj12);
root = tree.insertInKd3D(obj13);
root = tree.insertInKd3D(obj14);
root = tree.insertInKd3D(obj15);
root = tree.insertInKd3D(obj16);
root = tree.insertInKd3D(obj17);
root = tree.insertInKd3D(obj18);
root = tree.insertInKd3D(obj19);
root = tree.insertInKd3D(obj20);
root = tree.insertInKd3D(obj21);
root = tree.insertInKd3D(obj22);
root = tree.insertInKd3D(obj23);
root = tree.insertInKd3D(obj24);
root = tree.insertInKd3D(obj25);
root = tree.insertInKd3D(obj26);
root = tree.insertInKd3D(obj27);
root = tree.insertInKd3D(obj28);
root = tree.insertInKd3D(obj29);
root = tree.insertInKd3D(obj30);
root = tree.insertInKd3D(obj31);
root = tree.insertInKd3D(obj32);
root = tree.insertInKd3D(obj33);
root = tree.insertInKd3D(obj34);
root = tree.insertInKd3D(obj35);
root = tree.insertInKd3D(obj36);
root = tree.insertInKd3D(obj37);
root = tree.insertInKd3D(obj38);
root = tree.insertInKd3D(obj39);
root = tree.insertInKd3D(obj40);
return root;
        }
}
int main()
{
        system("color B5");
        cout << "________________________________________________________________________________________________" << endl;
        cout << "------------------------------------------------------------------------------------------------" << endl;
        cout << "**********************======MOVIE RECOMMENDATION SYSTEM PROJECT======************************" << endl;
        cout << "________________________________________________________________________________________________" << endl;
        cout << "------------------------------------------------------------------------------------------------" << endl;
        cout << "   ******PROJECT MADE BY RAMIN(22K-4654), MUNIBA(22K-4338) AND RAKHSHANDA(22K-4461)******   " << endl;
        cout << "________________________________________________________________________________________________" << endl;
        cout << "------------------------------------------------------------------------------------------------" << endl;
        cout << "     ******Welcome to our movie recommendation system powered by KD-trees!******    " << endl;
        cout << "________________________________________________________________________________________________" << endl;
        cout << "------------------------------------------------------------------------------------------------" << endl;
        cout << "      ***Discover personalized movie suggestions based on your preferences ";
        cout << "and enjoy a tailored cinematic experience***" << endl;
        cout << "******************************================ACCOUNT===============*******************************" << endl;
        cout << "1.LOGIN" << endl;
        cout << "2.REGISTER" << endl;
        cout << "3.Exit" << endl;
        cout << "Enter your choice" << endl;
        int choice1 = 0;
        cin >> choice1;
        cout << endl;
        user obj;
        kdtree tree;
        tree.root = NULL;
        for (int i = 0; choice1 != 3; i++)
        {
            switch (choice1)
            {
            case(2):
            {
                Register(obj);
                break;
            }
            case(1):
            {
                int flag = 0;
                flag = login(obj);
                if (flag == 1)
                {
                    system("cls");
                    cout << "************WELCOME BACK**************" << endl;
                    cout << "Choose from the following options" << endl;
                    int choice2 = 0;
                    cout << "1. Get movie Recommendation" << endl << "2. Give feedback" << endl << "3.Exit" << endl;
                    cin >> choice2;
                    for (int j = 0; choice2 != 3; j++)
                    {
                        if (choice2 == 1)
                        {
                            system("cls");
                            cout << "Choose from the following options" << endl;
                            cout << "1. Recommendation on basis of movie attributes" << endl << "2. Recommendation on basis of your history" << endl << "3. Exit" << endl;
                            int choice3 = 0;
                            cin >> choice3;
                            for (int k = 0; choice3 != 3; k++)
                            {
                                if (choice3 == 1)
                                {
                                    system("cls");
                                    cout << "Choose from the following options" << endl;
                                    cout << "1. Get Top rated movies" << endl;
                                    cout << "2. Recommendation on basis of only one attributs" << endl;
                                    cout << "3. Recommendation on basis of two attributs" << endl;
                                    cout << "4. Recommendation on basis of three attributs" << endl;
                                    cout << "5. Exit" << endl;
                                    int choice4 = 0;
                                    cin >> choice4;
                                    for (int l = 0; choice4 != 5; l++)
                                    {
                                        if (choice4 == 1)
                                        {
                                            system("cls");
                                            tree.root = insertobjects(4, 0, tree);
                                            tree.printTopRatedMovies(tree.root);
                                        }
                                        else if (choice4 == 2)
                                        {
                                            system("cls");
                                            cout << "Choose from the following options" << endl;
                                            cout << "1. Get Recommendation on the basis of Genre" << endl;
                                            cout << "2. Get Recommendation on the basis of Type" << endl;
                                            cout << "3. Get Recommendation on the basis of Released Year" << endl;
                                            cout << "4. Exit" << endl;
                                            int choice5 = 0;
                                            cin >> choice5;
                                            for (int m = 0; choice5 != 4; m++)
                                            {
                                                if (choice5 == 1)
                                                {
                                                    cout << "Enter Genre(Action,Fantasy,Thriller,Comedy): ";
                                                    string inputG;
                                                    cin >> inputG;
                                                    tree.root = insertobjects(1, 1, tree);
                                                    Result recommendedMovies = tree.recommendMovies1D(1, inputG);
                                                    if(recommendedMovies.size==0)
                                                    {
                                                    	cout<<"Sorry no such movies in our data"<<endl;
													}
													else{
                                                    cout << "Recommended movies with genre " << inputG << ":" << endl;
                                                    movie* currentMovie=new movie();
                                                    for (int o = 0; o < recommendedMovies.size; ++o)
                                                    {
                                                        currentMovie = recommendedMovies.movies[o];
                                                        cout << currentMovie->getTitle();
                                                        cout << "  [Do you want it's further info(yes or no)]: ";
                                                        string answer;
                                                        cin >> answer;
                                                        if (answer == "yes")
                                                        {
                                                            currentMovie->printmoviedetail();
                                                            obj.addToHistory(currentMovie);
                                                        }
                                                    }
                                                    cout<<"****Recommendation Eneded****"<<endl;
                                                    }
                                                }
                                                if (choice5 == 2)
                                                {
                                                    cout << "Enter Type(Hollywood,Bollywood): ";
                                                    string inputT;
                                                    cin >> inputT;
                                                    tree.root = insertobjects(1, 2, tree);
                                                    Result recommendedMovies = tree.recommendMovies1D(2, inputT);
                                                    if(recommendedMovies.size==0)
                                                    {
                                                    	cout<<"Sorry no such movies in our data"<<endl;
													}
													else{
                                                    cout << "Recommended movies with Type " << inputT << ":" << endl;
                                                    movie* currentMovie=new movie();
                                                    for (int n = 0; n < recommendedMovies.size; ++n)
                                                    {
                                                        currentMovie = recommendedMovies.movies[n];
                                                        cout << currentMovie->getTitle();
                                                        cout << "  [Do you want it's further info(yes or no)]: ";
                                                        string answer;
                                                        cin >> answer;
                                                        if (answer == "yes")
                                                        {
                                                            currentMovie->printmoviedetail();
                                                            obj.addToHistory(currentMovie);
                                                        }
                                                    }
                                                    cout<<"****Recommendation Eneded****"<<endl;
                                                    }
                                                }
                                                if (choice5 == 3)
                                                {
                                                    cout << "Enter Released year(2017,2018,2019,2020,2021,2022): ";
                                                    string inputY;
                                                    cin >> inputY;
                                                    tree.root = insertobjects(1, 3, tree);
                                                    Result recommendedMovies = tree.recommendMovies1D(3, inputY);
                                                    if(recommendedMovies.size==0)
                                                    {
                                                    	cout<<"Sorry no such movies in our data"<<endl;
													}
													else{
                                                    cout << "Recommended movies with year " << inputY << ":" << endl;
                                                    movie* currentMovie=new movie();
                                                    for (int p = 0; p < recommendedMovies.size; ++p)
                                                    {
                                                        currentMovie = recommendedMovies.movies[p];
                                                        cout << currentMovie->getTitle();
                                                        cout << "  [Do you want it's further info(yes or no)]: ";
                                                        string answer;
                                                        cin >> answer;
                                                        if (answer == "yes")
                                                        {
                                                            currentMovie->printmoviedetail();
                                                            obj.addToHistory(currentMovie);
                                                        }
                                                    }
                                                    cout<<"****Recommendation Eneded****"<<endl;
                                                    }
                                                }
                                                cout << "Choose from the following options" << endl;
                                                cout << "1. Get Recommendation on the basis of Genre" << endl;
                                                cout << "2. Get Recommendation on the basis of Type" << endl;
                                                cout << "3. Get Recommendation on the basis of Released Year" << endl;
                                                cout << "4. Exit" << endl;
                                                cin >> choice5;
                                            }

                                        }
                                        else if (choice4 == 3)
                                        {
                                            system("cls");
                                            cout << "Choose from the following options" << endl;
                                            cout << "1. Get Recommendation on the basis of Genre and Tyoe" << endl;
                                            cout << "2. Get Recommendation on the basis of Genre and Year" << endl;
                                            cout << "3. Get Recommendation on the basis of Year and type" << endl;
                                            cout << "4. Exit" << endl;
                                            int choice6 = 0;
                                            cin >> choice6;
                                            for (int i = 0; choice6 != 4; i++)
                                            {
                                                if (choice6 == 1)
                                                {
                                                    system("cls");
                                                    cout << "Enter Genre(Action,Fantasy,Thriller,Comedy): ";
                                                    string inputG, inputT;
                                                    cin >> inputG;
                                                    cout << "Enter Type(Hollywood,Bollywood): ";
                                                    cin >> inputT;
                                                    tree.root = insertobjects(2, 1, tree);
                                                    Result recommendedMovies = tree.recommendMovies2D(inputG, inputT, choice6);
                                                    if(recommendedMovies.size==0)
                                                    {
                                                    	cout<<"Sorry no such movies in our data"<<endl;
													}
													else{
                                                    cout << "Recommended movies with genre " << inputG << " and type " << inputT << " : " << endl;
                                                    movie* currentMovie=new movie();
                                                    for (int q = 0; q < recommendedMovies.size; ++q)
                                                    {
                                                       currentMovie = recommendedMovies.movies[q];
                                                        cout << currentMovie->getTitle();
                                                        cout << "[Do you want it's further info(yes or no)]: ";
                                                        string answer;
                                                        cin >> answer;
                                                        if (answer == "yes")
                                                        {
                                                            currentMovie->printmoviedetail();
                                                            obj.addToHistory(currentMovie);
                                                        }
                                                    }
                                                    cout<<"****Recommendation Eneded****"<<endl;
                                                    }
                                                }
                                                else if (choice6 == 2)
                                                {
                                                    tree.clear();
                                                    system("cls");
                                                    cout << "Enter Genre(Action,Fantasy,Thriller,Comedy): ";
                                                    string inputG, inputY;
                                                    cin >> inputG;
                                                    cout << "Enter Released year(2017,2018,2019,2020,2021,2022): ";
                                                    cin >> inputY;
                                                    tree.root = insertobjects(2, choice6, tree);
                                                    Result recommendedMovies = tree.recommendMovies2D(inputG, inputY, choice6);
                                                    if(recommendedMovies.size==0)
                                                    {
                                                    	cout<<"Sorry no such movies in our data"<<endl;
													}
													else{
                                                    cout << "Recommended movies with genre " << inputG << " and Year " << inputY << " : " << endl;
                                                    movie* currentMovie=new movie();
                                                    for (int r = 0; r < recommendedMovies.size; ++r)
                                                    {
                                                        currentMovie = recommendedMovies.movies[r];
                                                        cout << currentMovie->getTitle();
                                                        cout << "  [Do you want it's further info(yes or no)]: ";
                                                        string answer;
                                                        cin >> answer;
                                                        if (answer == "yes")
                                                        {
                                                            currentMovie->printmoviedetail();
                                                            obj.addToHistory(currentMovie);
                                                        }
                                                    }
                                                    cout<<"****Recommendation Eneded****"<<endl;
                                                    }
                                                }
                                                else if (choice6 == 3)
                                                {
                                                    system("cls");
                                                    cout << "Enter Type(Hollywood, Bollywood) : ";
                                                    string inputT, inputY;
                                                    cin >> inputT;
                                                    cout << "Enter Released year(2017,2018,2019,2020,2021,2022): ";
                                                    cin >> inputY;
                                                    tree.root = insertobjects(2, 3, tree);
                                                    Result recommendedMovies = tree.recommendMovies2D(inputT, inputY, choice6);
                                                    if(recommendedMovies.size==0)
                                                    {
                                                    	cout<<"Sorry no such movies in our data"<<endl;
													}
													else{
                                                    cout << "Recommended movies with genre " << inputT << "and Year " << inputY << " : " << endl;
                                                    movie* currentMovie=new movie();
                                                    for (int s = 0; s < recommendedMovies.size; ++s)
                                                    {
                                                        currentMovie = recommendedMovies.movies[s];
                                                        cout << currentMovie->getTitle();
                                                        cout << "  [Do you want it's further info(yes or no)]: ";
                                                        string answer;
                                                        cin >> answer;
                                                        if (answer == "yes")
                                                        {
                                                            currentMovie->printmoviedetail();
                                                            obj.addToHistory(currentMovie);
                                                        }
                                                    }
                                                    cout<<"****Recommendation Eneded****"<<endl;
                                                    }
                                                }
                                                cout << "Choose from the following options" << endl;
                                                cout << "1. Get Recommendation on the basis of Genre and Tyoe" << endl;
                                                cout << "2. Get Recommendation on the basis of Genre and Year" << endl;
                                                cout << "3. Get Recommendation on the basis of Year and type" << endl;
                                                cout << "4. Exit" << endl;
                                                cin >> choice6;
                                            }
                                        }
                                        else if (choice4 == 4)
                                        {
                                            system("cls");
                                            string inputG, inputT, inputY;
                                            cout << "Enter Genre(Action,Fantasy,Thriller,Comedy): ";
                                            cin >> inputG;
                                            cout << "Enter Type(Hollywood, Bollywood) : ";
                                            cin >> inputT;
                                            cout << "Enter Released year(2017,2018,2019,2020,2021,2022): ";
                                            cin >> inputY;
                                            tree.root = insertobjects(4, 0, tree);
                                            Result recommendedMovies = tree.recommendMoviesin3D(inputG, inputT, inputY);
                                            if(recommendedMovies.size==0)
                                            {
                                               	cout<<"Sorry no such movies in our data"<<endl;
											}
											else{
											cout<< "Recommended movies with genre " << inputT << " Year " << inputY << " Type " << inputT << " ; " << endl;
                                            movie* currentMovie;
                                            for (int t = 0; t < recommendedMovies.size; ++t)
                                            {
                                               currentMovie = recommendedMovies.movies[t];
                                                cout << currentMovie->getTitle();
                                                cout << "  [Do you want it's further info(yes or no)]: ";
                                                string answer;
                                                cin >> answer;
                                                if (answer == "yes")
                                                {
                                                    currentMovie->printmoviedetail();
                                                    obj.addToHistory(currentMovie);
                                                }
                                            }
                                            cout<<"****Recommendation Eneded****"<<endl;
                                            }
                                        }
                                        cout << "Choose from the following options" << endl;
                                        cout << "1. Get Top rated movies" << endl;
                                        cout << "2. Recommendation on basis of only one attributs" << endl;
                                        cout << "3. Recommendation on basis of two attributs" << endl;
                                        cout << "4. Recommendation on basis of three attributs" << endl;
                                        cout << "5. Exit" << endl;
                                        cin >> choice4;
                                    }
                                }
                                else if (choice3 == 2)
                                {
                                    int size = obj.getHistorySize();
                                    if (size == 0)
                                    {
                                        cout << "Your system history is empty you can't take recommendation on basis of history" << endl;
                                    }
                                    else
                                    {
                                    	tree.clear();
                                        cout << "Select recommendation type:\n";
                                        cout << "1. Genre\n";
                                        cout << "2. Type\n";
                                        cout << "3. Year\n";
                                        cout << "4. Exit\n";
                                        cout << "Enter your choice: ";
                                        int choice = 0;
                                        cin >> choice;
                                        for (int u = 0; choice != 4; u++)
                                        {
                                            if(choice==1)
                                            {
                                            	tree.root = insertobjects(1, 1, tree);
											}
											else if(choice==2)
											{
                                                tree.root = insertobjects(1, 2, tree);												
											}
											else if(choice==3)
											{
                                                tree.root = insertobjects(1, 3, tree);												
											}
											else
											{
												cout<<"Invalid choice"<<endl;
											}
                                            Result recmovies = obj.recommendMovies(choice);
                                            cout << "Recommended movies based on your history: " << endl;
                                            movie* currentMovie=new movie();
                                            for (int v = 0; v < recmovies.size; ++v)
                                            {
                                                currentMovie = recmovies.movies[v];
                                                cout << currentMovie->getTitle();
                                                cout << "  [Do you want it's further info(yes or no)]: ";
                                                string answer;
                                                cin >> answer;
                                                if (answer == "yes")
                                                {
                                                    currentMovie->printmoviedetail();
                                                    obj.addToHistory(currentMovie);
                                                }
                                            }
                                            cout<<"****Recommendation Ended****"<<endl;
                                            cout << "Select recommendation type:\n";
                                            cout << "1. Genre\n";
                                            cout << "2. Type\n";
                                            cout << "3. Year\n";
                                            cout << "4. Exit\n";
                                            cout << "Enter your choice: ";
                                            cin >> choice;
                                        }
                                    }
                                }
                                cout << "Choose from the following options" << endl;
                                cout << "1. Recommendation on basis of movie attributes" << endl << "2. Recommendation on basis of your history" << endl << "3. Exit" << endl;
                                cin >> choice3;
                            }
                        }
                        else if (choice2 == 2)
                        {
                            system("cls");
                            givefeedback();
                        }
                        else 
                        {
                        	cout<<"Invalid choice"<<endl;
						}
                        cout << "Choose from the following options" << endl;
                        cout << "1. Get movie Recommendation" << endl << "2. Give feedback" << endl << "3.Exit" << endl;
                        cin >> choice2;
                    }
                }
				break;  
            }
            default:
            cout<<"Invalid choice"<<endl;
            break;
        }
        cout << "1.LOGIN" << endl;
        cout << "2.REGISTER" << endl;
        cout << "3.Exit" << endl;
        cout << "Enter your choice" << endl;
        cin >> choice1;
        }
        cout << "**************THANK YOU HOPE YOU WILL COME BACK*********************" << endl;
}