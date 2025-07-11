#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

const int MAX_MOVIES = 5;

struct Movie {
    int id;
    string name;
    int availableSeats;
};

Movie movies[MAX_MOVIES];

void loadMovies() {
    ifstream fin("movies.txt");
    for (int i = 0; i < MAX_MOVIES && fin >> movies[i].id; i++) {
        fin.ignore();
        getline(fin, movies[i].name);
        fin >> movies[i].availableSeats;
    }
    fin.close();
}

void saveMovies() {
    ofstream fout("movies.txt");
    for (int i = 0; i < MAX_MOVIES; i++) {
        fout << movies[i].id << endl;
        fout << movies[i].name << endl;
        fout << movies[i].availableSeats << endl;
    }
    fout.close();
}

void displayMovies() {
    cout << "\nAvailable Movies:\n";
    for (int i = 0; i < MAX_MOVIES; i++) {
        cout << movies[i].id << ". " << movies[i].name 
             << " (" << movies[i].availableSeats << " seats available)\n";
    }
}

void bookTicket() {
    string customerName;
    int movieChoice, seatCount;

    cout << "\nEnter your name: ";
    cin.ignore();
    getline(cin, customerName);

    displayMovies();
    cout << "\nChoose movie ID to book: ";
    cin >> movieChoice;

    if (movieChoice < 1 || movieChoice > MAX_MOVIES) {
        cout << "Invalid choice.\n";
        return;
    }

    cout << "Enter number of tickets: ";
    cin >> seatCount;

    if (seatCount <= 0 || seatCount > movies[movieChoice - 1].availableSeats) {
        cout << "Invalid seat count.\n";
        return;
    }

    movies[movieChoice - 1].availableSeats -= seatCount;
    saveMovies();

    ofstream fout("bookings.txt", ios::app);
    fout << customerName << "," << movies[movieChoice - 1].name 
         << "," << seatCount << "\n";
    fout.close();

    cout << "\n🎫 Ticket booked successfully!\n";
    cout << "Name: " << customerName << "\nMovie: " 
         << movies[movieChoice - 1].name << "\nSeats: " << seatCount << "\n";
}

void viewBookings() {
    ifstream fin("bookings.txt");
    string line;
    cout << "\n📋 Bookings List:\n";
    while (getline(fin, line)) {
        cout << line << endl;
    }
    fin.close();
}

int main() {
    loadMovies();
    int choice;

    do {
        system("cls"); // clears console
        cout << "🎬 Movie Ticket Booking System 🎟️\n";
        cout << "1. Show Movies\n";
        cout << "2. Book Ticket\n";
        cout << "3. View Bookings\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayMovies();
            break;
        case 2:
            bookTicket();
            break;
        case 3:
            viewBookings();
            break;
        case 4:
            cout << "Thank you for using the system!\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

        if (choice != 4) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 4);

    return 0;
}